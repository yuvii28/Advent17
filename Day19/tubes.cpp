#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <queue>

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

	int indexA = 0;
	int indexB = 0;

 	bool isA = true;

 	int sound = 0;

	std::map<std::string, long long> registersA;
	std::map<std::string, long long> registersB;

	registersB["p"] = 0;
	registersB["p"] = 1;

	std::queue<long long> bufferA;
	std::queue<long long> bufferB;


	while(true){
		//Determine which register we are working on
		if (isA){
			if (indexA < 0 || indexA >= int(instructions.size())){
				break;
			}
			line = instructions[indexA];
		} else {
			if (indexB < 0 || indexB >= int(instructions.size())){
				break;
			}
			line = instructions[indexB];
		}
		std::cout << line << std::endl;
		//Split up line
		std::istringstream iss(line);
		std::vector<std::string> splitLine;

		//read each word
		while (iss >> word){
			splitLine.push_back(word);
		}
		std::string instruction = splitLine[0];

		//Run instruction
		if (instruction == "snd"){
			if (isA){
				int val = getVal(splitLine[1], registersA);
				bufferA.push(val);
				sound++;
			} else {
				int val = getVal(splitLine[1], registersB);
				bufferB.push(val);
			}

		} else if (instruction == "set"){
			//First value is always a register
			std::string reg = splitLine[1];

			//Check what we are working on
			if (isA){
				if (registersA.find(reg) == registersA.end()){
					registersA[reg] = 0;
					std::cout << reg << " created in A\n";
				}
				int val = getVal(splitLine[2], registersA);
				//Set register
				registersA[reg] = val;				
			} else {
				if (registersB.find(reg) == registersB.end()){
					registersB[reg] = 0;
					std::cout << reg << " created in B\n";
				}
				int val = getVal(splitLine[2], registersB);
				//Set register
				registersB[reg] = val;
			}
		} else if (instruction == "add"){
			//First value is always a register
			std::string reg = splitLine[1];

			//Check what we are working on
			if (isA){
				if (registersA.find(reg) == registersA.end()){
					registersA[reg] = 0;
					std::cout << reg << " created in A\n";
				}
				int val = getVal(splitLine[2], registersA);
				//Set register
				registersA[reg] += val;				
			} else {
				if (registersB.find(reg) == registersB.end()){
					registersB[reg] = 0;
					std::cout << reg << " created in B\n";
				}
				int val = getVal(splitLine[2], registersB);
				//Set register
				registersB[reg] += val;
			}
		} else if (instruction == "mul"){
			//First value is always a register
			std::string reg = splitLine[1];

			//Check what we are working on
			if (isA){
				if (registersA.find(reg) == registersA.end()){
					registersA[reg] = 0;
					std::cout << reg << " created in A\n";
				}
				int val = getVal(splitLine[2], registersA);
				//Set register
				registersA[reg] *= val;				
			} else {
				if (registersB.find(reg) == registersB.end()){
					registersB[reg] = 0;
					std::cout << reg << " created in B\n";
				}
				int val = getVal(splitLine[2], registersB);
				//Set register
				registersB[reg] *= val;
			}
		} else if (instruction == "mod"){
			//First value is always a register
			std::string reg = splitLine[1];

			//Check what we are working on
			if (isA){
				if (registersA.find(reg) == registersA.end()){
					registersA[reg] = 0;
					std::cout << reg << " created in A\n";
				}
				int val = getVal(splitLine[2], registersA);
				//Set register
				if (val != 0){
					registersB[reg] %= val;
				}
			} else {
				if (registersB.find(reg) == registersB.end()){
					registersB[reg] = 0;
					std::cout << reg << " created in B\n";
				}
				int val = getVal(splitLine[2], registersB);
				//Set register
				if (val != 0){
					registersB[reg] %= val;
				}
			}
		} else if (instruction == "rcv"){
			//If both are empty end
			std::string reg = splitLine[1];
			if (isA){
				int val = getVal(reg, registersA);
				if (val == 0){
					indexA++;
					continue;
				}
				//Is B also trying to receive?
				std::string oline = instructions[indexB];
				if(oline.find("rcv") != std::string::npos){
					//Both trying to receive
					//Are they both empty
					if (bufferA.empty() && bufferB.empty()){
						break;
					}
				}
				//Check if it needs to swap streams
				if (!bufferB.empty()){
					registersA[reg] = bufferB.front();
					bufferB.pop();
				} else {
					//Swap
					isA = false;
					continue;
				}
				
			} else {
				int val = getVal(reg, registersB);
				if (val == 0){
					indexB++;
					continue;
				}
				//Is B also trying to receive?
				std::string oline = instructions[indexA];
				if(oline.find("rcv") != std::string::npos){
					//Both trying to receive
					//Are they both empty
					if (bufferA.empty() && bufferB.empty()){
						break;
					}
				}				
			
				//Check if it needs to swap streams
				if (!bufferA.empty()){
					registersB[reg] = bufferA.front();
					bufferA.pop();
				} else {
					//Swap
					isA = true;
					continue;
				}
			}

		} else if (instruction == "jgz"){
			//First value is always a register
			std::string reg = splitLine[1];
			if (isA){
				int checkVal = getVal(reg, registersA);
				if (!isDigit(reg[reg.size()-1])){
				 	if (registersA.find(reg) == registersA.end()){
						registersA[reg] = 0;
						std::cout << reg << " created in A\n";
					}
				} 
				if (checkVal > 0){
					//Set register
					int val = getVal(splitLine[2], registersA);
					indexA += val;
					continue;
				}				
			} else {
				int checkVal = getVal(reg, registersB);
				if (!isDigit(reg[reg.size()-1])){
				 	if (registersB.find(reg) == registersB.end()){
						registersB[reg] = 0;
						std::cout << reg << " created in B\n";
					}
				}

				if (checkVal > 0){
					//Set register
					int val = getVal(splitLine[2], registersB);
					indexB += val;
					continue;
				}
			}
		}

		if (isA){
			indexA++;			
		} else {
			indexB++;
		}
	}
	std::cout << indexA << " " << indexB << std::endl;


	std::cout << sound << " were sent\n";
	return 0;
}