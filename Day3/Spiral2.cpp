#include <iostream>

int main(int argc, char* argv[]){	
	int spiral [501][501];
	spiral[250][250] = 1;
	spiral[250][251] = 1;
	spiral[249][251] = 2;
	int i = 249;
	int j = 250;

	bool pass = false;
	int numFill = 2;
	int toFill = 2;

	//How to move
	char nextMove = 'l';

	while (true){
		//Fill box
		spiral[i][j] = spiral[i+1][j-1] + spiral[i+1][j] + spiral[i+1][j+1] + 
		    spiral[i][j-1] + spiral[i][j+1] + spiral[i-1][j-1] + spiral[i-1][j] +
		     spiral[i-1][j+1];

		if (spiral[i][j] > 368078){
			break;
		}

		toFill--;
		
		//Subtract number. If last, 		
		if (toFill == 0){
			if (pass){
				numFill++;
				pass = false;
				toFill = numFill;
			} else {
				pass = true;
				toFill = numFill;				
			}

			if (nextMove == 'u'){
				nextMove = 'l';
			}
			else if (nextMove == 'l'){
				nextMove = 'd';
			}
			else if (nextMove == 'd'){
				nextMove = 'r';
			} 
			else {
				nextMove = 'u';
			}
		}

		//Move in direction
		if (nextMove == 'u'){
			i -= 1;
		}
		else if (nextMove == 'd'){
			i += 1;
		}
		else if (nextMove == 'r'){
			j += 1;
		} 
		else {
			j -= 1;
		}

	}
	std::cout << spiral[i][j] << "\n";
	return 0;
}



