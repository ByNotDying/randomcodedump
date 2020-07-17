#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//creates a character frequency table, where the ascii character is the position in the vector, and the value stored in that position refers to the characters frequency
vector<int> createFreqTable(string fileContent) {
	vector<int> charFrequency(128, 0); //the frequency table must be set to size 128 for this.
	for (int fileContentIterator = 0; fileContentIterator <= fileContent.size() - 1; fileContentIterator++) { //as fileContentIt iterates through the encrypted text
		charFrequency.at(static_cast<int>(fileContent.at(fileContentIterator)))++;   //this should safely typecast the value of the ascii character at position indicated to int,
	}
	return charFrequency;
}

//using a frequency table created with the function above, 
string createCipher(vector<int> charFrequency) {
	string presentChars;
	for (int currentPos = 0; currentPos <= 127; currentPos++) {
		if (currentPos == 10) { currentPos++; } //This line is required to deal with any EOL characters  
		if (charFrequency.at(currentPos) > 0) {
			presentChars.push_back(static_cast<char>(currentPos)); //this should typecast the integer into a char
		}
	}
	presentChars = presentChars + presentChars; //appends string to self, to allow for operations involving ciphers.
	return presentChars;
}

void decipher(vector<int> charFrequency, string presentChars, string fileContent) {

	int presentCharsHalfwayPoint = (presentChars.size() / 2); //used in calculating offset, marks second half of string
	string tempFileContent; //copy of FileContent to be shifted 
	int maxIter;//iterator for keeping track of current "max value" to check
	int maxPos; //to keep track of location of current "max value"
	char tempChar;
	string sdf; //cin fodder

	bool maxFound = false;
	int offset = 0;

	//checks for max value on frequency table. Feels a little roundabout, tbh.
	for (maxIter = fileContent.size() - 1; maxIter >= 1; maxIter--) { //highest value iterator, starts with size of file, iterates down
		for (int currentPos = 0; currentPos <= 127; currentPos++) { //position iterator, iterates through charFreq, which stores values representing frequency in their corresponding ascii value
			tempFileContent = fileContent;

			if (charFrequency[currentPos] == maxIter) {//if the current iterated position in the frequency table is the current iterated ascii value we are checking as maximum...
				maxPos = currentPos;
				maxFound = true;
			}

			if (maxFound == true) {
				offset = presentChars.find(maxPos, presentCharsHalfwayPoint) - presentChars.find(" ", presentCharsHalfwayPoint); //calculate offset
				for (int i = 0; i <= tempFileContent.size() - 1; i++) {
					tempChar = tempFileContent.at(i);
					if (tempChar != '\n') {
						tempChar = presentChars.at(presentChars.find(tempChar, presentCharsHalfwayPoint) - offset);
					}
					tempFileContent.at(i) = tempChar;
				}
				cout << tempFileContent;
				cout << endl;

				std::size_t found = tempFileContent.find("the");
				if (found != std::string::npos) {
					std::cout << "We have found the word \"the\". " << endl;
				}
				else { std::cout << "We have NOT found the word \"the\". " << endl; }
				
				std::size_t found2 = tempFileContent.find("at");
				if (found2 != std::string::npos) {
					std::cout << "We have found the word \"at\". " << endl;
				}
				else { std::cout << "We have NOT found the word \"at\". " << endl; }

				cout << "Type any character to cycle the Cipher." << endl;
				cin >> sdf;
				maxFound = false;
			}
		}
	}
	return;
}

int main()
{
	cout << "Luke Liu" << endl;
	cout << "20275196" << endl;
	
	//grabbing fileContent now so I don't have to do it again for each function
	string fileName;
	fileName = "encrypt.txt";
	ifstream ifs{ fileName };
	string fileContent{ istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };

	vector<int> charFrequency = createFreqTable(fileContent); // makes a character frequency table
	string presentChars = createCipher(charFrequency); // uses the frequency table to create a string to serve as a "Cipher"
	decipher(charFrequency, presentChars, fileContent); // take the frequency table and cipher to make educated guesses at the proper deciphering


	return 0;
}

//create vector of size 128, populate with 0's
//scan text, each time a letter appears, increase the vector.at(asciiValue) by 1
//when done, create a vector/string presentChars containing only the ascii letters present in the file in alphabetical order, and then make it repeat itself once (for offsetting)
//then, find the "max char" by counting an iterator down from fileContent.size(), and make sure to save the positions of ALL iterators
//apply offset using frequency analysis (most common letter is space), by replacing the current iterated location in the string with presentChars.at(presentChars.find()+offset)

//TODO:
//check answer using common 2-3 letter words (I haven't implemented this and probably won't tbh)
//print out results from checking for common words
//prompt user to ask if they would like to shift the cipher using the next highest max char

//Note: you shift the cipher by shifting only the present letters.
// common knowledge of the ceaser cipher dictates "CBCZ" shifts to "BABY"
// CBCZ cannot shift to BABY. YBYA shifts to baby, however.
// CBCZ does not contain any of the letters of baby.
// YBYA contains ABY, so Y->B, B->A, A->Y
//in addition, you must account for EOL characters, which must not be shifted.

/*
	//pretty sure I made this just to test an auto loop
	int asdf = 0;
	for (auto pos : charFrequency) {
		cout << asdf << " ";
		cout << pos;
		cout << endl;
		asdf++;
	}
	cout << endl;
	*/

