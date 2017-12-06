#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	int digit;
	std::vector<int> instructions;

	int index = 0;
	int rounds = 0;

	//Read over digits
	while (in >> digit){
		//Add into vector 
		instructions.push_back(digit);
	}
	in.close();	

	while (true){
		//If outside the set end
		if (index < 0 || index >= int(instructions.size())){
			break;	
		}
		rounds++;
		auto pastIndex = index;
		index += instructions[index];
		if (instructions[pastIndex] >= 3){
			instructions[pastIndex]--;
		} else {
			instructions[pastIndex]++;
		}
	}

	std::cout << rounds << "\n";

	return 0;
}