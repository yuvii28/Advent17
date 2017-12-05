#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string words;
	std::string word;
	int result = 0;
	//Read over lines
	while (std::getline(in, words)){
		std::istringstream iss(words);
		std::set<std::string> dict;
		bool hasDup = false;
		//read each word
		while (iss >> word){
			std::sort(word.begin(), word.end());
			if (dict.find(word) == dict.end()){
				dict.insert(word);
			} else {
				hasDup = true;
				break;
			}
		}
		if (!hasDup){
			result++;
		}
	}
	in.close();	
	std::cout << result << "\n";
	return 0;
}

