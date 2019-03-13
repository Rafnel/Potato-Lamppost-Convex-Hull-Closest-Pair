#ifndef CLOSEST_PAIR_H_INCLUDED
#define CLOSEST_PAIR_H_INCLUDED

#include <vector>
#include "point.h"
#include <cmath>
#include <algorithm>

using namespace std;

double distance(point p1, point p2);
double brute_ClosestPair(vector<point> points);
double divconq_ClosestPair(vector<point> points);

bool yComparator(point p1, point p2);
bool xComparator(point p1, point p2);

#endif // CLOSEST_PAIR_H_INCLUDED
