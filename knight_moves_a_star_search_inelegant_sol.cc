#include <iostream>
#include <set>

#define MAX_L 300
#define NONE 0
#define OPEN 1
#define CLOSED 2

class comp {
	public:
		bool operator () (const std::pair< std::pair<unsigned int, unsigned int>, unsigned int > &lhs, const std::pair< std::pair<unsigned int, unsigned int>, unsigned int > &rhs) const {
			return lhs.second < rhs.second || (lhs.second == rhs.second && (lhs.first.first < rhs.first.first || (lhs.first.first == rhs.first.first && lhs.first.second < rhs.first.second)));
		}
};

unsigned int h(const unsigned int y1, const unsigned int x1, const unsigned int y2, const unsigned int x2) {
	unsigned int dx = x1 > x2 ? (x1 - x2 + 1) / 2 : (x2 - x1 + 1) / 2; 
	unsigned int dy = y1 > y2 ? (y1 - y2 + 1) / 2 : (y2 - y1 + 1) / 2; 
	return dx > dy ? dx : dy;
}

unsigned int get_num_knight_move(const unsigned int l, const unsigned int x1, const unsigned int y1, const unsigned int x2, const unsigned int y2, int state[][MAX_L], unsigned int g_score[][MAX_L], unsigned int f_score[][MAX_L]) {
	unsigned int h_score, tentative_g_score, old_f_score = 0;
	std::set< std::pair< std::pair<unsigned int, unsigned int>, unsigned int >, comp > q;
	for (size_t y = 0; y < l; ++y) {
		for (size_t x = 0; x < l; ++x) {
			state[y][x] = NONE;
		}
	}
	h_score = h(y1, x1, y2, x2);
	q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(y1, x1), h_score));
	g_score[y1][x1] = 0;
	f_score[y1][x1] = h_score;
	while (!q.empty()) {
		std::pair<unsigned int, unsigned int> pt;
		std::set< std::pair< std::pair<unsigned int, unsigned int>, unsigned int > >::const_iterator pt_iter = q.begin();
		pt = pt_iter -> first;
		if (pt.first == y2 && pt.second == x2) {
			return g_score[y2][x2];
		}
		q.erase(pt_iter);
		state[pt.first][pt.second] = CLOSED;
		tentative_g_score = g_score[pt.first][pt.second] + 1;
		if (pt.first + 2 < l && pt.second + 1 < l && state[pt.first + 2][pt.second + 1] != CLOSED) {
			if (state[pt.first + 2][pt.second + 1] != OPEN || tentative_g_score < g_score[pt.first + 2][pt.second + 1]) {
				if (state[pt.first + 2][pt.second + 1] == OPEN) {
					old_f_score = f_score[pt.first + 2][pt.second + 1];
				}
				g_score[pt.first + 2][pt.second + 1] = tentative_g_score;
				f_score[pt.first + 2][pt.second + 1] = tentative_g_score + h(pt.first + 2, pt.second + 1, y2, x2);
				if (state[pt.first + 2][pt.second + 1] != OPEN) {
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 2, pt.second + 1), f_score[pt.first + 2][pt.second + 1]));
					state[pt.first + 2][pt.second + 1] = OPEN;
				}else {
					q.erase(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 2, pt.second + 1), old_f_score));
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 2, pt.second + 1), f_score[pt.first + 2][pt.second + 1]));
				}
			}
		}
		if (pt.first + 1 < l && pt.second + 2 < l && state[pt.first + 1][pt.second + 2] != CLOSED) {
			if (state[pt.first + 1][pt.second + 2] != OPEN || tentative_g_score < g_score[pt.first + 1][pt.second + 2]) {
				if (state[pt.first + 1][pt.second + 2] == OPEN) {
					old_f_score = f_score[pt.first + 1][pt.second + 2];
				}
				g_score[pt.first + 1][pt.second + 2] = tentative_g_score;
				f_score[pt.first + 1][pt.second + 2] = tentative_g_score + h(pt.first + 1, pt.second + 2, y2, x2);
				if (state[pt.first + 1][pt.second + 2] != OPEN) {
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 1, pt.second + 2), f_score[pt.first + 1][pt.second + 2]));
					state[pt.first + 1][pt.second + 2] = OPEN;
				}else {
					q.erase(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 1, pt.second + 2), old_f_score));
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 1, pt.second + 2), f_score[pt.first + 1][pt.second + 2]));
				}
			}
		}
		if (pt.first > 1 && pt.second > 0 && state[pt.first - 2][pt.second - 1] != CLOSED) {
			if (state[pt.first - 2][pt.second - 1] != OPEN || tentative_g_score < g_score[pt.first - 2][pt.second - 1]) {
				if (state[pt.first - 2][pt.second - 1] == OPEN) {
					old_f_score = f_score[pt.first - 2][pt.second - 1];
				}
				g_score[pt.first - 2][pt.second - 1] = tentative_g_score;
				f_score[pt.first - 2][pt.second - 1] = tentative_g_score + h(pt.first - 2, pt.second - 1, y2, x2);
				if (state[pt.first - 2][pt.second - 1] != OPEN) {
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 2, pt.second - 1), f_score[pt.first - 2][pt.second - 1]));
					state[pt.first - 2][pt.second - 1] = OPEN;
				}else {
					q.erase(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 2, pt.second - 1), old_f_score));
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 2, pt.second - 1), f_score[pt.first - 2][pt.second - 1]));
				}
			}
		}
		if (pt.first > 0 && pt.second > 1 && state[pt.first - 1][pt.second - 2] != CLOSED) {
			if (state[pt.first - 1][pt.second - 2] != OPEN || tentative_g_score < g_score[pt.first - 1][pt.second - 2]) {
				if (state[pt.first - 1][pt.second - 2] == OPEN) {
					old_f_score = f_score[pt.first - 1][pt.second - 2];
				}
				g_score[pt.first - 1][pt.second - 2] = tentative_g_score;
				f_score[pt.first - 1][pt.second - 2] = tentative_g_score + h(pt.first - 1, pt.second - 2, y2, x2);
				if (state[pt.first - 1][pt.second - 2] != OPEN) {
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 1, pt.second - 2), f_score[pt.first - 1][pt.second - 2]));
					state[pt.first - 1][pt.second - 2] = OPEN;
				}else {
					q.erase(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 1, pt.second - 2), old_f_score));
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 1, pt.second - 2), f_score[pt.first - 1][pt.second - 2]));
				}
			}
		}
		if (pt.first > 1 && pt.second < l && state[pt.first - 2][pt.second + 1] != CLOSED) {
			if (state[pt.first - 2][pt.second + 1] != OPEN || tentative_g_score < g_score[pt.first - 2][pt.second + 1]) {
				if (state[pt.first - 2][pt.second + 1] == OPEN) {
					old_f_score = f_score[pt.first - 2][pt.second + 1];
				}
				g_score[pt.first - 2][pt.second + 1] = tentative_g_score;
				f_score[pt.first - 2][pt.second + 1] = tentative_g_score + h(pt.first - 2, pt.second + 1, y2, x2);
				if (state[pt.first - 2][pt.second + 1] != OPEN) {
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 2, pt.second + 1), f_score[pt.first - 2][pt.second + 1]));
					state[pt.first - 2][pt.second + 1] = OPEN;
				}else {
					q.erase(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 2, pt.second + 1), old_f_score));
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 2, pt.second + 1), f_score[pt.first - 2][pt.second + 1]));
				}
			}
		}
		if (pt.first + 2 < l && pt.second > 0 && state[pt.first + 2][pt.second - 1] != CLOSED) {
			if (state[pt.first + 2][pt.second - 1] != OPEN || tentative_g_score < g_score[pt.first + 2][pt.second - 1]) {
				if (state[pt.first + 2][pt.second - 1] == OPEN) {
					old_f_score = f_score[pt.first + 2][pt.second - 1];
				}
				g_score[pt.first + 2][pt.second - 1] = tentative_g_score;
				f_score[pt.first + 2][pt.second - 1] = tentative_g_score + h(pt.first + 2, pt.second - 1, y2, x2);
				if (state[pt.first + 2][pt.second - 1] != OPEN) {
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 2, pt.second - 1), f_score[pt.first + 2][pt.second - 1]));
					state[pt.first + 2][pt.second - 1] = OPEN;
				}else {
					q.erase(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 2, pt.second - 1), old_f_score));
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 2, pt.second - 1), f_score[pt.first + 2][pt.second - 1]));
				}
			}
		}
		if (pt.first + 1 < l && pt.second > 1 && state[pt.first + 1][pt.second - 2] != CLOSED) {
			if (state[pt.first + 1][pt.second - 2] != OPEN || tentative_g_score < g_score[pt.first + 1][pt.second - 2]) {
				if (state[pt.first + 1][pt.second - 2] == OPEN) {
					old_f_score = f_score[pt.first + 1][pt.second - 2];
				}
				g_score[pt.first + 1][pt.second - 2] = tentative_g_score;
				f_score[pt.first + 1][pt.second - 2] = tentative_g_score + h(pt.first + 1, pt.second - 2, y2, x2);
				if (state[pt.first + 1][pt.second - 2] != OPEN) {
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 1, pt.second - 2), f_score[pt.first + 1][pt.second - 2]));
					state[pt.first + 1][pt.second - 2] = OPEN;
				}else {
					q.erase(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 1, pt.second - 2), old_f_score));
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first + 1, pt.second - 2), f_score[pt.first + 1][pt.second - 2]));
				}
			}
		}
		if (pt.first > 0 && pt.second + 2 < l && state[pt.first - 1][pt.second + 2] != CLOSED) {
			if (state[pt.first - 1][pt.second + 2] != OPEN || tentative_g_score < g_score[pt.first - 1][pt.second + 2]) {
				if (state[pt.first - 1][pt.second + 2] == OPEN) {
					old_f_score = f_score[pt.first - 1][pt.second + 2];
				}
				g_score[pt.first - 1][pt.second + 2] = tentative_g_score;
				f_score[pt.first - 1][pt.second + 2] = tentative_g_score + h(pt.first - 1, pt.second + 2, y2, x2);
				if (state[pt.first - 1][pt.second + 2] != OPEN) {
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 1, pt.second + 2), f_score[pt.first - 1][pt.second + 2]));
					state[pt.first - 1][pt.second + 2] = OPEN;
				}else {
					q.erase(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 1, pt.second + 2), old_f_score));
					q.insert(std::pair< std::pair<unsigned int, unsigned int>, unsigned int>(std::pair<unsigned int, unsigned int>(pt.first - 1, pt.second + 2), f_score[pt.first - 1][pt.second + 2]));
				}
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	unsigned int N, l, x1, y1, x2, y2;
	int state[MAX_L][MAX_L];
	unsigned int g_score[MAX_L][MAX_L], f_score[MAX_L][MAX_L];
	std::cin >> N;
	for (unsigned int n = 0; n < N; ++n) {
		std::cin >> l >> x1 >> y1 >> x2 >> y2;
		std::cout << get_num_knight_move(l, x1, y1, x2, y2, state, g_score, f_score) << std::endl;
	}
	return 0;
}
