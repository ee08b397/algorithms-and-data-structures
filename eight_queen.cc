#include <iostream>

#define BOARD_SIZE 8

bool find_sol(const unsigned int col, const unsigned int board_size, unsigned int pos[]){
	if (col >= board_size){
		return true;
	}
	bool a, sol = false;
	for (unsigned int p = 0; p < board_size; ++p){
		a = false;
		for (unsigned int c = 0; c < col; ++c){
			if (pos[c] == p || pos[c] - p == col - c || pos[c] - p == c - col){
				a = true;
				break;
			}
		}
		if (!a){
			pos[col] = p;
			if (find_sol(col + 1, board_size, pos)){
				sol = true;
				break;
			}
		}
	}
	return sol;
}

int main(int argc, char *argv[]){
	unsigned int sol[BOARD_SIZE];
	for (unsigned int i = 0; i < BOARD_SIZE; ++i){
		sol[i] = BOARD_SIZE;
	}
	if (find_sol(0, BOARD_SIZE, sol)){
		for (unsigned int i = 0; i < BOARD_SIZE; ++i){
			for (unsigned int j = 0; j < BOARD_SIZE; ++j){
				if (i == sol[j]){
					std::cout<<" Q";
				}else{
					std::cout<<" #";
				}
			}
			std::cout<<'\n';
		}
	}
	return 0;
}
