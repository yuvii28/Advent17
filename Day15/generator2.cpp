#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

unsigned int reGenerate(long long input, long long factor, int mod);

int main(int argc, char* argv[]){
	unsigned int genA = 703;
	unsigned int genB = 516;

	int modA = 4;
	int modB = 8;

	double Afactor = 16807;
	double Bfactor = 48271;

	unsigned int bit = 65535;

	int numMatches = 0;

	for (size_t i = 0; i < 5000000; i++){
		//Calculate new generator values
		unsigned int tempA = reGenerate(genA, Afactor, modA);
		unsigned int tempB = reGenerate(genB, Bfactor, modB);


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

unsigned int reGenerate(long long input, long long factor, int mod){
	long long int mult = input * factor;
	while (true){
		mult = mult % 2147483647;
		if (mult % mod == 0){
			break;
		} 
		mult *= factor;
	}
	return mult;
}