//
// Author: Robert Tizzard
// 
// Class: CLife
//
// Description: Base class implementation of Conway's game of life a cellular automaton.
// 
// Dependencies: 
// 
// C11++ : Use of C11++ features.
//
// Copyright 2018.
//

// =============
// INCLUDE FILES
// =============

//
// C++ STL
//

#include <cstring>

//
// Life Cell Grid Class
//

#include "CLife.hpp"

//
// Reserve Memory for cell grid and runtime copy.
//

CLife::CLife(int cellGridHeight, int cellGridWidth) : m_cellGridHeight{cellGridHeight}, m_cellGridWidth{cellGridWidth}
{
    m_cellMasterGrid.reset(new std::uint8_t [m_cellGridWidth * m_cellGridHeight]);
    m_cellGridReadOnly.reset(new std::uint8_t [m_cellGridWidth * m_cellGridHeight]);
}

CLife::~CLife() {
}

//
// Wrap around X,Y coordinates to cell grid .
//

std::pair<int, int> CLife::gridBounds(int y, int x) {
    
    if (y < 0) {
        y = m_cellGridHeight - 1;
    } else if (y == m_cellGridHeight) {
        y = 0;
    }

    if (x < 0) {
        x = m_cellGridWidth - 1;
    } else if (x == m_cellGridWidth) {
        x = 0;
    }
    
    return(std::make_pair(y, x));
    
}

//
// Return true if a cell is active.
//

bool CLife::isCellActive(int y, int x) {

    auto coords = gridBounds(y, x);

    return (m_cellGridReadOnly[cellIndex(coords.first, coords.second)]);

}

//
// Determine the number of active neighbours a cell has around it.
//

int CLife::activeCellNeighbours(int y, int x) {
    
    int activeNeighbours = 0;
    
    if (isCellActive(y - 1, x - 1)) {
        activeNeighbours++;
    }
    if (isCellActive(y - 1, x)) {
        activeNeighbours++;
    }
    if (isCellActive(y - 1, x + 1)) {
        activeNeighbours++;
    }
    if (isCellActive(y, x - 1)) { 
        activeNeighbours++;
    }
    if (isCellActive(y, x + 1)) { 
        activeNeighbours++;
    }
    if (isCellActive(y + 1, x - 1)) {
        activeNeighbours++;
    }
    if (isCellActive(y + 1, x)) {
        activeNeighbours++;
    }
    if (isCellActive(y + 1, x + 1)) {
        activeNeighbours++;
    }
    
    return (activeNeighbours);

}

//
// Update cell grid using readonly copy as a source and change any visual
// representation through refresh.
//

void CLife::nextTick() {

    if (!m_running) {
        return;
    }
    
    std::memcpy(m_cellGridReadOnly.get(), m_cellMasterGrid.get(), this->m_cellGridHeight * this->m_cellGridWidth);

    for (int y = 0; y < this->m_cellGridHeight; y++) {
        for (int x = 0; x < this->m_cellGridWidth; x++) {
            int activeCellCount = activeCellNeighbours(y, x);
            if (isCellActive(y, x)) {
                if ((activeCellCount < 2) || (activeCellCount > 3)) {
                    setCell(y, x, false);
                }
            } else {
                if (activeCellCount == 3) {
                    setCell(y, x, true);
                }
            }
        }
    }
    
    refresh();
    
    m_tick++;
    
}

//
// Change Cells state (true==active, false==dead) and update any external 
// representation.
//

void CLife::setCell(int y, int x, bool active) {

    auto coords = gridBounds(y, x);

    m_cellMasterGrid[cellIndex(coords.first, coords.second)] = active;
    
    updateCell(y, x, active);

}

//
// Get cells current state (true==active, false==dead).
//

bool CLife::getCell(int y, int x) {

    auto coords = gridBounds(y, x);
       
    return (m_cellMasterGrid[cellIndex(coords.first, coords.second)]);
    
}

//
// Start cell grid updates
//

void CLife::start() {
     m_running = true;
}

//
// Stop cell grid updates.
//

void CLife::stop() {
    m_running = false;
}

//
// Getter/Setter methods.
//

int CLife::getCellGridHeight() const {
    return m_cellGridHeight;
}

int CLife::getCellGridWidth() const {
    return m_cellGridWidth;
}

void CLife::setTick(int tick) {
    m_tick = tick;
}

int CLife::getTick() const {
    return m_tick;
}
