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


point p0;
bool lessThan(point p1, point p2){
    //these first two checks are for if one of the points is our p0
    if(p1.getX()== p0.getX() && p1.getY()==p0.getY()){
        return true;
    }
    if(p2.getX()== p0.getX() && p2.getY()==p0.getY()){
        return false;
    }
    //If p1 == p2
    if(p1.getX()== p2.getX() && p1.getY()==p2.getY()){
        return true;
    }
    //If on same vertical line
    if(p1.getX()== p2.getX()){
      if(p1.getX()>p0.getX()){
        return (p1.getY()<p2.getY());
      }else{
          return (p1.getY()>p2.getY());
      }
    }
    //if on same horizontal line
    if(p1.getY()== p2.getY()){
      return (p1.getX()>p2.getX());
    }

    if (p1.getX()>=p0.getX() && p2.getX()<=p0.getX()){
        return true;
    }
    if (p2.getX()>=p0.getX() && p1.getX()<=p0.getX()){
        return false;
    }
    return (
       (double)(p1.getY()-p0.getY())/(double)(p1.getX()-p0.getX())<
       (double)(p2.getY()-p0.getY())/(double)(p2.getX()-p0.getX())
    );
}

void drawWholeStack(stack <point> values){

    while (!values.empty()) {
    	values.top().display(cout);
	values.pop();
    }
}
bool isRightHandTurn(point p, point m, point n){
    double slope1,slope2;
    if(m.getX()==p.getX() && m.getY()==p.getY()){
        return true;
    }
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
    slope2=((double)(p.getY() - n.getY()))/((double)(p.getX() - n.getX()));
    if (abs(slope1-slope2)<0.0000001){
//        cout<<"small slope"<<endl;
        return true;
    }
    if(n.getY() == p.getY() + slope1 * (n.getX() - p.getX())){
        return true;
    }
    if (m.getX()>p.getX()) {//0,100 to 100,0 for example
        return (n.getY() < p.getY() + slope1 * (n.getX() - p.getX()));
    } else{//100,0 to 0,100  for example
        return (n.getY() > p.getY() + slope1 * (n.getX() - p.getX()));
    }
}
void divideAndConquer_ConvexHull(SDL_Plotter &g,vector<point> points){
    int minY;
    stack <point> values;
    point prev,mid,next;

    //Plotting points

    //Getting lowest leftmost point and setting as p0 and minY
    p0=points.at(0);
    minY=p0.getY();
    for (int i=0;i<points.size();i++){
        //Getting lowest
        if(points.at(i).getY()<p0.getY()){
            minY=points.at(i).getY();
            p0=points.at(i);
        }
        //If 2 of the lowest share the same y then it is determined
        //by the lowest x
        else if (points.at(i).getY() == p0.getY()){
            if (points.at(i).getX() < p0.getX()){
                minY=points.at(i).getY();
                p0=points.at(i);
            }
        }
    }

    //Sorting points in ascending order
    sort(points.begin(),points.end(),lessThan);

    //Check to see if convex hull is possible on thee points
    if (points.size()<4){
        drawWholeStack(values,points.size());
        return;
    }

    prev = points.at(0);
    mid = points.at(1);
    values.push(prev);
    values.push(mid);

    for (int i = 2; i < points.size(); i++){
        next=points.at(i);
        //Loop to pop right hand turns
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
        //drawWholeStack(values,points.size());//take this line out to remove animation
    }
    drawWholeStack(values,g,points.size());
}

