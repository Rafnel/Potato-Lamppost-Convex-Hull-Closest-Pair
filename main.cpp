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
#include <iostream>
#include "convexHull.h"
#include <unordered_set>

const int ROW_MAX = 500;
const int COL_MAX = 1000;

using namespace std;

/*
main

description: function will have a master loop in which the user is
shown a main menu and have the choice to select certain algorithms
to show and data set sizes for each algorithm. Once selected,
the algorithm will run and will then allow the user to exit back
to the main menu.
return: int
precondition: none
postcondition: the user will have been allowed to view different
algorithms for closest pair and convex hull problems.
*/
int main(int argc, char* argv[])
{
    vector<point> points;


    int dataSize=atoi(argv[1]);

    srand(time(NULL));
    for(int i = 0; i < dataSize; i++){
       int x = (rand() % 980) +10;
       int y = (rand() % 430) + 20;
       point p(x, y);
       points.push_back(p);
    }
   vector<point> ans = *(brute_ConvexHull(points));
   cout<<"brute force count: "<<ans.size()<<endl;
   for(int i=0; i<ans.size(); ++i){
       ans.at(i).display(cout);
   }
   divideAndConquer_ConvexHull(points);

    return 0;
}

