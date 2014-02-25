/*
        g++ -Wall -O2 juggle_fest.cc -o jugglefest
        ./jugglefest < jugglefest.txt
 */

#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <queue>
#include <set>
#include <map>

#define CIRCUIT_PREFIX "C"
#define JUGGLER_PREFIX "J"
#define H_LABEL 'H'
#define E_LABEL 'E'
#define P_LABEL 'P'

template <bool REVERSE, typename KEY_TYPE, typename SCORE_TYPE> class compare_score {
	public : 
		bool operator () (const std::pair<KEY_TYPE, SCORE_TYPE> &lhs, const std::pair<KEY_TYPE, SCORE_TYPE> &rhs) const {
			/* if REVERSE, then the smallest key will appear on top of the priority queue */
			return REVERSE ? lhs.second > rhs.second : lhs.second < rhs.second;
		}
};

class juggler;

void try_next_match(const size_t, juggler *);
void print_match(const juggler *);

class circuit {
	public :
		const size_t num;
		const unsigned long H, P, E; 
		circuit(const size_t _num, const unsigned long _H, const unsigned long _P, const unsigned long _E) : num(_num), H(_H), P(_P), E(_E) {}
		bool match(const size_t max_circuit_size, juggler *candidate, const unsigned long candidate_score) {
			if (max_circuit_size == candidates.size()) {
				std::pair<juggler *, unsigned long> alt = candidates.top();
				if (alt.second < candidate_score) {
					candidates.pop();
					candidate_objs.erase(alt.first);
					try_next_match(max_circuit_size, alt.first);
					candidates.push(std::pair<juggler *, unsigned long>(candidate, candidate_score));
					candidate_objs.insert(candidate);
					return true;
				}
				return false;
			}
			candidates.push(std::pair<juggler *, unsigned long>(candidate, candidate_score));
			candidate_objs.insert(candidate);
			return true;
		}

		void print_candidates() const {
			for (std::set<juggler *>::const_iterator co_iter = candidate_objs.begin(); co_iter != candidate_objs.end();) {
				print_match((const juggler *)*co_iter);
				++co_iter;
				if (co_iter != candidate_objs.end()) {
					std::cout << ", ";
				}else {
					std::cout << std::endl;
					break;
				}
			}
		}
		~circuit() {}

	private :
		static size_t size;
		std::set<juggler *> candidate_objs;
		std::priority_queue< std::pair<juggler *, unsigned long>, std::vector< std::pair<juggler *, unsigned long> >, compare_score<true, juggler *, unsigned long> > candidates;
};

class juggler {
	public :
		const size_t num;
		const unsigned long H, P, E;
		juggler(const size_t _num, const unsigned long _H, const unsigned long _P, const unsigned long _E) : num(_num), H(_H), P(_P), E(_E) {}
		void add_circuit(circuit * ptr) {
			std::pair<circuit *, unsigned long> cm(ptr, ptr -> H * H + ptr -> P * P + ptr -> E * E);
			preference.push(cm);
			preferred.insert(ptr);
			match_score_list.push_back(cm);
		}
		void add_remaining_circuit(const std::map<size_t, circuit *> & c_map) {
			for (std::map<size_t, circuit *>::const_iterator c_iter = c_map.begin(); c_iter != c_map.end(); ++c_iter) {
				if (preferred.find(c_iter -> second) == preferred.end()) {
					preference.push(std::pair<circuit *, unsigned long>(c_iter -> second, c_iter -> second -> H * H + c_iter -> second -> P * P + c_iter -> second -> E * E));
				}
			}
		}
		void match(const size_t max_circuit_size) {
			std::pair<circuit *, unsigned long> m = preference.front();
			while (!m.first -> match(max_circuit_size, this, m.second)) {
				preference.pop();
				if (preference.empty()) {
					break;
				}
				m = preference.front();
			}
		}
		void match_next(const size_t max_circuit_size) {
			preference.pop();
			if (!preference.empty()) {
				match(max_circuit_size);
			}
			/* std::cerr << num << " match_next " << success << std::endl; */
		}
		void print_match_score_list() const{
			for (std::list< std::pair<circuit *, unsigned long> >::const_iterator l_iter = match_score_list.begin(); l_iter != match_score_list.end();) {
				std::cout << CIRCUIT_PREFIX << l_iter -> first -> num << ":" << l_iter -> second;
				 ++l_iter;
				if (l_iter != match_score_list.end()) {
					std::cout << " ";
				}else {
					return;
				}
			}
		}
		size_t get_current_match() const {
			return preference.front().first -> num;
		}
		~juggler() {}
	private :
		std::queue< std::pair<circuit *, unsigned long> > preference;
		std::list< std::pair<circuit *, unsigned long> > match_score_list;
		std::set<circuit *> preferred;
};

