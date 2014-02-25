#include <iostream>
#include <string>

static inline double levenshtein_similarity(const std::string& s1, const std::string& s2){
	const size_t len1 = s1.size(), len2 = s2.size();
	unsigned int **d = new unsigned int*[len1 + 1];
	for (unsigned int i = 0; i < len1 + 1; ++i) d[i] = new unsigned int[len2 + 1];
	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;
	for(unsigned int i = 1; i <= len1; ++i) for(unsigned int j = 1; j <= len2; ++j) d[i][j] = std::min(std::min(d[i - 1][j] + 1,d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
	for (unsigned int i = 0; i < len1; ++i) delete [] d[i];
	delete [] d;
	return 1.0 - d[len1][len2] * 1.0 / std::max(len1, len2);
}

int main(int arc, char *argv[]) {
	std::cout<<levenshtein_similarity("hello", "h3llo")<<std::endl;
	std::cout<<levenshtein_similarity("h", "haa")<<std::endl;
	std::cout<<levenshtein_similarity("ah", "ahaa")<<std::endl;
	return 0;
}
