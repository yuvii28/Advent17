#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

bool isDigit(char c){
	return (c >= '0' && c <= '9');
}

int getVal(std::string &value, 	std::map<std::string, long long> &registers){
	int val = 0;
	//Second value is either a register or number
	if (isDigit(value[value.size()-1])){
		val = std::stoi(value);
	} else {
		std::string reg2 = value;
		//Find register -> make new if non exist
		if (registers.find(reg2) == registers.end()){
			registers[reg2] = 0;
		}
		val = registers[reg2];
	}
	return val;
}

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");

	std::string line;
	std::string word;

	std::vector<std::string> instructions;

	//Read over lines
	while (std::getline(in, line)){
		instructions.push_back(line);
	}
	in.close();

	int index = 0;
	int sound = 0;

	std::map<std::string, long long> registers;

	while(index >= 0 && index < int(instructions.size())){
		line = instructions[index];
		//Split up line
		std::istringstream iss(line);
		std::vector<std::string> splitLine;
		//read each word
		while (iss >> word){
			splitLine.push_back(word);
		}
		std::string instruction = splitLine[0];

		if (instruction == "snd"){
			std::string reg = splitLine[1];
			if (registers.find(reg) == registers.end()){
				registers[reg] = 0;
				std::cout << reg << " created\n";
			}
			sound = registers[reg];

		} else if (instruction == "set"){
			//First value is always a register
			std::string reg = splitLine[1];
			if (registers.find(reg) == registers.end()){
				registers[reg] = 0;
				std::cout << reg << " created\n";
			}
			int val = getVal(splitLine[2], registers);
			//Set register
			registers[reg] = val;
		} else if (instruction == "add"){
			//First value is always a register
			std::string reg = splitLine[1];
			if (registers.find(reg) == registers.end()){
				registers[reg] = 0;
				std::cout << reg << " created\n";
			}

			//Set register
			int val = getVal(splitLine[2], registers);
			registers[reg] += val;

		} else if (instruction == "mul"){
			//First value is always a register
			std::string reg = splitLine[1];
			if (registers.find(reg) == registers.end()){
				registers[reg] = 0;
				std::cout << reg << " created\n";
			}

			//Set register
			int val = getVal(splitLine[2], registers);
			registers[reg] *= val;
		} else if (instruction == "mod"){
			//First value is always a register
			std::string reg = splitLine[1];
			if (registers.find(reg) == registers.end()){
				registers[reg] = 0;
				std::cout << reg << " created\n";
			}

			//Set register
			int val = getVal(splitLine[2], registers);
			if (val != 0){
				registers[reg] %= val;
			}
		} else if (instruction == "rcv"){
			//First value is always a register
			std::string reg = splitLine[1];
			if (registers.find(reg) == registers.end()){
				registers[reg] = 0;
				std::cout << reg << " created\n";
			}

			if (registers[reg] != 0){
				std::cout << sound << std::endl;
				return 0;
			}

		} else if (instruction == "jgz"){
			//First value is always a register
			std::string reg = splitLine[1];
			if (registers.find(reg) == registers.end()){
				registers[reg] = 0;
				std::cout << reg << " created\n";
			} else if (registers[reg] > 0){
				//Set register
				int val = std::stoi(splitLine[2]);
				index += val;
				continue;
			}

		}
		index++;
	}
	std::cout << "hmm\n";
	return 0;
}