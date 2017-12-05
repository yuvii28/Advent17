#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string digits;
	std::string digit;
	int result = 0;

	//Read over digits
	while (std::getline(in, digits)){
		std::istringstream iss(digits);
		std::vector<int> numbers;
		//Iterate over numbers in each line
		while (iss >> digit){
			numbers.push_back(std::atoi(digit.c_str()));
		}
		//add difference
		for (size_t i = 0; i < numbers.size()-1; i++){
			for (size_t j = i+1; j < numbers.size(); j++){
				if (numbers[i] % numbers[j] == 0){
					result += (numbers[i]/ numbers[j]);
					break;
				}
				if (numbers[j] % numbers[i] == 0){
					result += (numbers[j]/ numbers[i]);
					break;
				}
			}
		}
	}
	in.close();	
	std::cout << result << "\n";
	return 0;
}