#include "point.hpp"
#include <vector>

class Lagrange {
public:
	Lagrange(std::vector<Point> points);
	~Lagrange();
	
	double p(double x);
private:
	std::vector<Point> points;
	std::vector<double> fg_n;
	
	double g(unsigned int n, double x);
};