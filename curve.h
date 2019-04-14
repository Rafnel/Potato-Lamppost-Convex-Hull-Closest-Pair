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

/*
 * This file contains the class declaration and function comments for the
 * curve class.
 */

#ifndef CURVE_H
#define CURVE_H

using namespace std;

#include <vector>
#include <fstream>
#include "line.h"

typedef vector<pair<int,long double>> DataSet_t;
typedef vector<DataSet_t> Data_t;

class curve {
public:
    /*
     * description: Creates a curve() objects, which will plot curves using
     *     using the SDL Plotter
     * return: none
     * precondition:  Constructor called properly
     * postcondition: Creates curve() object with sameScale set to false
    */
    curve();

    /*
     * description: Function called when the lifetime of this object ends
     * return: none
     * precondition:  curve() object exists
     * postcondition: the resources that the object may have acquired
     *     during its lifetime are freed; since this object does not have
     *     to release any dynamically allocated memory, the implementation
     *     of this function is simply left empty
    */
    virtual ~curve() {};

    /*
     * description: Outputs each of the sets of ordered pairs in data
     * return: void
     * precondition:  curve() object exists
     * postcondition: Outputs the x and y coordinates of coordinate pairs
     *    stored in DataSet_t objects stored in data; each DataSet_t in data
     *    represents a different function; the ordered points for each
     *    function are displayed on a separate line with a dotted line
     *    separating the different functions
    */
    void display(Data_t data, ostream&);

    /*
     * description: Draws the different functions in data using the
     *     SDL Plotter; also draws x and y axis with 10 tick marks each
     * return:  void
     * precondition:  curve() object exists, and data points for each of the
     *    functions that are to be plotted are stored correctly in their
     *    respective DataSet_t's
     * postcondition: Draws the points of the functions in each of the
     *     DataSet_t's in data; each function is drawn in a different color.
     *     If sameScale == true, then all functions are plotted according
     *     to the maximum x and y values among all the data sets. Otherwise,
     *     the functions are plotted relative to their own maximum x
     *     and y values.
    */
    void draw(Data_t data, SDL_Plotter&);

    /*
     * description: Returns the value of sameScale
     * return: bool
     * precondition:  curve() object exists
     * postcondition: returns the value of the sameScale data member
     *     for the curve object
    */
    bool getSameScale(){ return sameScale; }

     /*
    * description: Changes the sameScale data member
    * return: void
    * precondition:  curve() object exists
    * postcondition: the value of the sameScale data member for the
    *     curve object is changed to match that of the argument passed
    *     to the function (t)
   */
    void setSameScale(bool t){sameScale = t;}

private:
    /*
     * description: Plots x and y axis using the SDL Plotter
     * return: void
     * precondition:  curve() object exists; margin represent the percent
     *     margin that should be allotted between the edge of the SDL Plotter
     *     window and the axis themselves
     * postcondition: Draws the x and y axis using the SDL Plotter; axis color
     *    is black.
    */
    void plotAxis(int margin, int maxX, int maxY, SDL_Plotter& g);

    /*
     * description: Plots 10 tick marks that are evenly spaced using the
     *     SDL Plotter
     * return: void
     * precondition:  curve() object exists; margin represent the percent
     *     margin that should be allotted between the edge of the SDL Plotter
     *     window and the axis themselves
     * postcondition: 10 evenly-spaced tick marks are plotted; tick marks will
     *    lie along the x and y axis (when plotted using plotAxis)
     *    and will scale with different dimensions of the plotter window
    */
    void plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter& g);

    /*
    * description: Plots the line a using the SDL Plotter
    * return: bool
    * precondition:  line() object exists; margin represent the percent
    *     margin that should be allotted between the edge of the SDL Plotter
    *     window and the axis themselves; this value for marin should match
    *     the value used when calling plotTickMarks() and plotAxis() in order
    *     for the drawing of the line to match the axis that are plotted
    * postcondition: If the x and y values for p1 of line a will plot within
    *     the SDL Plotter given the window, the line is drawn, and the value
    *     true is returned; otherwise, the line is not plotted and the value
    *     false is returned.
   */
    bool goodPoints(line a, int margin, SDL_Plotter& g);
    bool sameScale;
};

#endif
