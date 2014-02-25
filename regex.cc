#include <regex.h>
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
	regex_t reg;
	
	std::string pattern = "[^tpr]{2,}";
	std::string str = "topcoder";
	
	regmatch_t matches[1];
	
	regcomp(&reg,pattern.c_str(),REG_EXTENDED|REG_ICASE);
	
	if (regexec(&reg,str.c_str(),1,matches,0) == 0) {
		std::cout << "Match "; 
		std::cout << str.substr(matches[0].rm_so,matches[0].rm_eo-matches[0].rm_so); 
		std::cout << " found starting at: ";
		std::cout << matches[0].rm_so;
		std::cout << " and ending at "; 
		std::cout << matches[0].rm_eo;
		std::cout << std::endl;
	} else {
		std::cout << "Match not found." << std::endl;
		std::cout << std::endl;
	}
	regfree(&reg);

	return 0;
}
