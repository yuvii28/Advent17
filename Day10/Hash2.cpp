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

	char length;
	std::string line;

	//Read over digits
	std::getline(in, line);
	std::istringstream iss(line);
	//Iterate over numbers in line
	while (iss >> length){
		input.push_back(int(length));
	}
	//Push extra values 17, 31, 73, 47, 23
	input.push_back(17);
	input.push_back(31);
	input.push_back(73);
	input.push_back(47);
	input.push_back(23);
	
	in.close();	


	int skipSize = 0;
	int currIndex = 0;
	//Perform 64 times
	for (size_t x = 0; x < 64; x++){
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
	}

	//Split up into 16 blocks
	std::vector<std::vector<int>> blocks;

	for (size_t i = 0; i < 16; i++){
		blocks.push_back(std::vector<int>{});
		for (size_t j = 0; j < 16; j++){
			blocks[i].push_back(hash[((i*16) + j)]);
		}
	}

	//Perform bitwise on each
	for (size_t i = 0; i < 16; i++){
		int result = 0;
		for (size_t j = 0; j < 16; j++){
			result ^= blocks[i][j];
		}

		std::cout << std::dec << result << " " << std::hex << result << std::endl;
	}


	return 0;
}