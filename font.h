/*
* Author: Zac Steudel, Chase Manseth, Gennie Mansi, Reece Kemball-Cook, Bob Rein
* Assignment Title: CSI 3344 Spring 2019 Group Project
* Assignment Description: This program uses C++ and the SDL to graphically
*   represent the runtime characteristics of the brute force closest pair,
*   D/C closest pair, brute force convex hull, and D/C convex hull algorithms
* Due Date: 04/02/2019
* Date Created: 03/06/2019
* Date Last Modified: 04/14/2019
 */
#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <fstream>
#include "SDL_Plotter.h"
#include <sstream>
#include "color_rgb.h"
#include <string>
#include <cstdlib>

const int CHARCOUNT = 37;
const int TOTAL_COLORS = 12;
const int COLCOUNT = 25;
const int ROWCOUNT = 25;
const int NUMCOUNT = 10;
enum letter{a = 0,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,colon};


class fontClass{
public:
    color_rgb color;
    int currentColor;
    char letters[CHARCOUNT][COLCOUNT][ROWCOUNT];
    int numbers[NUMCOUNT][COLCOUNT][ROWCOUNT];
    /*
     * Description: The function reads the data from
     *              "font.txt" to the three-dimensional array font
     * Return: none
     * Precondition: "font.txt" has data
     * Postcondition: the font array has enough data to print the alphabet
     */
    void initLetter();
    /*
     * Description: A single letter is drawn
     * Return: none
     * Precondition: g, c, r, and ltr exist
     * Postcondition: A letter, indicated by the enum ltr,
     *                is drawn to the SDL Plotter
     */
    void drawLetter(SDL_Plotter& g, int c, int r, letter ltr);
    /*
     * Description: The function reads the data from
     *              "nums.txt" to the three-dimensional array font
     * Return: none
     * Precondition: "nums.txt" has data
     * Postcondition: the font array has enough data
     *                to print the numbers 0-9
     */
    void initNumber();
    /*
     * Description: A single number is drawn
     * Return: none
     * Precondition: g, c, r, and num exist
     * Postcondition: A number is displayed the SDL Plotter
     */
    void printNum(SDL_Plotter& g, int c, int r, int num);

    void eraseLetter(SDL_Plotter& g, int c, int r, letter ltr);

    void setColor(color_rgb c);

    void nextColor();

};


#endif // FONT_H_INCLUDED
