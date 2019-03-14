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
 * This file contains the implementations of functions in the curve class.
 */

// floor() function from cmath used
#include <cmath>
#include "curve.h"

const int MARGIN = 2;

curve::curve() {
    this -> sameScale = false;
}

void curve::plotAxis(int margin, int maxX, int maxY, SDL_Plotter &g) {

    // This calculates the number of pixels that are to be left as a space
    // between the edge of the SDL Plotter window and the plot of the axis.
    int pixelBuffer_x = ((double)margin/100)*g.getCol();
    int pixelBuffer_y = ((double)margin/100)*g.getRow();

    // This makes the points that are used to draw the x axis.
    point p1x(pixelBuffer_x, g.getRow()-pixelBuffer_y);
    point p2x((g.getCol()-pixelBuffer_x), g.getRow()-pixelBuffer_y);
    // The line that represents the x axis.
    line xAxis(p1x, p2x);

    // This makes the points that are used to draw the y axis.
    point p1y(pixelBuffer_x, pixelBuffer_y);
    point p2y(pixelBuffer_x, g.getRow()-pixelBuffer_y);
    // The line that represents the y axis
    line yAxis(p1y, p2y);

    // This draws the x and y axis.
    xAxis.draw(g);
    yAxis.draw(g);
}


void curve::plotTickMarks(int margin, int maxX, int maxY, SDL_Plotter &g) {
    // This is used to standardize the length of the tick marks along the
    // x and y axis; tickLength is the length of the ticks in pixels.
    const int tickLength = 7;

    // This calculates the number of pixels that are to be left as a space
    // between the edge of the SDL Plotter window and the plot of the axis.
    int pixelBuffer_x = ((double)margin/100)*g.getCol();
    int pixelBuffer_y = ((double)margin/100)*g.getRow();

    // This calculates the length and width (in pixels) of the screen that can
    // be plotted on given the margin. The reason we multiply pixelBuffer by
    // 2 is that there is a left and right margin, and a top and bottom margin
    int usableLength_x = g.getCol() - 2*pixelBuffer_x;
    int usableLength_y = g.getRow() - 2*pixelBuffer_y;

    // This calculates how far apart the tick marks should be placed along the
    // x and y axis.
    int tickSpacing_x = floor(usableLength_x/10);
    int tickSpacing_y = floor(usableLength_y/10);

    // This actually plots the tick marks along the x axis.
    for(int i = 0; i <= 10; i++){
        point pTick1_x(pixelBuffer_x + tickSpacing_x*i,
                       g.getRow() - pixelBuffer_y);
        point pTick2_x(pixelBuffer_x + tickSpacing_x*i,
                       g.getRow() - pixelBuffer_y - tickLength);
        line xAxisTick (pTick1_x, pTick2_x);
        xAxisTick.draw(g);
    }

    // This actually plots the tick marks along the y axis.
    for(int i = 0; i <= 10; i++){
        point pTick1_y(pixelBuffer_x,
                       g.getRow() - pixelBuffer_y - i*tickSpacing_y);
        point pTick2_y(pixelBuffer_x + tickLength,
                       g.getRow() - pixelBuffer_y - i*tickSpacing_y);
        line yAxisTick (pTick1_y, pTick2_y);
        yAxisTick.draw(g);
    }
}


bool curve::goodPoints(line a, int margin, SDL_Plotter &g) {

    // This calculates the number of pixels that are to be left as a space
    // between the edge of the SDL Plotter window and the plot of the axes.
    int pixelBuffer_x = ((double)margin/100)*g.getCol();
    int pixelBuffer_y = ((double)margin/100)*g.getRow();

    // The coordinate system for the SDL Plotter is different from the
    // standard Cartesian coordinate system. The coordinate system has the
    // origin, (0,0), in the top left-hand corner of the screen, with the
    // x and y values increasing right and down. The coordinates for the points
    // in a are given according to the standard Cartesian coordinate system;
    // these lines of code are used to properly calculate the points defining
    // the line, given the different coordinate system and the margin that is
    // supposed to be placed between the edge of the screen and the plot itself.
    int point1_X = a.getP1().getX() + pixelBuffer_x;
    int point2_X = a.getP2().getX() + pixelBuffer_x;
    int point1_Y = g.getRow() - pixelBuffer_y - a.getP1().getY();
    int point2_Y = g.getRow() - pixelBuffer_y - a.getP2().getY();

    // If p1 for line a can be plotted on the graph,
    // then the line will be graphed, and the value true will be returned
    // from the function.
    if(point1_X < g.getCol() - pixelBuffer_x &&
       point1_Y <= g.getRow() && point1_Y > pixelBuffer_y &&
       point1_X >= 0 && point1_Y >= 0){

            line L(point(point1_X, point1_Y), point(point2_X, point2_Y));
            L.setColor(a.getColor());
            L.draw(g);

            return true;
    }
    // However, if p1 is not valid, then we won't graph the
    // line; we will return false.
    else{
        return false;
    }
}

