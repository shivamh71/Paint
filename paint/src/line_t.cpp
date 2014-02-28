#include "point_t.h"
#include "color_t.h"
#include "line_t.h"
#include "pixel_t.h"
#include <GL/glut.h>
#include <iostream>
using namespace std;
#include <cmath>

// line_t class implementation

line_t::line_t() {} // default constructor for line_t

line_t::line_t(point_t &s, point_t &e) { // constructor for line_t
	this->startPoint = s;
	this->endPoint = e;
}

line_t::line_t(point_t &s, point_t &e, color_t &c) { // constructor for line_t
	this->startPoint = s;
	this->endPoint = e;
	this->lineColor = c;
}

void line_t::operator= (line_t l) { // operator= for line_t
	this->startPoint = l.getLineStartPoint();
	this->endPoint = l.getLineEndPoint();
	this->lineColor = l.getLineColor();
}

point_t line_t::getLineStartPoint() const { // accessor for start point
	return startPoint;
}

point_t line_t::getLineEndPoint() const { // accessor for end point
	return endPoint;
}

color_t line_t::getLineColor() const { // accessor for line color
	return lineColor;
}

void line_t::setLineStartPoint(point_t &s) { // modifier for start point
	startPoint = s;
}

void line_t::setLineEndPoint(point_t &e) { // modifier for end point
	endPoint = e;
}

void line_t::setLineColor(color_t &c) { // modifier for line color
	lineColor = c;
}

void swap(int &x, int &y) { // swapping two integers
	int temp = x;
	x = y; 
	y = temp;
}

void line_t::draw(vector<vector<pixel_t> > &raster) { // draw method for line [bresenham algorithm]
	int x1 = endPoint.getX(), x0 = startPoint.getX(), y0 = startPoint.getY(), y1 = endPoint.getY();
	bool steep = abs(y1 - y0) > abs(x1 - x0);
  	if (steep){
		swap(x0, y0);
		swap(x1, y1);
    }
	if (x0 > x1){
		swap(x0, x1);
		swap(y0, y1);
	}
	int deltax = x1 - x0;
	int deltay = abs(y1 - y0);
	float error = 0.0;
	float deltaerr = (float)deltay / (float)deltax;
	int distance=2*deltay-deltax;
	int ystep;
	int y = y0;
	if (y0 < y1) ystep = 1; else ystep = -1;
	// drawing line by coloring 2D array
	for (int x=x0; x < x1; x++){
		int size = startPoint.getPointSize();
		if (steep) {			
			for (int i=0;i<size;i++) {
				for (int j=0;j<size;j++) {
					raster[y+i][x+j].r = lineColor.getRedValue();
					raster[y+i][x+j].g = lineColor.getGreenValue();
					raster[y+i][x+j].b = lineColor.getBlueValue();
				}
			}
		} 
		else {
			for (int i=0;i<size;i++) {
				for (int j=0;j<size;j++) {
					raster[x+i][y+j].r = lineColor.getRedValue();
					raster[x+i][y+j].g = lineColor.getGreenValue();
					raster[x+i][y+j].b = lineColor.getBlueValue();
				}
			}
		}
		error = error + deltaerr;
		if (distance >0) {
			y = y + ystep;
			distance = distance +2*(deltay-deltax);
		}
		else {
			distance=distance+2*deltay;
		}
	}
}