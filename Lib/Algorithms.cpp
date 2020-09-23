#pragma once
#include <random>
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
	virtual void operator ()(Sortable<T>* array, size_t sz) const = 0;
	virtual ~Sort() = default;
};

template <typename T>
class BubbleSort: public Sort<T> {
public:	
	void operator ()(Sortable<T>* array, size_t sz) const override {

		for (size_t i = 0; i < sz - 1; ++i){
			for (size_t j = 0; j < sz - i - 1; ++j){

				if (array[j + 1] < array[j]){
					swap(array[j], array[j + 1]);
				}
			}
		}
	}
};

template <typename T>
class SelectionSort: public Sort<T> {
public:
	void operator ()(Sortable<T>* array, size_t sz) const override {

		for (size_t i = 0; i < sz - 1; ++i){

			size_t min_idx = i;

			for (size_t j = i + 1; j < sz ; ++j){
           		if (array[j] < array[min_idx]){
                	min_idx = j;
            	}
        	}

	        if (min_idx != i){
		        swap(array[i], array[min_idx]);
       		}
    	}
	}
};

template <typename T>
void test_sort(const Sort<T>& sort, size_t sz) {

	Sortable<T>* array = reinterpret_cast<Sortable<T>*>(::operator new(sizeof(Sortable<T>) * sz));

	for (size_t i = 0; i < sz; ++i){
		array[i] = rand(); 
	};

	Sortable<T>::reset_cmp_counter();
	Sortable<T>::reset_cpy_counter();

	sort(array, sz);
}
