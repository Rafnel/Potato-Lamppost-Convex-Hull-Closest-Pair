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
#include "point.h"
point::point(){
    this->x = 0;
    this->y = 0;
}

point::point(int x, int y){
    this->x = x;
    this->y = y;

}

point::point(const point& p){
    this->x = p.x;
    this->y = p.y;

}

point::~point(){}

void point::setY(int y){
    this->y = y;
}

void point::setX(int x){
    this->x = x;
}

int point::getX(){
    return this->x;
}

int point::getY(){
    return this->y;
}

point& point::operator=(const point& rhs){
    if(this != &rhs){
        this->x = rhs.x;
        this->y = rhs.y;
    }

    return *this;
}

void point::display(ostream& o){
    o << "(" << this->x << ", " << this->y << ")" << endl;
}

