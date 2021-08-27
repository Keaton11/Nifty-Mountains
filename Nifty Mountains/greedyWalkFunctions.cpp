/*  Name: Keaton Lee
 *  Date: May 5, 2021
 *  Title: Nifty Mountains
 *
 *  Description: Contains functions for drawing different greedy walk methods
*/

// include header files
#include "header.h"
#include "apmatrix.h"
#include <allegro5/allegro_primitives.h>
#include <vector>

int drawLowestElevPath(const apmatrix<short> &elevations, apmatrix<bool> &filled, ALLEGRO_COLOR colour, short startRow, short startCol, bool draw, short direction) {
// function recives elevations apmatrix, filled paths apmatrix, a colour, a starting row, a starting column, a boolean value for whether or not to draw, and a direction as parameters
// function draws greedy walk from East to West or West to East, minimizing change in elevation
// function returns total elevation change on the given path
    // variables are declared
    Direction directionCost;            // holds change in elevation (cost) based on different directions
    int totalElevationChange = 0;       // holds total elevation of path
    short currentElevation, bestRow;    // current elevation holds elevations at a certain point and best row contains row with lowest cost
    NextRowDirection nextRow;           // next row holds next row direction

    if (draw) {
        // draws first pixel of path and sets filled value of pixel to true
        al_draw_filled_rectangle(startCol, startRow, startCol + 1, startRow + 1, colour);
        filled[startRow][startCol] = true;
    }

    for (int i = startCol; true; i += direction) {

        // for loop ends if either the West side or the East side of the screen is reached
        if (i + direction < 0 || i + direction > elevations.numcols() - 1) {
            break;
        }

        // elevation at current point is calculated
        currentElevation = elevations[startRow][i];

        // elevation change from current point to point straight ahead is calculated
        directionCost.straight = abs(currentElevation - elevations[startRow][i + direction]);

        if (startRow > 0) {
            // elevation change from current point to point straight ahead and upwards is calculated
            directionCost.straightUp = abs(currentElevation - elevations[startRow - 1][i + direction]);
        } else {
            // if the path is on the top row, it cannot move further upwards
            directionCost.straightUp = -1;
        }

        if (startRow < elevations.numrows() - 1) {
            // elevation change from current point to point straight ahead and downwards is calculated
            directionCost.straightDown = abs(currentElevation - elevations[startRow + 1][i + direction]);
        } else {
            // if the path is on the bottom row, it cannot move further downwards
            directionCost.straightDown = -1;
        }

        // by default, the best row is set to straight
        bestRow = directionCost.straight;
        nextRow = STRAIGHT;

        if ((directionCost.straightUp != -1) && (directionCost.straightUp < bestRow)) {
            // if the direction cost upwards is lower, the best row is updated to straight and upwards
            bestRow = directionCost.straightUp;
            nextRow = STRAIGHTUP;
            if ((directionCost.straightUp == directionCost.straightDown) && (rand() % 2 == 1)) {
                // if the direction cost upwards is equal to that downwards, the chosen direction is randomized
                nextRow = STRAIGHTDOWN;
            }
        }

        if ((directionCost.straightDown != -1) && (directionCost.straightDown < bestRow)) {
            // if the direction cost downwards is lower, the best row is updated to straight and downwards
            nextRow = STRAIGHTDOWN;
        }

        // function is called to update row and total elevation change
        nextRowCalculation(nextRow, startRow, totalElevationChange, directionCost);

        if (draw) {
            // draws path pixel by pixel and sets filled value of drawn pixels to true
            al_draw_filled_rectangle(i + direction, startRow, i + direction + 1, startRow + 1, colour);
            filled[startRow][i + direction] = true;
        }
    }

    if (draw) {
        al_flip_display();
    }

    // total elevation change is returned
    return totalElevationChange;
}

void nextRowCalculation(NextRowDirection nextRow, short &startRow, int &totalElevationChange, Direction directionCost) {
//function recives next row direction, current row, current column, total elevation change, and direction cost as parameters
//function updates row based on row direction, and updates total elevation cost using direction cost
//function returns row and total elevation cost via pass by reference
    switch(nextRow) {
        // switch statement uses next row direction to make appropriate changes to tow and total elevation
        case (STRAIGHTUP):
            startRow--;
            totalElevationChange += directionCost.straightUp;
            break;
        case (STRAIGHT):
            totalElevationChange += directionCost.straight;
            break;
        case (STRAIGHTDOWN):
            startRow++;
            totalElevationChange += directionCost.straightDown;
            break;
    }
}

