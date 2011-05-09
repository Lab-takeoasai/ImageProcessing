#include "Matrix.hpp"

Matrix::Matrix(int row, int column) {
	this->row = row;
	this->column = column;
	
	for ( int n = 0; n < row; n++ ) {
		std::vector<double> v(column);
		this->values.push_back(v);
	}
}

void Matrix::description() {
	for ( unsigned int n = 0; n < this->values.size(); n++ ) {
		printf("| ");
		for ( unsigned int m = 0; m < this->values[0].size(); m++ ) {
			printf("%f ", this->values[m][n]);
		}
		printf("|\n");
	}
}

Matrix::~Matrix() {
	
}
