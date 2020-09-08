#include <cstdio>
#include <utility>
#include "Sortable.cpp"
#include "Algorithms.cpp"

template <typename T>
size_t Sortable<T>::cpy_counter = 0;

template <typename T>
size_t Sortable<T>::cmp_counter = 0;

int main(void){
	Sortable<int>::reset_cmp_counter();
	Sortable<int>::reset_cpy_counter();

	Sortable<int> array[5] = {1, 2, 3, 4, 5};

	bubble_sort(array, 5);

	printf("Compare: %lu, Copy: %lu\n", Sortable<int>::count_cmp(), Sortable<int>::count_cpy());

	return 0;
}
