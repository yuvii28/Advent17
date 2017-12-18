#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

int main(int argc, char* argv[]){
	int currPos = 0;
	int supposedSize = 1;
	int steps = 337;

	int result = 0;

	for (int i = 1; i < 50000000; i++){
		//Move forward n % size steps
		int move = steps % supposedSize;
		currPos = (currPos + move) % supposedSize;
		if (currPos == 0){
			result = i;
		}
		supposedSize++;
		currPos++;
	}

	std::cout << result << std::endl;

	return 0;
}