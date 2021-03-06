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
const float CLOSETOZERO = 0.00001;
const int RUNTIME = 15000;
const int SMALLEST = 4;
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

                    g.Sleep(500);
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



bool sortByAngle( pair<point,float> &a, pair<point,float> &b){
    if(abs(a.second-b.second)<CLOSETOZERO){
        if(a.first.getX()==b.first.getX()){
            return (a.first.getY()<b.first.getY());
        }
        return (a.first.getX()<b.first.getX());
    }
    return (a.second < b.second);
}
float getRadians(point p1,point p0){
    float answer = atan2(p1.getY()-p0.getY(), p1.getX()-p0.getX() );
    return answer;
}
void drawWholeStack(stack <point> values,SDL_Plotter&g,int size){
    while (!values.empty()) {
       point p1(values.top().getX(),g.getRow() - values.top().getY());
       values.pop();
       if(!values.empty()){
            point p2(values.top().getX(),g.getRow() - values.top().getY());
            line myline(p1, p2);
            myline.setColor(color_rgb(0,0,255));
            myline.draw(g);
       }
    }
    g.update();
    g.Sleep(RUNTIME / size);
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
    if (abs(slope1-slope2)<CLOSETOZERO){
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
    int minY,start=2;
    stack <point> values;
    vector< pair <point,float> > data;
    point prev,mid,next,p0;

    //Plotting points
    g.clear();
    plotPoints(g, points);
    running(g, false);
    g.update();

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

    for(int i=0;i<points.size();i++){
        data.push_back(make_pair(points.at(i),getRadians(points.at(i),p0)));
    }
    sort(data.begin(), data.end(), sortByAngle);

    //Check to see if convex hull is possible on thee points
    if (data.size()<SMALLEST){
        g.clear();
        plotPoints(g, points);
        point pFinal(values.top().getX(),g.getRow() - values.top().getY());
        point pInitial(p0.getX(),g.getRow() - p0.getY());
        line myline(pInitial, pFinal);
        myline.setColor(color_rgb(0,0,255));
        myline.draw(g);
        drawWholeStack(values,g,points.size());
        return;
    }

    prev = p0;
    mid = data.at(1).first;
    while(data.at(start).second <CLOSETOZERO){
        mid = data.at(start).first;
        start++;
    }
    values.push(prev);
    values.push(mid);

    for (int i = start; i < data.size(); i++){
        next=data.at(i).first;
        //Loop to pop right hand turns
        while (isRightHandTurn(prev,mid,next)&& values.size()>2){
            values.pop();
            values.pop();
            mid = prev;
            prev= values.top();
            values.push(mid);
        }
        values.push(data.at(i).first);
        prev=mid;
        mid = values.top();
        drawWholeStack(values,g,points.size());//take this line out to remove animation
    }

    g.clear();
    plotPoints(g, points);
    point pFinal(values.top().getX(),g.getRow() - values.top().getY());
    point pInitial(p0.getX(),g.getRow() - p0.getY());
    line myline(pInitial, pFinal);
    myline.setColor(color_rgb(0,0,255));
    myline.draw(g);
    drawWholeStack(values,g,data.size());
}

