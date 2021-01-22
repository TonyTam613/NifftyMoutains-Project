/****************************************************************************************************************
 *  Tony Tam    Sept. 10, 2019  Nifty Mountains Assignment                                                      *
 *                                                                                                              *
 *  This program takes a file filled with Numbers                                                               *
 *  Indicating the elevations of a mountain                                                                     *
 *  Using the numbers, I drew a map                                                                             *
 *  Red being the lowest elevations, Blue being the middle elevations and Green being the highest elevations    *
 *  Using the elevations I drew paths through the mountain                                                      *
 *  The paths show the most efficient paths from each starting point                                            *
 *  where the elevation changes the least, the green path indicating the very best path                         *
 *                                                                                                              *
 *  Theres also a different method where it always chooses                                                      *
 *  the lowest elecation despite the size of the elevation change                                               *
 *  It displays them one after another to compare them.                                                         *
 ****************************************************************************************************************/
#include "Niffty Mountains Header.h"

//Declares and Initializes Global Variables
ALLEGRO_DISPLAY *display;
ALLEGRO_FONT *arial;

int main(int argc, char *argv[]) {

    //Declares and Initializes Variables
    srand(time(0));
    apmatrix<int> Square(ROWS, COLUMNS);
    apvector<int> Differences(ROWS);
    int LowestDifferenceIndex = 0;
    int Minimum = 0;
    int Maximum = 0;
    char fname[] = "Colorado.dat";
    bool bestLine = false;

    //Ends program is the files fails to open
    if (!MapDataDrawer(fname, Square)) {
        return 1;
    }

    //Finds the Max and Min of the Matrix
    Minimum = findMin(Square);
    Maximum = findMax(Square);

    //Initializes Allegro
    initializeAllegro(COLUMNS, ROWS + 50, "Map");

    //Draws the map to the window
    drawMap(Square, Maximum, Minimum);

    al_flip_display();

    //Finds and draws a path of lowest elevation change for each starting row and provides the total elevation change of each path
    for (int iRow = 0; iRow < ROWS; iRow++) {
        Differences[iRow] = drawLowestElevPath(Square, iRow, bestLine);
        al_flip_display();
    }

    //indicates that we are about to draw the best line (line of least elevation change)
    bestLine = true;

    //Finds which starting row has the path of least elevation
    LowestDifferenceIndex = indexOfLowestElevPath(Differences);

    //Draws the best line
    drawLowestElevPath(Square, LowestDifferenceIndex, bestLine);

    //Puts a Header telling the user which method is being displayed
    al_draw_text(arial, BLACK, 1, 1, ALLEGRO_ALIGN_LEFT, "Lowest Change in Elevation Method");

    al_flip_display();
    al_rest(5);

    //resets the screen to black
    al_clear_to_color(BLACK);
    al_flip_display();

    //Draws the map again
    drawMap(Square, Maximum, Minimum);
    al_flip_display();

    //Draws the paths using the second methos (always going towards the lowest elevation)
    for (int iRow = 0; iRow < ROWS; iRow++) {
        drawLowestPath(Square, iRow);
        al_flip_display();
    }

    //Puts the header indicating what method is being displayed
    al_draw_text(arial, BLACK, 1, 1, ALLEGRO_ALIGN_LEFT, "Goes Towards Lowest Elevation Method");
    al_flip_display();
    al_rest(5);

    al_destroy_display(display);
    al_destroy_font(arial);
    return 0;
}

int findMin(const apmatrix<int> &Square) {
    ifstream FileNumbers("Colorado.dat");
    int Minimum = Square[0][0];
    for (int iRow = 0; iRow < ROWS; iRow++) {
        for (int iCol = 0; iCol < COLUMNS; iCol++) {
            if (Square[iRow][iCol] < Minimum) {
                Minimum = Square[iRow][iCol];
            }
        }
    }
    return Minimum;
}
int findMax(const apmatrix<int> &Square) {
    int Maximum = Square[0][0];
    for (int iRow = 0; iRow < ROWS; iRow++) {
        for (int iCol = 0; iCol < COLUMNS; iCol++) {
            if (Square[iRow][iCol] > Maximum) {
                Maximum = Square[iRow][iCol];
            }
        }
    }
    return Maximum;
}
float ColourValue(int matrixNumber, int biggest, int smallest) {
    //assigns a value between 0-255 in order to convert it to a colour
    float colourNum = 0.0;
    colourNum = ((float(matrixNumber) - float(smallest)) / (float(biggest) - float(smallest))) * float(255);
    return colourNum;
}
int initializeAllegro(int width, int height, const char title[]) {

    // Initialize Allegro
    al_init();

    // initialize display
    display = al_create_display(width, height);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    al_set_window_title(display, title);

    // Initialize keyboard routines
    if (!al_install_keyboard()) {
        al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Initialize primative add on
    if (!al_init_primitives_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // initialize the font addon
    al_init_font_addon();
    // initialize the ttf (True Type Font) addon
    al_init_ttf_addon();

    //loads arial onto the font pointer
    arial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 43, 0);
    if (!arial) {
        al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_flip_display();
    return 0;
}
