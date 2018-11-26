/* 
 * File:   main.cpp
 * Author: robt
 *
 * Created on 25 November 2018, 10:55
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

using namespace std;

typedef unsigned char CELL;

#define CELL_ALIVE  ((CELL) ~0)
#define CELL_DEAD    0

#define GRID_HEIGHT 20
#define GRID_WIDTH  20

#define cellIndex(y, x) ((y)*GRID_HEIGHT+(x))

inline bool cellActive(CELL *cellGrid, int y, int x) {

    if (y < 0) {
        y = GRID_HEIGHT-1;
    } else if (y == GRID_HEIGHT) {
        y = 0;
    }
    
    if (x < 0) { 
        x = GRID_WIDTH-1;
    } else if (x == GRID_WIDTH) {
        x = 0;
    }
    
    return(cellGrid[cellIndex(y, x)]==CELL_ALIVE);
     
}

int activeCellNeighbours(CELL *cellGrid, int y, int x) {
    int active=0;
    if (cellActive(cellGrid, y-1, x-1))active++;
    if (cellActive(cellGrid, y-1,  x)) active++;
    if (cellActive(cellGrid, y-1, x+1)) active++;
    if (cellActive(cellGrid, y, x-1)) active++;
    if (cellActive(cellGrid, y, x+1)) active++;
    if (cellActive(cellGrid, y+1, x-1)) active++;
    if (cellActive(cellGrid, y+1, x)) active++;
    if (cellActive(cellGrid, y+1, x+1)) active++;
    return(active);
    
}

void patternGlider(CELL *cellGrid, int y, int x) {
    
    cellGrid[cellIndex(y,x)] = CELL_ALIVE;
    cellGrid[cellIndex(y,x+2)] = CELL_ALIVE;
    cellGrid[cellIndex(y+1,x+1)] = CELL_ALIVE;
    cellGrid[cellIndex(y+1,x+2)] = CELL_ALIVE;
    cellGrid[cellIndex(y+2,x+1)] = CELL_ALIVE;

}

void patternSpaceShip(CELL *cellGrid, int y, int x) {
    
    cellGrid[cellIndex(y,x+1)] = CELL_ALIVE;
    cellGrid[cellIndex(y,x+2)] = CELL_ALIVE;
    cellGrid[cellIndex(y+1,x)] = CELL_ALIVE;   
    cellGrid[cellIndex(y+1,x+1)] = CELL_ALIVE;  
    cellGrid[cellIndex(y+1,x+2)] = CELL_ALIVE;  
    cellGrid[cellIndex(y+1,x+3)] = CELL_ALIVE;  
    cellGrid[cellIndex(y+2,x)] = CELL_ALIVE;
    cellGrid[cellIndex(y+2,x+1)] = CELL_ALIVE;
    cellGrid[cellIndex(y+2,x+3)] = CELL_ALIVE;
    cellGrid[cellIndex(y+2,x+4)] = CELL_ALIVE;
    cellGrid[cellIndex(y+3,x+2)] = CELL_ALIVE;
    cellGrid[cellIndex(y+3,x+3)] = CELL_ALIVE;
       
}

void patternToad(CELL *cellGrid, int y, int x) {
    
    cellGrid[cellIndex(y,x+1)] = CELL_ALIVE;
    cellGrid[cellIndex(y,x+2)] = CELL_ALIVE;
    cellGrid[cellIndex(y,x+3)] = CELL_ALIVE;
    cellGrid[cellIndex(y+1,x)] = CELL_ALIVE;
    cellGrid[cellIndex(y+1,x+1)] = CELL_ALIVE;
    cellGrid[cellIndex(y+1,x+2)] = CELL_ALIVE;
}

void initCellGrid(CELL *cellGrid) {

    patternSpaceShip(cellGrid, 3, 2);

}

void displayCellGrid(CELL *cellGrid, int iteration) {
    
    printf("Iteration %d\n\n", iteration);
       
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            char cell = (cellGrid[cellIndex(y, x)] == CELL_ALIVE) ? '*' : '_';
            printf("%c", cell);
        }
        printf("\n");
    }
    printf("\n");
    
}

void updateCellGrid(CELL *cellGrid) {
    
    CELL cellGridCopy[GRID_HEIGHT*GRID_WIDTH] {0};
    memcpy(cellGridCopy, cellGrid, GRID_HEIGHT*GRID_WIDTH);
    
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            int active = activeCellNeighbours(cellGridCopy, y, x);
            if (cellGridCopy[cellIndex(y, x)]==CELL_ALIVE) {
                if ((active < 2) || (active > 3)){
                    cellGrid[cellIndex(y, x)]=CELL_DEAD;
                } 
            } else {
                if (active==3) {
                    cellGrid[cellIndex(y, x)]=CELL_ALIVE;
                }
            }
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
   
    CELL cellGrid[GRID_HEIGHT*GRID_WIDTH] {0};
    
    int iteration = 0;
    
    initCellGrid(cellGrid);
    
    displayCellGrid(cellGrid, iteration);
       
    while(true) {
        sleep(1);
        updateCellGrid(cellGrid);
        displayCellGrid(cellGrid, iteration++);
    }
    
    return 0;
}

