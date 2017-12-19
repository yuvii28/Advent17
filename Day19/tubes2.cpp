#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

bool isValid(char c){
	if (c == '|' || c == '-' || c == '+' || (c >= 'A' && c <= 'Z')){
		return true;
	}
	return false;
}

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string line;

	std::vector<std::string> map;

	int count = 0;
	//Read over input
	while (std::getline(in, line)){
		map.push_back(line);
	}
	in.close();	

	//Dir represents direction to travel 
	char dir = 'd';

	size_t x = 0;
	size_t y = 0;
	//Find coordinate to start on
	for (size_t i = 0; i < map[0].size(); i++){
		if (map[0][i] == '|'){
			x = i;
			break;
		}
	}

	while (true){
		count++;
  		if (dir == 'd'){
			//Check below
			if (y < map.size()-1 && isValid(map[y+1][x])){
				//Move 
				y += 1;
				if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
					std::cout << map[y][x];
				}
			} else {
				//Turn
				if (x < map[y].size()-1 && isValid(map[y][x+1])){
					x+= 1;
					dir = 'r';
					if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
						std::cout << map[y][x];
					}
				} else if (x > 0 && isValid(map[y][x-1])){
					x-= 1;
					dir = 'l';
					if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
						std::cout << map[y][x];
					}
				} else {
					break;
				}
			}
		} else if (dir == 'u'){
			//Check below
			if (y > 0 && isValid(map[y-1][x])){
				//Move 
				y -= 1;
				if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
					std::cout << map[y][x];
				}
			} else {
				//Turn
				if (x < map[y].size()-1 && isValid(map[y][x+1])){
					x+= 1;
					dir = 'r';
					if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
						std::cout << map[y][x];
					}
				} else if (x > 0 && isValid(map[y][x-1])){
					x-= 1;
					dir = 'l';
					if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
						std::cout << map[y][x];
					}
				} else {
					break;
				}
			}
		} else if (dir == 'r'){
			//Check below
			if (x < map[y].size()-1 && isValid(map[y][x+1])){
				//Move 
				x += 1;
				if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
					std::cout << map[y][x];
				}
			} else {
				//Turn
				if (y < map.size()-1 && isValid(map[y+1][x])){
					y += 1;
					dir = 'd';
					if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
						std::cout << map[y][x];
					}
				} else if (y > 0 && isValid(map[y-1][x])){
					y-= 1;
					dir = 'u';
					if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
						std::cout << map[y][x];
					}
				} else {
					break;
				}
			}
		} else if (dir == 'l'){
			//Check below
			if (x > 0 && isValid(map[y][x-1])){
				//Move 
				x -= 1;
				if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
					std::cout << map[y][x];
				}
			} else {
				//Turn
				if (y < map.size()-1 && isValid(map[y+1][x])){
					y += 1;
					dir = 'd';
					if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
						std::cout << map[y][x];
					}
				} else if (y > 0 && isValid(map[y-1][x])){
					y-= 1;
					dir = 'u';
					if (map[y][x] >= 'A' && map[y][x] <= 'Z'){
						std::cout << map[y][x];
					}
				} else {
					break;
				}
			}
		}
	}
	std::cout << std::endl;
	std::cout << count << std::endl;
	return 0;
}