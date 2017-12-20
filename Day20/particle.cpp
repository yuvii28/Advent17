#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

struct particle{
	int id;

	long long posX;
	long long posY;
	long long posZ;

	long long velX;
	long long velY;
	long long velZ;

	long long accX;
	long long accY;
	long long accZ;

	bool lockedX = false;
	bool lockedY = false;
	bool lockedZ = false;
	
	
	long long getDistance(){
		return std::abs(posX) + std::abs(posY) + std::abs(posZ);
	}

	void update(){
		velX += accX;
		velY += accY;
		velZ += accZ;
		posX += velX;
		posY += velY;
		posZ += velZ;
		if (!lockedX && ((posX >= 0 && velX >= 0 && accX >= 0) 
			|| (posX <= 0 && velX <= 0 && accX <= 0))){
			lockedX = true;
		}
		if (!lockedY && ((posY >= 0 && velY >= 0 && accY >= 0) 
			|| (posY <= 0 && velY <= 0 && accY <= 0))){
			lockedY = true;
		}
		if (!lockedZ && ((posZ >= 0 && velZ >= 0 && accZ >= 0) 
			|| (posZ <= 0 && velZ <= 0 && accZ <= 0))){
			lockedZ = true;
		}
	}

	//Check if the particle is moving away
	bool movingAway(){
		if (lockedX && lockedY && lockedZ){
			return true;
		}
		return false;
	}
};

//Determine the closest particle at a given time
int getClosest(std::vector<particle> particles){
	int bestIndex = particles[0].id;
	int bestDistance = particles[0].getDistance();
	//Check each particle
	for (auto p = particles.begin(); p != particles.end(); p++){
		if (p->getDistance() < bestDistance){
			bestDistance = p->getDistance();
			bestIndex = p->id;
		}
	}
	return bestIndex;
}


int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");

	std::string line;
	std::string word;

	std::vector<particle> particles;

	//Read over lines
	while (std::getline(in, line)){
		particle p;
		p.id = particles.size();
		std::istringstream iss(line);
		while (iss >> word){
			if (word[0] == 'p'){
				//Collect substring between arrows
				word.erase(0, 3);
				word.erase(word.size()-2, 2);
				//Split up values
				std::replace(word.begin(), word.end(), ',', ' ');
				std::istringstream iss2(word);
				std::string val;
				std::vector<std::string> aspects;
				while (iss2 >> val){
					aspects.push_back(val);
				}
				//Set values
				p.posX = std::stol(aspects[0]);
				p.posY = std::stol(aspects[1]);
				p.posZ = std::stol(aspects[2]);
			} else if (word[0] == 'v'){
				//Collect substring between arrows
				word.erase(0, 3);
				word.erase(word.size()-2, 2);
				//Split up values
				std::replace(word.begin(), word.end(), ',', ' ');
				std::istringstream iss2(word);
				std::string val;
				std::vector<std::string> aspects;
				while (iss2 >> val){
					aspects.push_back(val);
				}
				//Set values
				p.velX = std::stol(aspects[0]);
				p.velY = std::stol(aspects[1]);
				p.velZ = std::stol(aspects[2]);
			} else {
				//Collect substring between arrows
				word.erase(0, 3);
				word.erase(word.size()-1, 1);
				//Split up values
				std::replace(word.begin(), word.end(), ',', ' ');
				std::istringstream iss2(word);
				std::string val;
				std::vector<std::string> aspects;
				while (iss2 >> val){
					aspects.push_back(val);
				}
				//Set values
				p.accX = std::stol(aspects[0]);
				p.accY = std::stol(aspects[1]);
				p.accZ = std::stol(aspects[2]);
			}
		}
		particles.push_back(p);
	}
	in.close();

	for (size_t i = 0; i < 1000; i++){
		for (auto p = particles.begin(); p != particles.end(); p++){
			p->update();
		}
	}

/*
	while (particles.size() > 1){
		int best = getClosest(particles);
		std::vector<particle> toKeep;
		for (auto p = particles.begin(); p != particles.end(); p++){
			//If a particle is not the closest, and is forever moving away
			if (p->id != best){
				if (!p->movingAway()){
					//Remove the particle from list
					toKeep.push_back(*p);
				}
			}
			p->update();
		}
		particles = toKeep;
	}
*/


	std::cout << getClosest(particles) << std::endl;

	return 0;
}