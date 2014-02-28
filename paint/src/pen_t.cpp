#include "color_t.h"
#include "pen_t.h"

// pen class implementation

pen_t::pen_t() { // constructor for pen_t
	// set default pen color to black
	// size = some default value
	eraseMode = false;
}

void pen_t::operator= (pen_t p) { // operator= for pen_t
	this->size = p.getPenSize();
	this->penColor = p.getPenColor();
	this->eraseMode = p.getEraseMode();
}

int pen_t::getPenSize() const { // accessor for pen size
	return size;
}

color_t pen_t::getPenColor() const { // accessor for pen color
	return penColor;
}

bool pen_t::getEraseMode() const { // accessor for pen erase mode
	return eraseMode;
}

void pen_t::setPenSize(int s) { // modifier for pen size
	size = s;
}

void pen_t::setPenColor(color_t &c) { // modifier for pen color
	penColor = c;
}

void pen_t::setEraseMode(bool b) { // modifier for pen erase mode
	eraseMode = b;
}