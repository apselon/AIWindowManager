#pragma once
#include <new>
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
class MergeSort: public Sort<T> {
private:
	void merge(Sortable<T>* array, size_t l, size_t m, size_t r, Sortable<T>* tmp_L, Sortable<T>* tmp_R) const {

		size_t len_L = m - l + 1;
		size_t len_R = r - m;



		for (size_t i = 0; i < len_L; ++i){
			tmp_L[i] = array[l + i];
		}

		for (size_t i = 0; i < len_L; ++i){
			tmp_R[i] = array[m + 1 + i];
		}

		size_t i = 0,
			   j = 0,
			   k = l;

		while (i < len_L && j < len_R){
			if (tmp_L[i] <= tmp_R[i]){
				array[k] = tmp_L[i++];
			}

			else {
				array[k] = tmp_R[j++];
			}

			++k;
		}

		while (i < len_L){
			array[k++] = tmp_L[i++];
		}

		while (j < len_R){
			array[k++] = tmp_R[j++];
		}

	}

	void merge_sort(Sortable<T>* array, size_t l, size_t r, Sortable<T>* tmp_L, Sortable<T>* tmp_R) const {
		if (l < r){
			size_t m = l + (r - l) / 2;
			merge_sort(array, l, m, tmp_L, tmp_R);
			merge_sort(array, m + 1, r, tmp_L, tmp_R);
			merge(array, l, m, r, tmp_L, tmp_R);
		}
	}

public:	
	void operator ()(Sortable<T>* array, size_t sz) const override {
		auto tmp_L = reinterpret_cast<Sortable<T>*>(::operator new(sizeof(Sortable<T>) * sz));
		auto tmp_R = reinterpret_cast<Sortable<T>*>(::operator new(sizeof(Sortable<T>) * sz));

		merge_sort(array, 0, sz - 1, tmp_L, tmp_R);

		::operator delete(tmp_L);
		::operator delete(tmp_R);
	}
};

template <typename T>
class QuickSort: public Sort<T> {
private:
	size_t partition(Sortable<T>* array, size_t start, size_t end) const {


		Sortable<T> pivot = array[end];
		size_t p_index = start;

		for (size_t i = start; i < end; ++i){
			if (array[i] <= pivot){
				swap(array[i], array[p_index]);
				++p_index;
			}
		}

		swap(array[end], array[p_index]);

		return p_index;
	}

	void quick_sort(Sortable<T>* array, size_t start, size_t end) const {
		if (start < end){
			size_t p_index = partition(array, start, end);

			if (p_index > 0) {
				quick_sort(array, start,       p_index - 1);
			}

			quick_sort(array, p_index + 1, end);
		}
	}

public:
	void operator ()(Sortable<T>* array, size_t sz) const override {
			quick_sort(array, 0, sz - 1);
	}
};

template <typename T>
void test_sort(const Sort<T>& sort, size_t sz) {

	Sortable<T>* array = reinterpret_cast<Sortable<T>*>(::operator new(sizeof(Sortable<T>) * (2 * sz)));

	for (size_t i = 0; i < sz; ++i){
		array[i] = Sortable<T>(rand()); 
	};

	Sortable<T>::reset_cmp_counter();
	Sortable<T>::reset_cpy_counter();

	sort(array, sz);

	::operator delete(array);
}
