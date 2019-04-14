/*
* Author: Zac Steudel, Chase Manseth, Gennie Mansi, Reece Kemball-Cook, Bob Rein
* Assignment Title: CSI 3344 Spring 2019 Group Project
* Assignment Description: This program uses C++ and the SDL to graphically
*   represent the runtime characteristics of the brute force closest pair,
*   D/C closest pair, brute force convex hull, and D/C convex hull algorithms
* Due Date: 04/02/2019
* Date Created: 03/06/2019
* Date Last Modified: 04/01/2019
 */
#include "font.h"

void fontClass::initLetter(){
    color.setR(0);
    color.setB(0);
    color.setG(0);
    currentColor = 0;

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
                g.plotPixel(col + startX, row + startY,
                            color.getR(),color.getB(),color.getG());
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
                g.plotPixel(col + startX, row + startY,
                            color.getR(),color.getB(),color.getG());
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

void fontClass::setColor(color_rgb c){
    color = c;
}

void fontClass::nextColor() {
    // These are all the colors curves can get plotted in.
    color_rgb colorPossibilities[TOTAL_COLORS] = { color_rgb(255,255,255),
                                         color_rgb(255,0,0),
                                         color_rgb(255,128,0),
                                         color_rgb(255,255,0),
                                         color_rgb(128,255,0),
                                         color_rgb(0,255,255),
                                         color_rgb(0,128,255),
                                         color_rgb(0,0,255),
                                         color_rgb(127,0,255),
                                         color_rgb(255,0,255),
                                         color_rgb(255,0,127),
                                         color_rgb(128,128,128)};
    // currentColor is incremented in such a way that it will loop through
    // all the indices of colorPossibilities.
    currentColor = (currentColor + 1)%TOTAL_COLORS;
    // After the index of the currentColor is updated, we update the data
    // member color to reflect the new color.
    color = colorPossibilities[currentColor];
}
