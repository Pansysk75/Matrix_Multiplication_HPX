
#pragma once
#include "Matrix.h"
#include <assert.h>
#include <future>
#include <algorithm>
#include "hpx/hpx.hpp"


namespace matops { namespace seq{

	template <typename T>
	bool equal(Matrix<T>& m1, Matrix<T>& m2) {		
		if (m1.rows() != m2.rows() || m1.cols() != m2.cols()) return false; 		
		return std::equal(m1.begin(), m1.end(), m2.begin());
	}

	template <typename T>
	Matrix<T> add(Matrix<T>& m1, Matrix<T>& m2) {
		assert(m1.rows() == m2.rows() && m1.cols() == m2.cols());
		Matrix<T> result(m1.rows(), m1.cols());
		for (int i = 0; i < m1.rows() * m1.cols(); i++) {
			result[i] = m1[i] + m2[i];
		}
		return result;
	}

	template <typename T>
	Matrix<T> product(Matrix<T>& m1, Matrix<T>& m2) {
		assert(m1.cols() == m2.rows());
		Matrix<T> result(m1.rows(), m2.cols());
		for (int r = 0; r < result.rows(); r++) {
			for (int c = 0; c < result.cols(); c++){
				//for each element of our result matrix
				for (int i = 0; i < m1.cols(); i++)
					result.at(r, c) += m1.at(r, i) * m2.at(i, c);
			}
		}
		return result;
	}
}}

namespace matops { namespace par {

	template <typename T>
	Matrix<T> product(Matrix<T>& m1, Matrix<T>& m2) {	
		assert(m1.cols() == m2.rows());

		Matrix<T> result(m1.rows(), m2.cols());
		std::vector<hpx::future<void>> futures;

		for (int r = 0; r < m1.rows(); r++) {
			for (int c = 0; c < m2.cols(); c++) {
				//runs lambda for each element [r,c] of our final matrix
				futures.push_back( hpx::async([&m1, &m2, &result, r, c]() {
					for (int i = 0; i < m1.cols(); i++) {
						result.at(r, c) += m1.at(r, i) * m2.at(i, c);
					}
					}
				));
			}
		}
		hpx::wait_all(futures);
		return result;
	}

	template <typename T>
	Matrix<T> equal(Matrix<T>& m1, Matrix<T>& m2) {
		if (m1.rows() != m2.rows() || m1.cols() != m2.cols()) return false;
		return hpx::equal(hpx::execution::par_unseq, m1.begin(), m1.end(), m2.begin());
	}

}}
 
