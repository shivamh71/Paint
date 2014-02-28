#include "color_t.h"
#include "pixel_t.h"
#include <iostream>
#include <vector>
using namespace std;

// point class headerfile

#ifndef POINT_T
#define POINT_T

class point_t {
private:

	int x; // x-coordinate of point
	int y; // y-coordinate of point
	int pointSize; // point size
	color_t pointColor; // color of point

public:

	point_t(); // default constructor for point_t

	point_t(int x, int y); // constructor for point_t

	void operator= (point_t p); // operator= for point_t

	int getX() const; // accessor for x-coordinate

	int getPointSize() const; // accessor for pointSize
		
	int getY() const; // accessor for y-coordinate
		
	void setX(int x); // modifier for x-coordinate

	void setPointSize(int size); // modifier for point size
		
	void setY(int y); // modifier for y-coordinate
		
	void draw(vector<vector<pixel_t> > &raster); // draw method for point

	color_t getPointColor(); // accessor for point color

	void setPointColor(color_t &c); // modifier for point color
};

#endif