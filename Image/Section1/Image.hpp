#include <string>
#include <iostream>
#include <fstream>

class Color {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Color(unsigned char r, unsigned char g, unsigned char b);
	~Color();
};

class Image {
public:
	Image(std::string path);
	Image(int width, int height);
	~Image();
	
	Color at(int x, int y);
	void set(int x, int y, Color clr);
	void description();
	
	void save(std::string path);
protected:
	char type[2];
	int size;
	short int reserved1;
	short int reserved2;
	int offset_bits;
	int header_size;
	int width;
	int height;
	short int planes;
	short int bit_count;
	int compression;
	int image_size;
	int x_pixel_per_meter;
	int y_pixel_per_meter;
	int color_used;
	int color_important;
	char *binary;
private:
	int bpp;
	int line_size;
};
