#include <iostream>

int main(int argc, char* argv[]){	
	int input = 368078;
	int square = 1;
	int factor = 0;
	int numMoves = 0;

	//Find the diagonal its a member of
	while (square < input){
		numMoves++;
		factor += 8;
		square += factor;
	}
	//Find the quadrant
	int i = 0;
	int pos = 0;
	int boundA = 0;
	for (i = 2; i <= 9; i++){
		auto val = i - 1;
		pos = i;
		//Find wall its in
		while (input > pos){
			val += 8;
			pos += val;
		}
		//Did u go too far?
		if (pos > square){
			continue;
		} else {
			//Get the other bound
			if (i != 2){
				if (i % 2 == 0){
					boundA = pos;
				}
				else {
					auto boundB = pos;
					val = i - 2;
					pos = i-1;
					//Loop to find other bound
					while (pos < boundB){
						val += 8;
						pos += val;
					}
					boundA = pos - val;
				}
			} else {
				boundA = pos;
			}
			break;
		}
	}
	auto result = numMoves + abs(input - boundA);
	std::cout << result << "\n";
	return 0;
}
/*



37	36	35	34	33	32	31
38	17	16	15	14	13	30
39	18	5	4	3	12	29
40	19	6	1	2	11	28
41	20	7	8	9	10	27
42	21	22	23	24	25	26
43	44	45	46	47	48	49	50....

*/

// 0 1 2 1 5 1 12 2 1 28 3  2 
// 1 2 3 4 5 6 7  8 9 10 11 12