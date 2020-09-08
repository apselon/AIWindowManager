#pragma once
#include "Sortable.cpp"

template <typename T>
void swap(T& a, T& b){
	auto tmp = (a);
	a        = (b);
	b        = (tmp);
}

template <typename T>
class Sort {
public:
	virtual void operator ()(Sortable<T>* array, size_t sz) = 0;
};

template <typename T>
class BubbleSort: Sort<T> {
public:	
	void operator ()(Sortable<T>* array, size_t sz) override {

		for (size_t i = 0; i < sz - 1; ++i){
			for (size_t j = 0; j < sz - i - 1; ++j){

				if (array[j + 1] < array[j]){
					swap(array[j], array[j + 1]);
				}

			}
		}

	}
};


