#include <cstdio>
#include <cmath>
#include <algorithm>

#define MAX_N 101

struct vec{
	double x, y;
	bool operator < (const vec &a) const {
		double t = atan2(y, x), at = atan2(a.y, a.x);
		return t < at;
	}
};

int main(int argc, char *argv[]){
	unsigned int N;
	double x, y, max_x, max_y, cur_x, cur_y;
	struct vec v[MAX_N << 1];
	while (scanf("%u", &N) != EOF && N) {
		for (unsigned int n = 0; n < N; ++n){
			scanf("%lf%lf", &x, &y);
			v[n << 1].x = x;
			v[n << 1].y = y;
			v[n << 1 | 1].x = -x;
			v[n << 1 | 1].y = -y;
		}
		std::sort(v, v + (N << 1));
		cur_x = cur_y = 0;
		for (unsigned int n = 0; n < N; ++n){
			cur_x += v[n].x;
			cur_y += v[n].y;
		}
		max_x = cur_x;
		max_y = cur_y;
		for (unsigned int n = 0, end = N << 1; n < end; ++n){
			unsigned int ci = (n + N) % end;
			
			cur_x += v[ci].x - v[n].x;
			cur_y += v[ci].y - v[n].y;
			if (cur_x * cur_x + cur_y * cur_y > max_x * max_x + max_y * max_y) max_x = cur_x, max_y = cur_y;
		}
		
		printf("Maximum distance = %.3f meters.\n", sqrt((double)max_x * max_x + max_y * max_y));
	}

	return 0;
}
