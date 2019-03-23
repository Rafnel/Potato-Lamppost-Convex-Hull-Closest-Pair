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

const int ROW_MAX = 500;
const int COL_MAX = 1000;

using namespace std;

int main(int argc, char* argv[])
{

    SDL_Plotter g(ROW_MAX, COL_MAX);
    g.update();

    //closest pair tester
    vector<point> points;
    /*int x, y;
    int numPoints;
    cin >> numPoints;
    int count = 0;

    while(count < numPoints){
        cin >> x >> y;
        point p(x, y);
        points.push_back(p);

        count++;
    }*/

    while(!g.getQuit()){
        if(g.kbhit()){
            g.clear();
            points.clear();

            srand(time(NULL));
            for(int i = 0; i < 50; i++){
                int x = (rand() % 980) +10;
                int y = (rand() % 430) + 20;
                point p(x, y);

                points.push_back(p);
            }

            // brute force closest pair
            if(g.getKey() == 'P'){
                brute_ClosestPair(g, points);
            }
            if(g.getKey() == 'H'){
                brute_ConvexHull(points, g);
            }
            if(g.getKey() == 'C'){
                pair<point, point> p;
                divconq_ClosestPair(g, points, true, p, points);
            }

        }
    }




    /* *************************** divconq tests *******************
    vector<point> * convexHull = brute_ConvexHull(points);

    cout << "Brute Force Convex Hull Points:" << endl;
    for(int i = 0; i < convexHull->size(); i++){
        convexHull->at(i).display(cout);
        cout << endl;
    }*/

    return 0;
}
