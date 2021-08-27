/*  Name: Keaton Lee
 *  Date: May 5, 2021
 *  Title: Nifty Mountains
 *
 *  Description: Contains functions for analyzing and comparing different
 *  path finding methods
*/

// include header files
#include "header.h"
#include "apmatrix.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include <vector>

extern ALLEGRO_FONT *font;

void indexOfLowestElevPath(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation) {
// recives elevations apmatrix, filled paths apmatrix, and apmatrix containing method elevations as parameters
// determines the lowest elevation path of greedy walks from West to East starting from each row
// calls function to interpret data
    // variables are declared
    short currentElevation;
    short lowestElevation = drawLowestElevPath(elevations, filled, RED1, 0, 0, true, 1);
    short lowestElevationPath = 0;

    for (int i = 1; i < elevations.numrows(); i++) {

        // greedy walk function is called for each row
        currentElevation = drawLowestElevPath(elevations, filled, RED1, i, 0, true, 1);

        if (currentElevation < lowestElevation) {
            // path with the lowest elevation is determined
            lowestElevation = currentElevation;
            lowestElevationPath = i;
        }
        // loading bar is updated based on the number of rows in which the total elevation has been calculated
        loadingBar(short(float(i+1)/elevations.numrows()*100));
    }

    // path with the lowest elevation is drawn
    drawLowestElevPath(elevations, filled, RED2, lowestElevationPath, 0, true, 1);

    // function is called to interpret data
    interpretData(0, lowestElevationPath, 0, lowestElevation, methodElevation);
}

void indexOfLowAsPossible(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation) {
// recives elevations apmatrix, filled paths apmatrix, and apmatrix containing method elevations as parameters
// determines the lowest elevation path of greedy walks favouring minimal elevation from West to East starting from each row
// calls function to interpret data
    // variables are declared
    int currentElevation;
    int lowestElevation = drawLowAsPossible(elevations, filled, GREEN1, 0);
    short lowestElevationPath = 0;

    for (int i = 1; i < elevations.numrows(); i++) {

        // greedy walk function favouring minimal upwards elevation is called for each row
        currentElevation = drawLowAsPossible(elevations, filled, GREEN1, i);

        if (currentElevation < lowestElevation) {
            // path with the lowest elevation is determined
            lowestElevation = currentElevation;
            lowestElevationPath = i;
        }
        // loading bar is updated based on the number of rows in which the total elevation has been calculated
        loadingBar(short(float(i+1)/elevations.numrows()*100));
    }

    // path with the lowest elevation is drawn
    drawLowAsPossible(elevations, filled, GREEN2, lowestElevationPath);

    // function is called to interpret data
    interpretData(1, lowestElevationPath, 0, lowestElevation, methodElevation);
}

void indexOfLowestElevPoints(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation) {
// recives elevations apmatrix, filled paths apmatrix, and apmatrix containing method elevations as parameters
// determines the lowest elevation path of greedy walks starting from the lowest elevation point of each column
// calls function to interpret data
    // variables are declared
    short lowestElevationRow = 0;
    short lowestElevationCol = 0;
    short totalElevation;

    // function is called to determine lowest elevation row and column
    drawLowestElevPoints(elevations, filled, lowestElevationRow, lowestElevationCol);

    // path with lowest elevation is drawn, and total elevation is calculated
    totalElevation = drawLowestElevPath(elevations, filled, BLUE3, lowestElevationRow, lowestElevationCol, true, 1);
    totalElevation += drawLowestElevPath(elevations, filled, BLUE3, lowestElevationRow, lowestElevationCol, true, -1);

    // function is called to interpret data
    interpretData(2, lowestElevationRow, lowestElevationCol, totalElevation, methodElevation);
}


void indexOfEveryCoordinateGreedy(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation) {
// recives elevations apmatrix, filled paths apmatrix, and apmatrix containing method elevations as parameters
// determines the lowest elevation path of greedy walks starting from each coordinate of the map
// calls function to interpret data
    // variables are declared
    short lowestElevationRow = 0;
    short lowestElevationCol = 0;
    short totalElevation;

    // function is called to determine lowest elevation row and column
    everyCoordinateGreedy(elevations, filled, lowestElevationRow, lowestElevationCol);

    // path with lowest elevation is drawn, and total elevation is calculated
    totalElevation = drawLowestElevPath(elevations, filled, YELLOW, lowestElevationRow, lowestElevationCol, true, 1);
    totalElevation += drawLowestElevPath(elevations, filled, YELLOW, lowestElevationRow, lowestElevationCol, true, -1);

    // function is called to interpret data
    interpretData(3, lowestElevationRow, lowestElevationCol, totalElevation, methodElevation);
}

