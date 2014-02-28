#include "color_t.h"
#include "fill_t.h"
#include "point_t.h"
#include "pixel_t.h"
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// fill_t class implementation

fill_t::fill_t(string fillType, point_t &c) { // constructor for fill_t
	this->fillType = fillType;
	this->fillPoint = c;
	fillColor = fillPoint.getPointColor();
}

string fill_t::getFillType() const { // accessor for fill type
	return fillType;
}

color_t fill_t::getFillColor() const { // accessor for fill color
	return fillColor;
}

void fill_t::setFillType(string t) { // modfifier for fill type
	fillType = t;
}

void fill_t::setFillColor(color_t &c) { // modfifier for fill color
	fillColor = c;
}

void fill_t::floodFill(vector<vector<pixel_t> > &raster, int width, int height) { // flood fill method
	stack<pixel_t> s;
	stack<int> X;
	stack<int> Y;
	int startX=0;
	int startY=0;
	int endX=width-1;
	int endY=height-1;
	int rangeX=endX-startX;
	int rangeY=endY-startY;
	int cx = fillPoint.getX();
	int cy = fillPoint.getY();
	s.push(raster[cx][cy]);
	X.push(cx);
	Y.push(cy);
	pixel_t col, white;
	white = raster[cx][cy];
	col.r = firstColor.getRedValue();
	col.g = firstColor.getGreenValue();
	col.b = firstColor.getBlueValue();
	// coloring neighbours
	while(!s.empty()){
		cx = X.top();
		cy = Y.top();
		s.pop();
		X.pop();
		Y.pop();
		if(cx >startX && raster[cx-1][cy]==white){
			raster[cx-1][cy]=col;
			s.push(raster[cx-1][cy]);
			X.push(cx-1);
			Y.push(cy);
		}
		if(cx < endX && raster[cx+1][cy]==white){
			raster[cx+1][cy]=col;
			s.push(raster[cx+1][cy]);
			X.push(cx+1);
			Y.push(cy);
		}
		if(cy > startY && raster[cx][cy-1]==white){
			raster[cx][cy-1]=col;
			s.push(raster[cx][cy-1]);
			X.push(cx);
			Y.push(cy-1);
		}
		if(cy < endY && raster[cx][cy+1]==white){
			raster[cx][cy+1]=col;
			s.push(raster[cx][cy+1]);
			X.push(cx);
			Y.push(cy+1);
		}
	}
}

void fill_t::checkerFill(vector<vector<pixel_t> > &raster, int width, int height) { // checker fill method
	stack<pixel_t> s;
	stack<int> X;
	stack<int> Y;
	int startX=0;
	int startY=0;
	int endX=width-1;
	int endY=height-1;
	int rangeX=endX-startX;
	int rangeY=endY-startY;
	int cx = fillPoint.getX();
	int cy = fillPoint.getY();
	int mod = 2*checkSize;
	s.push(raster[cx][cy]);
	X.push(cx);
	Y.push(cy);
	pixel_t col, white, altcol, temp;
	white = raster[cx][cy];
	col.r = firstColor.getRedValue();
	col.g = firstColor.getGreenValue();
	col.b = firstColor.getBlueValue();
	altcol.r = secondColor.getRedValue();
	altcol.g = secondColor.getGreenValue();
	altcol.b = secondColor.getBlueValue();
	// coloring neighbours with checks 
	while(!s.empty()){
		cx = X.top();
		cy = Y.top();
		s.pop();
		X.pop();
		Y.pop();
		if(cx >startX && raster[cx-1][cy]==white){
			if(((cx-1)%mod>=checkSize && cy%mod < checkSize) || ((cx-1)%mod < checkSize && cy%mod>=checkSize)){
				raster[cx-1][cy]=altcol;
			}
			else
				raster[cx-1][cy]=col;
			s.push(raster[cx-1][cy]);
			X.push(cx-1);
			Y.push(cy);
		}
		if(cx < endX && raster[cx+1][cy]==white){
			if(((cx+1)%mod>=checkSize && cy%mod < checkSize) || ((cx+1)%mod < checkSize && cy%mod>=checkSize)){
				raster[cx+1][cy]=altcol;
			}
			else
				raster[cx+1][cy]=col;
			s.push(raster[cx+1][cy]);
			X.push(cx+1);
			Y.push(cy);
		}
		if(cy > startY && raster[cx][cy-1]==white){
			if((cx%mod>=checkSize && (cy-1)%mod < checkSize) || (cx%mod < checkSize && (cy-1)%mod>=checkSize)){
				raster[cx][cy-1]=altcol;
			}
			else
				raster[cx][cy-1]=col;
			s.push(raster[cx][cy-1]);
			X.push(cx);
			Y.push(cy-1);
		}
		if(cy < endY && raster[cx][cy+1]==white){
			if((cx%mod>=checkSize && (cy+1)%mod < checkSize) || (cx%mod < checkSize && (cy+1)%mod>=checkSize)){
				raster[cx][cy+1]=altcol;
			}
			else
				raster[cx][cy+1]=col;
			s.push(raster[cx][cy+1]);
			X.push(cx);
			Y.push(cy+1);
		}
	}
}