#include <cstddef>
#include <cassert>

template <typename T> class binary_indexed_tree {
	public : 
		binary_indexed_tree(const size_t __size) : size(__size), data(new T[size]) {
			/* memset(data, 0, size * sizeof(T)); */ 
			for (size_t offset = 0; offset < size; ++offset) {
				data[offset] = 0;
			}
		}
		binary_indexed_tree(const size_t __size, const T __data[]) : size(__size), data(new T[size]) {
			/* memset(data, 0, size * sizeof(T)); */
			for (size_t offset = 0; offset < size; ++offset) {
				data[offset] = 0;
			}
			for (size_t offset = 0; offset < size; ++offset) {
				update(offset, __data[offset]);
			}
		}
		~binary_indexed_tree() {
			delete [] data;
		}
		void set(const size_t offset, const T value) {
			update(offset, value - get(offset));
		}
		void update(const size_t offset, const T diff) {
			size_t n = offset + 1;
			while (n <= size) {
				data[n - 1] += diff;
				n += n & (~n + 1);
			}
		}
		T get(const size_t offset) const {
			/*
			size_t n = offset + 1, n0 = n & offset, z = offset;
			T result = 0;
			while (n != n0) {
				result += data[n - 1];
				n -= n & (~n + 1);
			}
			while (z != n0) {
				result -= data[z - 1];
				z -= z & (~z + 1);
			}
			return result;
			*/
			T result = data[offset];
			if (offset) {
				size_t n = offset + 1, z = n - (n & (~n + 1));
				n = offset;
				while (n != z) {
					result -= data[n - 1];
					n -= n & (~n + 1);
				}
			}
			return result;
		}
		T get_accumulative_sum(const size_t offset) const {
			size_t n = offset + 1;
			T result = 0;
			while (n) {
				result += data[n - 1];
				n -= n & (~n + 1);
			}
			return result;
		}
	private :
		const size_t size;
		T *const data;
};

int main(int argc, char *argv[]) {
	int data[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
	int sum = 0, result;
	binary_indexed_tree<int> b(10, data);
	for (size_t idx = 0; idx < 10; ++idx) {
		assert(data[idx] == b.get(idx));
	}
	for (size_t idx = 0; idx < 10; ++idx) {
		//std::cout << b.get(idx) << std::endl;
		sum += data[idx]; 
		result = b.get_accumulative_sum(idx);
		assert(result == sum);
	}
	sum = 0;
	for (size_t idx = 0; idx < 10; ++idx) {
		b.update(idx, 2);
		data[idx] += 2;
		sum += data[idx]; 
		result = b.get_accumulative_sum(idx);
		assert(result == sum);
	}
	for (size_t idx = 0; idx < 10; ++idx) {
		assert(data[idx] == b.get(idx));
	}
	sum = 0;
	for (size_t idx = 0; idx < 10; ++idx) {
		b.update(idx, (idx * 3 + 4) % 7 + 2);
		data[idx] += (idx * 3 + 4) % 7 + 2;
		sum += data[idx]; 
		result = b.get_accumulative_sum(idx);
		assert(result == sum);
	}
	for (size_t idx = 0; idx < 10; ++idx) {
		assert(data[idx] == b.get(idx));
	}
	sum = 0;
	for (size_t idx = 0; idx < 10; ++idx) {
		b.set(idx, (idx * 3 + 4) % 7 + 2);
		data[idx] = (idx * 3 + 4) % 7 + 2;
		sum += data[idx]; 
		result = b.get_accumulative_sum(idx);
		assert(result == sum);
	}
	for (size_t idx = 0; idx < 10; ++idx) {
		assert(data[idx] == b.get(idx));
	}
	return 0;
}
