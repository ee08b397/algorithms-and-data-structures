#include <cstddef>
#include <cassert>
#include <cstdlib>
#include <ctime>

template <typename T> class two_dimensional_binary_indexed_tree {
	public : 
		two_dimensional_binary_indexed_tree(const size_t __height, const size_t __width) : width(__width), height(__height), data(new T*[__height]) {
			/* memset(data, 0, size * sizeof(T)); */ 
			for (size_t h = 0; h < height; ++h) {
				data[h] = new T[width];
				for (size_t w = 0; w < width; ++w) {
					data[h][w] = 0;
				}
			}
		}
		two_dimensional_binary_indexed_tree(const size_t __height, const size_t __width, const T ** const __data) : width(__width), height(__height), data(new T*[height]) {
			/* memset(data, 0, size * sizeof(T)); */ 
			for (size_t h = 0; h < height; ++h) {
				data[h] = new T[width];
				for (size_t w = 0; w < width; ++w) {
					data[h][w] = 0;
				}
			}
			for (size_t h = 0; h < height; ++h) {
				for (size_t w = 0; w < width; ++w) {
					update(h, w, __data[h][w]);
				}
			}
		}
		~two_dimensional_binary_indexed_tree() {
			for (size_t h = 0; h < height; ++h) {
				delete [] data[h];
			}
			delete [] data;
		}
		void set(const size_t h, const size_t w, const T value) {
			update(h, w, value - get(h, w));
		}
		void update(const size_t h, const size_t w, const T diff) {
			size_t H = h + 1, W;
			while (H <= height) {
				W = w + 1;
				while (W <= width) {
					data[H - 1][W - 1] += diff;
					W += W & (~W + 1);
				}
				H += H & (~H + 1);
			}
		}
		T get(const size_t h, const size_t w) const {
			T result = get_accumulative_sum(h, w);
			if (h) {
				result -= get_accumulative_sum(h - 1, w);
			}
			if (w) {
				result -= get_accumulative_sum(h, w - 1);
			}
			if (h && w) {
				result += get_accumulative_sum(h - 1, w - 1);
			}
			return result;
		}
		T get_accumulative_sum(const size_t h, const size_t w) const {
			T result = 0;
			size_t H = h + 1, W; 
			while (H) {
				W = w + 1;
				while (W) {
					result += data[H - 1][W - 1];
					W -= W & (~W + 1);
				}
				H -= H & (~H + 1);
			}
			return result;
		}
	private :
		const size_t width, height;
		T **const data;
};

int main(int argc, char *argv[]) {
	int sum, *data[6];
	srand(time(0));
	for (size_t i = 0; i < 6; ++i) {
		data[i] = new int[8];
	}
	for (size_t i = 0; i < 6; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			data[i][j] = rand() % 100 - 200;
		}
	}
	two_dimensional_binary_indexed_tree<int> t(6, 8, (const int **)data);
	assert(data[0][0] == t.get(0, 0));
	assert(data[3][4] == t.get(3, 4));
	assert(data[0][4] == t.get(0, 4));
	assert(data[3][0] == t.get(3, 0));
	sum = 0;
	for (size_t i = 0; i <= 4; ++i) {
		for (size_t j = 0; j <= 3; ++j) {
			sum += data[i][j];
		}
	}
	assert(t.get_accumulative_sum(4, 3) == sum);
	sum = 0;
	for (size_t i = 0; i < 6; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			sum += data[i][j];
		}
	}
	assert(t.get_accumulative_sum(5, 7) == sum);
	sum = 0;
	for (size_t i = 0; i < 6; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			int diff = rand() % 100 - 200;
			data[i][j] += diff;
			t.update(i, j, diff);
			sum += data[i][j];
		}
	}
	assert(t.get_accumulative_sum(5, 7) == sum);
	for (size_t i = 0; i < 6; ++i) {
		delete [] data[i];
	}
	return 0;
}
