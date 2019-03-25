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
#include "closest_pair.h"
#include "curve.h"

bool operator==(point p1, point p2){
    return (p1.getY() == p2.getY() && p1.getX() == p2.getX());
}

vector<point> * brute_ConvexHull(vector<point> points, SDL_Plotter& g) {
    //brute force: compute the line segment between every point and check if
    // all other points are on the same side of that line segment; if so, those
    // two points are in the convex hull
    //O(n^3)

    vector <point> * convexHullPoints = new vector<point>();
    bool pointsOnSameSide = true;

    // Draw all of the points
    for(int i = 0; i < points.size(); i++){
        drawRect(g, points[i]);
    }

    // Label the top right of the graph with "running" to denote that the
    // algorithm is still running
    running(g, false);
    g.update();


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
                    // Every time we find a pair of points in the convex hull,
                    // we update our display of what we've found so far
                    point point1(points[i].getX(), g.getRow()-points[i].getY());
                    point point2(points[j].getX(), g.getRow()-points[j].getY());
                    line convexH(point1, point2);
                    convexH.setColor(color_rgb(0,0,255));
                    convexH.draw(g);
                    g.update();

                    this_thread::sleep_for(chrono::milliseconds(500));
                }


                // reset pointsOnSameSide for the next set of points
                pointsOnSameSide = true;

            }
        }
    }

    running(g, true);
    finished(g, false);
    g.update();

    return convexHullPoints;
}


point p0;
bool lessThan(point p1, point p2){
    if(p1.getX()== p0.getX() && p1.getY()==p0.getY()){
        return true;
    }
    if(p1.getX()== p2.getX() && p1.getY()==p2.getY()){
        return true;
    }
    if(p1.getX()== p2.getX()){
        return (p1.getY()<p2.getY());
    }
    if(p2.getX()== p0.getX() && p2.getY()==p0.getY()){
        return false;
    }
    if (p1.getX()>p0.getX() && p2.getX()<=p0.getX()){
        return true;
    }
    if (p2.getX()>p0.getX() && p1.getX()<=p0.getX()){
        return false;
    }
    return (
       (double)(p1.getY()-p0.getY())/(double)(p1.getX()-p0.getX())<
       (double)(p2.getY()-p0.getY())/(double)(p2.getX()-p0.getX())
       );
}
bool isRightHandTurn(point p, point m, point n){
    double slope1;

    if (m.getX()==p.getX()){
        if (m.getY()>p.getY()) {
            return n.getX()>m.getX();
        } else{
            return n.getX()<m.getX();
        }
    }
    if (m.getY()==p.getY()){
        if (m.getX()>p.getX()) {
            return n.getY() < m.getY();
        } else{
            return n.getY() > m.getY();
        }
    }
    slope1=((double)(p.getY() - m.getY()))/((double)(p.getX() - m.getX()));
    if (m.getX()>p.getX()) {//0,100 to 100,0 for example
        return (n.getY() < p.getY() + slope1 * (n.getX() - p.getX()));
    } else{//100,0 to 0,100  for example
        return (n.getY() > p.getY() + slope1 * (n.getX() - p.getX()));
    }
}
vector<point> * divideAndConquer_ConvexHull(vector<point> points){

    vector <point> * convexHullPoints = new vector<point>();
    int minY;
    stack <point> values;
    point prev,mid,next;

    p0=points.at(0);
    minY=p0.getY();
    for (int i=0;i<points.size();i++){
        if(points.at(i).getY()<p0.getY()){
            minY=points.at(i).getY();
            p0=points.at(i);
        }
    }

    sort(points.begin(),points.end(),lessThan);

    *convexHullPoints=points;
    if (points.size()<4){
        return convexHullPoints;
    }

    prev= points.at(0);
    mid = points.at(1);
    values.push(prev);
    values.push(mid);

    for (int i = 2; i < points.size(); i++){
        next=points.at(i);
        while (isRightHandTurn(prev,mid,next)){
            values.pop();
            values.pop();
            mid = prev;
            prev= values.top();
            values.push(mid);
        }
        values.push(points.at(i));
        prev=mid;
        mid = values.top();
    }

    convexHullPoints->clear();
    while (!values.empty()) {
       convexHullPoints->push_back(values.top());
       values.pop();
    }
    return convexHullPoints;
}
