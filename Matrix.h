#pragma once
#include <vector>

template <typename T>
class Matrix {
private:
	std::vector<T> _data;
	size_t _rows;
	size_t _cols;

public:

	Matrix(size_t rows, size_t columns) :_rows(rows), _cols(columns) {
		_data.resize(_rows * _cols);
	}

	size_t rows() {
		return _rows;
	}

	size_t cols() {
		return _cols;
	}

	typename std::vector<T>::iterator begin() {
		return _data.begin();
	}

	typename std::vector<T>::iterator end() {
		return _data.end();
	}

	T& at(size_t row, size_t column) {
		return _data[row * _cols + column];
	}

	T& operator[](int i) {
		return _data[i];
	}

	typename std::vector<T>& data() {
		return data;
	}
};