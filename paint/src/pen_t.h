#include "color_t.h"

#ifndef PEN_T
#define PEN_T

// pen class headerfile

class pen_t {
private:

	int size; // thickness of pen
	color_t penColor; // color of pen
	bool eraseMode; // erase mode of pen

public:
	
	pen_t(); // constructor for pen_t

	void operator= (pen_t p); // operator= for pen_t

	int getPenSize() const; // accessor for pen size

	color_t getPenColor() const; // accessor for pen color

	bool getEraseMode() const; // accessor for pen erase mode
		
	void setPenSize(int s); // modifier for pen size
		
	void setPenColor(color_t &c); // modifier for pen color
		
	void setEraseMode(bool b); // modifier for pen erase mode
};

#endif
