#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

std::string toString (std::vector<int> instructions);

int main(int argc, char* argv[]){
	int result = 0;

	std::ifstream in;
	in.open("input.txt");
	
	int digit;
	std::vector<int> instructions;

	//Read over digits
	while (in >> digit){
		//Add into vector 
		instructions.push_back(digit);
	}
	in.close();	

	//Encode vector into a string
	std::vector<std::string> allocations;
	std::string key = toString(instructions);

	int size = instructions.size();
	//While a repetition hasnt occured
	while (std::find(allocations.begin(), allocations.end(), key) == allocations.end()){
		result++;
		//Store key
		allocations.push_back(key);
		//Find largest value and index
		int index = 0;
		int value = instructions[0];
		int currIndex = -1;

		for (auto i = instructions.begin(); i != instructions.end(); i++){
			currIndex++;
			if (*i > value){
				value = (*i);
				index = currIndex;
			}
		}

		//Perform reallocation
		instructions[index] = 0;
		index++;
		while (value > 0){
			instructions[index % size]++;
			value--;
			index++;
		}

		key = toString(instructions);
	}
		
	//Find first use of key


	std::cout << result << std::endl;
	for (size_t i = 0; i < allocations.size(); i++){
		if (key == allocations[i]){
			std::cout << result - i << std::endl;
		}
	}

	return 0;
}

std::string toString (std::vector<int> instructions){
  	std::ostringstream oss;
  	if (!instructions.empty()) {
	    // Convert all but the last element to avoid a trailing ","
	    std::copy(instructions.begin(), instructions.end()-1,
	        std::ostream_iterator<int>(oss, ","));

	    // Now add the last element with no delimiter
	    oss << instructions.back();
  	}
	return oss.str();
}