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

#ifndef CLOSEST_PAIR_H_INCLUDED
#define CLOSEST_PAIR_H_INCLUDED

#include <vector>
#include "point.h"
#include <cmath>
#include "line.h"
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "convexHull.h"
#include <time.h>
#include "font.h"

using namespace std;

/*
 * description: calculates the Euclidean distance between two points
 * return: double
 * precondition: p1 and p2 exist and represent the two points whose distance
 *      we want to find
 * postcondition: returns the Euclidean ("straight line") distance between
 *      two points
 *
*/
double distance(point p1, point p2);

/*
 * description: finds closest distance between any two points belonging
 *      to a given set using a brute force algorithm
 * return: double
 * precondition: points contains at least 2 distinct points
 * postcondition: the closest distance between two points in the set is
 *      returned; the parameter, points, is unchanged after the function call
 *
*/
double brute_ClosestPair(SDL_Plotter &g, vector<point> points);

/*
 * description: finds closest distance between any two points belonging
 *      to a given set using a divide and conquer algorithm
 * return: double
 * precondition: points contains at least 2 distinct points
 * postcondition: the closest distance between two points in the set is
 *      returned; the parameter, points, is unchanged after the function call
 *
*/
double divconq_ClosestPair(SDL_Plotter &g, vector<point> points, bool topLevel,
                           pair<point, point> &best, vector<point> &orig);

/*
 * description: compares the y coordinates of two points
 * return: bool
 * precondition: p1 and p2 exist and represent the two points whose y
 *      coordinates we wish to compare
 * postcondition: returns true if the value of p1's y coordinate is less than
 *      the value of p2's y coordinate
 *
*/
bool yComparator(point p1, point p2);

/*
 * description: compares the x coordinates of two points
 * return: bool
 * precondition: p1 and p2 exist and represent the two points whose x
 *      coordinates we wish to compare
 * postcondition: returns true if the value of p1's x coordinate is less than
 *      the value of p2's x coordinate
 *
*/
bool xComparator(point p1, point p2);

/*
 * description: Plots a set of given points
 * return: none
 * precondition: The SDL_Plotter object exists
 * postcondition: The set of points in the points vector is plotted and
 *    displayed by SDL_Plotter
 *
*/
void plotPoints(SDL_Plotter &g, vector<point> points);

/*
 * description: Draws a small rectangle (used in helping make individual
 *    points visible on the SDL_Plotter screen)
 * return: none
 * precondition: The SDL_Plotter object exists; p can be drawn in the window
 * postcondition: A small rectangle is drawn at the coordinate 
 *    represented by p
 *
*/
void drawRect(SDL_Plotter &g, point p);

/*
 * description: Displays or erases the word 'running' across the top of 
 *    the window
 * return: none
 * precondition: The SDL_Plotter object exists
 * postcondition: The word 'running' is displayed across the top of the 
 *    window; if er = true, then the word 'running' is erased instead
 *
*/
void running(SDL_Plotter &g, bool er);

/*
 * description: Displays the word 'finished' across the top of 
 *    the window
 * return: none
 * precondition: The SDL_Plotter object exists
 * postcondition: The word 'running' is displayed across the top of the 
 *    window; the value of er here does not have any impact on the result
 *
*/
void finished(SDL_Plotter &g, bool er);

#endif // CLOSEST_PAIR_H_INCLUDED