void indexOfDijkstraAlgo(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation) {
// recives elevations apmatrix, filled paths apmatrix, and apmatrix containing method elevations as parameters
// user selects a row and function determines the lowest elevation path starting from the first column of that row
// calls function to interpret data

    short selectedRow = -1;

    // updates display and tells user to input selected row into console
    al_draw_filled_rectangle(0, ROWS, COLUMNS, ROWS + 30, LAVENDER1);
    al_draw_text(font, BLACK, COLUMNS / 2, ROWS + 4, ALLEGRO_ALIGN_CENTRE, "Enter a row into console to perform Dijkstra's Algorithm");
    al_flip_display();

    // informs user about Dijkstra's Algorithm and waits for user to choose a row
    cout << "Dijkstra's Algorithm determines the shortest path from East to West of any given row." << endl;
    cout << "This algorithm requires several minutes to calculate the most efficient path." << endl;
    while (selectedRow < 0 || selectedRow > 479) {
        // ensures user input is within the range of rows
        cout << "Enter a row between 0 and 479 to perform Dijkstra's Algorithm: ";
        cin >> selectedRow;
    }
    cout << endl << "Drawing possible paths using Dijkstra's Algorithm . . .";

    al_draw_filled_rectangle(0, ROWS, COLUMNS, ROWS + 30, LAVENDER1);
    al_flip_display();

    // function is called to determine total elevation of lowest elevation path
    int totalElevation = dijkstraAlgo(elevations, filled, methodElevation, selectedRow);

    // uses VT100 escape code, ^[[2K and carriage return (\r) to erase the previous printed console line
    cout << "\33[2K\r";

    // function is called to interpret data
    interpretData(5, selectedRow, 0, totalElevation, methodElevation);
}

void interpretData(const int methodNum, const short row, const short column, const short elevation, vector<short> &methodElevation) {
// recieves method number, starting row, starting column, total elevation, and apmatrix containing method elevations as parameters
// outputs information on current path as well as a ranking comparing all drawn paths

    // methodName vector is declared and initialized
    vector<string> methodName;
    methodName.push_back("1 - Lowest of Greedy Walk rows from East to West");
    methodName.push_back("2 - Lowest of Greedy Walk rows favouring minimal elevation from East to West");
    methodName.push_back("3 - Lowest of Greedy Walks from the lowest elevation point of each column");
    methodName.push_back("4 - Lowest of Greedy Walks from every possible starting location");
    methodName.push_back("5 - Lowest of Floyd Warshall's shortest path algorithm");
    methodName.push_back("6 - Dijkstra's shortest path algorithm for selected row");

    // apmatrix containing method elevations is updated
    methodElevation[methodNum] = elevation;

    // method name, starting coordinates, and total elevation is outputted on console
    cout << "Pathfinding Method: " << methodName[methodNum] << endl;
    cout << "Starting Coordinates: (" << row << ", " << column << ")" << endl;
    cout << "Total Elevation: " << elevation << " meters" << endl << endl;

    vector <pair <short, short>> orderedMethods;

    // methods that have been drawn are added to a vector
    for (int i = 0; i < 6; i++) {
        if (methodElevation[i] != 0) {
            orderedMethods.push_back(make_pair(i, methodElevation[i]));
        }
    }

    // methods are sorted based on their elevation value (the second short in the pair)
    sort(orderedMethods.begin(), orderedMethods.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    // methods are outputted to console from lowest to greatest elevation value
    cout << "Methods Ordered by Efficiency:" << endl;

    for (int i = 0; i < orderedMethods.size(); i++) {
        cout << methodName[orderedMethods[i].first] << " (Elevation: " << orderedMethods[i].second << " meters)" << endl;
    }

    cout << endl;
}
