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

    this->color.setR(0);
    this->color.setB(0);
    this->color.setG(0);
}

point::point(const point& p){
    this->x = p.x;
    this->y = p.y;

    this->color = p.color;
}

point::~point(){}

void point::setY(int y){
    this->y = y;
}

void point::setX(int x){
    this->x = x;
}

void point::setColor(color_rgb c){
    this->color = c;
}

int point::getX(){
    return this->x;
}

int point::getY(){
    return this->y;
}

color_rgb point::getColor(){
    return this->color;
}

point& point::operator=(const point& rhs){
    if(this != &rhs){
        this->x = rhs.x;
        this->y = rhs.y;

        this->color = rhs.color;
    }

    return *this;
}

void point::display(ostream& o){
    o << "(" << this->x << ", " << this->y << ")" << endl;
    o << "Color in RGB: (" << this->color.getR() << ", " << this->color.getG()
      << ", " << this->color.getB() << ")" << endl;
}

void point::draw(SDL_Plotter& g){
    g.plotPixel(this->x, this->y, this->color.getR(), this->color.getG(),
                this->color.getB());
}
