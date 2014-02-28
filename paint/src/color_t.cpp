#include "color_t.h"

// color class implementation

color_t::color_t() { // constructor for color_t
	redValue = 0; // default value for red component
	blueValue = 0; // default value for blue component
	greenValue = 0; // default value for green component
}

color_t::color_t(int r, int g, int b) { // constructor for color_t
	redValue = r; // set value for red component
	greenValue = g; // set value for blue component
	blueValue = b; // set value for green component
}

void color_t::operator= (color_t c) { // operator= for color_t
	this->redValue = c.getRedValue();
	this->greenValue = c.getGreenValue();
	this->blueValue = c.getBlueValue();
}

int color_t::getRedValue() const { // accessor for red component
	return redValue;
}

int color_t::getGreenValue() const { // accessor for green component
	return greenValue;
}

int color_t::getBlueValue() const { // accessor for blue component
	return blueValue;
}

void color_t::setRedValue(int r) { // modifier for red component
	redValue = r;
}

void color_t::setGreenValue(int g) { // modifier for green component
	greenValue = g;
}

void color_t::setBlueValue(int b) { // modifier for blue component
	blueValue = b;
}