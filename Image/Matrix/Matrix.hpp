#include <vector>

class Matrix {
public:
	Matrix(int row = 3, int column = 3);
	~Matrix();
	
	void description();
	
	int row;
	int column;
private:
	std::vector< std::vector<double> > values;
};