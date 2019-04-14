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

using namespace std;
#include "line.h"

const int TOTAL_COLORS = 12;

line::line() {
    this -> p1 = point();
    this -> p2 = point();
    this -> currentColor = -1;
    nextColor();

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

    this -> currentColor = -1;
    nextColor();
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

void line::nextColor() {
    // These are all the colors curves can get plotted in.
    color_rgb colorPossibilities[TOTAL_COLORS] = { color_rgb(0,0,0),
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

void line::resetColor() {
    // This will reset the color of the line back to the initial set of rgb
    // values that lines are set to when they are initialized; currently,
    // that color is black (r = g = b = 0)
    currentColor = -1;
    nextColor();
}

void line::display(ostream &out) {
    out << p1.getX() << " " << p1.getY() << " " << p2.getX() <<
      " " << p2.getY() << " " << color.getR() << " "
    << color.getG() << " " << color.getB() << " " << currentColor;
}

void line::draw(SDL_Plotter &g) {
    // To store the slope of the line
    double m = 0.0;
    // To store the intercept of the line
    double b = 0.0;
    // To store/keep track of the x-values for which we will calculate y-values
    // using the equation of a line
    double xVal = p1.getX();
    double yVal = p1.getY();
    // To control how many points along the line we calculate and plot
    double incrementSize = 0.01;

    // If the line is not a vertical line (i.e., it has a slope), then the
    // y-values in the line can be found using the equation y = m*x + b, and we
    // can just increment x in order to find new values of y to plot.
    if(slope(m)){
        intercept(b);
        // While we haven't reach the other point AND while we are still within
        // the bounds of the plot screen itself, we want to keep on plotting
        // and calculating points.
        while(xVal < p2.getX() & xVal < g.getCol() & yVal < g.getRow()){
            g.plotPixel(xVal,yVal, color.getR(), color.getG(), color.getB());
            xVal+=incrementSize;
            yVal = m*xVal + b;
        }
    }
    // If the line is a vertical line, then the x coordinates in the line are
    // all the same, so in order to plot the line, we just increment the
    // y-values by incrementSize each time.
    else {
        // While we haven't reached the other point AND while we are still
        // within the bounds of the plot screen itself, we want to keep on
        // plotting and calculating points.
        while (yVal < p2.getY() && yVal < g.getRow()) {
            g.plotPixel(xVal, yVal, color.getR(), color.getG(), color.getB());
            yVal += incrementSize;
        }
    }
}
