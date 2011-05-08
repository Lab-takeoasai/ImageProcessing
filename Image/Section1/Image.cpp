#include "Image.hpp"
#include "stdlib.h"

#define ICEIL(dividend, divisor) (((dividend) + ((divisor) - 1)) / (divisor))

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::~Color() {
	
}

Image::Image(int width, int height) {
	this->type[0] = 'B';
	this->type[1] = 'M';
	this->reserved1 = 0;
	this->reserved2 = 0;
	this->offset_bits = 54;
	this->header_size = 40;
	this->width = width;
	this->height = height;
	this->planes = 1;
	this->bit_count = 24;
	this->compression = 0;
	this->bpp = this->bit_count / 8;
	this->line_size = ICEIL(this->bpp * this->width, sizeof(this->line_size)) * sizeof(this->line_size);
	this->image_size = this->line_size * this->height;
	this->binary = (char *)malloc(sizeof(char) * this->image_size);
	this->x_pixel_per_meter = 0;
	this->y_pixel_per_meter = 0;
	this->color_used = 0;
	this->color_important = 0;
	this->size = this->offset_bits + this->image_size;
}

Image::Image(std::string path) {
	
	std::ifstream stream;
	stream.open(path.c_str(), std::ios::binary);
	stream.read(this->type, 2);
	stream.read((char *)&this->size, 4);
	stream.read((char *)&this->reserved1, 2);
	stream.read((char *)&this->reserved2, 2);
	stream.read((char *)&this->offset_bits, 4);
	stream.read((char *)&this->header_size, 4);
	stream.read((char *)&this->width, 4);
	stream.read((char *)&this->height, 4);
	stream.read((char *)&this->planes, 2);
	stream.read((char *)&this->bit_count, 2);
	stream.read((char *)&this->compression, 4);
	stream.read((char *)&this->image_size, 4);
	stream.read((char *)&this->x_pixel_per_meter, 4);
	stream.read((char *)&this->y_pixel_per_meter, 4);
	stream.read((char *)&this->color_used, 4);
	stream.read((char *)&this->color_important, 4);
	
	this->bpp = this->bit_count / 8;
	this->line_size = ICEIL(this->bpp * this->width, sizeof(this->line_size)) * sizeof(this->line_size);
	this->image_size = this->line_size * this->height;
	this->binary = (char *)malloc(sizeof(char) * this->image_size);
	stream.read(this->binary, this->image_size);
	stream.close();
}

Color Image::at(int x, int y) {
	char *begin = (this->binary) + ((this->height-y)*this->line_size)+(x*this->bpp);
	unsigned char b = *(begin+0);
	unsigned char g = *(begin+1);
	unsigned char r = *(begin+2);
	return Color(r,g,b);
}

void Image::set(int x, int y, Color clr) {
	char *begin = (this->binary) + ((this->height-y)*this->line_size)+(x*this->bpp);
	*(begin+0) = clr.b;
	*(begin+1) = clr.g;
	*(begin+2) = clr.r;
}

void Image::description() {
	printf("type   [%s]\n", this->type);
	printf("size   [%d]\n", this->size);
	printf("offset [%d]\n", this->offset_bits);
	printf("h_size [%d]\n", this->header_size);
	printf("width  [%d]\n", this->width);
	printf("height [%d]\n", this->height);
	printf("planes [%d]\n", this->planes);
	printf("count  [%d]\n", this->bit_count);
	printf("comprs [%d]\n", this->compression);
	printf("i_size [%d]\n", this->image_size);
	printf("l_size [%d]\n", this->line_size);
}

void Image::save(std::string path) {
	std::ofstream stream;
	stream.open(path.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	stream.write(this->type, 2);
	stream.write((char *)&this->size, 4);
	stream.write((char *)&this->reserved1, 2);
	stream.write((char *)&this->reserved2, 2);
	stream.write((char *)&this->offset_bits, 4);
	stream.write((char *)&this->header_size, 4);
	stream.write((char *)&this->width, 4);
	stream.write((char *)&this->height, 4);
	stream.write((char *)&this->planes, 2);
	stream.write((char *)&this->bit_count, 2);
	stream.write((char *)&this->compression, 4);
	stream.write((char *)&this->image_size, 4);
	stream.write((char *)&this->x_pixel_per_meter, 4);
	stream.write((char *)&this->y_pixel_per_meter, 4);
	stream.write((char *)&this->color_used, 4);
	stream.write((char *)&this->color_important, 4);
	stream.write(this->binary, this->image_size);
	stream.close();
}

Image::~Image() {
	free(this->binary);
}
