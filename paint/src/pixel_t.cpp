#include "pixel_t.h"

// pixel class implementation

void pixel_t::operator=(pixel_t p) { // operator= for pixel class
	this->r = p.r;
	this->g = p.g;
	this->b = p.b;
}

bool pixel_t::operator==(pixel_t p) { // operator==  for pixel class
	return (r==p.r && g==p.g && b==p.b);
}