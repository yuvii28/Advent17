#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	//Set up numbers
	std::vector<int> hash;
	for (int i = 0; i < 256; i++){
		hash.push_back(i);
	}

	std::vector<int> input;

	int length;
	std::string line;

	//Read over digits
	std::getline(in, line);
	std::istringstream iss(line);
	//Iterate over numbers in line
	while (iss >> length){
		input.push_back(length);
	}
	in.close();	


	int skipSize = 0;
	int currIndex = 0;
	//For each line of input
	for (auto i = input.begin(); i != input.end(); i++){
		//Set up
		std::vector<int> values;
		length = *i;
		int tempIndex = currIndex;
		//get numbers from index to length
		while (length != 0){
			values.push_back(hash[tempIndex % 256]);
			length--;
			tempIndex++;
		}
		//Reverse values
		std::reverse(values.begin(), values.end());
		//Put them back in
		while (length != int(values.size())){
			hash[(currIndex+length)%256] = values[length];
			length++; 
		}

		//Finish off
		currIndex += (*i + skipSize) % 256;
		skipSize++;
	}
	std::cout << hash[0] * hash[1] << std::endl;
	return 0;
}