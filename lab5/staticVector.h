#pragma once

template<typename T, int N>
class Vector {
	T arr[N];

public:

	typedef T value_type;

	Vector(){
		for (int i = 0; i < N; i++) {
			arr[i] = 0;
		}
	}

	Vector(std::initializer_list<T> s) {
		int temp;
		auto ptr = s.begin();

		if (s.size() < N) temp = s.size(); else temp = N;

		for (int i = 0; i < temp; i++)
			arr[i] = ptr[i];

		if (temp < N)
			for (int i = temp; i < N; i++)
				arr[i] = 0;
	}

	Vector(const Vector<T, N>& vector) = default;
	
	int size() const {
		return N;
	}

	T& operator[](int i) {
		return arr[i];
	}

	T operator[](int i) const {
		return arr[i];
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector& obj) {
		for (int i = 0; i < N; i++) {
			os << obj[i];
			if (i < N - 1) os << " ";
		}
		return os;
	}

	Vector<T, N> operator+( const Vector<T,N>& obj) {
		Vector<T, N> ret{};
		
		for (int i = 0; i < ret.size(); i++) {
			ret[i] = arr[i] + obj[i];
		}

		return ret;
	}

};