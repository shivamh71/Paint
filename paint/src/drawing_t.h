#include <iostream>
#include <list>
#include "point_t.h"
#include "polygon_t.h"
#include "line_t.h"
#include "color_t.h"
#include "fill_t.h"
#include "pen_t.h"
#include "pixel_t.h"
using namespace std;

// drawing class headerfile

#ifndef DRAWING_T
#define DRAWING_T

class drawing_t {
public:

	list<point_t*> pointList; // list of points in drawing

	list<polygon_t*> polygonList; // list of polygon objects in drawing

	list<line_t*> lineList; // list of line objects in drawing

	void flushDrawing(); // flushes entire content of drawing

	void addPoint(point_t* p); // add point to list
		
	void addLine(line_t* l); // add line to list
		
	void addPolygon(polygon_t* p); // add polygon to list
		
	void draw(vector<vector<pixel_t> > &raster); // draw method
};

#endif