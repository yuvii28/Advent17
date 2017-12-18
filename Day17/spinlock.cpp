#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

int main(int argc, char* argv[]){
	std::vector<int> values;
	values.push_back(0);
	int currPos = 0;

	int steps = 337;

	for (int i = 1; i < 2018; i++){
		//Move forward n % size steps
		int move = steps % values.size();
		currPos = (currPos + move) % values.size();
		//Insert 
		if (currPos == int(values.size()) - 1){
			values.push_back(i);
		} else {
			values.insert(std::find(values.begin(), values.end(), values[currPos+1]), i);
		}			
		currPos++;
	}

	std::cout << values[currPos+1] << std::endl;

	return 0;
}