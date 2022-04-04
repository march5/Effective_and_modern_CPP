#pragma once
#include "staticVector.h"
#include <iostream>

struct VectorException : public std::runtime_error {
	virtual const char* what() const throw () {
		return "Invalid vector sizes";
	}
};

template<typename T>
class Vector<T, 0> {
	
	int N = 0;
	std::unique_ptr<T[]> arr;

public:

	typedef T value_type;

	Vector(T, int s) {
		arr = std::make_unique<T[]>(s);
		N = s;

		for (int i = 0; i < N; i++) arr[i] = 0;
	}

	Vector(std::initializer_list<T> list) {
		
		auto ptr = list.begin();

		if (list.size() == 1) {
			N = ptr[0];
			arr = std::make_unique<T[]>(N);
		}
		else {
			N = list.size();
			arr = std::make_unique<T[]>(N);
			

			for (int i = 0; i < N; i++) {
				arr[i] = ptr[i];
			}
		}
	}

	Vector(const Vector<T, 0>& vector) {
		N = vector.size();

		arr = std::make_unique<T[]>(N);

		for (int i = 0; i < N; i++) {
			arr[i] = vector[i];
		}
	}

	T& operator[](int i){
		return arr[i];
	}

	T operator[](int i) const {
		return arr[i];
	}

	int size() const {
		return N;
	}

	void resize(int newSize) {

		std::unique_ptr<T[]> temp = std::make_unique<T[]>(newSize);
		
		if (newSize > N) {
			for (int i = 0; i < N; i++) {
				temp[i] = arr[i];
			}
			for (int i = N; i < newSize; i++) temp[i] = 0;
		}
		else if (newSize < N) {
			for (int i = 0; i < newSize; i++) {
				temp[i] = arr[i];
			}
		}

		arr.swap(temp);
		N = newSize;
		temp.reset();
	}

	friend std::ostream& operator <<(std::ostream& os, const Vector& obj){
		for (int i = 0; i < obj.size(); i++) {
			os << obj.arr[i];
			if (i < obj.size() - 1) os << " ";
		}
		return os;
	};

	Vector<T, 0> operator+(const Vector<T, 0>& obj) {
		
		try {
			if (N != obj.size()) throw VectorException();
			Vector<T, 0> ret{(T)N};

			for (int i = 0; i < ret.size(); i++) {
				ret[i] = arr[i] + obj[i];
			}

			return ret;
		}
		catch (VectorException& e) {
			std::cout << e.what() << std::endl;
		}

	}

};


