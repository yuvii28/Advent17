#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string line;
	int result = 0;

	//Read over digits
	while (std::getline(in, line)){
		//Read over characters
		for (size_t i = 0; i < line.size(); i++){
			if (line[i] == '!'){
				//Ignore next character
				i++;
			} else if (line[i] == '<'){
				//Garbage
				i++;
				while (line[i] != '>'){
					if (line[i] == '!'){
						i++;
					} else {
						result++;
					}
					i++;
				}
			}
		}
	}
	in.close();	
	std::cout << result << std::endl;
	return 0;
}