void curve::draw(Data_t data, SDL_Plotter & g) {
    // Draw axes and tick marks for graph.
    plotAxis(MARGIN, g.getCol(), g.getRow(), g);
    plotTickMarks(MARGIN, g.getCol(), g.getRow(), g);

    // Calculate the number of pixels that will be placed as a buffer between
    // the end of the screen and the plot itself.
    int pixelBuffer_x = ((double)MARGIN/100)*g.getCol();
    int pixelBuffer_y = ((double)MARGIN/100)*g.getRow();

    // This line L is created to aid in plotting the functions stored in data.
    line L(point(0,0) , point(0,0));
    L.nextColor();

    // If getSameScale is true, then we will find the largest x value in all the
    // data and the largest y value in all the data, and then we will scale and
    // graph all the points in the DataSet_t's based off of these "universal"
    // maxima.
    if(getSameScale()){

        // Find "universal" maxX and maxY values; that is, find the largest
        // x and y values from among all the data sets.
        int maxX = ((data.begin()) -> begin()) -> first;
        long double maxY = ((data.begin()) -> begin()) -> second;
        for(vector<DataSet_t>::iterator maxEl = data.begin();
            maxEl != data.end(); maxEl++){
            for(vector<pair<int, long double>>::iterator maxVal=maxEl -> begin();
                maxVal != maxEl -> end(); maxVal++){
                if(maxVal -> first > maxX) {  maxX = maxVal -> first; }
                if(maxVal -> second > maxY) { maxY  = maxVal -> second; }
            }
        }

        // Use the universal max's in order to plot the points in the DataSets.
        for(vector<DataSet_t>::iterator itData = data.begin();
            itData != data.end(); itData++){
            for(vector<pair<int, long double>>::iterator itDataPairs=itData -> begin();
                itDataPairs != itData -> end() - 1; itDataPairs++){

                 // The x and y coordinates for each of the points in the
                 // DataSet_t are scaled according the maximum x and y values.
                    point p1(((double)itDataPairs -> first / maxX)*
                                  (g.getCol()-2*pixelBuffer_x),
                              (itDataPairs ->second / maxY)*
                                  (g.getRow()-2*pixelBuffer_y));

                    point p2(((double)(itDataPairs+1)-> first / maxX)*
                                  (g.getCol()-2*pixelBuffer_x),
                             ((itDataPairs+1)-> second / maxY)*
                                  (g.getRow()-2*pixelBuffer_y));

                // If the scaled x and y coordinates for adjacent points
                // are still valid coordinates (i.e., they still fit within
                // the plotter window) then we will go ahead and plot the
                // line that connects these two points.
                if(p1.getX() <= g.getCol() && p1.getY() <= g.getRow()
                   && p1.getY() >= 0 && p2.getY() >= 0
                   && p2.getX() <= g.getCol() && p2.getY() <= g.getRow()){

                    L.setP1(p1);
                    L.setP2(p2);
                    goodPoints(L, MARGIN, g);
                }
            }

            // Each function (i.e. set of points in each DataSet_t in data)
            // gets plotted in a different color.
            L.nextColor();
        }
    }

    // If getSameScale returns false, then within each DataSet_t, we search for
    // the largest x and the largest y, and then use these values to scale and
    // plot the values in that individual data set.
    else{
        // Loop through all the DataSets in data.
        for(vector<DataSet_t>::iterator itData = data.begin();
            itData != data.end(); itData++){

            // Find the largest x and y values in this individual DataSet_t
            int maxX = 1;
            long double maxY = 1.0;
            for(vector<pair<int, long double>>::iterator maxVal=itData->begin();
            maxVal != itData->end(); maxVal++){
                if(maxVal -> first > maxX) {  maxX = maxVal -> first; }
                if(maxVal -> second > maxY) { maxY  = maxVal -> second; }
            }


            // Graph each pair of points in the DataSet_t relative to maxX and
            // maxY, which were found in the section of code directly preceding
            // this for loop.
            for(vector<pair<int, long double>>::iterator itDataPairs=itData->begin();
                itDataPairs != itData->end() -1; itDataPairs++){

                // The x and y coordinates for each of the points in the
                // DataSet_t are scaled according the maximum x and y values.
                double p1X = (((double)itDataPairs -> first) / maxX)*
                                 (g.getCol()-2*pixelBuffer_x);
                long double p1Y = (itDataPairs ->second / maxY)*
                                 (g.getRow()-2*pixelBuffer_y);

                double p2X = (((double)(itDataPairs+1)-> first) / maxX)*
                        (g.getCol()-2*pixelBuffer_x);
                long double p2Y = ((itDataPairs+1)-> second / maxY)*
                        (g.getRow()-2*pixelBuffer_y);

                // If the scaled x and y coordinates for adjacent points
                // are still valid coordinates (i.e., they still fit within
                // the plotter window) then we will go ahead and plot the
                // line that connects these two points.
                if(p1X <= g.getCol() && p1Y <= g.getRow() && p2X <= g.getCol()
                   && p2Y <= g.getRow() && p1Y >= 0 && p2Y >= 0) {

                    point p1(p1X, p1Y);
                    point p2(p2X, p2Y);
                    L.setP1(p1);
                    L.setP2(p2);
                    goodPoints(L, MARGIN, g);

                }
            }

            // Each function (i.e. set of points in each DataSet_t in data)
            // gets plotted in a different color.
            L.nextColor();
        }
    }
}

