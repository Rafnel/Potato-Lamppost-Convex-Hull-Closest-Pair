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
#include <iostream>
#include "SDL_Plotter.h"
#include "closest_pair.h"
#include "convexHull.h"
#include <unordered_set>

const int ROW_MAX = 500;
const int COL_MAX = 1000;

using namespace std;
/*
blackOut

description: function will black out the screen for the main menu.
return: none
precondition: g must be a valid sdl_plotter object.
postcondition: the sdl_plotter window will be blacked out.
*/
void blackOut(SDL_Plotter &g);
/*
titleGroup

description: function will display the title to the main menu.
return: none
precondition: g must be a valid sdl_plotter object.
postcondition: the sdl_plotter window will have the group name written.
*/
void titleGroup(SDL_Plotter &p1);
/*
BFCP_option

description: function will display the brute force CP menu option.
return: none
precondition: g must be a valid sdl_plotter object.
postcondition: the sdl_plotter window will show the BFCP option.
*/
void BFCP_option(SDL_Plotter &p1);
/*
DCCH_option

description: function will display the divide and conquer CH menu option.
return: none
precondition: g must be a valid sdl_plotter object.
postcondition: the sdl_plotter window will show the DCCH option.
*/
void DCCH_option(SDL_Plotter &p1);
/*
DCCP_option

description: function will display the divide and conquer CP menu option.
return: none
precondition: g must be a valid sdl_plotter object.
postcondition: the sdl_plotter window will show the DCCP option.
*/
void DCCP_option(SDL_Plotter &p1);
/*
BFCH_option

description: function will display the brute force CH menu option.
return: none
precondition: g must be a valid sdl_plotter object.
postcondition: the sdl_plotter window will show the BFCH option.
*/
void BFCH_option(SDL_Plotter &p1);
/*
secondTitle

description: function will display the second title screen which
allows the user to select the data set size for their algorithm
of choice.
return: none
precondition: g must be a valid sdl_plotter object.
postcondition: the sdl_plotter window will show the second main menu.
*/
void secondTitle(SDL_Plotter &p1);
/*
displaySizes

description: function will display the sizes of the data sets for
the user to choose from.
return: none
precondition: g must be a valid sdl_plotter object.
postcondition: the sdl_plotter window will show the data set options
*/
void displaySizes(SDL_Plotter &p1);
/*
drawMenu

description: function will display the initial menu of the group
project.
return: none
precondition: g must be a valid sdl_plotter object.
postcondition: the sdl_plotter window will show the main menu.
*/
void drawMenu(SDL_Plotter &g);

/*
main

description: function will have a master loop in which the user is
shown a main menu and have the choice to select certain algorithms
to show and data set sizes for each algorithm. Once selected,
the algorithm will run and will then allow the user to exit back
to the main menu.
return: int
precondition: none
postcondition: the user will have been allowed to view different
algorithms for closest pair and convex hull problems.
*/
int main(int argc, char* argv[])
{
    bool userHit = false;
    SDL_Plotter g(ROW_MAX, COL_MAX);
    g.update();
    vector<point> points;

    drawMenu(g);

    char op;
    int dataSize;
    while(!g.getQuit()){

        if(g.kbhit() && !userHit){
            g.clear();
            points.clear();

            if(g.getKey() == 'P' || g.getKey() == 'H' ||
               g.getKey() == 'C' || g.getKey() == 'V'){
                op = g.getKey();
                blackOut(g);
                secondTitle(g);
                userHit = true;
                displaySizes(g);
                g.update();

            }

        }
        if(g.kbhit() && userHit){
            if(g.getKey() == 'A' || g.getKey() == 'B' ||
               g.getKey() == 'C' || g.getKey() == 'D'){
                userHit = false;

                if(g.getKey() == 'A'){
                   dataSize = 10;
                }
                if(g.getKey() == 'B'){
                   dataSize = 50;
                }
                if(g.getKey() == 'C'){
                   dataSize = 150;
                }
                if(g.getKey() == 'D'){
                   dataSize = 500;
                }

                srand(time(NULL));
                for(int i = 0; i < dataSize; i++){
                    int x = (rand() % 980) +10;
                    int y = (rand() % 430) + 20;
                    point p(x, y);

                    points.push_back(p);
                }

                g.clear();
                g.update();
                if(op == 'P'){
                    brute_ClosestPair(g, points);
                }
                if(op == 'H'){
                    brute_ConvexHull(points, g);
                }
                if(op == 'C'){
                    pair<point, point> p;
                    divconq_ClosestPair(g, points, true, p, points);
                }
                if(op == 'V'){
                    running(g, false);
                    divideAndConquer_ConvexHull(g,points);
                    running(g, true);
                    finished(g, false);
                    g.update();
                }

                while(!g.kbhit()){}
                drawMenu(g);
            }
        }
    }
    return 0;
}

