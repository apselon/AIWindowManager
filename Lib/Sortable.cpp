#pragma once
#include <utility>

using size_t = unsigned long;

template <typename T>
class Sortable {
private:


	static size_t cpy_counter;
	static size_t cmp_counter;
	T val = {};

public:

	Sortable(const T& val): val(val) {
		++cpy_counter;
	};

	Sortable(const Sortable& another): val(another.val) {}

	bool operator <(const Sortable& another) {

		++cmp_counter;

		return val < another.val;
	}


	Sortable& operator =(const Sortable& another){
		if (this != &another){
			val = another.val;

			++cpy_counter;
		}

		return *this;
	}

	Sortable& operator =(Sortable&& another){
		if (this != &another){
			val = std::move(another.val);

			++cpy_counter;
		}

		return *this;
	}

	T get_val(){
		return val;
	}

	static size_t count_cpy(){
		return cpy_counter;
	}

	static size_t count_cmp(){
		return cmp_counter;
	}

	static void reset_cpy_counter(){
		cpy_counter = 0;
	}

	static void reset_cmp_counter(){
		cmp_counter = 0;
	}

};
