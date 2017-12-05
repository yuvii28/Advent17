#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string digits;
	std::string digit;
	int result = 0;
	//Read over digits
	while (std::getline(in, digits)){
		std::istringstream iss(digits);
		int max = -1;
		int min = -1;
		//Iterate over numbers in each line
		while (iss >> digit){
			//Initialise on first digit
			if (max == -1){
				max = std::atoi(digit.c_str());
				min = std::atoi(digit.c_str());
				continue;
			}
			//Compare values
			auto value = std::atoi(digit.c_str());
			if (value > max){
				max = value;
			} else if (value < min) {
				min = value;
			}
		}
		//add difference
		result += (max - min);
	}
	in.close();	
	std::cout << result << "\n";
	return 0;
}