/*  Name: Keaton Lee
 *  Date: May 5, 2021
 *  Title: Nifty Mountains
 *
 *  Description: Contains function for Dijkstra's Algorithm
*/

// include header files
#include "header.h"
#include "apmatrix.h"
#include <algorithm>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <climits>
#include <vector>

extern ALLEGRO_DISPLAY *display;

int dijkstraAlgo(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation, const short selectedRow) {
// recives elevations apmatrix, filled paths apmatrix, and selected row as parameters
// determines shortest west to east path from selected row using Dijkstra's Algorithm
// while the shortest path is calculated, possible paths are drawn on the screen to illustrate Dijkstra's Algorithm
// once the shortest path has been found, the possible paths are erased and the most efficient path is drawn
// returns total elevation of lowest elevation path
    // variables are declared
    Direction directionCost;                                    // holds change in elevation (cost) based on different directions
    apmatrix<bool> checked(ROWS, COLUMNS, false);               // holds coordinates that have already been checked
    apmatrix<int> pathCost(ROWS, COLUMNS, INT_MAX);             // holds path cost to each coordinate (they start at the maximum value of an integer)
    apmatrix<pair <short, short>> previous(ROWS, COLUMNS);      // holds previous coodinate of given coordinate
    apmatrix<ALLEGRO_COLOR> saveColour(ROWS, COLUMNS, ORANGE1); // holds colour of specific coordinate
    apmatrix<bool> reColour(ROWS, COLUMNS, false);              // holds boolean of whether a coordinate has been recoloured or not
    int currentElevation, lowestPathCost, totalElevation;       // integers pertaining to elecation and path cost
    short row, column;                                          // current row and column
    short revolutions = 0;                                      // determines the number of revolutions the algorithm has gone through
    short loadingValue = 0;                                     // holds the largest loading value to update loading bar

    ALLEGRO_BITMAP *bitmap;
    bitmap = al_get_backbuffer(display);                        // used to determine colours of pixels on the screen

    // path cost from first point to itself is set to 0
    pathCost[selectedRow][0] = 0;

    while (true) {

        // the number of revolutions increases by 1
        revolutions++;

        // lowest path cost is set to the maximum value of an integer
        lowestPathCost = INT_MAX;

        for (int i = 0; i < elevations.numrows(); i++) {
            for (int j = 0; j < elevations.numcols(); j++) {
                if (pathCost[i][j] < lowestPathCost && !checked[i][j]) {
                    // the point which has lowest path cost that has not yet been checked is determined
                    // this ensures Dijkstra's Algorithm locates the shortest possible path
                    // however, as a result, Dijkstra's Algorithm is quite slow
                    lowestPathCost = pathCost[i][j];
                    row = i;
                    column = j;
                }
            }
        }

        // the point is updated to true in the checked array, so it will not be checked again
        checked[row][column] = true;

        // the point is coloured on the screen to illustrate Dijkstra's Algorithm
        // the colour of the replaced point is saved so that the map can be reverted once the lowest elevation path has been found
        saveColour[row][column] = al_get_pixel (bitmap , column , row);
        al_draw_filled_rectangle(column, row, column + 1, row + 1, ORANGE1);
        reColour[row][column] = true;

        if (revolutions % 50 == 0) {
            // the display is updated every 50 revolutions, so users can see how Dijkstra's Algorithm functions
            if (column + 1 > loadingValue) {
                // the loading bar is updated if progress has increased
                loadingValue = column + 1;
                loadingBar(short(float(column+1)/elevations.numcols()*100));
            }
            al_flip_display();
        }

        if (column == elevations.numcols() - 1) {
            // once a path has reached the final column, the shortest path has been found
            totalElevation = pathCost[row][column];
            break;
        }

        // elevation at current point is calculated
        currentElevation = elevations[row][column];

        // the path cost to the point straight ahead is calculated
        directionCost.straight = pathCost[row][column] + abs(currentElevation - elevations[row][column + 1]);

        if (directionCost.straight < pathCost[row][column + 1] && !checked[row][column + 1]) {
            // if this cost is lower than the current path cost to such point, its path cost is updated
            pathCost[row][column + 1] = directionCost.straight;
            previous[row][column + 1] = make_pair(row, column);
        }

        if (row > 0) {
            // the path cost to the point straight ahead and upwards is calculated
            directionCost.straightUp = pathCost[row][column] + abs(currentElevation - elevations[row - 1][column + 1]);
            if (directionCost.straightUp < pathCost[row - 1][column + 1] && !checked[row - 1][column + 1]) {
                // if this cost is lower than the current path cost to such point, its path cost is updated
                pathCost[row - 1][column + 1] = directionCost.straightUp;
                previous[row - 1][column + 1] = make_pair(row, column);
            }
        }

        if (row < elevations.numrows() - 1) {
            // the path cost to the point straight ahead and downwards calculated
            directionCost.straightDown = pathCost[row][column] + abs(currentElevation - elevations[row + 1][column + 1]);
            if (directionCost.straightDown < pathCost[row + 1][column + 1] && !checked[row + 1][column + 1]) {
                // if this cost is lower than the current path cost to such point, its path cost is updated
                pathCost[row + 1][column + 1] = directionCost.straightDown;
                previous[row + 1][column + 1] = make_pair(row, column);
            }
        }
    }

    // the loading bar is set to 100% complete
    loadingBar(100);

    // draws first pixel of shortest path and sets filled value of pixel to true
    al_draw_filled_rectangle(column, row, column + 1, row + 1, ORANGE2);
    filled[row][column] = true;
    reColour[row][column] = false;

    short bufferRow, bufferCol;

    for (int i = 0; i < elevations.numcols() - 1; i++) {
        // draws pixels of shortest path from East to West and sets filled value of pixels to true
        // path is drawn by determing the previous saved coodinate of the current coordinate
        bufferRow = previous[row][column].first;
        bufferCol = previous[row][column].second;
        row = bufferRow;
        column = bufferCol;

        al_draw_filled_rectangle(column, row, column + 1, row + 1, ORANGE2);
        filled[row][column] = true;
        reColour[row][column] = false;
    }

    for (int i = 0; i < elevations.numrows(); i++) {
        for (int j = 0; j < elevations.numcols(); j++) {
            if (reColour[i][j]) {
                // pixels that were coloured over while finding the shortest path are reverted
                // this is to make it easier to visualize other methods alongside Dijkstra's Algorithm
                al_draw_filled_rectangle(j, i, j + 1, i + 1, saveColour[i][j]);
            }
        }
    }

    al_flip_display();

    // returns total elevation of lowest elevation path
    return totalElevation;
}
