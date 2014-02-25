#include <iostream>

void dfs(bool **, bool **, const unsigned int, const unsigned int, const unsigned int, const unsigned int, unsigned int &);

int main(int argc, char *argv[]){
	unsigned int W, H, i, j, nc = 0;
	bool **m, **c;
	std::cin>>W>>H;
	m = new bool*[H];
	c = new bool*[H]; 
	for (i = 0; i < H; ++i){
		m[i] = new bool[W];
		c[i] = new bool[W];
		for (j = 0; j < W; ++j){
			std::cin>>m[i][j];
			c[i][j] = false;
		}
	}
	for (i = 0; i < H; ++i){
		for (j = 0; j < W; ++j){
			if (m[i][j] && !c[i][j]){
				++nc;
				dfs(m, c, i, j, W, H, nc);
			}
		}
	}
	for (i = 0; i < H; ++i){
		delete [] m[i];
		delete [] c[i];
	}
	delete [] m;
	delete [] c;
	std::cout<<"number of connected component(s): "<<nc<<'\n';
	return 0;
}

void dfs(bool **m, bool **c, const unsigned int x, const unsigned int y, const unsigned int W, const unsigned int H, unsigned int &nc){
	c[x][y] = true;
	/*
	if (x > 0){ 
		if (m[x - 1][y] && !c[x - 1][y]){
			dfs(m, c, x - 1, y, W, H, nc);
		}
	}
	// note: only this direction can be omitted without affecting correctness
	*/
	if (x < W - 1){ 
		if (m[x + 1][y] && !c[x + 1][y]){
			dfs(m, c, x + 1, y, W, H, nc);
		}
	}
	if (y > 0){ 
		if (m[x][y - 1] && !c[x][y - 1]){
			dfs(m, c, x, y - 1, W, H, nc);
		}
	}
	if (y < H - 1){ 
		if (m[x][y + 1] && !c[x][y + 1]){
			dfs(m, c, x, y + 1, W, H, nc);
		}
	}
}
