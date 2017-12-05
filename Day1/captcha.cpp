#include <iostream>
#include <fstream>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	char digit;
	int first = -1;
	int a = 0;
	int b= 0;
	int result = 0;

	//Read over digits
	while (in >> digit){
		//Set first value
		if (first == -1){
			first = int(digit) - 48;
			a = first;
			continue;
		}
		b = a;
		a = int(digit) - 48;
		std::cout << a << "\n";

		if (a == b){
			result += a;
		}
	}
	if (a == first){
		result += a;
	}
	in.close();	
	std::cout << result << "\n";
	return 0;
}