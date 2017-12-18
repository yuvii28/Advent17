#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

unsigned int reGenerate(long long input, long long factor);

int main(int argc, char* argv[]){
	unsigned int genA = 703;
	unsigned int genB = 516;

	double Afactor = 16807;
	double Bfactor = 48271;

	unsigned int bit = 65535;

	int numMatches = 0;

	for (size_t i = 0; i < 40000000; i++){
		//Calculate new generator values
		unsigned int tempA = reGenerate(genA, Afactor);
		unsigned int tempB = reGenerate(genB, Bfactor);


		genA = tempA;
		genB = tempB;

		tempA &= bit;
		tempB &= bit;
		if (tempA == tempB){
			numMatches++;
		}
	}


	std::cout << "Final matches of " << numMatches << std::endl;

	return 0;
}

unsigned int reGenerate(long long input, long long factor){
	long long int mult = input * factor;
	mult = mult % 2147483647;
	return mult;
}