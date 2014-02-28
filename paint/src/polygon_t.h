#include "line_t.h"
#include "point_t.h"
#include "color_t.h"
#include "pixel_t.h"
#include <iostream>
#include <vector>
#include <list>
using namespace std;

// polygon_t class headerfile

#ifndef POLYGON_T
#define POLYGON_T

class polygon_t {
private:

	list<line_t*> lineList; // line list of polygon
	color_t polygonBorderColor; // border color of polygon
	color_t polygonFillColor; // fill color of polygon
	bool isFilled;

public:

	polygon_t(); // default constructor for polygon_t
		
	polygon_t(list<line_t*> L, color_t b, color_t f, bool s = false); // constructor for polygon_t
		
	void operator= (polygon_t p); // operator= for polygon_t
		
	void addToLineList(line_t* l); // adding vertex to polygon
		
	void removeFromLineList(line_t* l); // removing vertex from polygon
		
	list<line_t*> getLineList() const; // accessor for vertex list
		
	color_t getPolygonBorderColor() const; // accessor for border color
		
	color_t getPolygonFillColor() const; // accessor for fill color
		
	bool getFillStatus() const; // accessor for fill status
		
	void setPolygonBorderColor(color_t &c); // modifier for body color
		
	void setPolygonFillColor(color_t &c); // modifier for fill color
		
	void setFillStatus(bool b); // modifier for fill status
	
	list<point_t> getPointList(); // get vertex list of a polygon

	void draw(vector<vector<pixel_t> > &raster); // draw method
};

#endif