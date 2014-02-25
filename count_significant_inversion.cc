#include <iostream>

size_t count_sgn_sgn_inv(const size_t, int * const);

int main(int argc, char *argv[]){
	size_t i, N; 
	unsigned int n_sgn_inv;
	int *a;
	std::cin>>N;
	a = new int[N];
	for (i = 0; i < N; ++i){
		std::cin>>a[i];
	}
	n_sgn_inv = count_sgn_sgn_inv(N, a);
	std::cout<<"sorted array: ";
	for (i = 0; i < N; ++i){
		std::cout<<a[i]<<", ";
	}
	std::cout<<"\nnumber of significant inversion(s): "<<n_sgn_inv<<'\n';
	delete [] a;
	return 0;
}

size_t count_sgn_sgn_inv(const size_t N, int * const a){
	if (N < 2){
		return 0;
	}
	size_t i, j, m = N / 2;
	int *temp = new int[N];
	size_t n_sgn_inv;
	for (i = 0; i < N; ++i){
		temp[i] = a[i];
	}
	n_sgn_inv = count_sgn_sgn_inv(m, temp) + count_sgn_sgn_inv(N - m, temp + m);
	i = 0;
	j = 0;
	while (i < m && j < N - m){
		if (temp[i] < temp[m + j]){
			a[i + j] = temp[i];
			++i;
		}else{
			a[i + j] = temp[m + j];
			++j;
		}
	}
	while (i < m){
		a[i + j] = temp[i];
		++i;
	}
	while (j < N - m){
		a[i + j] = temp[m + j];
		++j;
	}
	i = 0;
	j = 0;
	while (i < m && j < N - m){
		if (temp[i] <= 2 * temp[m + j]){
			++i;
		}else{
			n_sgn_inv += (m - i);
			++j;
		}
	}
	delete [] temp;
	return n_sgn_inv;
}
