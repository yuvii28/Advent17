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
	//Read over input
	std::getline(in, line);	
	in.close();	

	//Replace all commas with a space
	std::replace(line.begin(), line.end(), ',', ' ');

	//Read input in
	std::string direction;
	std::istringstream iss(line);
	std::vector<std::pair<std::string, int>> moves;

	//Initialise
	moves.push_back(std::pair<std::string, int>{"nw", 0});
	moves.push_back(std::pair<std::string, int>{"n", 0});
	moves.push_back(std::pair<std::string, int>{"ne", 0});
	moves.push_back(std::pair<std::string, int>{"sw", 0});
	moves.push_back(std::pair<std::string, int>{"s", 0});
	moves.push_back(std::pair<std::string, int>{"se", 0});
	
	//Iterate over numbers in line
	while (iss >> direction){
		for (size_t i = 0; i < moves.size(); i++){
			if (moves[i].first == direction){
				moves[i].second++;
				break;
			}
		}
	}

	int north = abs(moves[1].second - moves[4].second);
	int northEast = abs(moves[2].second - moves[3].second);
	int northWest = abs(moves[0].second - moves[5].second);

	int result = north + std::max(northEast, northWest);
	std::cout << "Moved north: " << north << std::endl;
	std::cout << "Moved NorthEast: " << northEast << std::endl;
	std::cout << "Moved NorthWest: " << northWest << std::endl;

	std::cout << result << " steps needed\n";


	return 0;
}