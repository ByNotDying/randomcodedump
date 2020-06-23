// testspace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <regex>
#include <signal.h>
#include <fstream>
#include <thread> 
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <condition_variable>
#include <chrono>
#include <array>
#include <atomic>

using namespace std;



struct cart {


	queue <string> items;
	int number;
	
	cart(){
		number = 0;
	}
	cart(int number) {
		this->number = number;
	}


	int getNumber() {
		return this->number;
	}
	void setNumber(int number) {
		this->number = number;
	}

	void makeCart(regex reg2, regex reg3, smatch matches1, smatch matches2, string::const_iterator searchStart, string::const_iterator searchStart1, string csvContent) { //those parameters tho


		string letter;
		string barcode;
		string h;
		string binary;
		string asdfasdf;
		long long int d = 0;
		float tempPrice = 0;
		float cartPrice = 0;



		searchStart1 = matches1.suffix().first;

		cartPrice = 0;
		while (regex_search(searchStart, searchStart1, matches2, reg3)) {

				//converts hex to decimal....
				h = matches2.str(1);
				//cout << matches2.str(1) << endl;
				//cout << h << endl;

				//then stores the decimal...
				d = stoll(h, 0, 16);
				//cout << d << endl;

				//to convert it to a binary number.
				string binary = bitset<48>(d).to_string();
				//cout << binary << endl;

				this->items.push(binary);

				cout << this->items.back() << " , ";

				searchStart = matches2.suffix().first;



		}
		searchStart = matches1.suffix().first;
		


	}

};


//84B062548848
//100001001011000001100010010101001000100001001
//100001001011000001100010010101001000100001001000
//100001001011000001100010010101001000100001001000
//001110000011010001000010001100000011011000110010001101010011010000111000001110000011010000111000



int main() {
	string fileName;

	//reading and parsing Carts.csv
	fileName = "Carts.csv";
	ifstream ifs2;
	ifs2.open(fileName);
	string csvContent{ istreambuf_iterator<char>(ifs2), istreambuf_iterator<char>() };
	//cout << csvContent << endl;

	regex reg2("Cart([0-9]{3})\n(?:(?:[0-z,]{12})[,\n])+");
	regex reg3("([0-z,]{12})[,\n]");
	//regex reg2("Cart([0-9]{3})[\s\S]+([0-z]{12})[,\n]"); //original regex statement
	smatch matches1;
	smatch matches2;

	string::const_iterator searchStart = csvContent.begin();//these two are used in makeCart
	string::const_iterator searchStart1 = csvContent.begin();


	cart testcart;

	//let us assume a costco with exactly two open lanes
	deque<cart> lane1;
	deque<cart> lane2;



	string letter;
	string barcode;
	string h;
	string binary;
	string asdfasdf;
	long long int d = 0;
	float tempPrice = 0;
	float cartPrice = 0;
	int laneIterator;
	while (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

		lane1.push_back(stoi(matches1.str(1)));	
		cout << "Cart # : " << lane1.back().getNumber() << " " << endl;
		lane1.front().makeCart(reg2,reg3,matches1,matches2,searchStart,searchStart1,csvContent);
		cout << endl << endl;

		searchStart = matches1.suffix().first;
	}
	


	return 0;

}






		

