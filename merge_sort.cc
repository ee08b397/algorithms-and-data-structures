#include <iostream>

template <typename T> void merge_sort(const ssize_t, const ssize_t, const ssize_t, T[], T[]);

int main(int argc, char *argv[]){
	int test_array[10] = {4, 1, 3, 7, 8, 5, 2, 0, 9, 6}, buffer[10];
	merge_sort<int>(10, 0, 9, test_array, buffer);
	for (ssize_t i = 0; i < 10; ++i){
		std::cout<<test_array[i]<<", ";
	}	
	return 0;
}

template <typename T> void merge_sort(const ssize_t n, const ssize_t l, const ssize_t r, T a[], T b[]){
	if (r - l >= 1){
		ssize_t m = (l + r) >> 1, lp = l, rp = m + 1, bp = l;
		merge_sort(n, l, m, a, b);
		merge_sort(n, m + 1, r, a, b);
		while (lp <= m && rp <= r){
			if (a[lp] < a[rp]){
				b[bp++] = a[lp++];
			}else{
				b[bp++] = a[rp++];
			}
		}
		while (lp <= m){
			b[bp++] = a[lp++];
		}	
		while (rp <= r){
			b[bp++] = a[rp++];
		}
		for (ssize_t i = l; i <= r; ++i){
			a[i] = b[i];
		} 
	}
}
