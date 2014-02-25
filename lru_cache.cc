#include <iostream>
#include <map>
#include <climits>

#define MAX_CMD_LENGTH 5
#define MAX_STR_LENGTH 10
#define BOUND "BOUND"
#define SET "SET"
#define GET "GET"
#define PEEK "PEEK"
#define DUMP "DUMP"

typedef struct queue_node {
	std::string key;
	struct queue_node *next, *prev;
} queue_node;

typedef struct cache_entry {
	std::string value;
	queue_node *qnode; 
} cache_entry;

void remove_lru(const size_t num, struct queue_node * const tail, std::map<std::string, cache_entry*> &cache) {
	size_t n = 0;
	while (n < num && !cache.empty()) {
		struct queue_node * const rm = tail -> prev;
		std::map<std::string, cache_entry*>::iterator iter;
		rm -> prev -> next = tail;
		tail -> prev = rm -> prev;
		iter = cache.find(rm -> key);
		delete iter -> second;
		cache.erase(iter);
		delete rm;
		++n;
	}
}

void free_cache(std::map<std::string, cache_entry*> &cache, const queue_node * const queue) {
	const queue_node *ptr = queue, *next;
	while (ptr) {
		next = ptr -> next;
		delete ptr;
		ptr = next;
	}
	for (std::map<std::string, cache_entry*>::const_iterator iter = cache.begin(); iter != cache.end(); ++iter) {
		delete iter -> second;
	}
}

int main(int argc, char *argv[]) {
	size_t N, max_size = 0;
	std::string cmd;
	queue_node *queue = new queue_node(), *tail;
	std::map<std::string, cache_entry*> cache; 
	std::cin >> N;
	queue -> next = new queue_node();
	queue -> prev = NULL;
	tail = queue -> next;
	tail -> prev = queue;
	tail -> next = NULL;
	while (N--) {
		std::cin >> cmd;
		if (!cmd.compare(BOUND)) {
			/* std::cerr << BOUND << " " << arg << std::endl; */
			size_t current_size = cache.size();
			std::cin >> max_size;
			if (current_size > max_size) {
				remove_lru(current_size - max_size, tail, cache);
			}
		}else if (!cmd.compare(SET)) {
			/* std::cerr << SET << " " << arg << std::endl; */
			size_t current_size = cache.size();
			std::string key, val;
			std::map<std::string, cache_entry*>::iterator iter;
			std::cin >> key >> val;
			if ((iter = cache.find(key)) != cache.end()) {

				/*
				queue_node *qnode = iter -> second -> qnode;
				*/

				iter -> second -> value = val;

				/*
				qnode -> prev = queue;
				qnode -> next = queue -> next;
				queue -> next -> prev = qnode;
				queue -> next = qnode;  
				*/

			}else {
				if (current_size == max_size) {
					remove_lru(1, tail, cache);
				}
				cache_entry *ent = new cache_entry();
				queue_node *qnode = new queue_node();
				ent -> value = val;
				ent -> qnode = qnode;
				/*
				qnode -> prev = tail -> prev;
				qnode -> next = tail;
				qnode -> key = key;
				tail -> prev -> next = qnode; 
				tail -> prev = qnode; 
				*/
				qnode -> prev = queue;
				qnode -> next = queue -> next;
				qnode -> key = key; 
				queue -> next -> prev = qnode;
				queue -> next = qnode;  
				cache.insert(std::pair<std::string, cache_entry*>(key, ent));
			}
		}else if (!cmd.compare(GET)) {
			/* std::cerr << GET << " " << arg << std::endl; */
			std::string key;
			std::cin >> key;
			std::map<std::string, cache_entry*>::const_iterator iter;
			if ((iter = cache.find(key)) == cache.end()) {
				std::cout << "NULL" << std::endl;
			}else {
				queue_node *qnode = iter -> second -> qnode;
				qnode -> prev -> next = qnode -> next;
				qnode -> next -> prev = qnode -> prev;
				qnode -> prev = queue;
				qnode -> next = queue -> next;
				queue -> next -> prev = qnode;
				queue -> next = qnode;
				std::cout << iter -> second -> value << std::endl;
			}
		}else if (!cmd.compare(PEEK)) {
			/* std::cerr << PEEK << " " << arg << std::endl; */
			std::string key;
			std::cin >> key;
			std::map<std::string, cache_entry*>::const_iterator iter;
			if ((iter = cache.find(key)) == cache.end()) {
				std::cout << "NULL" << std::endl;
			}else {
				std::cout << iter -> second -> value << std::endl;
			}
		}else if (!cmd.compare(DUMP)) {
			/* std::cerr << DUMP << std::endl; */
			for (std::map<std::string, cache_entry*>::const_iterator iter = cache.begin(); iter != cache.end(); ++iter) {
				std::cout << iter -> first << " " << iter -> second -> value << std::endl;
			}
		}
	}
	free_cache(cache, (const queue_node *)queue);
	return 0;
}
