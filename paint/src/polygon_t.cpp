#include "line_t.h"
#include "color_t.h"
#include "polygon_t.h"
#include "pixel_t.h"
#include "point_t.h"
#include <iostream>
#include <vector>
#include <list>
using namespace std;

// polygon_t class implementation

polygon_t::polygon_t() { // default constructor for polygon_t
	isFilled = false;
}

polygon_t::polygon_t(list<line_t*> L, color_t b, color_t f, bool s) { // constructor for polygon_t
	lineList = L;
	polygonBorderColor = b;
	polygonFillColor = f;
	isFilled = s;
}

void polygon_t::operator= (polygon_t p) { // operator= for polygon_t
	lineList = p.getLineList();
	polygonBorderColor = p.getPolygonBorderColor();
	polygonFillColor = p.getPolygonFillColor();
	isFilled = p.getFillStatus();
}

void polygon_t::addToLineList(line_t* l){ // adding vertex to polygon
	lineList.push_back(l);
}

void polygon_t::removeFromLineList(line_t* l) { // removing vertex from polygon
	list<line_t*>::iterator it, rit;
	for (it=lineList.begin();it!=lineList.end();it++){
		if (*it == l)
			rit = it;
	}
	lineList.erase(rit);
}

list<line_t*> polygon_t::getLineList() const { // accessor for vertex list
	return lineList;
}

color_t polygon_t::getPolygonBorderColor() const { // accessor for border color
	return polygonBorderColor;
}

color_t polygon_t::getPolygonFillColor() const { // accessor for fill color
	return polygonFillColor;
}

bool polygon_t::getFillStatus() const { // accessor for fill status
	return isFilled;
}

void polygon_t::setPolygonBorderColor(color_t &c) { // modifier for body color
	polygonBorderColor = c;
}

void polygon_t::setPolygonFillColor(color_t &c) { // modifier for fill color
	polygonFillColor = c;
}

void polygon_t::setFillStatus(bool b) { // modifier for fill status
	isFilled = b;
}

void polygon_t::draw(vector<vector<pixel_t> > &raster) { // draw method
	list<line_t*>::iterator it;
	for (it=lineList.begin();it!=lineList.end();it++)
		(*it)->draw(raster);
}

list<point_t> polygon_t::getPointList() { // get vertex list of polygon
	list<point_t> l;
	list<line_t*>::iterator it;
	for (it=lineList.begin();it!=lineList.end();it++)
		l.push_back((*it)->getLineStartPoint());
	return l;
}