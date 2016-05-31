/*
 * Matrix.cpp
 *
 *  Created on: May 24, 2016
 *      Author: user
 */
#include "Matrix.h"
#include "Utils.h"

template<class T>
Matrix<T>::Matrix(int rows, int columns) {

	_matrix = new T*[rows];
	for (int i = 0; i < rows; i++){
		_matrix[i] = new T[columns];
	}

	_rows = rows;
	_columns = columns;
}

template<class T>
void Matrix<T>::init(T value) {
	for (int r = 0; r < _rows; r++){
		for (int c = 0; c < _columns; c++){
			_matrix[r][c] = value;
		}
	}
}

template<class T>
void Matrix<T>::init(Matrix<T>* matrix) {
	for (int r = 0; r < _rows; r++){
		for (int c = 0; c < _columns; c++){
			_matrix[r][c] = matrix->get(r,c);
		}
	}
}

template<class T>
void Matrix<T>::set(int row, int col, T value) {
	_matrix[row][col] = value;
}

template<class T>
Matrix<T>::~Matrix() {
	for (int i = 0; i < _rows; i++){
		delete [] _matrix[i];
	}
	delete [] _matrix;
}


template class Matrix<Utils::CELL_STATUS>;
//template class Matrix<Point*>;
