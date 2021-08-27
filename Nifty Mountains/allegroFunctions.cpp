/*  Name: Keaton Lee
 *  Date: May 5, 2021
 *  Title: Nifty Mountains
 *
 *  Description: Contains functions pertaining to allegro, including allegro
 *  initialization, updates based on user input, and loading bar
*/

// include header files
#include "header.h"
#include "apmatrix.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <vector>

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;

bool initializeAllegro() {
// function recieves no parameters
// allegro is initialzed
// returns true if allegro is correctly initialized and false if it is not

    // allegro is initialized
	al_init();

    // allegro display is initialized
    display = al_create_display(COLUMNS, ROWS + 513);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // title is added to display
    al_set_window_title(display, "Keaton Lee: ICS4U - Nifty Mountains Assignment");

    // primitives addon is initialized
    if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return false;
	}

	// font addon is initialized
    if (!al_init_font_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize font add on", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // ttf addon is initialized
    if (!al_init_ttf_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize font ttf on", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // font (sniglet) is initialized
    font = al_load_ttf_font("sniglet.ttf", 18, 0);
    if (!font){
        al_show_native_message_box(display, "Error", "Error", "Could not load sniglet.ttf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // keyboard is initialized
    if (!al_install_keyboard()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize the keyboard", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // event queue is created
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // event sources are registered
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // returns true if allegro is correctly initialized
	return true;
}

bool userInput(const apmatrix<short> &elevations, apmatrix<bool> &filled, vector<short> &methodElevation) {
// recives apmatrix containing elevations, apmatrix containing drawn paths, and apmatrix containing method elevations as parameters
// waits for user input, and draws paths or changes visuals accordingly
// returns true if allegro display is closed or escape key is pressed

    // variables are declared
    int grayscale = false;                  // map is initialized to coloured by default
    vector<bool> methodDrawn(6, false);     // used to determine whether methods have already been drawn

    while (true) {

        // allegro event recieves user keyboard input
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                // if escape key is clicked, function returns true
                return true;

            } else if (ev.keyboard.keycode == ALLEGRO_KEY_1 && !methodDrawn[0]) {
                // if '1' is clicked and method hasn't been drawn, legend is updated and function to draw corresponding method is called
                updateLegend(0);
                indexOfLowestElevPath(elevations, filled, methodElevation);
                methodDrawn[0] = true;

            } else if (ev.keyboard.keycode == ALLEGRO_KEY_2 && !methodDrawn[1]) {
                // if '2' is clicked and method hasn't been drawn, legend is updated and function to draw corresponding method is called
                updateLegend(1);
                indexOfLowAsPossible(elevations, filled, methodElevation);
                methodDrawn[1] = true;

            } else if (ev.keyboard.keycode == ALLEGRO_KEY_3 && !methodDrawn[2]) {
                // if '3' is clicked and method hasn't been drawn, legend is updated and function to draw corresponding method is called
                updateLegend(2);
                indexOfLowestElevPoints(elevations, filled, methodElevation);
                methodDrawn[2] = true;

            } else if (ev.keyboard.keycode == ALLEGRO_KEY_4 && !methodDrawn[3]) {
                // if '4' is clicked and method hasn't been drawn, legend is updated and function to draw corresponding method is called
                updateLegend(3);
                indexOfEveryCoordinateGreedy(elevations, filled, methodElevation);
                methodDrawn[3] = true;

            } else if (ev.keyboard.keycode == ALLEGRO_KEY_5 && !methodDrawn[4]) {
                // if '5' is clicked and method hasn't been drawn, legend is updated and function to draw corresponding method is called
                updateLegend(4);
                floydWarshallAlgo(elevations, filled, methodElevation);
                methodDrawn[4] = true;

            } else if (ev.keyboard.keycode == ALLEGRO_KEY_6 && !methodDrawn[5]) {
                // if '6' is clicked and method hasn't been drawn, legend is updated and function to draw corresponding method is called
                updateLegend(5);
                indexOfDijkstraAlgo(elevations, filled, methodElevation);
                methodDrawn[5] = true;

            } else if (ev.keyboard.keycode == ALLEGRO_KEY_R) {
                // if 'R' is clicked, console, legend, and minimum elevation values are reset
                system("CLS");
                updateLegend(-1);
                methodElevation.assign(6, 0);

                // all values of apmatrix containing drawn paths are set to false
                for (int i = 0; i < ROWS; i++) {
                    for (int j = 0; j < COLUMNS; j++) {
                        filled[i][j] = false;
                    }
                }

                // methodDrawn vector is reset, so that all methods can be redrawn
                for (int i = 0; i < 6; i++) {
                    methodDrawn[i] = false;
                }

                // map is re-drawn
                drawMap(elevations, filled, grayscale);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_G) {
                // if 'G' is clicked, graphics are changed and map is redrawn
                grayscale = !grayscale;
                drawMap(elevations, filled, grayscale);
            }

        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // if allegro display is closed, function returns true
            return true;
        }

    }
}

void loadingBar(short percent) {
// recives a percentage as parameters
// illustrates current loding status on screen based on given percentage
    al_draw_filled_rectangle(0, ROWS, COLUMNS, ROWS + 30, LAVENDER1);

    if (percent == 100) {
        // draws title on screen when no paths are currently loading
        al_draw_text(font, BLACK, COLUMNS / 2, ROWS + 4, ALLEGRO_ALIGN_CENTRE, "Keaton Lee: ICS4U - Nifty Mountains Assignment");
    } else {
        // loading bar is drawn to screen based on the percent value
        al_draw_filled_rounded_rectangle(300, ROWS + 2, 300 + float(percent)/100*244, ROWS + 30 - 2, 3, 3, LAVENDER2);
        al_draw_rounded_rectangle(300, ROWS + 2, COLUMNS - 300, ROWS + 30 - 2, 3, 3, BLACK, 2);

        // the percent value is drawn to the screen above the loading bar
        al_draw_textf(font, BLACK, COLUMNS / 2, ROWS + 4, ALLEGRO_ALIGN_CENTRE, "%d%% Complete", percent);
    }
}
