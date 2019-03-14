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


#include <iostream>
#include "SDL_Plotter.h"
#include "closest_pair.h"
#include "convexHull.h"

using namespace std;

int main(int argc, char* argv[])
{
    //closest pair tester
    vector<point> points;
    int x, y;
    int numPoints;
    cin >> numPoints;
    int count = 0;

    while(count < numPoints){
        cin >> x >> y;
        point p(x, y);
        points.push_back(p);

        count++;
    }

    //cout << "Brute Force: " << brute_ClosestPair(points) << endl;
    //cout << "Div & Conquer: " << divconq_ClosestPair(points) << endl;




    vector<point> * convexHull = brute_ConvexHull(points);

    cout << "Brute Force Convex Hull Points:" << endl;
    for(int i = 0; i < convexHull->size(); i++){
        convexHull->at(i).display(cout);
        cout << endl;
    }

    return 0;
}