#include <iostream>

#define INF 0x7EFFFFFF
#define NONE 0x7EFFFFFF

void bellman_ford(const unsigned int num_vertex, const unsigned int src, const int** w) {
	bool neg_cycle = false, terminated = false;
	int iter = 0;
	int *dist = new int[num_vertex];
	//int *alt_dist = new int[num_vertex];
	unsigned int *pred = new unsigned int[num_vertex];
	for (unsigned int i = 0; i < num_vertex; ++i) {
		dist[i] = (i == src ? 0 : INF);
		pred[i] = NONE;	
	}
	while (!terminated) {
		++iter;
		terminated = true;
		/*
		for (unsigned int j = 0; j < num_vertex; ++j) {
			alt_dist[j] = dist[j];
		}
		*/
		for (unsigned int j = 0; j < num_vertex; ++j) {
			for (unsigned int k = 0; k < num_vertex; ++k) {
				if (j == k) {
					continue;
				}
				int alt;
				if (dist[j] != INF && (alt = dist[j] + w[j][k]) < dist[k]) {
					//alt_dist[k] = alt;
					dist[k] = alt;
					pred[k] = j;
					terminated = false;
				}
			}
		}
		/*
		for (unsigned int j = 0; j < num_vertex; ++j) {
			dist[j] = alt_dist[j];
		}
		*/
		std::cout << "\niteration " << iter << ":" << std::endl;
		for (unsigned int j = 0; j < num_vertex; ++j) {
			if (dist[j] == INF) {
				std::cout << "dist[" << (char)('A' + j) << "] == INF, pred[" << (char)('A' + j) << "] == NONE" << std::endl;
			}else {
				std::cout << "dist[" << (char)('A' + j) << "] == " << dist[j] << ", pred[" << (char)('A' + j);
				if (pred[j] == NONE) {
					std::cout << "] == NONE" << std::endl;
				}else {
					std::cout << "] == " << (char)('A' + pred[j]) << std::endl;
				}
			}
		}
	}
	for (unsigned int j = 0; j < num_vertex; ++j) {
		for (unsigned int k = 0; k < num_vertex; ++k) {
			if (k == j) {
				continue;
			}
			if (dist[j] != INF && dist[k] != INF && dist[j] + w[j][k] < dist[k]) {
				std::cerr << "graph contains a negative-weight cycle" << std::endl;
				neg_cycle = true;
				break;
			}
		}
		if (neg_cycle) {
			break;
		}
	}
	delete [] dist;
	//delete [] alt_dist;
	delete [] pred;
}

int main(int argc, char *argv[]) {
	int **w = new int*[7];
	for (unsigned int i = 0; i < 7; ++i) {
		w[i] = new int[7];
		for (unsigned int j = 0; j < 7; ++j) {
			w[i][j] = (i == j ? 0 : INF);
		}
	}
	w[0][1] = 1;
	w[0][5] = 2;
	w[0][6] = 12;
	w[2][1] = -15;
	w[2][3] = 4;
	w[2][4] = 8;
	w[3][2] = 4;
	w[3][6] = -2;
	w[4][3] = 4;
	w[5][3] = 9;
	w[5][4] = 3;
	w[5][5] = 0;
	w[5][6] = 12;
	w[6][1] = -12;
	w[6][2] = 2;
	w[6][3] = 32;
	w[6][4] = -1;
	w[6][5] = -4;
	bellman_ford(7, 0, (const int **)w);
	for (unsigned int i = 0; i < 7; ++i) {
		delete [] w[i];
	}
	delete [] w;
	return 0;
}
