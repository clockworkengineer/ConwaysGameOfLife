/* 
 * File:   main.cpp
 * Author: robt
 *
 * Created on 25 November 2018, 10:55
 */

#include <stdio.h>
#include <unistd.h>

#include "CLife.hpp"

#define GRID_HEIGHT 20
#define GRID_WIDTH  20

void patternGlider(CLife *cellGrid, int y, int x) {
    
    cellGrid->setCell(y,x,true);
    cellGrid->setCell(y,x+2,true);
    cellGrid->setCell(y+1,x+1,true);
    cellGrid->setCell(y+1,x+2,true);
    cellGrid->setCell(y+2,x+1,true);

}

void patternSpaceShip(CLife *cellGrid, int y, int x) {
    
    cellGrid->setCell(y,x+1,true);
    cellGrid->setCell(y,x+2,true);
    cellGrid->setCell(y+1,x,true);   
    cellGrid->setCell(y+1,x+1,true);  
    cellGrid->setCell(y+1,x+2,true);  
    cellGrid->setCell(y+1,x+3,true);  
    cellGrid->setCell(y+2,x,true);
    cellGrid->setCell(y+2,x+1,true);
    cellGrid->setCell(y+2,x+3,true);
    cellGrid->setCell(y+2,x+4,true);
    cellGrid->setCell(y+3,x+2,true);
    cellGrid->setCell(y+3,x+3,true);
       
}

void patternToad(CLife *cellGrid, int y, int x) {
    
    cellGrid->setCell(y,x+1,true);
    cellGrid->setCell(y,x+2,true);
    cellGrid->setCell(y,x+3,true);
    cellGrid->setCell(y+1,x,true);
    cellGrid->setCell(y+1,x+1,true);
    cellGrid->setCell(y+1,x+2,true);
}

void initCellGrid(CLife *cellGrid) {

    patternSpaceShip(cellGrid, 3, 2);

}

void displayCellGrid(CLife *cellGrid, int iteration) {
    
    printf("Iteration %d\n\n", iteration);
       
    for (int y = 0; y < cellGrid->getCellGridHeight(); y++) {
        for (int x = 0; x < cellGrid->getCellGridWidth(); x++) {
            char cell = cellGrid->getCell(y, x) ? '*' : '_';
            printf("%c", cell);
        }
        printf("\n");
    }
    printf("\n");
    
}

/*
 * 
 */
int main(int argc, char** argv) {
   
    CLife cellGrid { GRID_HEIGHT, GRID_WIDTH};
    
    int iteration = 0;
    
    initCellGrid(&cellGrid);
    
    displayCellGrid(&cellGrid, iteration);
       
    while(true) {
        sleep(1);
        cellGrid.update();
        displayCellGrid(&cellGrid, iteration++);
    }
    
    return 0;
}

