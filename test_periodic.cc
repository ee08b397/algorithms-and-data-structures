#include <cmath>
#include <iostream>

#define N_T 80
#define MAX_L 8
#define N_K 8

int main(int argc, char *argv[]){
	unsigned int results[N_T] = {
2,6,3,2,3,
2,8,3,2,1,
1,8,3,6,8,
5,8,8,7,4,
2,6,7,2,4,
5,6,6,6,8,
4,6,7,2,4,
2,6,8,5,3,
4,2,6,6,4,
2,2,7,6,8,
5,1,3,2,3,
1,6,7,7,1,
2,8,3,7,3,
5,6,7,7,4,
5,6,3,6,4,
5,2,7,6,4,
	}, l = 0, count[N_K][MAX_L], denom[MAX_L]; 
	double min_ent_pt = 1e9;
	for (size_t i = 1; i <= MAX_L; ++i){
		double ent_pt = 0.0;
		for (size_t j = 0; j < MAX_L; ++j){
			for (unsigned int k = 0; k < N_K; ++k){
				count[k][j] = 0;
			}
			denom[j] = 0;
		}
		for (size_t j = 0; j < N_T; ++j){
			++count[results[j] - 1][j % i];
			++denom[j % i];
		}
		for (size_t j = 0; j < i; ++j){
			if (denom[j]){
				for (unsigned int k = 0; k < N_K; ++k){
					if (count[k][j]){
						double p = 1.0 * count[k][j] / denom[j];
						ent_pt -= p * log2(p) / i;
					}
				}
			}
		}
		std::cout<<"c == "<<i<<", ent_pt == "<<ent_pt<<'\n';
		if (ent_pt < min_ent_pt){
			min_ent_pt = ent_pt;
			l = i;
		}
	}
	std::cout<<"l == "<<l<<'\n';
	return 0;
}
