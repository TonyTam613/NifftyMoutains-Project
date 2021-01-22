#ifndef NIFFTY_MOUNTAINS_HEADER_H_INCLUDED
#define NIFFTY_MOUNTAINS_HEADER_H_INCLUDED


#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <apmatrix.h>
#include <apvector.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define BLACK   al_map_rgb(0,0,0)

using namespace std;

int findMin(const apmatrix<int> &Square);
int findMax(const apmatrix<int> &Square);
bool MapDataDrawer(const char *fname, apmatrix<int> &Square);
void drawMap(const apmatrix<int> &Square, int biggest, int smallest);
float ColourValue(int matrixNumber, int biggest, int smallest);
int initializeAllegro(int width, int height, const char title[]);
int drawLowestElevPath(const apmatrix<int> &Square, int row, bool bestLine);
int indexOfLowestElevPath(const apvector<int> &elevationDiffs);
void drawLowestPath(const apmatrix<int> &Square, int row);

const int ROWS = 480;
const int COLUMNS = 844;



#endif // NIFFTY_MOUNTAINS_HEADER_H_INCLUDED
