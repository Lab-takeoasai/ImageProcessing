#include "Image.hpp"

int main (int argc, char const *argv[])
{
//	Image image = Image("sample.bmp");
	
	Image image = Image(500, 500);
	
	image.at(300,300);
	
	for ( int i = 0; i<150; i++ ) {
		for ( int j = 0; j < 150; j++ ) {
			image.set(i, j, Color(255,255,0));
		}
	}
	
	image.save("test.bmp");
	
	
	return 0;
}