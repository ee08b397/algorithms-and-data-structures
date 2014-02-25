#include <iostream>

template <typename T> void heap_sort(const ssize_t, T[]);
template <typename T> void s_up(ssize_t, T[]);
template <typename T> void s_down(const ssize_t, ssize_t, T[]);

int main(int argc, char *argv[]){
	int test_array[10] = {3, 2, 7, 1, 6, 0, 9, 4, 5, 8};

	heap_sort<int>(10, test_array);
	for (ssize_t i = 0; i < 10; ++i){
		std::cout<<test_array[i]<<", ";
	} 		
	return 0;
}

template <typename T> void heap_sort(const ssize_t n, T a[]){
	T temp; 
	for (ssize_t i = 1; i < n; ++i){
		s_up(i, a);
	}
	for (ssize_t i = n - 1; i > 0; --i){
		temp = a[i];
		a[i] = a[0];
		a[0] = temp;	
		s_down<T>(i, 0, a);	
	}
}

template <typename T> void s_up(ssize_t current, T a[]){
	ssize_t parent;
	T temp;
	while (current){
		parent = (current & 1) ? (current >> 1) : ((current >> 1) - 1);
		if (a[current] > a[parent]){
			temp = a[parent];
			a[parent] = a[current];
			a[current] = temp;
			current = parent;
		}else{
			return;
		}		
	}
}

template <typename T> void s_down(const ssize_t n, ssize_t current, T a[]){
	for (;;){
		ssize_t l = (current << 1) + 1, r = (current << 1) + 2, swap = current;
		T temp;
		if (l < n && a[l] > a[swap]){
			swap = l;
		}
		if (r < n && a[r] > a[swap]){
			swap = r;
		}
		if (swap != current){
			temp = a[swap];
			a[swap] = a[current];
			a[current] = temp;
			current = swap;
		}else{
			return;
		}
	}
}
