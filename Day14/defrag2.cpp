#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <queue>

std::string getHash(std::string string, int line);

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string line;

	//Read over digits
	std::getline(in, line);
	std::vector<std::string> map;

	//Make map
	for (int i = 0; i < 128; i++){
		map.push_back(getHash(line, i));
	}

	int regions = 0;

	//Search for number of regions
	for (int i = 0; i < 128; i++){
		for (int j = 0; j < 128; j++){
			//When you find a 1, change it and convert region
			if (map[i][j] == '1'){
				regions++;
				//Wipe region
				std::queue<std::pair<int, int>> toWipe;
				toWipe.push(std::pair<int, int>{i, j});
				while (!toWipe.empty()){
					//Pop off value
					std::pair<int, int> coords = toWipe.front();
					toWipe.pop();

					//Find adjacent
					if (coords.first != 0 && map[coords.first-1][coords.second] == '1'){
						toWipe.push(std::pair<int, int>{coords.first-1, coords.second});
					}
					if (coords.second != 0 && map[coords.first][coords.second-1] == '1'){
						toWipe.push(std::pair<int, int>{coords.first, coords.second-1});
					}
					if (coords.first != 127 && map[coords.first+1][coords.second] == '1'){
						toWipe.push(std::pair<int, int>{coords.first+1, coords.second});
					}
					if (coords.second != 127 && map[coords.first][coords.second+1] == '1'){
						toWipe.push(std::pair<int, int>{coords.first, coords.second+1});
					}

					//erase point
					map[coords.first][coords.second] = '0';
				}
			}
		}
	}

	std::cout << regions << std::endl;
	return 0;
}

//Function to return number of 1's in a knot hash
std::string getHash(std::string string, int line){
	string.append("-");
	string.append(std::to_string(line));	

	//Set up numbers
	std::vector<int> hash;
	for (int i = 0; i < 256; i++){
		hash.push_back(i);
	}

	std::vector<int> input;

	for (int i = 0; i < int(string.length()); i++){
		input.push_back(int(string[i]));
	}
	
	//Push extra values 17, 31, 73, 47, 23
	input.push_back(17);
	input.push_back(31);
	input.push_back(73);
	input.push_back(47);
	input.push_back(23);


	int skipSize = 0;
	int currIndex = 0;
	//Perform 64 times
	for (size_t x = 0; x < 64; x++){
		//For each line of input
		for (auto i = input.begin(); i != input.end(); i++){
			//Set up
			std::vector<int> values;
			int length = *i;
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
	std::string final;
	//Perform bitwise on each
	for (size_t i = 0; i < 16; i++){
		int result = 0;
		for (size_t j = 0; j < 16; j++){
			result ^= blocks[i][j];
		}
		final.append(std::bitset<8>(result).to_string());
	}
	return final;
}