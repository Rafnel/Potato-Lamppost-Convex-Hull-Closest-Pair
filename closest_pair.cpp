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


#include "closest_pair.h"

double distance(point p1, point p2){
    return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

bool yComparator(point p1, point p2){
    return (p1.getY() < p2.getY());
}
bool xComparator(point p1, point p2){
    return (p1.getX() < p2.getX());
}

double brute_ClosestPair(SDL_Plotter &g, vector<point> points){
    //brute force: find the distance between every point and every other point.
    //O(n^2)

    //graphics part 1: plot all the points.
    plotPoints(g, points);
    g.update();

    double minDist;
    bool distChanged = false;
    bool distInitialized = false;

    for(int i = 0; i < points.size(); i++){
        //graphics step 2: highlight the currently-considered point.
        color_rgb c(255, 0, 0);
        points[i].setColor(c);
        drawRect(g, points[i]);
        g.update();
        this_thread::sleep_for(chrono::milliseconds(10000 / points.size()));

        for(int j = i + 1; j < points.size(); j++){
            //check that these aren't the same points, in case
            //there are duplicates for some reason.
            if(points[i].getX() != points[j].getX() ||
               points[i].getY() != points[j].getY()){
                if(!distInitialized){
                    //if this is the first set of valid points, set the
                    //initial minDist to this distance
                    minDist = distance(points[i], points[j]);
                    distInitialized = true;
                    distChanged = true;
                }
                if(distance(points[i], points[j]) < minDist){
                    minDist = distance(points[i], points[j]);
                    distChanged = true;
                }

                //graphics step 3: draw the line between the current closest
                //pair.
                if(distChanged){
                    cout << minDist << endl;
                    g.clear();
                    plotPoints(g, points);

                    point p1(points[i].getX(), g.getRow() - points[i].getY());
                    point p2(points[j].getX(), g.getRow() - points[j].getY());
                    line closest(p1, p2);
                    closest.setColor(points[j].getColor());
                    closest.draw(g);

                    distChanged = false;

                    g.update();
                }
            }
        }

        //2.5: set color back to black after finishing.
        c.setR(0);
        points[i].setColor(c);
        drawRect(g, points[i]);
        g.update();
    }

    return minDist;
}

double divconq_ClosestPair(SDL_Plotter &g, vector<point> points){
    //divide and conquer closest pair algorithm. Runs in O(nlog(n)).

    //handle an edge case where the user sends in an empty list or a list
    //with one point. In that case, distance is 0.
    if(points.size() <= 1){
        return 0;
    }

    //first, establish a base case: only two points in the vector, so return
    //the distance between those two points.
    if(points.size() == 2){
        return distance(points[0], points[1]);
    }
    else if(points.size() == 3){
        //we can't let divide and conquer tackle a vector of 3 points because
        //it will split into a vector of 1 point, which the algorithm won't
        //handle correctly.
        return brute_ClosestPair(g, points);
    }

    /* Division part of the algorithm: sort the vector by increasing x-values
     * and then divide the vector into two sub-vectors, where the point of
     * division is the median of the sorted vector.
    */
    sort(points.begin(), points.end(), xComparator);
    int median = points.size() / 2;

    vector<point> firstHalf(points.begin(), points.begin() + median);
    vector<point> secondHalf(points.begin() + median, points.end());

    double dist1 = divconq_ClosestPair(g, firstHalf);
    double dist2 = divconq_ClosestPair(g, secondHalf);

    double minDist = min(dist1, dist2);

    /* Now for the hard part: handle the points that could be closest pairs
     * that cross over the dividing line. Any point that is within minDist
     * of the median of the original sorted array will go into a new array
     * of candidate points. This checks specifically for x-distance from the
     * median so that our region of candidacy is a rectangle.
     * This scan will take O(n).
    */
    vector<point> candidates;
    for(int i = 0; i < points.size(); i++){
        if(abs(points[i].getX() - points[median].getX()) <= minDist){
            candidates.push_back(points[i]);
        }
    }

    /* sort candidates vector by y-values, and then we can apply an O(n) scan
     * through the array that only checks against 6 points maximum for each
     * candidate point.
    */
    sort(candidates.begin(), candidates.end(), yComparator);

    //this looks like it's O(n^2), but due to the fact that there will be at
    //maximum 6 points to check against each candidate, that is a constant,
    //meaning this is O(n). (Packing Theorem)
    for(int i = 0; i < candidates.size(); i++){
        for(int j = i + 1; j < candidates.size() &&
                           candidates[j].getY() - candidates[i].getY() <= minDist; j++){
            minDist = min(minDist, distance(candidates[i], candidates[j]));
        }
    }

    return minDist;
}


void plotPoints(SDL_Plotter &g, vector<point> points){
    for(int i = 0; i < points.size(); i++){
        if(points[i].getX() > 0 && points[i].getX() < g.getCol() &&
           points[i].getY() > 0 && g.getRow() - points[i].getY() > 0){
            drawRect(g, points[i]);
        }
    }
}

void drawRect(SDL_Plotter &g, point p){
    for(int x = p.getX() - 2; x < p.getX() + 2; x++){
        for(int y = p.getY() - 2; y < p.getY() + 2; y++){
            if(x > 0 && x < g.getCol() && y > 0 && g.getRow() - y > 0){
                int yVal = g.getRow() - y;
                g.plotPixel(x, yVal, p.getColor().getR(), p.getColor().getB(),
                            p.getColor().getG());
           }
        }
    }
}


