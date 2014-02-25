/*
    given 3 arrays A, B, C, find min_{a\in A, b\in B, c\in C} {|a - b| + |b - c| + |c - a|}
*/

#include <algorithm>
#include <iostream>

#define ABS(A, B) ((A) < (B) ? (B) - (A) : (A) - (B)) 

int min_triplet(const size_t nA, const size_t nB, const size_t nC, int *A, int *B, int *C, size_t &idx_A, size_t &idx_B, size_t &idx_C) {
	int current_sum; 
	size_t ia = 0, ib = 0, ic = 0;
	if (nA == 0 || nB == 0 || nC == 0) {
		return -1;
	}
	std::sort(A, A + nA);
	std::sort(B, B + nB);
	std::sort(C, C + nC);
	idx_A = 0;
	idx_B = 0;
	idx_C = 0;
	current_sum = ABS(A[0], B[0]) + ABS(B[0], C[0]) + ABS(C[0], A[0]);
	while (ia < nA && ib < nB && ic < nC) {
		if (A[ia] <= B[ib] && A[ia] <= C[ic]) {
			if (ia + 1 < nA) {
				++ia;
				int sum = ABS(A[ia], B[ib]) + ABS(B[ib], C[ic]) + ABS(C[ic], A[ia]);
				if (sum < current_sum) {
					idx_A = ia;
					idx_B = ib;
					idx_C = ic;
					current_sum = sum;
				}
			}else {
				break;
			}
		}else if (B[idx_B] <= C[idx_C] && B[idx_B] <= A[idx_A]) {
			if (ib + 1 < nB) {
				++ib;
				int sum = ABS(A[ia], B[ib]) + ABS(B[ib], C[ic]) + ABS(C[ic], A[ia]);
				if (sum < current_sum) {
					idx_A = ia;
					idx_B = ib;
					idx_C = ic;
					current_sum = sum;
				}
			}else {
				break;
			}
		}else {
			if (ic + 1 < nC) {
				++ic;
				int sum = ABS(A[ia], B[ib]) + ABS(B[ib], C[ic]) + ABS(C[ic], A[ia]);
				if (sum < current_sum) {
					idx_A = ia;
					idx_B = ib;
					idx_C = ic;
					current_sum = sum;
				}
			}else {
				break;
			}
		}
	}
	return current_sum;
}

int main(int argc, char *argv[]) {
	//std::cout << ABS(5 + 3 - 1, 2 + 9) << std::endl;
	size_t nA, nB, nC, idx_A, idx_B, idx_C; 
	int *A, *B, *C;
	std::cin >> nA >> nB >> nC;
	if (nA == 0 || nB == 0 || nC == 0) {
		return 0;
	}
	//std::cout << nA << ", " << nB << ", " << nC << std::endl;
	A = new int[nA];
	B = new int[nB];
	C = new int[nC];
	for (size_t i = 0; i < nA; ++i) {
		std::cin >> A[i];
	}
	for (size_t i = 0; i < nB; ++i) {
		std::cin >> B[i];
	}
	for (size_t i = 0; i < nC; ++i) {
		std::cin >> C[i];
	}
	min_triplet(nA, nB, nC, A, B, C, idx_A, idx_B, idx_C);
	std::cout << "A: ";
	for (size_t i = 0; i < nA; ++i) {
		std::cout << A[i] << ", ";
	}
	std::cout << "\nB: ";
	for (size_t i = 0; i < nB; ++i) {
		std::cout << B[i] << ", ";
	}
	std::cout << "\nC: "; 
	for (size_t i = 0; i < nC; ++i) {
		std::cout << C[i] << ", ";
	}
	std::cout << "\n";
	std::cout << "|" << A[idx_A] << " - " << B[idx_B] << "| + |"<<B[idx_B] << " - " << C[idx_C] << "| + |" << C[idx_C] << " - " << A[idx_A] << "| = " << (ABS(A[idx_A], B[idx_B]) + ABS(B[idx_B], C[idx_C]) + ABS(C[idx_C], A[idx_A])) << std::endl;
	delete [] A;
	delete [] B;
	delete [] C;
	return 0;
}
