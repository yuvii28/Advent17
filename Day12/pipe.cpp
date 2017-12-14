#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

int main(int argc, char* argv[]){
	std::ifstream in;
	in.open("input.txt");
	
	std::string connection;
	std::string line;

	std::vector<std::vector<int>> pipes;

	//Read over lines
	while (std::getline(in, line)){
		//Create the new pipeline
		std::vector<int> pipe;

		std::istringstream iss(line);
		//Iterate over numbers in line and add to pipe connections
		while (iss >> connection){
			auto found = connection.find_first_of("<->");
			//Is it a number
			if (found == std::string::npos){
				//Is there a trailing , -> remove it
				auto found = connection.find_first_of(",");
				if (found != std::string::npos){
					connection.erase(connection.size()-1, 1);
				}
				//Add into pipeline
				pipe.push_back(std::stoi(connection));
			}
		}
		pipes.push_back(pipe);
	}
	in.close();	

	//Start a queue and list of seen
	std::queue<int> queue;
	int seen[pipes.size()] = {0};
	int numConnections = 0;
	//Add 0 to queue to start
	queue.push(0);
	//While queue has items, add everything from queue pipe into queue
	while (!queue.empty()){
		int index = queue.front();
		queue.pop();
		//Has it been seen?
		if (seen[index]){
			continue;
		}
		numConnections++;
		seen[index] = 1;
		for (auto i = pipes[index].begin(); i != pipes[index].end(); i++){
			//If not visited add to queue
			if (!seen[*i]){
				queue.push(*i);
			}
		}
	}
	std::cout << numConnections << std::endl;


	return 0;
}