void curve::display(Data_t data, ostream & os){
    // Loop through all the DataSets in Data_t and output each of the pairs
    // in each DataSet to the ostream os; each of the different data sets
    // is separated by a dotted line.
    for(vector<DataSet_t>::iterator itData = data.begin();
        itData != data.end(); itData++) {
        for (vector<pair<int, long double>>::iterator itDataPairs=itData->begin();
             itDataPairs != itData->end() - 1; itDataPairs++) {

            os << itDataPairs -> first << " "
                 << itDataPairs -> second << endl;
        }
        os << "---------------------------------------------" << endl;
    }
}

/*** CODE USED FOR TESTING DIFFERENT FUNCTIONS IN THIS CLASS; CODE LEFT
 * INTENTIONALLY FOR DOCUMENTATION AND TESTING PURPOSES.
 *
 *  cout << "pixelBuufer x: " << pixelBuffer_x << endl;
    cout << "pixelBuffer y: " << pixelBuffer_y << endl;

    cout << "x c1: " << pixelBuffer_x << endl;
    cout << "x c2: " << g.getCol() - pixelBuffer_x << endl;

    cout << "p1: (" << point1_X << ", " << point1_Y << ")" << endl;
    cout << "p2: (" << point2_X << ", " << point2_Y << ")" << endl;
    cout << "pixelB_x: " << pixelBuffer_x << endl;
    cout << "pixelB_y: " << pixelBuffer_y << endl;
    cout << "point1_x valid? "
    << (point1_X >= pixelBuffer_x & point1_X <= g.getCol() - pixelBuffer_x )
    << endl;
    cout << "point1_y valid? "
    << (point1_Y <= g.getRow() - pixelBuffer_y) << " " << (point1_Y >= pixelBuffer_y)
    << endl;

    cout << "maxX: " << maxX << endl;
    cout << "maxY: " << maxY << endl;

    cout << "point1_x: " << p1.getX() << " ";
    cout << "point1_y: " << p1.getY() << " ";
    cout << "point2_x: " << p2.getX() << " ";
    cout << "point2_y: " << p2.getY() << endl;

    cout << "--------------------------------------" << endl;

 ***/