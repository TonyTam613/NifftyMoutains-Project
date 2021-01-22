#include "Niffty Mountains Header.h"

void drawLowestPath(const apmatrix<int> &Square, int row) {
    //declares variables
    int CurrentRow = row;
    int CurrentColumn = 0;
    int UpRightRow = 0;
    int DownRightRow = 0;
    int randomNumber = 0;
    int upElev = 0;
    int downElev = 0;
    int forwardsElev = 0;
    ALLEGRO_COLOR LineColour;

    //sets line colour to Cyan
    LineColour = al_map_rgb(0, 255, 255);

    //Draws the paths using the new method
    while (CurrentColumn < (COLUMNS - 1)) {
        al_draw_pixel(CurrentColumn + 1, CurrentRow + 51, LineColour);

        UpRightRow = CurrentRow - 1;
        DownRightRow = CurrentRow + 1;

        if (DownRightRow >= ROWS) {
            DownRightRow = (ROWS - 1);
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

        upElev = Square[UpRightRow][CurrentColumn + 1];
        downElev = Square[DownRightRow][CurrentColumn + 1];
        forwardsElev = Square[CurrentRow][CurrentColumn + 1];

        CurrentColumn++;

        if ((upElev < downElev) && (upElev < forwardsElev)) {
            CurrentRow = UpRightRow;
        } else if ((downElev < upElev) && (downElev < forwardsElev)) {
            CurrentRow = DownRightRow;
        } else if ((forwardsElev < downElev) && (forwardsElev < upElev)) {
            CurrentRow += 0;
        } else if ((upElev != forwardsElev) && (upElev == downElev)) {
            randomNumber = rand() % 2 + 1;
            switch(randomNumber) {
            case 1 :
                CurrentRow = UpRightRow;
                break;
            case 2 :
                CurrentRow = DownRightRow;
                break;
            }
        }
    }
}
