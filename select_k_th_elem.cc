#include <iostream>

int select(const size_t, const size_t, int * const);

int main(int argc, char *argv[]){
	size_t i, N, K;
	int *a;
	std::cin>>N>>K;
	a = new int[N];	
	for (i = 0; i < N; ++i){
		std::cin>>a[i];
	}
	std::cout<<select(N, K, a)<<'\n';   //print the k-th largest element
	delete [] a;
	return 0;
}

int select(const size_t N, const size_t K, int * const a){
	if (N == 1){
		return *a;
	}
	size_t m = N / 2, i = 0, j = N - 2;
	int p = a[m], temp;
	temp = a[N - 1];
	a[N - 1] = a[m];
	a[m] = temp;
	while (i < j){
		while (a[i] < p){
			++i;
		}
		while (a[j] > p){
			--j;
		}
		if (i < j){
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}else{
			break;
		}
	}
	temp = a[i];
	a[i] = p;
	a[N - 1] = temp;
	if (i < K){
		return select(N - i, K - i, a + i);
	}
	if (i > K){
		return select(i, K, a);
	}
	return p;
}
