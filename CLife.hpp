/* 
 * File:   CLife.hpp
 * Author: robt
 *
 * Created on 27 November 2018, 13:57
 */

#ifndef CLIFE_HPP
#define CLIFE_HPP

#include <memory>

class CLife {
    
public:
    
    using Cell = unsigned char;

    static const Cell  kCellActive {1};
    static const Cell  kCellDead {0};
    
    explicit CLife(int cellGridWidth, int cellGridHeight);
    virtual ~CLife();
    
    void setCell(int y, int x, bool active);
    bool getCell(int y, int x);
    void update();

    CLife(const CLife& orig) = delete;
    CLife(const CLife && orig) = delete;
    CLife& operator=(CLife other) = delete;   
            
    int getCellGridHeight() const;
    int getCellGridWidth() const;
  
private:
    
    int cellIndex(int y, int x);
    bool cellActive(int y, int x);
    int activeCellNeighbours(int y, int x);
    
    int m_cellGridWidth;
    int m_cellGridHeight;
    std::unique_ptr<std::uint8_t[]> m_cellGrid {nullptr};
    std::unique_ptr<std::uint8_t[]> m_cellGridCopy {nullptr};
    
};

#endif /* CLIFE_HPP */

