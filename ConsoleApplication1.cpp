// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Luke Liu 20275196

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;


int main()
{
	char userChar;
	int tempInt;
	int tempInt2;
	
	vector<int> bitList;
	tempInt = 1;
	cout << "This program is for the Bitset Excersize. Please enter your character:";
	cin >> noskipws >> userChar;
	cout << endl;
	tempInt = userChar;
	tempInt2 = userChar;
	
	cout << endl;
	//cout << tempInt << endl; // remember to comment this out
	while (tempInt > 0) {
		if (tempInt % 2 == 1) {
			bitList.push_back(1);
		}
		if (tempInt % 2 == 0) {
			bitList.push_back(0);
		}
		tempInt = tempInt / 2;
		//cout << tempInt << endl; // remember to comment this out
	}

	 
	cout << "Bits ";
	int i = bitList.size();
	//cout << i << endl; //remember to comment this out
	bool printComma = 0;
	for (int i = bitList.size(); i >= 1; i = i - 1) {
		
		if (bitList.at(i-1) == 1) { //print all bits that are not 0
			if (printComma == 1) { cout << ","; }
			cout << i - 1;
			if (i - 1 != 0) { // for printing out commas
				printComma = 1;
			}
		}
	}
	cout << endl;

	cout << endl ;
	printComma = 0;
	for (int i = bitList.size(); i >= 1; i = i - 1) {
		if (bitList.at(i - 1) == 1) { //print all bits that are not 0
			if (printComma == 1) { cout << "and "; }
			cout << "2^" << i - 1 << " ";
			if (i - 1 != 0) { // for printing out commas
				printComma = 1;
			}
		}
	}
	cout << "= ";
	printComma = 0;
	for (int i = bitList.size(); i >= 1; i = i - 1) {
		if (bitList.at(i - 1) == 1) { //print all bits that are not 0
			if (printComma == 1) { cout << "+ "; }
			cout << pow(2,i-1) << " ";
			if (i - 1 != 0) { // for printing out commas
				printComma = 1;
			}
		}
	}
	cout << "= " << tempInt2 << " =" << " '" << userChar << "' ";
	cout << endl << endl;
	
	cout << "... I don't know if you wanted us to add in that last part, but I felt it would be better to be safe than sorry." << endl;

	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
