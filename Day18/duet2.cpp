#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

bool isDigit(char c){
	return (c >= '0' && c <= '9');
}

//Determine the value of input
long long getValue(std::string val, std::map<std::string, long long> &registers){
	if (isDigit(val[val.size()-1])){
		return std::stol(val);
	} else {
		//Check if the register exists
		if (registers.find(val) == registers.end()){
			std::cout << "Created " << val << std::endl;
			registers[val] = 0;
		}
		std::cout << "Returning " << registers[val] << " for " << val << std::endl;
		return registers[val];
	}
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

	//Start system
	bool isWaiting0 = false;
	bool isWaiting1 = false;

	bool is0 = true;

	int sound = 0;
	int sounds = 0;

	int index0 = 0;
	int index1 = 0;

	std::queue<long long> buffer0;
	std::queue<long long> buffer1;

	std::map<std::string, long long> registers0;
	std::map<std::string, long long> registers1;

	//Initialise the register1
	registers1["p"] = 1; 

	while (index0 >= 0 && index0 < int(instructions.size()) &&
	 index1 >= 0 && index1 < int(instructions.size())){
		//Get instruction
		if (is0){
			line = instructions[index0];
		} else {
			line = instructions[index1];
		}
		//Split up line
		std::istringstream iss(line);
		std::vector<std::string> splitLine;
		//read each word
		while (iss >> word){
			splitLine.push_back(word);
		}
		std::string instruction = splitLine[0];
		//Check the Instruction to determine command

		if (instruction == "snd"){
			//Send the value of X to other program
			sounds++;
			if (is0){
				long long X = getValue(splitLine[1], registers0);
				//Add value to buffer for 0
				buffer0.push(X);
				index0++;
			} else {
				//Count sounds
				sound++;
				long long X = getValue(splitLine[1], registers0);
				//Add value to buffer for 1
				buffer1.push(X);
				index1++;
			}
		} else if (instruction == "rcv") {
			//Receive the next value from buffer
			if (is0){
				//Check if buffer1 has values
				//If empty, check if a deadlock has occurred
				if (buffer1.empty()){
					//Deadlock if both instructions are waiting
					if (isWaiting0 && isWaiting1){
						break;
					}
					//Otherwise, swap programs and mark waiting
					is0 = false;
					isWaiting0 = true;
					continue;
				}
				//If value exists, pop it and continue
				isWaiting0 = false;
				std::string reg = splitLine[1];
				registers0[reg] = buffer1.front();

				buffer1.pop();
				index0++;
			} else {
				//Check if buffer0 has values
				//If empty, check if a deadlock has occurred
				if (buffer0.empty()){
					//Deadlock if both instructions are waiting
					if (isWaiting0 && isWaiting1){
						break;
					}
					//Otherwise, swap programs and mark waiting
					is0 = true;
					isWaiting1 = true;
					continue;
				}
				//If value exists, pop it and continue
				isWaiting1 = false;
				std::string reg = splitLine[1];
				registers1[reg] = buffer0.front();
				buffer0.pop();
				index1++;
			}
		} else if (instruction == "set") {
			//Set next register as value
			std::string reg = splitLine[1];
			if (is0){
				registers0[reg] = getValue(splitLine[2], registers0);
				index0++;
			} else {
				registers1[reg] = getValue(splitLine[2], registers1);
				index1++;
			}
		} else if (instruction == "add") {
			//Add Y to X
			std::string reg = splitLine[1];
			if (is0){
				registers0[reg] += getValue(splitLine[2], registers0);
				index0++;
			} else {
				registers1[reg] += getValue(splitLine[2], registers1);
				index1++;
			}
		} else if (instruction == "mul") {
			//Multiply X by Y
			std::string reg = splitLine[1];
			if (is0){
				registers0[reg] *= getValue(splitLine[2], registers0);
				index0++;
			} else {
				registers1[reg] *= getValue(splitLine[2], registers1);
				index1++;
			}
		} else if (instruction == "mod") {
			//Modulus X by Y
			std::string reg = splitLine[1];
			if (is0){
				registers0[reg] *= getValue(splitLine[2], registers0);
				index0++;
			} else {
				registers1[reg] *= getValue(splitLine[2], registers1);
				index1++;
			}
		} else if (instruction == "jgz") {
			//Jump Y based on X
			if (is0){
				long long X = getValue(splitLine[1], registers0);
				if (X > 0){
					index0 += getValue(splitLine[2], registers0);
				} else {
					index0++;
				}
			} else {
				long long X = getValue(splitLine[1], registers1);
				if (X > 0){
					index1 += getValue(splitLine[2], registers1);
				} else {
					index1++;
				}
			}
		}
	}
	std::cout << "Program 1 sent " << sound << " times\n";
	std::cout << "There were a total of " << sounds << "\n";

	return 0;
}