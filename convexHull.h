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

#ifndef CONVEXHULL_H_INCLUDED
#define CONVEXHULL_H_INCLUDED

#include <vector>
#include "point.h"
#include <cmath>
#include "closest_pair.h"
#include <algorithm>
#include <stack>

using namespace std;

//doesn't need to be a class, can just be a function or set
//of functions for the convex hull algorithm, rather than
//keeping all of those functions in main.cpp and clogging it.


/*
 * description: finds the points belonging to the convex hull of a given set
 *      of points using a brute force algorithm
 * return: a vector of points
 * precondition: points contains at least 3 distinct points
 * postcondition: a vector of points containing the points in the convex hull
 *      is returned; the parameter, points, is unchanged after the function call
 *
*/
vector<point> * brute_ConvexHull(vector<point> points, SDL_Plotter &g);

/*
 * description: finds the points belonging to the convex hull of a given set
 *      of points using a divide and conquer algorithm
 * return: none
 * precondition: points contains at least 3 distinct points
 * postcondition: the convex hull is properly drawn
*/
void divideAndConquer_ConvexHull(SDL_Plotter &g,vector<point> points);


/*
 * description: determines if two points have the same coordinates
 * return: bool
 * precondition: points p1 and p2 exist
 * postcondition: returns true if the x and y coordinates of p1 and p2 are
 *      equal and false otherwise
 *
*/
bool operator==(point p1, point p2);

/*
 * description: comparator used to sort by a vector by angle
 * return: bool
 * precondition: pairs a and b exist
 * postcondition: returns true a is less than b, false otherwise
 *
*/
bool sortByAngle( pair<point,float> &a, pair<point,float> &b);

/*
 * description: gives the angle (in radians) that a line (made by the two
                                                points) and the x-axis make
 * return: float
 * precondition: points p1 and p0 exist
 * postcondition: returns the correct answer in radians
 *
*/
float getRadians(point p1,point p0);

/*
 * description: draws from each point in the stack and the point before it
 * return: none
 * precondition: the stack of points, the plotter, and size exist accurately
 * postcondition: the whole path is drawn to the screen with the plotter
 *
*/
void drawWholeStack(stack <point> values,SDL_Plotter&g,int size);

/*
 * description: checks if the turn can be considered a right hand turn
 * return: bool
 * precondition: points p,m, and n all exist
 * postcondition: returns true if the points represent a right hand turn
 *
*/
bool isRightHandTurn(point p, point m, point n);
#endif // CONVEXHULL_H_INCLUDED
