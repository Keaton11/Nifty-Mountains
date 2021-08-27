/*  Name: Keaton Lee
 *  Date: May 5, 2021
 *  Title: Nifty Mountains
 *
 *  Description: Contains definitions, constants and function prototypes
*/

// checks if header was defined to avoid double inclusions
#ifndef HEADER_H
#define HEADER_H

// includes header files
#include "apmatrix.h"
#include <allegro5/allegro.h>
#include <vector>

using namespace std;

// defines colours
#define BLACK	    al_map_rgb(0, 0, 0)
#define GREY	    al_map_rgb(150, 150, 150)
#define WHITE	    al_map_rgb(255, 255, 255)
#define LAVENDER1   al_map_rgb(230, 190, 255)
#define LAVENDER2   al_map_rgb(195, 145, 220)
#define RED1		al_map_rgb(233, 150, 122)
#define RED2		al_map_rgb(255, 0, 0)
#define GREEN1	    al_map_rgb(60, 179, 113)
#define GREEN2	    al_map_rgb(0, 255, 0)
#define BLUE1	    al_map_rgb(0, 130, 200)
#define BLUE2	    al_map_rgb(0, 25, 155)
#define BLUE3	    al_map_rgb(0, 130, 255)
#define ORANGE1     al_map_rgb(189, 94, 0)
#define ORANGE2     al_map_rgb(255, 195, 77)
#define YELLOW	    al_map_rgb(255, 225, 25)
#define PURPLE	    al_map_rgb(145, 30, 180)

// declares constants
const char DATA_FILE[15] = "colorado.dat";
const int ROWS = 480;
const int COLUMNS = 844;

// struct containing path directions
struct Direction {
    short straightUp;
    short straight;
    short straightDown;
};

// enum for row direction
typedef enum {
    STRAIGHTUP,
    STRAIGHT,
    STRAIGHTDOWN
} NextRowDirection;

#endif

// functions are prototyped

// functions used in allegroFunctions.cpp
bool initializeAllegro();
bool userInput(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation);
void loadingBar(short percent);

// functions used in drawMapFunctions.cpp
bool mapDataDrawer(const char *fname, apmatrix<short> &elevations);
int findMin(const apmatrix<short> &elevations);
int findMax(const apmatrix<short> &elevations);
void drawMap(const apmatrix<short> &elevations, apmatrix<bool> filled, bool grayscale);

// functions used in legendFunctions.cpp
void drawLegend();
void updateLegend(const int methodNum);

// functions used in greedyWalkFunctions.cpp
int drawLowestElevPath(const apmatrix<short> &elevations, apmatrix<bool> &filled, ALLEGRO_COLOR colour, short startRow, short startCol, bool draw, short direction);
void nextRowCalculation(NextRowDirection nextRow, short &startRow, int &totalElevationChange, Direction directionCost);
int drawLowAsPossible(const apmatrix<short> &elevations, apmatrix<bool> &filled, ALLEGRO_COLOR colour, short startRow);
void drawLowestElevPoints(const apmatrix<short> &elevations, apmatrix<bool> &filled, short &lowestElevationRow, short &lowestElevationCol);
void everyCoordinateGreedy(const apmatrix<short> &elevations, apmatrix<bool> &filled, short &lowestElevationRow, short &lowestElevationCol);

// function used in floydWarshallFunctions.cpp
void floydWarshallAlgo(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation);

// function used in dijkstraFunctions.cpp
int dijkstraAlgo(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation, const short selectedRow);

// functions used in analyzePathFunctions.cpp
void indexOfLowestElevPath(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation);
void indexOfLowAsPossible(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation);
void indexOfLowestElevPoints(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation);
void indexOfEveryCoordinateGreedy(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation);
void indexOfDijkstraAlgo(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation);
void interpretData(const int methodNum, const short row, const short column, const short elevation, vector<short> &methodElevation);
