#include <assert.h>
#include <iostream>

template<typename T> class node {
	private:
		node *next;	
	public:
		const T val;
		node(const T __val) : next(NULL), val(__val) {} 
		node(const T __val, node *__next) : next(__next), val(__val) {} 
		~node(void) {}
		void set_next(node * __next) {
			next = __next;
		}
		node *get_next(void) const {
			return next;
		}
};

template<typename T> class stack {
	private:
		size_t stack_size;
		node<T> *top;
	public:
		stack(void) : stack_size(0), top(NULL) {}
		~stack(void) {
			node<T> *ptr_next, *ptr = top;
			while (ptr) {
				ptr_next = ptr -> get_next();
				delete ptr;
				ptr = ptr_next;
			}
		}
		void push(const T __val) {
			if (!top) {
				top = new node<T>(__val);
			}else {
				top = new node<T>(__val, top);	
			}
			++stack_size;
		}
		T pop(void) {
			assert(top);
			T val = top -> val;
			node<T> *next = top -> get_next(); 
			delete top;
			top = next;
			--stack_size;
			return val;
		}
		bool empty(void) const {
			return top == NULL;
		} 
		size_t size(void) const {
			return stack_size;
		}
};

template<typename T> class queue
{

	private:
		stack<T> in, out;
	public:
		queue(void) {}
		~queue(void) {}
		void enqueue(T val) {
			in.push(val);
		}	
		T dequeue(void) {
			if (out.empty()) {
				assert(!in.empty()); 	
				while (!in.empty()) {
					out.push(in.pop());
				}
				return out.pop();
			}else {
				return out.pop();
			}
		}
		bool empty(void) const {
			return in.empty() && out.empty(); 
		}
		size_t size(void) const {
			return in.size() + out.size();
		}
};

int main(int argc, char *argv[]) {
	queue<int> q;
	for (int i = 0; i < 10; ++i) {
		q.enqueue(i * i);
		if (i % 4 == 1) {
			q.dequeue();
		}
	}
	while (!q.empty()) {
		std::cout<<q.dequeue()<<", ";
	}
	std::cout<<"\n";
	return 0;
}
