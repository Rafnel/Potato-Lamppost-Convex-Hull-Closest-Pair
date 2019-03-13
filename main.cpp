#include <iostream>
#include "SDL_Plotter.h"
#include "closest_pair.h"

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

    cout << "Brute Force: " << brute_ClosestPair(points) << endl;
    cout << "Div & Conquer: " << divconq_ClosestPair(points) << endl;

    return 0;
}
