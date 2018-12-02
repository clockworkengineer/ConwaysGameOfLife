/* 
 * File:   CLife.hpp
 * Author: robt
 *
 * Created on 27 November 2018, 13:57
 */

#ifndef CLIFE_HPP
#define CLIFE_HPP

#include <memory>
#include <utility>

class CLife {
    
public:
    
    using Cell = unsigned char;
    
    explicit CLife(int cellGridHeight, int cellGridWidth);
    virtual ~CLife();
    
    virtual void updateCell(int y, int x, bool active) { }
    virtual void refresh() {}
    
    void setCell(int y, int x, bool active);
    bool getCell(int y, int x);
    void nextTick();

    CLife(const CLife& orig) = delete;
    CLife(const CLife && orig) = delete;
    CLife& operator=(CLife other) = delete;   
            
    void start();
    void stop();
    
    int getCellGridHeight() const;
    int getCellGridWidth() const;
    void setTick(int tick);
    int getTick() const;
  
private:
    
    std::pair<int, int> gridBounds(int y, int x);
    
    int cellIndex(int y, int x) {
        return ((y * m_cellGridWidth) + x);
    }
    
    bool isCellActive(int y, int x);
    int activeCellNeighbours(int y, int x);
    
    bool m_running {false};
    int m_tick {0};
    int m_cellGridWidth {0};
    int m_cellGridHeight {0};
    std::unique_ptr<std::uint8_t[]> m_cellMasterGrid {nullptr};
    std::unique_ptr<std::uint8_t[]> m_cellGridReadOnly {nullptr};
    
};

#endif /* CLIFE_HPP */

