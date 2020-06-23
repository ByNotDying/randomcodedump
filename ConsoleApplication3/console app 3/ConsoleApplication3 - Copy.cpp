//luke liu
//20275196

//current plan: make a vector of size 128, each position corresponds to a different ascii letter
// then,
//1.linked list that is already sorted based on that array
// which means, rather than make a linked list out of order and sort it, make a linked list that is already in order based on frequency analysis
//2. either a string or a linked list that orders them all alphabetically, but does not contain any ascii characters that do not exist in the text
// find the offset 
// for each letter in fileContent.at(whatever), do a search with freqStr.find(letterInQuestion), then find whatever that returns + the offset. 
//So if the offest is 3, and the first letter in fileContent is a, and freqStr.find(a) returns 2, replace fileContent.at(0) with freqStr.at(5)
//nvm this plan sucks

//more current plan 2.0
//create vector of size 128, populate with 0's
//scan text, each time a letter appears, increase the vector.at(asciiValue) by 1
//when done, create a vector/string presentChars containing only the ascii letters present in the file in alphabetical order, and then make it repeat itself once (for offsetting)
//then, find the max char by counting an iterator down from fileContent.size(), and make sure to save the positions of ALL iterators
//apply offset using frequency analysis (most common letter is space), by replacing the current iterated location in the string with presentChars.at(presentChars.find()+offset)
//check answer using common 2-3 letter words
//find next max char (iterate through whole vector) if none are found
//if found, print and return
//it would probably be better to use a linked list, but I don't want to fiddle with function members right now

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/*
class Node
{
public:
	SNode();
	SNode(int data);
private:
	char asciiChar;
	int frequency;
	Node* next;
};

class SList {
public:
	SList();
	bool empty() const;
	const E& front() const;
	void addFront(const int& userData);
	void removeFront();
	void display();

	//private:
	E* head;
};
*/

using namespace std;

int main()
{
	cout << "Luke Liu" << endl;
	cout << "20275196" << endl;
	string fileName;
	//string fileContent; 
	
	fileName = "encrypt.txt";
	
	//read in a file and copy its contents to a string
	ifstream ifs{fileName};
	string fileContent{ istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };

	// populateFreqTable(string fileContent)
	//performing frequency analysis, increments value in a cell up each time that cells corresponding ascii letter shows up
	vector<int> charFrequency(128, 0);
	int currentPos;
	char currentChar;
	int convertedInt = 0; // for personal clarity, using these to convert
	char convertChar = 0; // for personal clarity
	for (currentPos = 0; currentPos <= fileContent.size() - 1; currentPos = currentPos + 1) {
		currentChar = fileContent.at(currentPos);
		convertedInt = currentChar;
		charFrequency.at(convertedInt) = charFrequency.at(convertedInt) + 1;
	}

	/*
	for (int v = 0; v <= 127; v++) {
		convertChar = v;
		cout << convertChar;
		cout << charFrequency.at(v);
		cout << endl;
	}
	*/

	// createCipher(vector charFrequency)
	//this would probably be much more efficient with a linked list...
	string presentChars; 
	int presentCharsHalfwayPoint; //used in calculating offset, marks second half of string
	for (currentPos = 0; currentPos <= 127; currentPos = currentPos + 1) {
		if (currentPos == 10) { currentPos = currentPos + 1; } //to deal with EOL, if needed
		convertChar = currentPos;
		if (charFrequency.at(currentPos) > 0) {
			presentChars.push_back(convertChar);
		}
	}

	presentCharsHalfwayPoint = presentChars.size() -1; 

	//cout << presentChars << endl;
	
	presentChars = presentChars + presentChars;

	//cout << presentChars << endl;

	/*
	for (auto pos : presentChars) {
		cout << pos;
	}
	*/
	
	//decrypt(vector charFrequency, string presentChars)
	string tempFileContent;
	tempFileContent = fileContent;
	int currMax;
	int maxIter;//iterator for keeping track of current max
	int maxPos; //to keep track of location of current max
	char maxChar;
	char tempChar;
	char sdf; //cin fodder

	bool maxFound = false;
	int offset = 0;

	for (maxIter = fileContent.size() - 1; maxIter >= 1; maxIter = maxIter - 1) { //highest value iterator, starts with size of file, iteratess down
		for (currentPos = 0; currentPos <= 127; currentPos = currentPos + 1) { //position iterator, iterates through charFreq, which stores values representing frequency in their corresponding ascii value
			tempFileContent = fileContent;
			if (charFrequency[currentPos] == maxIter) {//if the current iterated position in the frequency table is the current iterated value we are checking as maximum...
				maxPos = currentPos;
				maxFound = true;
			}
			if (maxFound == true) {
				maxChar = maxPos; //convert position to corresponding ascii char
				offset = presentChars.find(maxChar, presentCharsHalfwayPoint) - presentChars.find(" ", presentCharsHalfwayPoint); //calculate offset
				//cout << endl << offset << endl;
				//cout << endl << "should be a space here. llll" << presentChars.at(presentChars.find(maxChar, presentCharsHalfwayPoint)-offset) << "llll" << endl;
				for (int i = 0; i <= tempFileContent.size() - 1; i++) {
					tempChar = tempFileContent.at(i);
					if (tempChar != '\n') {
						tempChar = presentChars.at(presentChars.find(tempChar, presentCharsHalfwayPoint) - offset);
					}
					tempFileContent.at(i) = tempChar;
				}



				cout << tempFileContent;
				cin >> sdf;
				maxFound = false;
			}
		}
	}
	return 0;
}

