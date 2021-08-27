/***************************************************************************
 *  Name: Keaton Lee                                          May 6, 2021  *
 *  Title: Nifty Mountains                                                 *
 *                                                                         *
 *  Description: This program reads a set of topographic data into an      *
 *  apmatrix and writes several methods to compute some paths through the  *
 *  mountains that minimize change in elevation. The program then          *
 *  illustrates the topographic data and paths for the user to visualize   *
 *                                                                         *
 *  Program Overview: This program contains 6 different path finding       *
 *  algorithms which the user can choose from.                             *
 *                                                                         *
 *  1) Method 1 draws greedy walk paths starting from each row (from West  *
 *  to East). The most efficient path is re-drawn in another colour.       *
 *                                                                         *
 *  2) Method 2 draws greedy walk paths favouring minimal upwards          *
 *  elevation starting from each row (from West to East). The most         *
 *  efficient path is re-drawn in another colour.                          *
 *                                                                         *
 *  3) Method 3 locates the minimum elevation point in each column. These  *
 *  points are drawn, and greedy walks are calculated from these points.   *
 *  The most efficient path is re-drawn in another colour.                 *
 *                                                                         *
 *  4) Method 4 calculates the best possible greedy walk from every x and  *
 *  y position. This requires many calculations, and is thus slower than   *
 *  most of the other methods. The best greedy walk is then drawn.         *
 *                                                                         *
 *  5) Method 5 uses Floyd Warshall's shortest path algorithm to           *
 *  determine the best possible west to east walk. The shortest path from  *
 *  west to east is then drawn.                                            *
 *                                                                         *
 *  6) Method 6 uses Dijkstra's shortest path algorithm to determine the   *
 *  best possible west to east walk from a selected row. As this method    *
 *  determines the most efficient route, it tests many possible paths. As  *
 *  a result, this function takes about 10 minutes to run. While the path  *
 *  is calculated, the checked paths are drawn on the screen. Once the     *
 *  shortest path has been located, the checked paths are replaced by the  *
 *  most efficient path.                                                   *
 **************************************************************************/

// includes header files
#include "header.h"
#include "apmatrix.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <vector>

// global allegro variables
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_FONT *font = nullptr;

int main() {

    // allows for the generation of random numbers by seeding rand with a starting value
    srand(0);

    // variables are declared
    apmatrix<short> elevations(ROWS, COLUMNS);      // used to hold elevation values given by file containing topographic data
    apmatrix<bool> filled(ROWS, COLUMNS, false);    // used to determine where paths have been drawn
    vector<short> methodElevation(6, 0);            // used to hold minimum elevation calculated by each path finding method

    // initializes allegro and reads topographic data from input file
    if (!initializeAllegro() || !mapDataDrawer(DATA_FILE, elevations)) {
        // returns 1 if allegro fails to initialize or file cannot be found
        return 1;
    }

    // draws map using topographic data
    drawMap(elevations, filled, false);

    // draws legend below map
    drawLegend();

    // allows user to select which paths they would like the program to run
    // while loop ends once user closes the screen or presses escape
    while (!userInput(elevations, filled, methodElevation));

    return 0;
}
