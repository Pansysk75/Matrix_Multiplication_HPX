
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

		Matrix<T> m3(m1.rows(), m2.cols());	

		hpx::for_each(
			hpx::execution::par_unseq,
			m3.begin(),
			m3.end(),
			[&m1, &m2, &m3](auto&& item) {
				int idx = &item - &(m3[0]);
				for (int j = 0; j < m1.cols(); j++) {
					item += m1.at(idx / m2.cols(), j) * m2.at(j, idx % m2.cols());
				}
			}
			);

		return m3;
	}



	template <typename T>
	Matrix<T> product2(Matrix<T>& m1, Matrix<T>& m2) {
		assert(m1.cols() == m2.rows());

		std::vector<hpx::shared_future<T>> d3(m1.rows() * m2.cols());

		for (size_t i = 0; i < d3.size(); i++) {
			d3[i] = hpx::async([&m1, &m2, i]() {
				T sum = 0;
				for (size_t j = 0; j < m1.cols(); j++) {
					sum += m1.at(i / m2.cols(), j) * m2.at(j, i % m2.cols());
				}
				return sum;
				});
		}
		//transfer results from futures to Matrix object that will be returned
		Matrix<T> m3(m1.rows(), m2.cols());
		for (size_t i = 0; i < d3.size(); i++) {
			m3[i] = d3[i].get();
		}
		return m3;
	}



	template <typename T>
	Matrix<T> equal(Matrix<T>& m1, Matrix<T>& m2) {
		if (m1.rows() != m2.rows() || m1.cols() != m2.cols()) return false;
		return hpx::equal(hpx::execution::par_unseq, m1.begin(), m1.end(), m2.begin());
	}

}}
 
