// pixel class headerfile

#ifndef PIXEL_T
#define PIXEL_T

class pixel_t {
public:

	float r; // red value of pixel
	
	float g; // green value of pixel
	
	float b; // blue value of pixel
	
	int x; // x coordinate of pixel
	
	int y; // y coordinate of pixel

	void operator=(pixel_t p); // operator=  for pixel class

	bool operator==(pixel_t p); // operator==  for pixel class
};

#endif