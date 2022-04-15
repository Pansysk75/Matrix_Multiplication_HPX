#pragma once
#include <vector>

template <typename T>
class Matrix {
private:
	std::vector<T> data;
	size_t _rows;
	size_t _cols;

public:

	Matrix(size_t rows, size_t columns) :_rows(rows), _cols(columns) {
		data.resize(_rows * _cols);
	}

	size_t rows() {
		return _rows;
	}

	size_t cols() {
		return _cols;
	}

	typename std::vector<T>::iterator begin() {
		return data.begin();
	}

	typename std::vector<T>::iterator end() {
		return data.end();
	}

	T& at(int row, int column) {
		return data[row * _cols + column];
	}

	T& operator[](int i) {
		return data[i];
	}

};