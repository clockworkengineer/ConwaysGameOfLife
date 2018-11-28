/* 
 * File:   CLife.cpp
 * Author: robt
 * 
 * Created on 27 November 2018, 13:57
 */


#include <cstring>
#include "CLife.hpp"

CLife::CLife(int cellGridWidth, int cellGridHeight) : m_cellGridWidth{cellGridWidth}, m_cellGridHeight{cellGridHeight} 
{
    m_cellGrid.reset(new std::uint8_t [m_cellGridWidth*m_cellGridHeight]);
    m_cellGridCopy.reset(new std::uint8_t [m_cellGridWidth*m_cellGridHeight]);
}

int CLife::getCellGridHeight() const {
    return m_cellGridHeight;
}

int CLife::getCellGridWidth() const {
    return m_cellGridWidth;
}

CLife::~CLife() {
}

int CLife::cellIndex(int y, int x) {
    return(y*this->m_cellGridHeight+x);
}

bool CLife::cellActive(int y, int x) {

    if (y < 0) {
        y = m_cellGridHeight-1;
    } else if (y == m_cellGridHeight) {
        y = 0;
    }
    
    if (x < 0) { 
        x = m_cellGridWidth-1;
    } else if (x == m_cellGridWidth) {
        x = 0;
    }
    
    return(m_cellGridCopy[cellIndex(y, x)]==kCellActive);
     
}

int CLife::activeCellNeighbours(int y, int x) {
    int active=0;
    if (cellActive(y-1, x-1))active++;
    if (cellActive(y-1,  x)) active++;
    if (cellActive(y-1, x+1)) active++;
    if (cellActive(y, x-1)) active++;
    if (cellActive(y, x+1)) active++;
    if (cellActive(y+1, x-1)) active++;
    if (cellActive(y+1, x)) active++;
    if (cellActive(y+1, x+1)) active++;
    return(active);
    
}

void CLife::update() {
    
    std::memcpy(m_cellGridCopy.get(), m_cellGrid.get(), this->m_cellGridHeight*this->m_cellGridWidth);
    
    for (int y = 0; y < this->m_cellGridHeight; y++) {
        for (int x = 0; x < this->m_cellGridWidth; x++) {
            int active = activeCellNeighbours(y, x);
            if (m_cellGridCopy[cellIndex(y, x)]==kCellActive) {
                if ((active < 2) || (active > 3)){
                    m_cellGrid[cellIndex(y, x)]=kCellDead;
                } 
            } else {
                if (active==3) {
                    m_cellGrid[cellIndex(y, x)]=kCellActive;
                }
            }
        }
    }
}

void CLife::setCell(int y, int x, bool active) {
    if (active) {
         m_cellGrid[cellIndex(y, x)]=kCellActive;
    } else{
        m_cellGrid[cellIndex(y, x)]=kCellDead;
    }
}

bool CLife::getCell(int y, int x) {
    return(m_cellGrid[cellIndex(y, x)]==kCellActive);
}