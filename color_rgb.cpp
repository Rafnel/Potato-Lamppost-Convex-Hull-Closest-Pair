#include "color_rgb.h"
using namespace std;

color_rgb::color_rgb(){
    //set initial color to black
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

color_rgb::color_rgb(int r, int g, int b){
    this->r = r;
    this->g = g;
    this->b = b;
}

color_rgb::color_rgb(color_rgb const& c){
    this->r = c.r;
    this->g = c.g;
    this->b = c.b;
}

color_rgb::~color_rgb(){}

int color_rgb::getR(){
    return this->r;
}

int color_rgb::getG(){
    return this->g;
}

int color_rgb::getB(){
    return this->b;
}

void color_rgb::setR(int r){
    this->r = r;
}

void color_rgb::setG(int g){
    this->g = g;
}

void color_rgb::setB(int b){
    this->b = b;
}

void color_rgb::operator=(const color_rgb& c){
    if(this != &c){
        this->r = c.r;
        this->g = c.g;
        this->b = c.b;
    }
}
