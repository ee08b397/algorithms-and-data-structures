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
				std::cout << "dist[" << j << "] == INF, pred[" << j << "] == NONE" << std::endl;
			}else {
				std::cout << "dist[" << j << "] == " << dist[j] << ", pred[" << j;
				if (pred[j] == NONE) {
					std::cout << "] == NONE" << std::endl;
				}else {
					std::cout << "] == " << pred[j] << std::endl;
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
	int **w = new int*[30];
	for (unsigned int i = 0; i < 30; ++i) {
		w[i] = new int[30];
		for (unsigned int j = 0; j < 30; ++j) {
			w[i][j] = (i == j ? 0 : INF);
		}
	}

	w[0][1] = 0;
	w[0][16] = -4;

	w[1][2] = 0;
	w[1][10] = -7;

	w[2][3] = 0;
	w[2][7] = -3;

	w[3][4] = 0;
	w[3][8] = -5;

	w[4][5] = 0;
	w[4][6] = -4;

	w[5][29] = 0;

	w[6][29] = 0;

	w[7][8] = 0;
	w[7][14] = -5;

	w[8][9] = 0;
	w[8][13] = -4;
	
	w[9][29] = 0;

	w[10][11] = 0;
	w[10][18] = -3;

	w[11][12] = 0;
	w[11][19] = -5;

	w[12][13] = 0;
	w[12][15] = -4;
	
	w[13][29] = 0;

	w[14][15] = 0;
	w[14][20] = -4;

	w[15][29] = 0;


	w[16][17] = 0;
	w[16][25] = -7;

	w[17][18] = 0;
	w[17][22] = -3;

	w[18][19] = 0;
	w[18][23] = -5;

	w[19][20] = 0;
	w[19][21] = -4;

	w[20][29] = 0;

	w[21][29] = 0;

	w[22][23] = 0;
	
	w[23][24] = 0;
	w[23][28] = -4;

	w[24][29] = 0;

	w[25][26] = 0;

	w[26][27] = 0;

	w[27][28] = 0;

	w[28][29] = 0;

	bellman_ford(30, 0, (const int **)w);
	for (unsigned int i = 0; i < 30; ++i) {
		delete [] w[i];
	}
	delete [] w;
	return 0;
}
