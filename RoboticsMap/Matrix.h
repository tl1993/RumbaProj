#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
// #include "Utils.h"
//#include "PathPlanning/Point.h"
#include <stdexcept>

using namespace std;

template<class T>
class Matrix {
private:
	/**
	 * Declare the matrix
	 */
	T** _matrix;
	int _rows;
	int _columns;

public:
	virtual ~Matrix();

	/**
	 * Constrator - Create new Matrix with the specified size
	 */

	Matrix(int xSize, int ySize);

	T get(int row, int col) const{
		if (row < _rows && col < _columns){
			return _matrix[row][col];
		}

        throw std::invalid_argument( "matrix received exceeded value" );

	};

	int getRows() const{
		return _rows;
	};

	int getColumns() const{
		return _columns;
	};

	void set(int x, int y, T value);
	void init(T value);
	void init(Matrix<T>* matrix);

	void print() const{
		for (int i = 0; i < _rows; i++){
				for (int j = 0; j < _columns; j++){
					cout << get(i, j) << "";
				}
				cout << "\n";
			}
	}
};

#endif /* MATRIX_H_ */
