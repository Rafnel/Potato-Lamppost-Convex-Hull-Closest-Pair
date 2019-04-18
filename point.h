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
#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <ostream>

using namespace std;
class point {
	private:
		int x,y;
public:
    /*
    * description: constructor will set default values to the point.
    * return: none
    * precondition: none
    * postcondition: new point is created with default values for x and y.
    */
	point();
	/*
    * description: constructor will set x and y of the point to x and y sent in.
    * return: none
    * precondition: x and y are valid ints.
    * postcondition: point is instantiated with values for x and y from user.
    */
	point(int x, int y);
	/*
    * description: copy constructor will set this point to p.
    * return: none
    * precondition: p is a valid point.
    * postcondition: new point is created with p's values.
    */
	point(const point& p);
	/*
    * description: destructor would de-allocate any dynamic memory.
    * return: none
    * precondition: none
    * postcondition: dynamically allocated memory is de-allocated.
    */
	virtual ~point();
	/*
    * description: function will set y to value sent in.
    * return: none
    * precondition: y is a valid int.
    * postcondition: y is set to value sent in by user.
    */
	void setY(int y);
	/*
    * description: function will set x to value sent in.
    * return: none
    * precondition: x is a valid int.
    * postcondition: x is set to value sent in by user.
    */
	void setX(int x);
	/*
    * description: function will set color to value sent in.
    * return: none
    * precondition: c is a valid color.
    * postcondition: color is set to value sent in by user.
    */
	int getX();
	/*
    * description: function will return y.
    * return: int
    * precondition: none
    * postcondition: this's y is returned.
    */
	int getY();
	/*
    * description: function will return color.
    * return: color_rgb
    * precondition: none
    * postcondition: this's color is returned.
    */
	point& operator=(const point& rhs);
	/*
    * description: function will display the point's values to the ostream.
    * return: none
    * precondition: none
    * postcondition: point's values displayed to the ostream.
    */
	void display(ostream&);
	/*
    * description: function will plot the point to the screen.
    * return: none
    * precondition: this's point is of valid values to be plotted.
    * postcondition: the point will be plotted to the screen.
    */
	
};


#endif // POINT_H_INCLUDED
