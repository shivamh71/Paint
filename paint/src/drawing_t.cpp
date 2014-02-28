#include <iostream>
#include <list>
#include <vector>
#include "point_t.h"
#include "polygon_t.h"
#include "line_t.h"
#include "color_t.h"
#include "fill_t.h"
#include "pen_t.h"
#include "drawing_t.h"
#include "pixel_t.h"
using namespace std;

void drawing_t::flushDrawing() { // flush entire contents of drawing
	pointList.clear();
	lineList.clear();
	polygonList.clear();
}

void drawing_t::addPoint(point_t* p) { // add point to list
	pointList.push_back(p);
} 

void drawing_t::addLine(line_t* l) { // add line to list
	lineList.push_back(l);
}

void drawing_t::addPolygon(polygon_t* p) { // add polygon to list
	polygonList.push_back(p);
}

void drawing_t::draw(vector<vector<pixel_t> > &raster) { // draw method

	// draw all the points
	list<point_t*>::iterator pit;
	for (pit=pointList.begin();pit!=pointList.end();pit++) {
		(*pit)->draw(raster);
	}

	// draw all the lines
	list<line_t*>::iterator lit;
	for (lit=lineList.begin();lit!=lineList.end();lit++) {
		(*lit)->draw(raster);
	}

	// draw all the polygons
	list<polygon_t*>::iterator plit;
	for (plit=polygonList.begin();plit!=polygonList.end();plit++) {
		(*plit)->draw(raster);
	}
}