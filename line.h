/*
* Author: Gennie Mansi
* Assignment Title: Programming Assignment 1
* Assignment Description: Using only the SDL_Plotter class write a function
*      that will display multiple sets of ordered pairs.
* Due Date: 01/28/2019
* Date Created: 01/18/2019
* Date Last Modified: 01/28/2019
 */

/*
 * This file contains the class declaration and function comments for the
 * line class.
 */

#ifndef LINE_H
#define LINE_H

#include "point.h"


class line {
public:

    /*
     * description: Creates a line() object, which has as data members two
     *     point objects, a color_rbg object, and a currentColor data member
     *     for a line that can be plotted by the SDL Plotter
     * return: none
     * precondition:  Constructor called properly
     * postcondition: Creates line() object with default
     *     values r = g = b = 0, and x = y = 0 (for both points), and
     *     currentColor to 0
    */
    line();

    /*
     * description: Creates a line() object, which has as data members two
     *     point objects, a color_rbg object, and a currentColor data member
     *     for a line that can be plotted by the SDL Plotter
     * return: none
     * precondition:  Constructor called properly
     * postcondition: Creates point() object, initializing its member
     *     variables p1 and p2 to the values passed as arguments to the
     *     constructor, the color object to have default r = g = b = 0
     *     values, and currentColor to 0
    */
    line(point p1, point p2);

    /*
     * description: Function called when the lifetime of this object ends
     * return: none
     * precondition:  line() object exists
     * postcondition: the resources that the object may have acquired
     *     during its lifetime are freed; since this object does not have
     *     to release any dynamically allocated memory, the implementation
     *     of this function is simply left empty
    */
    virtual ~line() {};

    /*
     * description: Output the x and y coordinates of p1 and p2,
     *       color, and current data members to the ostream
     * return: void
     * precondition:  line() object exists
     * postcondition: Outputs the x and y coordinates of p1 and p2, the
     *     r,g,b values, and the value for currentColor for the line object
     *     each separated by a single space
    */
    void display(ostream&  out);

    /*
     * description: Plots the line using the SDL Plotter
     * return: void
     * precondition:  line() object exists
     * postcondition: Plots a line from p1 to p2 of the color
     *     represented by the rgb values stored in the color data member;
    */
    void draw(SDL_Plotter& g);

     /*
    * description: Changes the x and y coordinate for the p1 data member
    * return: void
    * precondition:  line() object exists
    * postcondition: the value of the x and y data member for the
    *     p1 point data member of the line  is changed
    *     to match that of the argument passed to the function
   */
    void setP1(point p){ this -> p1 = p; }

     /*
    * description: Changes the x and y coordinate for the p2 data member
    * return: void
    * precondition:  line() object exists
    * postcondition: the value of the x and y data member for the
    *     p2 point data member of the line  is changed
    *     to match that of the argument passed to the function
   */
    void setP2(point p){ this -> p2 = p; }

    /*
    * description: Changes the color of the line
    * return: void
    * precondition:  line() object exists
    * postcondition: the value of the color object that is a data member
    *     of the line  is changed to match that of the argument
    *     passed to the function
   */
    void setColor(color_rgb c){color = c;}

    /*
     * description: Returns the point, p1
     * return: point
     * precondition:  line() object exists
     * postcondition: returns the p1 data member for the line object
    */
    point getP1(){return p1;}

    /*
     * description: Returns the point, p2
     * return: point
     * precondition:  line() object exists
     * postcondition: returns the p2 data member for the line object
    */
    point getP2(){return p2;}

    /*
     * description: Returns the color of the line
     * return: color_rgb
     * precondition:  line() object exists
     * postcondition: returns the color data member for the line object
    */
    color_rgb getColor(){return color;}

    /*
     * description: Changes the color of the line
     * return: void
     * precondition:  line() object exists
     * postcondition: Changes the color of the object to the next color in an
     *    array of rgb values, updating currentColor accordingly
    */
    void nextColor();

    /*
    * description: Resets the color of the line
    * return: void
    * precondition:  line() object exists
    * postcondition: Changes the color of the object to the default color
    *     (currently black) that the line object is initialized to, updating c
    *     currentColor accordingly
   */
    void resetColor();

private:
    point p1, p2;
    color_rgb color;

    /*
    * description: Calculates the slope of the line
    * return: bool
    * precondition:  line() object exists
    * postcondition: If the slope exists (i.e. if the line is not vertical),
    *    the slope is calculated and stored in the double passed as a parameter,
    *    and the value true is returned; if the slope does not exist, the
    *    function returns false.
   */
    bool slope(double& m);

    /*
    * description: Calculates the y intercept of the line
    * return: bool
    * precondition:  line() object exists
    * postcondition: If the slope exists (i.e. if the line is not vertical),
    *    the y intercept is calculated and stored in the double
    *    passed as a parameter, and the value true is returned;
    *    if the line is vertical, and therefore does not have a y-intercept, the
    *    function returns false.
   */
    bool intercept(double& b);
    int currentColor;

};

#endif
