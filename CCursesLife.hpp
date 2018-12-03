
/*
 * File:   CCursesLife.hpp
 * 
 * Author: Robert Tizzard
 * 
 * Created on 25 November 2018, 10:55
 *
 * Copyright 2018.
 *
 */

#ifndef CCURESELIFE_HPP
#define CCURESELIFE_HPP

// =============
// INCLUDE FILES
// =============

//
// ncurses
//

#include <ncurses.h>

//
// Life Cell Grid Class
//

#include "CLife.hpp"

//
// Ncurses Cell Grid Display Class
//

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

#endif /* CCURESELIFE_HPP */

