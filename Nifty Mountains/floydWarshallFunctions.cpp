/*  Name: Keaton Lee
 *  Date: May 5, 2021
 *  Title: Nifty Mountains
 *
 *  Description: Contains function for Floyd Warshall Algorithm
*/

// include header files
#include "header.h"
#include "apmatrix.h"
#include <allegro5/allegro_primitives.h>
#include <vector>

void floydWarshallAlgo(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation) {
// recives elevations apmatrix, filled paths apmatrix, and method elevation vector as parameters
// determines shortest west to east path using Floyd Warshall Algorithm and draws such path
// calls function to interpret data
    // variables are declared
    apmatrix<short> pathCost(ROWS, COLUMNS, 0);                     // holds total path cost to a certain coordinate
    apmatrix<NextRowDirection> reversePathDirection(ROWS, COLUMNS); // keeps track of direction to draw path
    Direction costFromPrevious;                                     // used to hold chnage in elevation between certain points
    int currentElevation;                                           // holds current elevation at a specific point


    for (int i = 1; i < elevations.numcols(); i++) {
        for (int j = 0; j < elevations.numrows(); j++) {

            // elevation at current point is calculated
            currentElevation = elevations[j][i];

            if (j != 0) {
                // cost from previous path to move downwards is calculated
                costFromPrevious.straightDown = pathCost[j - 1][i - 1] + abs(currentElevation - elevations[j - 1][i - 1]);
            }

            // cost from previous path to move straight is calculated
            costFromPrevious.straight = pathCost[j][i - 1] + abs(currentElevation - elevations[j][i - 1]);

            if (j != elevations.numrows() - 1) {
                // cost from previous path to move upwards is calculated
                costFromPrevious.straightUp = pathCost[j + 1][i - 1] + abs(currentElevation - elevations[j + 1][i - 1]);
            }

            // by default, the best row is set to straight
            pathCost[j][i] = costFromPrevious.straight;
            reversePathDirection[j][i] = STRAIGHT;

            if (costFromPrevious.straightDown < pathCost[j][i] && j != 0) {
                // if the past cost from the previous point to move downwards is lower, the best row is updated
                pathCost[j][i] = costFromPrevious.straightDown;
                reversePathDirection[j][i] = STRAIGHTUP;
            }

            if (costFromPrevious.straightUp < pathCost[j][i] && j != elevations.numrows() - 1) {
                // if the past cost from the previous point to move upwards is lower, the best row is updated
                pathCost[j][i] = costFromPrevious.straightUp;
                reversePathDirection[j][i] = STRAIGHTDOWN;
            }
        }

        // loading bar is updated based on the number of columns in which the algorithm has been completed
        loadingBar(short(float(i+1)/elevations.numcols()*100));
        al_flip_display();
    }

    // variables pertaining to elevation are declared
    int lowestElevation = pathCost[0][elevations.numcols() - 1];
    int lowestElevationRow = 0;

    for (int i = 1; i < elevations.numrows(); i++) {
        if (pathCost[i][elevations.numcols() - 1] < lowestElevation) {
            // the row yielding the lowest elevation is calculated
            lowestElevation = pathCost[i][elevations.numcols() - 1];
            lowestElevationRow = i;
        }
    }

    int currentRow = lowestElevationRow;

    // draws first pixel of path and sets filled value of pixel to true
    al_draw_filled_rectangle(COLUMNS - 1, currentRow, COLUMNS, currentRow + 1, PURPLE);
    filled[currentRow][elevations.numcols() - 1] = true;

    // draws path pixel by pixel and sets filled value of drawn pixels to true
    for (int i = elevations.numcols() - 1; i > 0; i--) {

        // path is drawn from East to West, based on reverse path direction values
        if (reversePathDirection[currentRow][i] == STRAIGHTUP) {
            currentRow--;
        } else if (reversePathDirection[currentRow][i] == STRAIGHTDOWN) {
            currentRow++;
        }

        al_draw_filled_rectangle(i - 1, currentRow, i, currentRow + 1, PURPLE);
        filled[currentRow][i - 1] = true;
    }

    al_flip_display();

    // function is called to interpret data
    interpretData(4, currentRow, 0, lowestElevation, methodElevation);
}
