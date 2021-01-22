#include "Niffty Mountains Header.h"


int drawLowestElevPath(const apmatrix<int> &Square, int row, bool bestLine) {
    //declares and initializes variables
    int CurrentRow = row;
    int CurrentColumn = 0;
    int UpRightRow = 0;
    int DownRightRow = 0;
    int randomNumber = 0;
    int upDiff = 0;
    int downDiff = 0;
    int forwardsDiff = 0;
    int totalDiff = 0;
    ALLEGRO_COLOR LineColour;

    //Uses a yellow line if drawing the best line and Cyan if its a regular line
    if (!bestLine) {
        LineColour = al_map_rgb(0, 255, 255);
    } else {
        LineColour = al_map_rgb(255, 255, 0);
    }

    //Draws the paths and finds the total difference of the path
    while (CurrentColumn < (COLUMNS - 1)) {
        al_draw_pixel(CurrentColumn + 1, CurrentRow + 51, LineColour);

        UpRightRow = CurrentRow - 1;
        DownRightRow = CurrentRow + 1;

        if (DownRightRow >= ROWS) {
            DownRightRow = (ROWS - 1);
        }
        if (CurrentColumn > COLUMNS) {
            CurrentColumn = COLUMNS - 1;
        }
        if (CurrentRow < 0) {
            CurrentRow = 0;
        }
        if (CurrentRow >= ROWS) {
            CurrentRow = ROWS - 1;
        }
        if (UpRightRow < 0) {
            UpRightRow = 0;
        }

        //calucaltes the differences
        upDiff = abs(Square[UpRightRow][CurrentColumn + 1] - Square[CurrentRow][CurrentColumn]);
        downDiff = abs(Square[DownRightRow][CurrentColumn + 1] - Square[CurrentRow][CurrentColumn]);
        forwardsDiff = abs(Square[CurrentRow][CurrentColumn + 1] - Square[CurrentRow][CurrentColumn]);

        CurrentColumn++;

        //adds the differences to the total
        if ((upDiff < downDiff) && (upDiff < forwardsDiff)) {
            CurrentRow = UpRightRow;
            totalDiff += upDiff;
        } else if ((downDiff < upDiff) && (downDiff < forwardsDiff)) {
            CurrentRow = DownRightRow;
            totalDiff += downDiff;
        } else if ((forwardsDiff < downDiff) && (forwardsDiff < upDiff)) {
            totalDiff += forwardsDiff;
        } else if ((upDiff == forwardsDiff) && (upDiff == downDiff)) {
            totalDiff += forwardsDiff;
        } else if ((upDiff == forwardsDiff) && (upDiff != downDiff)) {
            totalDiff += forwardsDiff;
        } else if ((upDiff != forwardsDiff) && (upDiff == downDiff)) {
            randomNumber = rand() % 2 + 1;
            switch(randomNumber) {
            case 1 :
                CurrentRow = UpRightRow;
                totalDiff += upDiff;
                break;
            case 2 :
                CurrentRow = DownRightRow;
                totalDiff += downDiff;
                break;
            }
        } else if (forwardsDiff == downDiff) {
            totalDiff += forwardsDiff;
        }
    }
    return totalDiff;
}

bool MapDataDrawer(const char *fname, apmatrix<int> &Square) {
    //declares variables
    fstream FileNumbers(fname);
    int NumberHolder = 0;

    //returns false if file didn't open properly
    if (!FileNumbers.is_open()) {
        cout << "File not open" << endl;
        return false;
    }

    //extracts values from the file
    for (int iRow = 0; iRow < ROWS; iRow++) {
        for (int iCol = 0; iCol < COLUMNS; iCol++) {
            FileNumbers >> NumberHolder;
            Square[iRow][iCol] = NumberHolder;
        }
    }
    return true;
}

void drawMap(const apmatrix<int> &Square, int biggest, int smallest) {
    //declare vairables
    ALLEGRO_COLOR colour;
    float colourNum = 0;

    al_clear_to_color(al_map_rgb(255, 255, 255));

    //Draws the map using red blue and green to show the different elevations
    for (int iRow = 0; iRow < ROWS; iRow++) {
        for (int iCol = 0; iCol < COLUMNS; iCol++) {
            colourNum = ColourValue(Square[iRow][iCol], biggest, smallest);
            if (colourNum <= float(255 * 0.5)) {
                colour = al_map_rgb(colourNum, 0, 0);
            } else {
                colour = al_map_rgb(0, colourNum, 0);
            }
            al_draw_pixel(iCol + 1, iRow + 51, colour);
        }
    }
}

int indexOfLowestElevPath(const apvector<int> &elevationDiffs) {
    //Declares variables
    int lowestDiff = 0;
    int lowestDiffindex = 0;

    lowestDiff = elevationDiffs[0];

    //finds the index value for the lowest elevation difference
    for (int iRow = 0; iRow < ROWS; iRow++) {
        if (elevationDiffs[iRow] < lowestDiff) {
            lowestDiff = elevationDiffs[iRow];
            lowestDiffindex = iRow;
        }
    }
    return lowestDiffindex;
}

