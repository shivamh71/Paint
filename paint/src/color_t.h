// color class headerfile

#ifndef COLOR_T
#define COLOR_T

class color_t {
private:

	int redValue; // red component value
	int greenValue; // green component value
	int blueValue; // blue component value

public:

	color_t(); // constructor for color_t

	color_t(int r, int g, int b); // constructor for color_t

	void operator= (color_t c); // operator= for color_t

	int getRedValue() const; // accessor for red component

	int getGreenValue() const; // accessor for green component

	int getBlueValue() const; // accessor for blue component

	void setRedValue(int r); // modifier for red component

	void setGreenValue(int g); // modifier for green component

	void setBlueValue(int b); // modifier for blue component
};

#endif