#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string line;
	std::string instruction;

	std::vector<char> programs {'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 
		'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};

	std::map<std::string, std::string> transforms;

 	//Determine map
	std::string start = "abcdefghijklmnop";
	std::string end;


	std::getline(in, line);
	//Replace all commas with spaces
	std::replace(line.begin(), line.end(), ',', ' ');

	//Read over digits
	for (size_t run = 0; run < 1000000000; run++){
		//Have we seen this order?
		auto it = transforms.find(start);
		if (it == transforms.end()){
			std::istringstream iss(line);
			while (iss >> instruction){
				//First letter determines instruction
				if (instruction[0] == 's'){
					//Spin
					//Manipulate string
					instruction.erase(0, 1);
					std::istringstream iss2(instruction);
					int a;

					iss2 >> a;
					
					//Perform spin
					std::vector<char> v;

					//Copy all of the spun characters
					for (size_t i = programs.size() - a; i < (programs.size()*2) - a; i++){
						v.push_back(programs[i % programs.size()]);
					}

					for (size_t i = 0; i < programs.size(); i++){
						programs[i] = v[i];
					}

				} else if (instruction[0] == 'x'){
					//Exchange
					//Manipulate string
					std::replace(instruction.begin(), instruction.end(), '/', ' ');
					instruction.erase(0, 1);
					std::istringstream iss2(instruction);
					int a;
					int b;

					iss2 >> a;
					iss2 >> b;

					//Swap characters
					int temp = programs[a];
					programs[a] = programs[b];
					programs[b] = temp;

				} else {
					//Partner
					std::replace(instruction.begin(), instruction.end(), '/', ' ');
					instruction.erase(0, 1);
					std::istringstream iss2(instruction);
					char a;
					char b;

					iss2 >> a;
					iss2 >> b;

					//Perform partnering
					for (size_t i = 0; i < programs.size(); i++){
						if (programs[i] == a){
							programs[i] = b;
						} else if (programs[i] == b){
							programs[i] = a;
						}
					}
				}
			}
			end = "";
			for (auto i = programs.begin(); i != programs.end(); i++){
				end.push_back(*i);
			}
			transforms[start] = end;
		}
		start = transforms[start];
	}
	in.close();	

	std::cout << start << std::endl;
	return 0;
}