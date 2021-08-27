/*  Name: Keaton Lee
 *  Date: May 5, 2021
 *  Title: Nifty Mountains
 *
 *  Description: Contains functions for reading input file and drawing map
 *  based on corresponding topographic data
*/

// include header files
#include "header.h"
#include "apmatrix.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <fstream>
#include <iostream>

using namespace std;

bool mapDataDrawer(const char *fname, apmatrix<short> &elevations) {
// recives file name and apmatrix containing elevations as parameters
// reads input from data file into elevations apmatrix
// returns elevations apmatrix via pass by reference
// returns true if file is present and false if it is not

    // file stream is opened
    ifstream dataFile(fname);

    // checks if file is present
    if (!dataFile) {
        cout << "Data file not found" << endl;
        return false;
    }

    // data from file is read into elevations apmatrix
    for (int i = 0; i < elevations.numrows(); i++) {
        for (int j = 0; j < elevations.numcols(); j++) {
            dataFile >> elevations[i][j];
        }
    }

    // file stream is closed
    dataFile.close();

    // function returns true if file is present
    return true;
}

int findMin(const apmatrix<short> &elevations) {
// recieves apmatrix containing elevations as parameters
// determines smallest elevation value in matrix
// returns minimum elevation value
    int minElevation = elevations[0][0];

    for (int i = 0; i < elevations.numrows(); i++) {
        for (int j = 0; j < elevations.numcols(); j++) {
            // if any elevation is lower than the current lowest elevation, the minimum elevation is updated
            if (elevations[i][j] < minElevation) {
                minElevation = elevations[i][j];
            }
        }
    }

    // minimum elecation is returned
    return minElevation;
}

int findMax(const apmatrix<short> &elevations) {
// recieves apmatrix containing elevations as parameters
// determines largest elevation value in matrix
// returns maximum elevation value
    int maxElevation = elevations[0][0];

    for (int i = 0; i < elevations.numrows(); i++) {
        for (int j = 0; j < elevations.numcols(); j++) {
            // if any elevation is greater than the current lowest elevation, the maximum elevation is updated
            if (elevations[i][j] > maxElevation) {
                maxElevation = elevations[i][j];
            }
        }
    }

    // maximum elecation is returned
    return maxElevation;
}

void drawMap(const apmatrix<short> &elevations, apmatrix<bool> filled, bool grayscale) {
// recives apmatrix containing elevations, apmatrix containing drawn paths, and grayscale boolean as arguments
// draws map in either grayscale or colour and avoids drawing over drawn paths

    // variables are declared
    float colourValue;

    // minimum and maximum elevation are determined by calling respective functions
    int minElevation = findMin(elevations);
    int maxElevation = findMax(elevations);

    // map is drawn pixel by pixel
    if (grayscale) {
        for (int i = 0; i < elevations.numrows(); i++) {
            for (int j = 0; j < elevations.numcols(); j++) {
                // map is only updated on points where paths have not been drawn
                if (!filled[i][j]) {
                    // if map is grayscale, RGB values correspond to an appropriate grayscale value between white and black
                    // RGB values are scaled based on a range from the minimum to maximum elevation
                    colourValue = (float(elevations[i][j]) - minElevation) / (maxElevation - minElevation) * 255;
                    ALLEGRO_COLOR colour = al_map_rgb(colourValue, colourValue, colourValue);
                    al_draw_filled_rectangle(j, i, j + 1, i + 1, colour);
                }
            }
            al_flip_display();
        }
    } else {
        // variables are declared
        int red, green, blue;
        // vectors contain RGB values to draw map in colors other than a monochromatic scale
        vector<int> mapGreen{0, 20, 0};
        vector<int> mapBrown{181, 110, 29};
        for (int i = 0; i < elevations.numrows(); i++) {
            for (int j = 0; j < elevations.numcols(); j++) {
                // map is only updated on points where paths have not been drawn
                if (!filled[i][j]) {
                    colourValue = (float(elevations[i][j]) - minElevation) / (maxElevation - minElevation);

                    // appropriate colours are determined arithmetically using colour interpolation
                    red = (mapBrown[0] - mapGreen[0]) * colourValue + mapGreen[0];
                    green = (mapBrown[1] - mapGreen[1]) * colourValue + mapGreen[1];
                    blue = (mapBrown[2] - mapGreen[2]) * colourValue + mapGreen[2];

                    // colours are scaled so lower elevations are more green, while higher elevations are more brown
                    ALLEGRO_COLOR colour = al_map_rgb(red, green, blue);
                    al_draw_filled_rectangle(j, i, j + 1, i + 1, colour);
                }
            }
            al_flip_display();
        }

    }
}

