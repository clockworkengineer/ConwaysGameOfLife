/*
 * File:   gameoflife.cpp
 * 
 * Author: Robert Tizzard
 * 
 * Created on 25 November 2018, 10:55
 *
 * Copyright 2018.
 *
 */

//
// Program: Conways Game Of Life.
//
// Description: Ncurses implementation of Conway's game of life a cellular automaton
// details of which are found at https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life.
//
// Dependencies:
//
// C11++              : Use of C11++ features.
// ncurses            : Text terminal display
//

// =============
// INCLUDE FILES
// =============

//
// C++ STL
//

#include <thread>
#include <chrono>
#include <cstring>

//
// ncurses
//

#include <ncurses.h>

//
// Life Cell Grid Class
//

#include "CCursesLife.hpp"

//
// Title and footer strings.
//

constexpr const char *kHeaderString{ "Conway's Game Of Life (%dx%d)"};
constexpr const char *kCommandString{"1(Start) 2(Stop) 3(Reset) 4(Quit)"};

//
// Randomize cell grid.
//

void randomizeGrid(CLife *cellGrid) {

    time_t t;
    srand((unsigned) time(&t));

    for (int y = 0; y < cellGrid->getCellGridHeight(); y++) {
        for (int x = 0; x < cellGrid->getCellGridWidth(); x++) {
            int active = rand() % 2;
            cellGrid->setCell(y, x, active);
        }
    }
}

//
// Create cell grid ncurses window.
//

WINDOW *createCellGridWindow(int gridHeight, int gridWidth) {

    WINDOW *cellGridWindow;

    cellGridWindow = newwin(gridHeight, gridWidth, 1, 0);

    if (cellGridWindow) {
        box(cellGridWindow, 0, 0);
        curs_set(0);
        noecho();
        nodelay(stdscr, true);
        attron(A_REVERSE);
        mvwprintw(stdscr, 0, ((gridWidth - strlen(kHeaderString)) / 2), kHeaderString, gridHeight - 2, gridWidth - 2);
        attroff(A_REVERSE);
        mvwprintw(stdscr, gridHeight + 1, gridWidth - std::strlen(kCommandString), kCommandString);
    }

    return (cellGridWindow);

}

//
// Check for command key typed and process accordingly.
//

bool processNextTick(CLife *cellGrid) {

    char key = getch();
    if (key == '1') {  
        cellGrid->start();
    } else if (key == '2') {
        cellGrid->stop();
    } else if (key == '3') {
        cellGrid->stop();
        randomizeGrid(cellGrid);
        cellGrid->setTick(0);
        cellGrid->refresh();
    } else if (key == '4') {
        return (false);
    }

    return (true);

}

// ============================
// ===== MAIN ENTRY POINT =====
// ============================

int main(int argc, char** argv) {

    // Initialise ncurses and get cell grid window dimensions
    
    initscr();
    
    int gridHeight, gridWidth;
    getmaxyx(stdscr, gridHeight, gridWidth);
    gridHeight -= 2; // Allow for title/footer
    
    // Create Cell grid window
    
    WINDOW *cellGridWindow = createCellGridWindow(gridHeight, gridWidth);

    if (!cellGridWindow) {
        return (EXIT_FAILURE);
    }

    // Create life grid and initalize with random data and display
    
    CCursesLife cellGrid{ cellGridWindow, gridHeight - 2, gridWidth - 2};

    randomizeGrid(&cellGrid);
    refresh();
    cellGrid.refresh();

    // Loop displaying life game until quit
    
    cellGrid.start();
    while (processNextTick(&cellGrid)) {
        mvwprintw(stdscr, gridHeight + 1, 1, "Iteration: %-5d", cellGrid.getTick());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cellGrid.nextTick();
    }

    endwin();

    return (EXIT_SUCCESS);
    
}