void blackOut(SDL_Plotter &g){
    for(int i = 0; i < g.getCol(); i++){
        for(int j = 0; j < g.getRow(); j++){
            g.plotPixel(i, j, 0, 0, 0);
        }
    }
}

void titleGroup(SDL_Plotter &p1){
    fontClass fo;
    fo.initLetter();
    int startX = 10;
    //begin drawing title
    fo.nextColor();
    fo.drawLetter(p1, startX, 1, g);
    fo.nextColor();
    fo.drawLetter(p1, startX + 1, 1, r);
    fo.nextColor();
    fo.drawLetter(p1, startX + 2, 1, o);
    fo.nextColor();
    fo.drawLetter(p1, startX + 3, 1, u);
    fo.nextColor();
    fo.drawLetter(p1, startX + 4, 1, p);
    fo.nextColor();
    fo.drawLetter(p1, startX + 6, 1, p);
    fo.nextColor();
    fo.drawLetter(p1, startX + 7, 1, o);
    fo.nextColor();
    fo.drawLetter(p1, startX + 8, 1, t);
    fo.nextColor();
    fo.drawLetter(p1, startX + 9, 1, a);
    fo.nextColor();
    fo.drawLetter(p1, startX + 10, 1, t);
    fo.nextColor();
    fo.drawLetter(p1, startX + 11, 1, o);
    fo.nextColor();
    fo.drawLetter(p1, startX + 13, 1, l);
    fo.nextColor();
    fo.drawLetter(p1, startX + 14, 1, a);
    fo.nextColor();
    fo.drawLetter(p1, startX + 15, 1, m);
    fo.nextColor();
    fo.drawLetter(p1, startX + 16, 1, p);
    fo.nextColor();
    fo.drawLetter(p1, startX + 17, 1, o);
    fo.nextColor();
    fo.drawLetter(p1, startX + 18, 1, s);
    fo.nextColor();
    fo.drawLetter(p1, startX + 19, 1, t);
}

void BFCP_option(SDL_Plotter &p1){
	fontClass fo;
	fo.initLetter();
	int startX = 9;
	int y = 5;
	fo.nextColor();

	// begin drawing first option
	fo.drawLetter(p1, startX + 0, y, b);
	fo.drawLetter(p1, startX + 1, y, r);
	fo.drawLetter(p1, startX + 2, y, u);
	fo.drawLetter(p1, startX + 3, y, t);
	fo.drawLetter(p1, startX + 4, y, e);

	fo.drawLetter(p1, startX + 6, y, f);
	fo.drawLetter(p1, startX + 7, y, o);
	fo.drawLetter(p1, startX + 8, y, r);
	fo.drawLetter(p1, startX + 9, y, c);
	fo.drawLetter(p1, startX + 10, y, e);

	fo.drawLetter(p1, startX + 12, y, c);
	fo.drawLetter(p1, startX + 13, y, l);
	fo.drawLetter(p1, startX + 14, y, o);
	fo.drawLetter(p1, startX + 15, y, s);
	fo.drawLetter(p1, startX + 16, y, e);
	fo.drawLetter(p1, startX + 17, y, s);
	fo.drawLetter(p1, startX + 18, y, t);

	fo.drawLetter(p1, startX + 20, y, p);
	fo.drawLetter(p1, startX + 21, y, a);
	fo.drawLetter(p1, startX + 22, y, i);
	fo.drawLetter(p1, startX + 23, y, r);
	fo.drawLetter(p1, startX + 24, y, colon);

	fo.drawLetter(p1, startX + 26, y, p);
}

void BFCH_option(SDL_Plotter &p1){
	fontClass fo;
	fo.initLetter();
	int startX = 9;
	int y = 7;
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();

	// begin drawing first option
	fo.drawLetter(p1, startX + 0, y, b);
	fo.drawLetter(p1, startX + 1, y, r);
	fo.drawLetter(p1, startX + 2, y, u);
	fo.drawLetter(p1, startX + 3, y, t);
	fo.drawLetter(p1, startX + 4, y, e);

	fo.drawLetter(p1, startX + 6, y, f);
	fo.drawLetter(p1, startX + 7, y, o);
	fo.drawLetter(p1, startX + 8, y, r);
	fo.drawLetter(p1, startX + 9, y, c);
	fo.drawLetter(p1, startX + 10, y, e);

	fo.drawLetter(p1, startX + 12, y, c);
	fo.drawLetter(p1, startX + 13, y, o);
	fo.drawLetter(p1, startX + 14, y, n);
	fo.drawLetter(p1, startX + 15, y, v);
	fo.drawLetter(p1, startX + 16, y, e);
	fo.drawLetter(p1, startX + 17, y, x);

	fo.drawLetter(p1, startX + 19, y, h);
	fo.drawLetter(p1, startX + 20, y, u);
	fo.drawLetter(p1, startX + 21, y, l);
	fo.drawLetter(p1, startX + 22, y, l);
	fo.drawLetter(p1, startX + 23, y, colon);

	fo.drawLetter(p1, startX + 26, y, h);
}

