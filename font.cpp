#include "font.h"

void fontClass::initLetter(){
    ifstream inFont;
    string trash;
    inFont.open("font.txt");

    // Import letters
    for(int i = 0; i < CHARCOUNT; i++) {
        inFont >> trash;
        for(int j = 0; j < ROWCOUNT; j++) {
            for(int k = 0; k < COLCOUNT; k++) {
                inFont >> letters[i][j][k];
            }
        }
    }
    inFont.close();
}

void fontClass::drawLetter(SDL_Plotter& g, int c, int r, letter ltr){
    int startX = c * 25;
    int startY = r * 25;

    //prints single character
    for(int row = 0; row < ROWCOUNT; row++) {
        for(int col = 0; col < COLCOUNT; col++) {
            if(letters[ltr][row][col] == '1') {
                g.plotPixel(col + startX, row + startY, 0,0,0);
            }
        }
    }
}

void fontClass::initNumber(){
    ifstream inNum;

    inNum.open("nums.txt");

    // Imports numbers
    for(int i = 0; i < NUMCOUNT; i++) {
        for(int j = 0; j < ROWCOUNT; j++) {
            for(int k = 0; k < COLCOUNT; k++) {
                inNum >> numbers[i][j][k];
            }

        }
    }
    inNum.close();
}

void fontClass::printNum(SDL_Plotter& g, int c, int r, int num)
{
    int startX = c * 25;
    int startY = r * 25;

    //prints single character
    for(int row = 0; row < ROWCOUNT; row++) {
        for(int col = 0; col < COLCOUNT; col++) {
            if(numbers[num][row][col] == 1) {
                g.plotPixel(col + startX, row + startY, 0,0,0);
            }
        }
    }
}

void fontClass::eraseLetter(SDL_Plotter& g, int c, int r, letter ltr){
    int startX = c * 25;
    int startY = r * 25;

    //prints single character
    for(int row = 0; row < ROWCOUNT; row++) {
        for(int col = 0; col < COLCOUNT; col++) {
            if(letters[ltr][row][col] == '1') {
                g.plotPixel(col + startX, row + startY, 255, 255, 255);
            }
        }
    }
}
