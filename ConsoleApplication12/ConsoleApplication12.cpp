#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <list>
#include <algorithm>
#include <cstring>
#include <cmath>


/*std::string fileName;
	fileName = "sin.csv";
	std::ifstream ifs{ fileName };
	std::string sinContent{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
	*/

int main(int argc, char** argv) {

	std::string fileName = "sin.csv";
	std::ifstream ifs{ fileName };
	std::string xyContent{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };

	std::regex xyReg("(-?[0-9]\.[0-9]+),(-?[0-9]\.[0-9]+)");
	std::smatch xyMatches;

	std::string::const_iterator searchStart1 = (xyContent.begin());
	std::string::const_iterator searchStart2 = (xyContent.begin());

	std::vector< std::pair <double, double> > xyList;

	//std::cout << xyContent;

	while (std::regex_search(searchStart1, xyContent.cend(), xyMatches, xyReg)) {
		//std::cout << "pair in regex: " << xyMatches.str(1) << " " << xyMatches.str(2) << std::endl;
		xyList.push_back( std::make_pair (std::stod ( xyMatches.str(1)) , std::stod(xyMatches.str(2) ) ) );
		searchStart1 = xyMatches.suffix().first;
	}

	//std::cout << '\n';
	for (auto elem : xyList) {
		std::cout <<"pair: "<< elem.first << " " << elem.second << std::endl;
	}

	
	long double xSum = 0;
	long double ySum = 0;
	long double xSquareSum = 0;
	long double ySquareSum = 0;
	long double xySum = 0;
	long double numPoints = 0; //for good measure

	for (auto elem : xyList) {
		std::cout << "pair: " << elem.first << " " << elem.second << std::endl;
		xSum += elem.first;
		ySum += elem.second;
		xSquareSum += elem.first * elem.first;
		ySquareSum += elem.second * elem.second;
		xySum += (elem.first) * (elem.second);
		numPoints += 1;
	}

	//y = mx+b
	long double slope = (  ( (numPoints*xySum) - (xSum)*(ySum) )  /  ( (numPoints*xSquareSum) - (xSum)*(xSum) )  );
	long double intercept = ( (ySum) - (slope*xSum) );

	std::cout << std::endl;
	std::cout << "y = " << slope << "x + " << intercept;


	return 0;

}