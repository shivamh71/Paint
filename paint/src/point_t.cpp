#include "point_t.h"
#include "pixel_t.h"
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

// point class implementation

point_t::point_t() { // default constructor for point_t
	x = 0;
	y = 0;
}

point_t::point_t(int x, int y) { // constructor for point_t
	this->x = x;
	this->y = y;
}

void point_t::operator= (point_t p) { // operator= for point_t
	this->x = p.getX();
	this->y = p.getY();
	this->pointSize = p.getPointSize();
	this->pointColor = p.getPointColor();
}

int point_t::getX() const { // accessor for x-coordinate
	return x;
}

int point_t::getY() const { // accessor for y-coordinate
	return y;
}

void point_t::setX(int x) { // modifier for x-coordinate
	this->x = x;
}

void point_t::setY(int y) { // modifier for y-coordinate
	this->y = y;
}

void point_t::setPointColor(color_t &c) { // modifier for point color
	pointColor = c;
}

color_t point_t::getPointColor() {// accessor for point color
	return pointColor;
}

int point_t::getPointSize() const { // accessor for point size
	return pointSize;
}

void point_t::setPointSize(int size) { // modifier for point size
	pointSize = size;
}

void point_t::draw(vector<vector<pixel_t> > &raster) { // draw method for point
	int size = pointSize;
	for (int i=0;i<size;i++) {
		for (int j=0;j<size;j++) {
			raster[x+i][y+j].r = pointColor.getRedValue();
			raster[x+i][y+j].g = pointColor.getGreenValue();
			raster[x+i][y+j].b = pointColor.getBlueValue();
		}
	}		
}