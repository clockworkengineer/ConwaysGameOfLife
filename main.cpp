/* 
 * File:   main.cpp
 * Author: robt
 *
 * Created on 25 November 2018, 10:55
 */

#include <thread>
#include <chrono>

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

CCursesLife::CCursesLife(WINDOW *cellGridWindow, int cellGridHeight, int cellGridWidth) : CLife(cellGridHeight, cellGridWidth), m_cellGridWindow(cellGridWindow) {

}

CCursesLife::~CCursesLife() {

}

void patternGlider(CLife *cellGrid, int y, int x) {

    cellGrid->setCell(y, x, true);
    cellGrid->setCell(y, x + 2, true);
    cellGrid->setCell(y + 1, x + 1, true);
    cellGrid->setCell(y + 1, x + 2, true);
    cellGrid->setCell(y + 2, x + 1, true);

}

void patternSpaceShip(CLife *cellGrid, int y, int x) {

    cellGrid->setCell(y, x + 1, true);
    cellGrid->setCell(y, x + 2, true);
    cellGrid->setCell(y + 1, x, true);
    cellGrid->setCell(y + 1, x + 1, true);
    cellGrid->setCell(y + 1, x + 2, true);
    cellGrid->setCell(y + 1, x + 3, true);
    cellGrid->setCell(y + 2, x, true);
    cellGrid->setCell(y + 2, x + 1, true);
    cellGrid->setCell(y + 2, x + 3, true);
    cellGrid->setCell(y + 2, x + 4, true);
    cellGrid->setCell(y + 3, x + 2, true);
    cellGrid->setCell(y + 3, x + 3, true);

}

void patternToad(CLife *cellGrid, int y, int x) {

    cellGrid->setCell(y, x + 1, true);
    cellGrid->setCell(y, x + 2, true);
    cellGrid->setCell(y, x + 3, true);
    cellGrid->setCell(y + 1, x, true);
    cellGrid->setCell(y + 1, x + 1, true);
    cellGrid->setCell(y + 1, x + 2, true);
}

void randomizeGrid(CLife *cellGrid) {
    
    time_t t;
    srand((unsigned) time(&t));
    
    for (int y = 0; y < cellGrid->getCellGridHeight(); y++) {
        for (int x = 0; x < cellGrid->getCellGridWidth(); x++) {
            int active=rand()%2;
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
    gridHeight -= 1;

    cellGridWindow = newwin(gridHeight, gridWidth, 1, 0);
    box(cellGridWindow, 0, 0);
    curs_set(0);

    return (cellGridWindow);

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

    CCursesLife cellGrid{ cellGridWindow, gridHeight - 2, gridWidth - 2};

    initialiseCellGrid(&cellGrid);

    int iteration = 0;
    while (true) {
        mvwprintw(stdscr, 0, 0, "Iteration %d", iteration++);
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cellGrid.update();
    }

    endwin();

    return 0;
}

