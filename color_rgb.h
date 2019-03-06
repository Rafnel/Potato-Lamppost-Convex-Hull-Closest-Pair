#ifndef COLOR_RGB_H_INCLUDED
#define COLOR_RGB_H_INCLUDED
class color_rgb {
public:
    /*
    * description: constructor sets initial color to black.
    * return: none
    * precondition: none
    * postcondition: new color is created, set to black.
    */
	color_rgb();
	/*
    * description: constructor sets initial color to values received.
    * return: none
    * precondition: r, g, and b are valid color values.
    * postcondition: new color is created, set to r, g, and b.
    */
	color_rgb(int r, int g, int b);
	/*
    * description: copy constructor copies the values from c to this's color.
    * return: none
    * precondition: c is a valid color.
    * postcondition: this is set to c's values.
    */
    color_rgb(color_rgb const& c);
    /*
    * description: destructor de-allocates dynamic memory, if there is any.
    * return: none
    * precondition: none
    * postcondition: dynamic memory de-allocated.
    */
	virtual ~color_rgb();
	/*
    * description: function gets the red value.
    * return: int
    * precondition: none
    * postcondition: value of red is returned.
    */
	int getR();
	/*
    * description: function gets the green value.
    * return: int
    * precondition: none
    * postcondition: value of green is returned.
    */
	int getG();
	/*
    * description: function gets the blue value.
    * return: int
    * precondition: none
    * postcondition: value of blue is returned.
    */
	int getB();

	/*
    * description: function sets the red value.
    * return: none
    * precondition: int r is in the valid color range.
    * postcondition: value of red is set to r.
    */
	void setR(int r);
	/*
    * description: function sets the green value.
    * return: none
    * precondition: int g is in the valid color range.
    * postcondition: value of green is set to r.
    */
	void setG(int g);
	/*
    * description: function sets the blue value.
    * return: none
    * precondition: int b is in the valid color range.
    * postcondition: value of blue is set to b.
    */
	void setB(int b);

	/*
    * description: function sets this color to c
    * return: none
    * precondition: c is a valid color
    * postcondition: this is set to the color c.
    */
	void operator=(const color_rgb& c);

private:
	int r,g,b;
};

#endif
