/*
* Author: Zac Steudel, Chase Manseth, Gennie Mansi, Reece Kemball-Cook, Bob Rein
* Assignment Title: CSI 3344 Spring 2019 Group Project
*   represent the runtime characteristics of the brute force closest pair,
*   D/C closest pair, brute force convex hull, and D/C convex hull algorithms
* Due Date: 04/02/2019
* Date Created: 03/06/2019
* Date Last Modified: 04/01/2019
 */

using namespace std;
#include "line.h"


line::line() {
    this -> p1 = point();
    this -> p2 = point();

}

line::line(point p1, point p2) {

    // If the line is not vertical we want p1 to be the point that is further
    // left on the graph; that is, p1 is the point with the smaller
    // x coordinate
    if(p1.getX() != p2.getX()){
        if(p1.getX() < p2.getX()){
            this -> p1 = p1;
            this -> p2 = p2;
        }
        else{
            this -> p1 = p2;
            this -> p2 = p1;
        }
    }
    // If the line is vertical, we want p1 to be the point that is higher up
    // on the graph; that is, p1 is the point with the smaller
    // y coordinate
    else{
        if(p1.getY() < p2.getY()){
            this -> p1 = p1;
            this -> p2 = p2;
        }
        else{
            this -> p1 = p2;
            this -> p2 = p1;
        }
    }

}

// The slope() function returns true if there is a slope. If
// the function returns true, then the calculation is performed,
// the result is stored in b, and the value true is returned.
bool line::intercept(double &b) {
    // If the slope exists, then we can calculate the Y intercept and store
    // that value in b
    double m;
    if(slope(m)) {
        b = (double)p1.getY() - m*p1.getX();
        return true;
    }

    return false;
}

bool line::slope(double &m) {
    // If the points are not vertically aligned, then the slope
    // exists. The value of the slope is stored in m, and the value true
    // is returned.
    if(p1 .getX() != p2.getX()){
        m = ((double)p2.getY() - p1.getY())/(p2.getX() - p1.getX());
        return true;
    }

    // Otherwise, the slope doesn't exist and the value false is returned;
    return false;
}


void line::display(ostream &out) {
    out << p1.getX() << " " << p1.getY() << " " << p2.getX() <<
      " " << p2.getY() ;
}

