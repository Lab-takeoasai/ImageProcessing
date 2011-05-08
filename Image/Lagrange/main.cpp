#include "lagrange.hpp"
#include "stdlib.h"

int main (int argc, char const *argv[])
{
	Point p1 = Point(0.1, 3.0);
	Point p2 = Point(2.1, 5.5);
	Point p3 = Point(4.0,21.0);
	Point p4 = Point(5.9,52.0);
	Point p5 = Point(7.1,26.0);
	Point p6 = Point(9.2, 3.0);
	std::vector<Point> points;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	points.push_back(p5);
	points.push_back(p6);
	
	Lagrange lagrange = Lagrange(points);
	
	for ( double x = 0.1; x < 10.0; x += 0.02 ) {
		double y = lagrange.p(x);
		printf("%f %f\n",x, y);
	}
	
	return 0;
}