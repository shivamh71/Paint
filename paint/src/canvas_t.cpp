#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include "canvas_t.h"
#include "pixel_t.h"
#include "color_t.h"
using namespace std;

// canvas class implementation

canvas_t::canvas_t(int w, int h) { // constructor for canvas class
	winWidth = w;
	winHeight = h;
}

int canvas_t::getWinHeight() const { // accessor for window height 
	return winHeight;
}

int canvas_t::getWinWidth() const { // accessor for window width
	return winWidth;
}

void canvas_t::setWinWidth(int w) { // accessor for window width
	winWidth = w;
}

void canvas_t::setWinHeight(int h) { // accessor for window height
	winHeight = h;
}

void canvas_t::initializeCanvas(vector<vector<pixel_t> > &raster, color_t &c) { // initialize new canvas
	// set canvas width, height, and color
	cout<<"Enter canvas width : ";
	cin>>canvasWidth;
	cout<<"Enter canvas height : ";
	cin>>canvasHeight;
	cout<<"enter canvas color (rgb values space separated) : ";
	cin>>backgroundRed;
	cin>>backgroundGreen;
	cin>>backgroundBlue;
	c.setRedValue(backgroundRed);
	c.setGreenValue(backgroundGreen);
	c.setBlueValue(backgroundBlue);
	pixel_t p;
	raster.assign(winWidth,vector<pixel_t>(winHeight,p));

	// color canvas
	for (int i=0;i<winWidth;i++) {
		for (int j=0;j<winHeight;j++) {
   			raster[i][j].r = 0;
   			raster[i][j].g = 0;
   			raster[i][j].b = 0;
   		}
	}
	for (int i=0;i<canvasWidth;i++) {
		for (int j=0;j<canvasHeight;j++) {
   			raster[i][j].r = backgroundRed;
   			raster[i][j].g = backgroundGreen;
   			raster[i][j].b = backgroundBlue;
   		}
	}
}

void canvas_t::displayCanvas(vector<vector<pixel_t> > &raster, int width, int height, int r, int g, int b) { // display canvas
	// display canvas in loading image
	pixel_t p;
	raster.assign(winWidth,vector<pixel_t>(winHeight,p));
	backgroundRed = r;
	backgroundGreen = g;
	backgroundBlue = b;
	canvasWidth = width;
	canvasHeight = height;
	for (int i=0;i<winWidth;i++) {
		for (int j=0;j<winHeight;j++) {
   			raster[i][j].r = 0;
   			raster[i][j].g = 0;
   			raster[i][j].b = 0;
   		}
	}
	for (int i=0;i<canvasWidth;i++) {
		for (int j=0;j<canvasHeight;j++) {
   			raster[i][j].r = r;
   			raster[i][j].g = g;
   			raster[i][j].b = b;
   		}
	}
}

void canvas_t::deinitializeCanvas(vector<vector<pixel_t> > &raster) { // deinitialize new canvas
	// clear canvas
	raster.clear();
}