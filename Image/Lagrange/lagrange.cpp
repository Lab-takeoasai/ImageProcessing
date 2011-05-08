#include "lagrange.hpp"

double Lagrange::g(unsigned int n, double x) {
	double value = 1.0f;
	for( unsigned int i = 0; i < this->points.size(); i++ ) {
		if ( i != n ) {
			value *= (x - this->points[i].x);
		}
	}
	return value;
}

Lagrange::Lagrange(std::vector<Point> points) {
	this->points = points;
	
	//	create Table
	for ( unsigned int i = 0; i < points.size(); i++ ) {
		fg_n.push_back( points[i].y / g(i, points[i].x) );
	}
}

double Lagrange::p(double x) {
	double value = 0.0f;
	for ( unsigned int i = 0; i < points.size(); i++ ) {
		value += fg_n[i] * g(i, x);
	}
	return value;
}

Lagrange::~Lagrange() {
	
}