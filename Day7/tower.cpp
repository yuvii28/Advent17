#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string words;
	std::string word;

	std::set<std::string> discNames;
	std::vector<std::string> allNames;
	//Read over lines
	while (std::getline(in, words)){
		std::istringstream iss(words);
		std::vector<std::string> line;
		//read each word
		while (iss >> word){
			//Check its disc name
			auto found = word.find_first_of("(-");
			if (found == std::string::npos){
				//Slice off comma
				auto found = word.find_first_of(",");
				if (found != std::string::npos){
					word.erase(word.size()-1, 1);
				}
				//Add word to line list
				line.push_back(word);
				allNames.push_back(word);
			}
		}
		for (auto i = line.begin(); i != line.end(); i++){
			//Check if exists in set
			if (discNames.find(*i) == discNames.end()){
				discNames.insert(*i);
			} else {
				discNames.erase(discNames.find(*i));
			}
		}
	}
	for (auto i = allNames.begin(); i != allNames.end(); i++){
		if (discNames.find(*i) != discNames.end()){
			std::cout << *i << "\n";
			break;
		}
	}

	in.close();	
	return 0;
}