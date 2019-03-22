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
#include "convexHull.h"


bool operator==(point p1, point p2){
    return (p1.getY() == p2.getY() && p1.getX() == p2.getX());
}

vector<point> * brute_ConvexHull(vector<point> points) {
    //brute force: compute the line segment between every point and check if
    // all other points are on the same side of that line segment; if so, those
    // two points are in the convex hull
    //O(n^3)

    vector <point> * convexHullPoints = new vector<point>();
    bool pointsOnSameSide = true;

    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points.size(); j++) {

            if ( !((points[i] == points[j])) ) {

                // Compute the line segment for p_i and p_j
                int a = points[j].getY() - points[i].getY();
                int b = points[i].getX() - points[j].getX();
                int c = points[i].getX() * points[j].getY()
                        - points[j].getX() * points[i].getY();

                int firstaxBy = c;

                // Determine if all points other than p_i and p_j are on
                // one side of the line segment; if so, then, p_i and p_j are
                // points in the convex hull
                for (int k = 0; k < points.size() && pointsOnSameSide; k++) {

                    if ( !((points[k] == points[i])) &&
                         !((points[k] == points[j])) ) {

                        int axBY = a * points[k].getX() + b * points[k].getY();

                        if(firstaxBy == c){
                            firstaxBy = axBY;
                        }

                        // If either one of the two below conditions is true,
                        // then not all of the points lie on one side of the
                        // line segment
                        if ((axBY > c && firstaxBy < c) ||
                            (axBY < c && firstaxBy > c)) {

                            pointsOnSameSide = false;
                        }
                    }
                }

                if (pointsOnSameSide) {
                    // If we haven't already identified p_i as a point in the
                    // convexHull, add it to the vector of convexHullPoints
                    if (count(convexHullPoints->begin(),
                             convexHullPoints->end(),
                             points[i]) == 0) {

                        convexHullPoints->push_back(points[i]);
                    }

                    // If we haven't already identified p_j as a point in the
                    // convexHull, add it to the vector of convexHullPoints
                    if (count(convexHullPoints->begin(),
                             convexHullPoints->end(),
                             points[j]) == 0) {

                        convexHullPoints->push_back(points[j]);
                    }
                }

                // reset pointsOnSameSide for the next set of points
                pointsOnSameSide = true;

            }
        }
    }

    return convexHullPoints;
}

//lowest y | DONE
//sort by angles
//remove all with same angle except longest
//if < 3 points then cannot make hull
//create stack
//push first 3
//remove all that dont make left
//done

// Supporting functions
point p0;
int compare(point *p1, point *p2){
   int x1,y1,x2,y2,angle1, angle2;
   x1 = p1.x - p0.x;
   x2 = p2.x - p0.x;
   y1 = p1.y - p0.y;
   y2 = p2.y - p0.y;
   angle1 = atan(y1/x1);
   angle2 = atan(y2/x2);
   if (angle1 == angle2){
     return 0;
   }
   if (angle1 < angle2){
     return -1;
   }
   if (angle1 > angle2) {
       return 1;
   }
}



vector<point> * divideAndConquer_ConvexHull(vector<point> points){
    vector <point> * convexHullPoints = new vector<point>();

    // finding bottom most point
    int minY = points[0].getY();
    int minNdx = 0;
    for(int i = 1; i < points.size()) {
        int pointY = points[i].getY();
        int pointX = points[i].getX();

        if(pointY < minY || (pointY == minY &&
            pointX < points[minNdx].getX())) {
                minY = pointY;
                minNdx = i;
            }
    }

    swap(points[0], points[minNdx]);
    p0 = points[0];

    sort(points.begin(),points.end(),compare);

    /*for (int i = 0; i < points.size()-1; i++){
        if (compare(points[i],points[i+1]) == 0){
            //a^2 + b^2 = c^2
            l1 =
            if ()
        }
    }*/

    return convexHullPoints;
}
