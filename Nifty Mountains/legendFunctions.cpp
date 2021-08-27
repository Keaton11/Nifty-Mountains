/*  Name: Keaton Lee
 *  Date: May 5, 2021
 *  Title: Nifty Mountains
 *
 *  Description: Contains functions to draw initial legend and make
 *  updates to legend
*/

// include header files
#include "header.h"
#include "apmatrix.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <vector>

extern ALLEGRO_FONT *font;

void drawLegend() {
// function recieves no parameters
// function draws initial legend to the screen
    // title is drawn directly below map
    al_draw_filled_rectangle(0, ROWS, COLUMNS, ROWS + 30, LAVENDER1);
    al_draw_text(font, BLACK, COLUMNS / 2, ROWS + 4, ALLEGRO_ALIGN_CENTRE, "Keaton Lee: ICS4U - Nifty Mountains Assignment");

    // legend displays the different buttons the user can click to draw corresponding paths
    al_draw_text(font, WHITE, 10, ROWS + 34, ALLEGRO_ALIGN_LEFT, "Click 1 to run through Greedy Walk rows from East to West");
    al_draw_text(font, WHITE, 10, ROWS + 60, ALLEGRO_ALIGN_LEFT, "Click 2 to run through Greedy Walk rows favouring minimal elevation from East to West");
    al_draw_text(font, WHITE, 10, ROWS + 86, ALLEGRO_ALIGN_LEFT, "Click 3 to run through Greedy Walks from the lowest elevation point of each column");
    al_draw_text(font, WHITE, 10, ROWS + 112, ALLEGRO_ALIGN_LEFT, "Click 4 to run through all Greedy Walks from every possible starting location (Slow)");
    al_draw_text(font, WHITE, 10, ROWS + 138, ALLEGRO_ALIGN_LEFT, "Click 5 to run through Floyd Warshall's shortest path algorithm");
    al_draw_text(font, WHITE, 10, ROWS + 164, ALLEGRO_ALIGN_LEFT, "Click 6 to run through Dijkstra's shortest path algorithm (Very Slow)");

    // default update legend function is called
    updateLegend(-1);

    // legend displays the different buttons the user can click to update the map
    al_draw_filled_rectangle(0, ROWS + 454, COLUMNS, ROWS + 513, LAVENDER1);
    al_draw_text(font, BLACK, 10, ROWS + 458, ALLEGRO_ALIGN_LEFT, "Click R to reset map");
    al_draw_text(font, BLACK, 10, ROWS + 484, ALLEGRO_ALIGN_LEFT, "Click G to change the graphics of the map");
    al_draw_text(font, BLACK, COLUMNS - 10, ROWS + 458, ALLEGRO_ALIGN_RIGHT, "See console for path analysis and comparison");
    al_draw_text(font, BLACK, COLUMNS - 10, ROWS + 484, ALLEGRO_ALIGN_RIGHT, "Click escape or close panel to exit");

    al_flip_display();
}

