#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "pixel_t.h"
#include "color_t.h"
using namespace std;

// canvas class headerfile

class canvas_t {
private:

	int winWidth; // width of main window
	int winHeight; // height of main window 

public:

	int canvasWidth; // width of canvas

	int canvasHeight; // height of canvas

	int backgroundRed; // red component of background

	int backgroundGreen; // green component of background
	
	int backgroundBlue; // blue component of background
	
	canvas_t(int w, int h); // constructor for canvas class
		
	int getWinHeight() const; // accessor for window height

	int getWinWidth() const; // accessor for window width
	
	void setWinWidth(int w); // modifier for window width

	void setWinHeight(int h); // modifier for window height

	void initializeCanvas(vector<vector<pixel_t> > &raster, color_t &c); // initialize new canvas
				
	void deinitializeCanvas(vector<vector<pixel_t> > &raster); // deinitialize new canvas

	void displayCanvas(vector<vector<pixel_t> > &raster, int width, int height, int r, int g, int b); // display canvas
};