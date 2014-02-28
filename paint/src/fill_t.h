#include "color_t.h"
#include "pixel_t.h"
#include "point_t.h"
#include <iostream>
#include <vector>
using namespace std;

// fill_t class headerfile

#ifndef FILL_T
#define FILL_T

class fill_t {
private:

	string fillType; // fill type (CHECKER_BOARD or SOLID)
	color_t fillColor; // color of fill

public:

	point_t fillPoint; // point of fill click

	color_t firstColor; // color of solid fill

	color_t secondColor; // color of checkerboard fill

	int checkSize; // check size
		
	fill_t(string fillType, point_t &c); // constructor for fill_t
				
	string getFillType() const; // accessor for fill type
		
	color_t getFillColor() const; // accessor for fill color
		
	void setFillType(string t); // modfifier for fill type
		
	void setFillColor(color_t &c); // modfifier for fill color
		
	void floodFill(vector<vector<pixel_t> > &raster, int width, int height); // flood fill method

	void checkerFill(vector<vector<pixel_t> > &raster, int width, int height); // checker fill method
};

#endif