void try_next_match(const size_t max_circuit_size, juggler * j) {
	j -> match_next(max_circuit_size);
}

void print_match(const juggler * j) {
	std::cout << JUGGLER_PREFIX << j -> num << " ";
	j -> print_match_score_list();
}

int main(int argc, char *argv[]) {
	size_t max_circuit_size;
	std::string prefix, w;
	std::map<size_t, juggler *> j_map;
	std::map<size_t, circuit *> c_map;
	while (std::cin >> prefix) {
		/* std::cerr << "prefix == " << prefix << std::endl; */
		size_t num;
		unsigned long H = 0, E = 0, P = 0;
		std::cin >> w;
		std::stringstream ss(w.substr(1));
		ss >> num;
		/* std::cerr << "num == " << num << std::endl; */
		for (unsigned int n = 0; n < 3; ++n) {
			std::cin >> w;
			std::stringstream ss(w.substr(2));
			if (w[0] == H_LABEL) {
				ss >> H;
				/* std::cerr << "H == " << H << std::endl; */
			}else if (w[0] == E_LABEL) {
				ss >> E;
				/* std::cerr << "E == " << E << std::endl; */
			}else if (w[0] == P_LABEL) {
				ss >> P;
				/* std::cerr << "P == " << P << std::endl; */
			}
		}
		if (prefix == JUGGLER_PREFIX) {
			std::cin >> w;
			std::stringstream ss(w);
			/* std::cerr << "preference == " << w << std::endl; */
			juggler *candidate = new juggler(num, H, P, E);
			while (std::getline(ss, w, ',')) {
				size_t c;
				std::stringstream cir_ss(w.substr(1));
				cir_ss >> c; 
				/* std::cerr << "circuit_num == " << c << std::endl; */
				candidate -> add_circuit(c_map[c]);
			}
			candidate -> add_remaining_circuit(c_map);
			j_map.insert(std::pair<size_t, juggler *>(num, candidate));
		}else {
			c_map.insert(std::pair<size_t, circuit *>(num, new circuit(num, H, P, E)));
		}
	}
	max_circuit_size = j_map.size() / c_map.size();
	for (std::map<size_t, juggler *>::const_iterator j_iter = j_map.begin(); j_iter != j_map.end(); ++j_iter) {
		j_iter -> second -> match(max_circuit_size);
	}
	for (std::map<size_t, circuit *>::const_iterator c_iter = c_map.begin(); c_iter != c_map.end(); ++c_iter) {
		std::cout << CIRCUIT_PREFIX << c_iter -> second -> num << ": "; 
		c_iter -> second -> print_candidates();
	}
	for (std::map<size_t, juggler *>::const_iterator j_iter = j_map.begin(); j_iter != j_map.end(); ++j_iter) {
		delete j_iter -> second;
	}
	for (std::map<size_t, circuit *>::const_iterator c_iter = c_map.begin(); c_iter != c_map.end(); ++c_iter) {
		delete c_iter -> second;
	}
	return 0;
}
