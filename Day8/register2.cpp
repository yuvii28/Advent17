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

	int maxValue = 0;

	//Store reference to registers
	std::vector<std::pair<std::string, int>> registers;
	//Read over lines
	while (std::getline(in, words)){
		std::istringstream iss(words);
		std::vector<std::string> splitLine;
		//read each word
		while (iss >> word){
			splitLine.push_back(word);
//			std::cout << word << std::endl;
		}
		int firstReg = -1;
		int secondReg = -1;

		//If first register doesnt exist, create
		//Find register value
		for (size_t index = 0; index < registers.size(); index++){
			if (registers[index].first == splitLine[0]){
				firstReg = index;
				break;
			}
		}	
		//If not found	
		if (firstReg == -1){
			//Make a new register
			registers.push_back(std::make_pair(splitLine[0], 0));
			firstReg = registers.size()-1;			
		}

		//Check for second register
		//Find register value
		for (size_t index = 0; index < registers.size(); index++){
			if (registers[index].first == splitLine[4]){
				secondReg = index;
				break;
			}
		}	
		//If not found	
		if (secondReg == -1){
			//Make a new register
			registers.push_back(std::make_pair(splitLine[4], 0));
			secondReg = registers.size()-1;
		}
		
		int adjustment = 0;
		//Determine adjustment value
		if (splitLine[1] == "inc"){
			adjustment += std::stoi(splitLine[2]);
		} else {
			adjustment -= std::stoi(splitLine[2]);
		}

		auto comparison = splitLine[5];
		int value = std::stoi(splitLine[6]);


		//Check the if statement
		if (comparison == ">"){
			if (registers[secondReg].second > value){
				registers[firstReg].second += adjustment;
			}
		} else if (comparison == "<"){
			if (registers[secondReg].second < value){
				registers[firstReg].second += adjustment;
			}
		} else if (comparison == ">="){
			if (registers[secondReg].second >= value){
				registers[firstReg].second += adjustment;
			}
		} else if (comparison == "<="){
			if (registers[secondReg].second <= value){
				registers[firstReg].second += adjustment;
			}
		} else if (comparison == "=="){
			if (registers[secondReg].second == value){
				registers[firstReg].second += adjustment;
			}
		} else if (comparison == "!="){
			if (registers[secondReg].second != value){
				registers[firstReg].second += adjustment;
			}
		}
		if (registers[firstReg].second > maxValue){
			maxValue = registers[firstReg].second;
		}
	}

	std::cout << maxValue << std::endl;

	in.close();	
	return 0;
}