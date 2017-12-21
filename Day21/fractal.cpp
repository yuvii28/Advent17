#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

std::string getString(std::vector<std::string> input){
	std::string ret;
	for (auto i = input.begin(); i != input.end(); i++){
		ret.append(*i);
		ret.append("/");
	}
	ret.erase(ret.size()-1, 1);
	return ret;
}

std::vector<std::string> getVec(std::string input){
	std::replace(input.begin(), input.end(), '/', ' ');
	std::vector<std::string> ret;
	std::istringstream iss(input);
	std::string word;
	while(iss >> word){
		ret.push_back(word);
	}
	return ret;
}

std::vector<std::string> rotate(std::vector<std::string> input){
	std::vector<std::string> ret = input;
	if (ret.size() == 2){
		//Swap corners
		auto temp = ret[0][0];
		ret[0][0] = ret[1][0];
		ret[1][0] = ret[1][1];
		ret[1][1] = ret[0][1];
		ret[0][1] = temp;
	} else {
		//Swap corners
		auto temp = ret[0][0];
		ret[0][0] = ret[2][0];
		ret[2][0] = ret[2][2];
		ret[2][2] = ret[0][2];
		ret[0][2] = temp;

		//Swap middle values
		temp = ret[1][0];
		ret[1][0] = ret[2][1];
		ret[2][1] = ret[1][2];
		ret[1][2] = ret[0][1];
		ret[0][1] = temp;

	}
	return ret;
}

std::vector<std::string> flip(std::vector<std::string> input){
	std::vector<std::string> ret;
	for (auto i = input.begin(); i != input.end(); i++){
		std::string j = *i;
		std::reverse(j.begin(), j.end());
		ret.push_back(j);
	}
	return ret;
}

//Take each section and put back together
std::vector<std::string> putTogether(std::vector<std::vector<std::string>> parts){
	std::vector<std::string> ret;
	for (size_t i = 0; i < parts[0].size(); i++){
		ret.push_back("");
	}
	for (auto part = parts.begin(); part != parts.end(); part++){
		for (size_t i = 0; i < ret.size(); i++){
			ret[i].append((*part)[i]);
		}
	}
	return ret;
}


int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string line;
	std::string word;
	std::map<std::string, std::string> rules;

	//Read over input
	while (std::getline(in, line)){
		std::istringstream iss(line);
		std::vector<std::string> split;
		while (iss >> word){
			split.push_back(word);
		}
		rules[split[0]] = split[2];
	}
	in.close();	

	std::vector<std::string> art;
	art.push_back(".#.");
	art.push_back("..#");
	art.push_back("###");

	//Perform 5 iterations
	for (size_t i = 0; i < 18; i++){
		std::vector<std::string> blocks;
		if (art.size() % 2 == 0){
			//Split into blocks of 2x2
			for (size_t y = 0; y < art.size(); y += 2){
				for (size_t x = 0; x < art.size(); x += 2){
					std::string s = "";
					s.push_back(art[y][x]);
					s.push_back(art[y][x+1]);
					s.append("/");
					s.push_back(art[y+1][x]);
					s.push_back(art[y+1][x+1]);
					blocks.push_back(s);
				}
			}
		} else {
			//Split into blocks of 3x3
			for (size_t y = 0; y < art.size(); y += 3){
				for (size_t x = 0; x < art.size(); x += 3){
					std::string s = "";
					s.push_back(art[y][x]);
					s.push_back(art[y][x+1]);
					s.push_back(art[y][x+2]);
					s.append("/");
					s.push_back(art[y+1][x]);
					s.push_back(art[y+1][x+1]);
					s.push_back(art[y+1][x+2]);
					s.append("/");
					s.push_back(art[y+2][x]);
					s.push_back(art[y+2][x+1]);
					s.push_back(art[y+2][x+2]);
					blocks.push_back(s);
				}
			}
		}
		//Convert each block
		std::vector<std::string> conversions;
		for (auto block = blocks.begin(); block != blocks.end(); block++){
			//Check if block exists
			if (rules.find(*block) != rules.end()){
				conversions.push_back(rules[*block]);
			} else {
				//Flip and rotate to find a match
				std::string search = (*block);
				bool isFound = false;
				for (size_t i = 0; i < 2 && !isFound; i++){
					for (size_t i = 0; i < 4 && !isFound; i++){
						search = getString(rotate(getVec(search)));
						//Does it match
						if (rules.find(search) != rules.end()){
							conversions.push_back(rules[search]);
							isFound = true;
						}
					}
					//Try a flipped version
					search = (*block);
					search = getString(flip(getVec(search)));
				}
			}
		}
		std::vector<std::string> final;
		int numBlocks = 0;
		//Put back together
		if (art.size() % 2 == 0){
			//Theres size / 2 blocks
			numBlocks = art.size() / 2;
		} else {
			numBlocks = art.size() / 3;
		}

		for (size_t i = 0; i < conversions.size(); i += numBlocks){
			std::vector<std::vector<std::string>> parts;
			for (int j = 0; j < numBlocks; j++){
				parts.push_back(getVec(conversions[i+j]));
			}

			//Put them together
			std::vector<std::string> fix = putTogether(parts);
			for (size_t j = 0; j < fix.size(); j++){
				final.push_back(fix[j]);
			}
		}
		art = final;

	} // End 5 loop
	int total = 0;
	for (size_t i = 0; i < art.size(); i++){
		for (size_t j = 0; j < art.size(); j++){
			if (art[i][j] == '#'){
				total++;
			}
		}
	}
	std::cout << total << std::endl;
	return 0;
}