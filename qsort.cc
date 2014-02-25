#include <iostream>

template <typename T> void qsort(const ssize_t, const ssize_t, const ssize_t, T[]);

int main(int argc, char *argv[]){
	int test_array[10] = {8, 2, 9, 5, 7, 1, 3, 6, 0, 4};
	qsort<int>(0, 9, 4, test_array);
	for (ssize_t i = 0; i < 10; ++i){
		std::cout<<test_array[i]<<", ";
	}	
	std::cout<<'\n';
	return 0;
}

template <typename T> void qsort(const ssize_t left, const ssize_t right, const ssize_t pivot, T a[]){
	if (right - left > 0){  
		ssize_t l = left, r = right - 1;
		T temp = a[pivot];
		a[pivot] = a[right];
		a[right] = temp;
		for (;;){	
			while (l < right && a[l] <= a[right]){
				++l;
			}
			while (r > left && a[r] >= a[right]){
				--r;
			}
			if (l < r){
				temp = a[r];
				a[r] = a[l];
				a[l] = temp;
			}else{
				break;
			}
		}		
		temp = a[l];	
		a[l] = a[right];
		a[right] = temp; 
		qsort<T>(left, l - 1, (left + l - 1) >> 1, a);
		qsort<T>(r + 1, right, (right + r + 1) >> 1, a);
	}
}
