/* 
 * File:   main.cpp
 * Author: robt
 *
 * Created on 25 November 2018, 10:55
 */

#include <thread>
#include <chrono>
#include <cstring>

#include <ncurses.h>

#include "CLife.hpp"

class CCursesLife : public CLife {
public:
    explicit CCursesLife(WINDOW *cellGridWindow, int cellGridHeight, int cellGridWidth);
    virtual ~CCursesLife();

    virtual void updateCell(int y, int x, bool active) {
        char cell = active ? '*' : ' ';
        mvwprintw(m_cellGridWindow, y + 1, x + 1, "%c", cell);
    }

    virtual void refresh() {

        if (m_cellGridWindow) {
            wrefresh(m_cellGridWindow);
        }

    }

    CCursesLife(const CLife& orig) = delete;
    CCursesLife(const CLife && orig) = delete;
    CCursesLife& operator=(CLife other) = delete;

    WINDOW *m_cellGridWindow{nullptr};

};

CCursesLife::CCursesLife(WINDOW *cellGridWindow, int cellGridHeight, int cellGridWidth) : 
            CLife(cellGridHeight, cellGridWidth), m_cellGridWindow(cellGridWindow) {

}

CCursesLife::~CCursesLife() {

}

constexpr const char *kHeaderString { "Conways Game Of Life(%dx%d)" };
constexpr const char *kCommandString {"1(Start) 2(Stop) 3(Reset) 4(Quit)"};

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

void initialiseCellGrid(CLife *cellGrid) {

    randomizeGrid(cellGrid);
    refresh();
    cellGrid->refresh();

}

WINDOW *createCellGridWindow() {

    WINDOW *cellGridWindow;
    int gridHeight, gridWidth;

    getmaxyx(stdscr, gridHeight, gridWidth);
    gridHeight -= 2;
    
    cellGridWindow = newwin(gridHeight, gridWidth, 1, 0);
    box(cellGridWindow, 0, 0);
    curs_set(0);

    return (cellGridWindow);

}

bool processCommand(CLife *cellGrid) {

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
        return(false);
    }

    return (true);

}

/*
 * 
 */
int main(int argc, char** argv) {

    WINDOW *cellGridWindow;
    int gridHeight, gridWidth;

    initscr();

    cellGridWindow = createCellGridWindow();
    getmaxyx(cellGridWindow, gridHeight, gridWidth);

    noecho();
    nodelay(stdscr, true);

    attron(A_REVERSE);
    mvwprintw(stdscr, 0, ((gridWidth-strlen(kHeaderString))/2), kHeaderString, gridHeight - 2, gridWidth - 2);
    attroff(A_REVERSE);
    
    mvwprintw(stdscr, gridHeight+1, gridWidth-std::strlen(kCommandString), kCommandString);
    
    CCursesLife cellGrid{ cellGridWindow, gridHeight - 2, gridWidth - 2};

    initialiseCellGrid(&cellGrid);

    cellGrid.start();
    
    while (processCommand(&cellGrid)) {
        mvwprintw(stdscr, gridHeight+1, 1, "Iteration: %-5d", cellGrid.getTick());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cellGrid.update();
    }

    endwin();

    return 0;
}

