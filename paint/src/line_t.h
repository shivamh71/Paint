#include "point_t.h"
#include "color_t.h"
#include "pixel_t.h"

// line_t class headerfile

#ifndef LINE_T
#define LINE_T

class line_t {
private:

	point_t startPoint; // first end point of line
	point_t endPoint; // second end point of line
	color_t lineColor; // color of line

public:

	line_t(); // default constructor for line_t

	line_t(point_t &s, point_t &e); // constructor for line_t
		
	line_t(point_t &s, point_t &e, color_t &c); // constructor for line_t
		
	void operator= (line_t l); // operator= for line_t
		
	point_t getLineStartPoint() const; // accessor for start point
		
	point_t getLineEndPoint() const; // accessor for end point
		
	color_t getLineColor() const; // accessor for line color
		
	void setLineStartPoint(point_t &s); // modifier for start point
		
	void setLineEndPoint(point_t &e); // modifier for end point
		
	void setLineColor(color_t &c); // modifier for line color
		
	void draw(vector<vector<pixel_t> > &raster); // draw method for line
};

#endif