#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

int getWeight(std::string name, std::map<std::string, int> &weights, 
	std::map<std::string, std::vector<std::string>> &children, std::map<std::string, int> &totalWeights);
bool isValid(std::string name, std::map<std::string, int> &weights, 
	std::map<std::string, std::vector<std::string>> &children, std::map<std::string, int> &totalWeights);

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string line;
	std::string word;

	std::vector<std::string> pipes;
	std::map<std::string, int> weights;
	std::map<std::string, int> totalWeights;

	std::map<std::string, std::vector<std::string>> children;

	//Read over lines
	while (std::getline(in, line)){
		std::istringstream iss(line);
		//read each word
		std::string name = "";

		while (iss >> word){
			auto found = word.find_first_of("-");
			if (found != std::string::npos){
				continue;
			}
			//Is it first word
			if (name == ""){
				name = word;
				pipes.push_back(name);
				continue;
			}

			//Is it the weight
			found = word.find_first_of("(");
			if (found != std::string::npos){
				word.erase(0, 1);
				word.erase(word.size()-1, 1);
				int weight = std::stoi(word);
				//Store
				weights[name] = weight;
				children[name] = {};
				continue;
			}

			//Check its disc name
			found = word.find_first_of(",");
			if (found != std::string::npos){
				word.erase(word.size()-1, 1);
			}
			children[name].push_back(word);

		}

	}
	in.close();

	//Pipe is valid if all children have same weight
	for (auto i = pipes.begin(); i != pipes.end(); i++){
		std::vector<int> w;
		for (auto j = children[*i].begin(); j != children[*i].end(); j++){
			//get childs weight
			w.push_back(getWeight(*j, weights, children, totalWeights));
		}
		//Check each weight for a difference
		if (w.size() > 1){
			for (size_t j = 0; j < w.size()-1; j++){
				if (w[j] != w[j+1] && isValid(*i, weights, children, totalWeights)){
					std::cout << *i << " has a mistake\n";
					if (j == 0){
						if (w[j] == w[j+2]){
							if (w[j] > w[j+1]){
								//Mistake in j+1
								std::cout << (weights[children[*i][j+1]]) + std::abs(w[j+1] - w[j]);								
							} else {
								//Mistake in j+1
								std::cout << (weights[children[*i][j+1]]) - std::abs(w[j+1] - w[j]);								
							}
						} else {
							if (w[j] < w[j+1]){
								//Mistake in j
								std::cout << (weights[children[*i][j]]) + std::abs(w[j+1] - w[j]);								
							} else {
								//Mistake in j
								std::cout << (weights[children[*i][j]]) - std::abs(w[j+1] - w[j]);								
							}
						}
					} else {
						if (w[j] == w[j-1]){
							if (w[j] > w[j+1]){
								//Mistake in j+1
								std::cout << (weights[children[*i][j+1]]) + std::abs(w[j+1] - w[j]);								
							} else {
								//Mistake in j+1
								std::cout << (weights[children[*i][j+1]]) - std::abs(w[j+1] - w[j]);								
							}
						} else {
							if (w[j] < w[j+1]){
								//Mistake in j
								std::cout << (weights[children[*i][j]]) + std::abs(w[j+1] - w[j]);								
							} else {
								//Mistake in j
								std::cout << (weights[children[*i][j]]) - std::abs(w[j+1] - w[j]);								
							}
						}
					}
					std::cout << std::endl;
					break;
				}
			}			
		}

	}

	return 0;
}

bool isValid(std::string name, std::map<std::string, int> &weights, 
	std::map<std::string, std::vector<std::string>> &children, std::map<std::string, int> &totalWeights){
	//Check all children weights are valid
	std::vector<int> vals;
	for (auto i = children[name].begin(); i != children[name].end(); i++){
		vals.push_back(getWeight(name, weights, children, totalWeights));
	}
	for (size_t i = 0; i < vals.size()-1; i++){
		if (vals[i] != vals[i+1]){
			return false;
		}
	}
	return true;
}

//Function to determine weight
int getWeight(std::string name, std::map<std::string, int> &weights, 
	std::map<std::string, std::vector<std::string>> &children, std::map<std::string, int> &totalWeights){

	//Weight = own weight with weights of all children
	if (children[name].size() == 0){
		return weights[name];
	} else {
		if (totalWeights.find(name) == totalWeights.end()){
			int totalWeight = weights[name];
			for (auto i = children[name].begin(); i != children[name].end(); i++){
				totalWeight += getWeight(*i, weights, children, totalWeights);
			}
			totalWeights[name] = totalWeight;
		}
		return totalWeights[name];
	}
}
