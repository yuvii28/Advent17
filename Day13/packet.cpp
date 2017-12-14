#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string size;
	std::string line;

	//Track what values have scanners
	std::vector<std::pair<int, int>> depths;


	//Read over lines
	while (std::getline(in, line)){
		//Create the new pipeline
		std::vector<int> pipe;

		std::istringstream iss(line);
		//Iterate over numbers in line and add to pipe connections
		std::pair<int, int> value{0, 0};
		while (iss >> size){
			//If it is the first number, add to depth
			auto found = size.find_first_of(":");
			if (found != std::string::npos){
				size.erase(size.size()-1, 1);
				value.first = std::stoi(size);
			} else {
				//If second, add as a range
				value.second = std::stoi(size);
				depths.push_back(value);
			}
		}
	}
	in.close();	

	int result = 0;
	//For each depth, check if caught
	for (auto i = depths.begin(); i != depths.end(); i++){
		//Depth value = pictosecond value
		int time = (*i).first;
		int range = (*i).second;
		//Find position within range of positions
		//Ie range of 3 scans -> 0 1 2 1 0, repeat every 4 seconds
		int position = time % ((range-1) * 2);

		if (position == 0){
			std::cout << "Caught at " << time << std::endl;
			result += time * range;
		}
	}

	std::cout << "Final severity of " << result << std::endl;

	return 0;
}