void updateLegend(const int methodNum) {
// function recives method number which corresponds to the path finding method that has been called
// legend is updated accordingly (coloured legend boxes appear for paths that have been drawn)
    switch (methodNum) {
        case -1:
            // default legens is drawn
            al_draw_filled_rectangle(0, ROWS + 192, COLUMNS, ROWS + 454, WHITE);

            // empty boxes and titles are drawn in grey (they become colourized once the corresponding path has been drawn
            for (int i = 0; i < 10; i++) {
                al_draw_rounded_rectangle(10, ROWS + 198 + 26 * i, 28, ROWS + 216 + 26 * i, 3, 3, GREY, 2);
            }

            al_draw_text(font, GREY, 35, ROWS + 196, ALLEGRO_ALIGN_LEFT, "1: Greedy Walk rows from East to West");
            al_draw_text(font, GREY, 35, ROWS + 222, ALLEGRO_ALIGN_LEFT, "1: Lowest of Greedy Walk rows from East to West");
            al_draw_text(font, GREY, 35, ROWS + 248, ALLEGRO_ALIGN_LEFT, "2: Greedy Walk rows favouring minimal elevation from East to West");
            al_draw_text(font, GREY, 35, ROWS + 274, ALLEGRO_ALIGN_LEFT, "2: Lowest of Greedy Walk rows favouring minimal elevation from East to West");
            al_draw_text(font, GREY, 35, ROWS + 300, ALLEGRO_ALIGN_LEFT, "3: Lowest elevation point of each column");
            al_draw_text(font, GREY, 35, ROWS + 326, ALLEGRO_ALIGN_LEFT, "3: Greedy Walks from the lowest elevation point of each column");
            al_draw_text(font, GREY, 35, ROWS + 352, ALLEGRO_ALIGN_LEFT, "3: Lowest of Greedy Walks from the lowest elevation point of each column");
            al_draw_text(font, GREY, 35, ROWS + 378, ALLEGRO_ALIGN_LEFT, "4: Greedy Walks from every possible starting location");
            al_draw_text(font, GREY, 35, ROWS + 404, ALLEGRO_ALIGN_LEFT, "5: Floyd Warshall's shortest path algorithm");
            al_draw_text(font, GREY, 35, ROWS + 430, ALLEGRO_ALIGN_LEFT, "6: Dijkstra's shortest path algorithm");
            break;
        case 0:
            // if method 0 has been called, legend is updated accordingly
            // titles for method 0 are re-drawn in black, and corresponding empty boxes are coloured red
            al_draw_text(font, BLACK, 35, ROWS + 196, ALLEGRO_ALIGN_LEFT, "1: Greedy Walk rows from East to West");
            al_draw_text(font, BLACK, 35, ROWS + 222, ALLEGRO_ALIGN_LEFT, "1: Lowest of Greedy Walk rows from East to West");

            al_draw_filled_rounded_rectangle(10, ROWS + 198, 28, ROWS + 216, 3, 3, RED1);
            al_draw_filled_rounded_rectangle(10, ROWS + 198 + 26 * 1, 28, ROWS + 216 + 26 * 1, 3, 3, RED2);

            al_draw_rounded_rectangle(10, ROWS + 198, 28, ROWS + 216, 3, 3, BLACK, 2);
            al_draw_rounded_rectangle(10, ROWS + 198 + 26 * 1, 28, ROWS + 216 + 26 * 1, 3, 3, BLACK, 2);
            break;
        case 1:
            // if method 1 has been called, legend is updated accordingly
            // titles for method 1 are re-drawn in black, and corresponding empty boxes are coloured green
            al_draw_text(font, BLACK, 35, ROWS + 248, ALLEGRO_ALIGN_LEFT, "2: Greedy Walk rows favouring minimal elevation from East to West");
            al_draw_text(font, BLACK, 35, ROWS + 274, ALLEGRO_ALIGN_LEFT, "2: Lowest of Greedy Walk rows favouring minimal elevation from East to West");

            al_draw_filled_rounded_rectangle(10, ROWS + 198 + 26 * 2, 28, ROWS + 216 + 26 * 2, 3, 3, GREEN1);
            al_draw_filled_rounded_rectangle(10, ROWS + 198 + 26 * 3, 28, ROWS + 216 + 26 * 3, 3, 3, GREEN2);

            al_draw_rounded_rectangle(10, ROWS + 198 + 26 * 2, 28, ROWS + 216 + 26 * 2, 3, 3, BLACK, 2);
            al_draw_rounded_rectangle(10, ROWS + 198 + 26 * 3, 28, ROWS + 216 + 26 * 3, 3, 3, BLACK, 2);
            break;
        case 2:
            // if method 2 has been called, legend is updated accordingly
            // titles for method 2 are re-drawn in black, and corresponding empty boxes are coloured blue
            al_draw_text(font, BLACK, 35, ROWS + 300, ALLEGRO_ALIGN_LEFT, "3: Lowest elevation point of each column");
            al_draw_text(font, BLACK, 35, ROWS + 326, ALLEGRO_ALIGN_LEFT, "3: Greedy Walks from the lowest elevation point of each column");
            al_draw_text(font, BLACK, 35, ROWS + 352, ALLEGRO_ALIGN_LEFT, "3: Lowest of Greedy Walks from the lowest elevation point of each column");

            al_draw_filled_rounded_rectangle(10, ROWS + 198 + 26 * 4, 28, ROWS + 216 + 26 * 4, 3, 3, BLUE1);
            al_draw_filled_rounded_rectangle(10, ROWS + 198 + 26 * 5, 28, ROWS + 216 + 26 * 5, 3, 3, BLUE2);
            al_draw_filled_rounded_rectangle(10, ROWS + 198 + 26 * 6, 28, ROWS + 216 + 26 * 6, 3, 3, BLUE3);

            al_draw_rounded_rectangle(10, ROWS + 198 + 26 * 4, 28, ROWS + 216 + 26 * 4, 3, 3, BLACK, 2);
            al_draw_rounded_rectangle(10, ROWS + 198 + 26 * 5, 28, ROWS + 216 + 26 * 5, 3, 3, BLACK, 2);
            al_draw_rounded_rectangle(10, ROWS + 198 + 26 * 6, 28, ROWS + 216 + 26 * 6, 3, 3, BLACK, 2);
            break;
        case 3:
            // if method 3 has been called, legend is updated accordingly
            // title for method 3 is re-drawn in black, and corresponding empty box is coloured yello
            al_draw_text(font, BLACK, 35, ROWS + 378, ALLEGRO_ALIGN_LEFT, "4: Greedy Walks from every possible starting location");

            al_draw_filled_rounded_rectangle(10, ROWS + 198 + 26 * 7, 28, ROWS + 216 + 26 * 7, 3, 3, YELLOW);

            al_draw_rounded_rectangle(10, ROWS + 198 + 26 * 7, 28, ROWS + 216 + 26 * 7, 3, 3, BLACK, 2);
            break;
        case 4:
            // if method 4 has been called, legend is updated accordingly
            // title for method 4 is re-drawn in black, and corresponding empty box is coloured purple
            al_draw_text(font, BLACK, 35, ROWS + 404, ALLEGRO_ALIGN_LEFT, "5: Floyd Warshall's shortest path algorithm");

            al_draw_filled_rounded_rectangle(10, ROWS + 198 + 26 * 8, 28, ROWS + 216 + 26 * 8, 3, 3, PURPLE);

            al_draw_rounded_rectangle(10, ROWS + 198 + 26 * 8, 28, ROWS + 216 + 26 * 8, 3, 3, BLACK, 2);
            break;
        case 5:
            // if method 5 has been called, legend is updated accordingly
            // title for method 5 is re-drawn in black, and corresponding empty box is coloured orange
            al_draw_text(font, BLACK, 35, ROWS + 430, ALLEGRO_ALIGN_LEFT, "6: Dijkstra's shortest path algorithm");

            al_draw_filled_rounded_rectangle(10, ROWS + 198 + 26 * 9, 28, ROWS + 216 + 26 * 9, 3, 3, ORANGE2);

            al_draw_rounded_rectangle(10, ROWS + 198 + 26 * 9, 28, ROWS + 216 + 26 * 9, 3, 3, BLACK, 2);
            break;
        default:
            break;
    }
}

