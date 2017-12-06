#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <set>

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
	std::set<std::string> allocations;
	std::string key = toString(instructions);

	int size = instructions.size();
	//While a repetition hasnt occured
	while (allocations.find(key) == allocations.end()){
		result++;
		//Store key
		allocations.insert(key);
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
		std::cout << key << std::endl;
	}

	
	std::cout << result << std::endl;


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