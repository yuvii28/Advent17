#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string line;

	std::vector<std::string> map;

	//Read over input
	while (std::getline(in, line)){
		map.push_back(line);
	}
	in.close();	

	return 0;
}