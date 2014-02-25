#include <iostream>
#include <stack>

int main(int argc, char *argv[]){
	unsigned int N;
	int v;
	std::stack< std::pair<int, int> > s;
	std::cin>>N;
	while (N--){
		std::cin>>v;
		if (s.empty()){
			s.push(std::pair<int, int>(v, v));
		}else{
			s.push(std::pair<int, int>(v, v < s.top().second ? v : s.top().second));
		}
	}
	while (!s.empty()){
		std::cout<<"value == "<<s.top().first<<", min == "<<s.top().second<<'\n';
		s.pop();
	}
	return 0;
}