int drawLowAsPossible(const apmatrix<short> &elevations, apmatrix<bool> &filled, ALLEGRO_COLOR colour, short startRow) {
// function recives elevations apmatrix, filled paths apmatrix, a colour, and a starting row as parameters
// function draws greedy walk from East to West or West to East, minimizing upwards elevation
// function returns total elevation change on the given path
    // variables are declared
    Direction directionCost;        // holds change in elevation (cost) based on different directions
    Direction directionElevation;   // holds elevation based on different directions
    int totalElevationChange = 0;   // holds total elevation of path
    int currentElevation, bestRow;  // current elevation holds elevations at a certain point and best row contains row with lowest cost
    NextRowDirection nextRow;       // next row holds next row direction

    // draws first pixel of path and sets filled value of pixel to true
    al_draw_filled_rectangle(0, startRow, 1, startRow + 1, colour);
    filled[startRow][0] = true;

    for (int i = 0; true; i++) {

        // for loop ends if either the West side or the East side of the screen is reached
        if (i + 1 < 0 || i + 1 > elevations.numcols() - 1) {
            break;
        }

        // elevation at current point is calculated
        currentElevation = elevations[startRow][i];

        // elevation of point straight ahead is calculated
        directionElevation.straight = elevations[startRow][i + 1];
        // elevation change from current point to point straight ahead is calculated
        directionCost.straight = abs(currentElevation - elevations[startRow][i + 1]);

        if (startRow > 0) {
            // elevation of point straight ahead and upwards is calculated
            directionElevation.straightUp = elevations[startRow - 1][i + 1];
            // elevation change from current point to point straight ahead and upwards is calculated
            directionCost.straightUp = abs(currentElevation - elevations[startRow - 1][i + 1]);
        } else {
            // if the path is on the top row, it cannot move further upwards
            directionElevation.straightUp = -1;
        }

        if (startRow < elevations.numrows() - 1) {
            // elevation of point straight ahead and downwards is calculated
            directionElevation.straightDown = elevations[startRow + 1][i + 1];
            // elevation change from current point to point straight ahead and downwards is calculated
            directionCost.straightDown = abs(currentElevation - elevations[startRow + 1][i + 1]);
        } else {
            // if the path is on the bottom row, it cannot move further downwards
            directionElevation.straightDown = -1;
        }

        // by default, the best row is set to straight
        bestRow = directionElevation.straight;
        nextRow = STRAIGHT;

        if ((directionElevation.straightUp != -1) && (directionElevation.straightUp < bestRow)) {
            // if the elevation upwards is lower, the best row is updated to straight and upwards
            bestRow = directionElevation.straightUp;
            nextRow = STRAIGHTUP;
            if ((directionElevation.straightUp == directionElevation.straightDown) && (rand() % 2 == 1)) {
                // if the elevation upwards is equal to that downwards, the chosen direction is randomized
                nextRow = STRAIGHTDOWN;
            }
        }

        if ((directionElevation.straightDown != -1) && (directionElevation.straightDown < bestRow)) {
            // if the elevation downwards is lower, the best row is updated to straight and downwards
            nextRow = STRAIGHTDOWN;
        }

        // function is called to update row and total elevation change
        nextRowCalculation(nextRow, startRow, totalElevationChange, directionCost);

        // draws path pixel by pixel and sets filled value of drawn pixels to true
        al_draw_filled_rectangle(i + 1, startRow, i + 2, startRow + 1, colour);
        filled[startRow][i + 1] = true;
    }

    al_flip_display();

    // total elevation change is returned
    return totalElevationChange;
}

void drawLowestElevPoints(const apmatrix<short> &elevations, apmatrix<bool> &filled, short &lowestElevationRow, short &lowestElevationCol) {
// function recives elevations apmatrix, filled paths apmatrix, lowest elevation row, and lowest elevation column as parameters
// function locates lowest elevation point of each column and draws greed walks from each of these points
// function returns row and column of lowest elevation path via pass by reference
    // variables are declared
    int lowestElevationPoint;
    short currentElevation = -1;
    short lowestElevation;

    for (int i = 0; i < elevations.numcols(); i++) {

        lowestElevationPoint = 0;

        // lowest elevation point of each column is determined
        for (int j = 1; j < elevations.numrows(); j++) {
            if (elevations[j][i] < elevations[lowestElevationPoint][i]) {
                lowestElevationPoint = j;
            }
        }

        // loading bar is updated based on the number of rows in which the lowest elevation point has been calculated
        loadingBar(short(float(i+1)/elevations.numcols()*100));

        // greedy walk functions are called to draw paths and determine elevations of such paths
        currentElevation = drawLowestElevPath(elevations, filled, BLUE2, lowestElevationPoint, i, true, 1);
        currentElevation += drawLowestElevPath(elevations, filled, BLUE2, lowestElevationPoint, i, true, -1);

        if (currentElevation < lowestElevation || lowestElevation == -1) {
            // the path with the lowest elevation is determined
            lowestElevation = currentElevation;
            lowestElevationRow = lowestElevationPoint;
            lowestElevationCol = i;
        }

        // the lowest elevation point in each column is drawn and the filled value of these points is set to true
        al_draw_filled_rectangle(i, lowestElevationPoint, i + 1, lowestElevationPoint + 1, BLUE1);
        al_flip_display();

        filled[lowestElevationPoint][i] = true;
    }
}

void everyCoordinateGreedy(const apmatrix<short> &elevations, apmatrix<bool> &filled, short &lowestElevationRow, short &lowestElevationCol) {
// function recives elevations apmatrix, filled paths apmatrix, lowest elevation row, and lowest elevation column as parameters
// function calculate total elevation cost of each greedy walk from every point on the map
// function returns row and column of lowest elevation path via pass by reference
    // variables are declared
    short currentElevation;
    short lowestElevation = drawLowestElevPath(elevations, filled, al_map_rgb(0, 0, 0), 0, 0, false, 1);

    for (int i = 0; i < elevations.numrows(); i++) {
        for (int j = 0; j < elevations.numcols(); j++) {

            // for every point, greedy walk functions to the west and east are called to determine the elevation cost
            currentElevation = drawLowestElevPath(elevations, filled, al_map_rgb(0, 0, 0), i, j, false, 1);
            currentElevation += drawLowestElevPath(elevations, filled, al_map_rgb(0, 0, 0), i, j, false, -1);

            if (currentElevation < lowestElevation) {
                // the path with the lowest elevation is determined
                lowestElevation = currentElevation;
                lowestElevationRow = i;
                lowestElevationCol = j;
            }
        }
        // loading bar is updated based on the number of rows in which the total elevation has been calculated
        loadingBar(short(float(i+1)/elevations.numrows()*100));
        al_flip_display();
    }
}