void DCCP_option(SDL_Plotter &p1){
	fontClass fo;
	fo.initLetter();
	int startX = 9;
	int y = 11;
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();

	// begin drawing first option
	fo.drawLetter(p1, startX + 0, y, d);
	fo.drawLetter(p1, startX + 1, y, c);

	fo.drawLetter(p1, startX + 3, y, c);
	fo.drawLetter(p1, startX + 4, y, l);
	fo.drawLetter(p1, startX + 5, y, o);
	fo.drawLetter(p1, startX + 6, y, s);
	fo.drawLetter(p1, startX + 7, y, e);
	fo.drawLetter(p1, startX + 8, y, s);
	fo.drawLetter(p1, startX + 9, y, t);

	fo.drawLetter(p1, startX + 11, y, p);
	fo.drawLetter(p1, startX + 12, y, a);
	fo.drawLetter(p1, startX + 13, y, i);
	fo.drawLetter(p1, startX + 14, y, r);
	fo.drawLetter(p1, startX + 15, y, colon);

	fo.drawLetter(p1, startX + 17, y, c);
}

void DCCH_option(SDL_Plotter &p1){
	fontClass fo;
	fo.initLetter();
	int startX = 9;
	int y = 13;
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();

	// begin drawing first option
	fo.drawLetter(p1, startX + 0, y, d);
	fo.drawLetter(p1, startX + 1, y, c);

	fo.drawLetter(p1, startX + 3, y, c);
	fo.drawLetter(p1, startX + 4, y, o);
	fo.drawLetter(p1, startX + 5, y, n);
	fo.drawLetter(p1, startX + 6, y, v);
	fo.drawLetter(p1, startX + 7, y, e);
	fo.drawLetter(p1, startX + 8, y, x);

	fo.drawLetter(p1, startX + 10, y, h);
	fo.drawLetter(p1, startX + 11, y, u);
	fo.drawLetter(p1, startX + 12, y, l);
	fo.drawLetter(p1, startX + 13, y, l);
	fo.drawLetter(p1, startX + 14, y, colon);

	fo.drawLetter(p1, startX + 17, y, v);
}

void secondTitle(SDL_Plotter &p1){
	fontClass fo;
	fo.initLetter();
	int startX = 10;
	int y = 5;
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();
	fo.nextColor();
    fo.nextColor();
    fo.nextColor();
    fo.nextColor();


	// begin drawing first option
	fo.drawLetter(p1, startX + 0, y, p);
	fo.drawLetter(p1, startX + 1, y, i);
	fo.drawLetter(p1, startX + 2, y, c);
	fo.drawLetter(p1, startX + 3, y, k);

	fo.drawLetter(p1, startX + 5, y, a);

	fo.drawLetter(p1, startX + 7, y, d);
	fo.drawLetter(p1, startX + 8, y, a);
	fo.drawLetter(p1, startX + 9, y, t);
	fo.drawLetter(p1, startX + 10, y, a);
	fo.drawLetter(p1, startX + 11, y, s);
	fo.drawLetter(p1, startX + 12, y, e);
	fo.drawLetter(p1, startX + 13, y, t);

	fo.drawLetter(p1, startX + 15, y, s);
	fo.drawLetter(p1, startX + 16, y, i);
	fo.drawLetter(p1, startX + 17, y, z);
	fo.drawLetter(p1, startX + 18, y, e);
	fo.drawLetter(p1, startX + 19, y, colon);

}

void displaySizes(SDL_Plotter &p1){
	fontClass fo;
	fo.initNumber();
	fo.initLetter();
	int startX = 11;
	int startY = 10;
	fo.nextColor();
	fo.nextColor();


	fo.drawLetter(p1, startX + 0, startY, a);
	fo.printNum(p1, startX + 0, startY + 2, 1);
	fo.printNum(p1, startX + 1, startY + 2, 0);
	fo.nextColor();

	fo.drawLetter(p1, startX + 5, startY, b);
	fo.printNum(p1, startX + 5, startY + 2, 5);
	fo.printNum(p1, startX + 6, startY + 2, 0);
	fo.nextColor();

	fo.drawLetter(p1, startX + 11, startY, c);
	fo.printNum(p1, startX + 10, startY + 2, 1);
    fo.printNum(p1, startX + 11, startY + 2, 5);
	fo.printNum(p1, startX + 12, startY + 2, 0);
	fo.nextColor();

	fo.drawLetter(p1, startX + 16, startY, d);
	fo.printNum(p1, startX + 15, startY + 2, 5);
	fo.printNum(p1, startX + 16, startY + 2, 0);
	fo.printNum(p1, startX + 17, startY + 2, 0);
}

void drawMenu(SDL_Plotter &g){
    //fill the screen with black
    blackOut(g);
    BFCP_option(g);
    BFCH_option(g);
    DCCP_option(g);
    DCCH_option(g);
    titleGroup(g);
    g.update();
}
