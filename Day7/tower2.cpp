#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <memory>

class disc{
public:
	disc(std::string name, int weight): name_{name}, weight_{weight}
	{ }

	inline std::string getName(){return name_;}
	inline int getWeight(){return weight_;}
	inline std::vector<std::string> getChildren(){return children_;}

	void setName(std::string name) {name_ = name;}

	void setWeight(int weight){weight_ = weight;}

	void addChild(std::string child){
		children_.push_back(child);
	}

private:
	//Disc has name, weight and list of children names
	std::string name_;
	int weight_;
	std::vector<std::string> children_;
};

//Given a disc, get weight
int getWeight(disc d, std::vector<std::shared_ptr<disc>> discs){
	int childrenWeight = 0;
	auto children = d.getChildren();
	for (auto i = children.begin(); i != children.end(); i++){
		//Find disc of matching name
		for (auto j = discs.begin(); j != discs.end(); j++){
			if ((*j).get()->getName() == (*i)){
				childrenWeight += getWeight(*(*j).get(), discs);
				break;
			}
		}
	}
	return d.getWeight() + childrenWeight;
}


int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string words;
	std::string word;

	//Vector containing all parent names
	std::vector<std::string> parents;
	std::vector<std::shared_ptr<disc>> discs;

	//Read over lines
	while (std::getline(in, words)){
		std::istringstream iss(words);
		std::vector<std::string> line;
		disc d{"", 0};
		//read each word
		std::string name = "";
		int weight = 0;
		while (iss >> word){
			//Is it first word
			if (name == ""){
				name = word;
				continue;
			}
			//Is it the weight
			auto found = word.find_first_of("(");
			if (found != std::string::npos){
				word.erase(0, 1);
				word.erase(word.size()-1, 1);
				weight = std::stoi(word);
				//Make disc
				d.setName(name);
				d.setWeight(weight);
				continue;
			}
			//Check its disc name
			found = word.find_first_of(",");
			if (found != std::string::npos){
				word.erase(word.size()-1, 1);
			}
			//add to list of children
			d.addChild(word);
		}
		discs.push_back(std::make_shared<disc>(d));
	}
	for (auto i = discs.begin(); i != discs.end(); i++){
		std::vector<int> weights;
		//For every disc, check its children weights
		auto children = (*i).get()->getChildren();

		for (auto j = children.begin(); j != children.end(); j++){
			//Find disc of matching name
			for (auto k = discs.begin(); k != discs.end(); k++){
				if ((*k).get()->getName() == (*j)){
					weights.push_back(getWeight(*(*k).get(), discs));
					break;
				}
			}
		}

		std::sort(weights.begin(), weights.end());
		//Check each childs weights
		for (int index = 0; index < int(weights.size())-1; index++){
			if (weights[index] != weights[index+1]){
				if (index == 0){
					std::cout << weights[index+1] << "\n";					
				} else {
					std::cout << weights[index] << "\n";
				}
				break;
			}
		}
	}

	in.close();	
	return 0;
}