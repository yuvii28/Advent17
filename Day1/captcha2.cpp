#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");

	//read digits into an array
	std::string digits;
	in >> digits;
	in.close();	

	int result = 0;
	//Factor to push buffer forward
	unsigned int factor = digits.size()/2;

	for (size_t i = 0; i < factor; i++){
		if (digits[i] == digits[i+factor]){
			result += int(digits[i])-48;
		}
	}

	std::cout << result*2 << "\n";
	return 0;
}