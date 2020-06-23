#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <list>
#include <algorithm>

using namespace std;

double damping = 1;

struct webPage {
	string pageName;
	double pageRank;

	webPage() { pageName = "0"; pageRank = 0; }
	webPage(string pageName, double pageRank) {
		this->pageName = pageName;
		this->pageRank = pageRank;
	}
};


int main()
{
	string fileName;
	fileName = "PageRank.html";
	ifstream ifs{ fileName };
	string htmlContent{ istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	
	regex titleReg ("<title>([A-z, ]+)<\/title>\n[\s\n\t]*<div class=\"other-links\">[\s\n\t ]*<ul>[\s\n\t]*(?:(?:[/s ]*<li><a href=\"http[:/A-z.]*\">)([A-z \s]*)<\/a><\/li>[\s\n\t ]*)*<\/ul>[\s\n\t]*");
	smatch titleMatches;
	regex linksReg(">([A-z, ]+)<\/a><\/li>");
	smatch linksMatches;
	int i = 1;

	string::const_iterator searchStart1 = (htmlContent.begin());
	string::const_iterator searchStart2 = (htmlContent.begin());
	
	/*
		map<string, double> testmap;

	while (regex_search(searchStart1, htmlContent.cend(), titleMatches, titleReg)) {
		cout << endl << "title: " << titleMatches.str(1) << endl;
		testmap[titleMatches.str(1)] = 0.15;
		searchStart1 = titleMatches.suffix().first;
	}

	for (auto elem : testmap){
		cout << endl << elem.first << " " << elem.second << endl;
	}
	*/

	searchStart1 = (htmlContent.begin());
	searchStart2 = (htmlContent.begin());
	map<pair<string, string>, double> edgeMap;
	map<string, vector<string>> vertexMap;
	map<string, double> pageRankTracker;
	int myIt = 1;
	double C;

	while (regex_search(searchStart1, htmlContent.cend(), titleMatches, titleReg)) {

		string ucTitleMatch = titleMatches.str(1); //need to change everything to same case, because the title is "HISTORY" but the links are "History"
		transform(ucTitleMatch.begin(), ucTitleMatch.end(), ucTitleMatch.begin(), ::toupper);//change it all to uppercase

		cout << endl << "title: " << ucTitleMatch << endl;
		i = 0;
		pageRankTracker.insert({ ucTitleMatch, 0 }); // needs to be done twice in the event of a link to a webpage whose link is not listed, also need this because we need the key

		searchStart2 = titleMatches.suffix().first;
		vertexMap[ucTitleMatch];

		cout << "links: ";

		while (regex_search(searchStart1, searchStart2, linksMatches, linksReg)) {

			string ucLinksMatch = linksMatches.str(1); //planning to change everything to uppercase, have to do this because it's "HISTORY" in the title and "History" in the links
			transform(ucLinksMatch.begin(), ucLinksMatch.end(), ucLinksMatch.begin(), ::toupper);  // change it all to uppercase

			cout << ucLinksMatch << " ";
			//cout << linksMatches.str(1) << " ";

			edgeMap.insert({{ ucTitleMatch , ucLinksMatch }, (1)}); //at this point the values in the edgelist aren't valid
			vertexMap.find(ucTitleMatch)->second.push_back(ucLinksMatch);

			pageRankTracker.insert({ ucLinksMatch, 0 }); // needs to be done twice in the event of a link to a webpage whose title has not been reached, also will break without this line
			//cout << pageRankTracker.find(linksMatches.str(1))->second;
			
			//pageRankTracker.find(ucLinksMatch)->second = (pageRankTracker.find(ucLinksMatch)->second) + (0.85) * ( pageRankTracker.find ( ucTitleMatch )->second / vertexMap[ucTitleMatch].size() ) ;

			searchStart1 = linksMatches.suffix().first;
		}
		searchStart1 = titleMatches.suffix().first;
	}
	
	/*
	searchStart1 = (htmlContent.begin());
	searchStart2 = (htmlContent.begin());
	while (regex_search(searchStart1, htmlContent.cend(), titleMatches, titleReg)) {
		
		searchStart2 = titleMatches.suffix().first;

		while (regex_search(searchStart1, searchStart2, linksMatches, linksReg)) {

			pageRankTracker.find(linksMatches.str(1))->second = (0.15) + (0.85) * (pageRankTracker.find(titleMatches.str(1))->second / vertexMap[titleMatches.str(1)].size());

			searchStart1 = linksMatches.suffix().first;
		}
		searchStart1 = titleMatches.suffix().first;
	}
	*/



	int userint = 1; // was originally a bool
	bool booleanCreatedBecauseICanNotGetRidOfThatBracket = 0;

	

	while (userint > 0) {

		//	map<string, vector<string>> vertexMap;
		//	map<pair<string, string>, double> edgeMap;
		//	map<string, double> pageRankTracker;

		for (map<string, vector<string>>::iterator vertexIt = vertexMap.begin(); vertexIt != vertexMap.end(); vertexIt++) {
			for (vector<string>::iterator vertexIt2 = vertexIt->second.begin(); vertexIt2 != vertexIt->second.end(); vertexIt2++) { //makes an iterator that is equal to a pointer pointing to first item in the vector
				
				//this looks like it would break on multiple iterations, but I have loops to reset these values
				edgeMap.find(make_pair(vertexIt->first, *vertexIt2))->second = (edgeMap.find(make_pair(vertexIt->first, *vertexIt2))->second / vertexIt->second.size());
				pageRankTracker.find(*vertexIt2)->second = (pageRankTracker.find(*vertexIt2)->second) +((damping) * edgeMap.find(make_pair(vertexIt->first, *vertexIt2))->second);
				//because it's already set to 1-damping before these loops, I can just add the values
				
				//the PR of the second item in the edge pair = the current pr of the second item pair + (damping) * (the value of any edge with the current item as it's second vertex)
				//pageRankTracker.find(vertexIt->first)->second = (damping)*edgeMap.find(make_pair(vertexIt->first, *vertexIt2))->second;
				//to find a pages page rank, we need to find the value of the ranking of all outgoing links leading to a page
				//these values should already be divided based on how many links each page has
				//to find these values, we'd need to access the second element of the first element, which means the second element in the pair of strings that is the first element
				//I think I may have used a bad data type somewhere but I feel like I wasn't supposed to actually make a real adjacency list/matrix

			}
		}

		string comparator = "a"; // set to a random value
			for (map < pair<string, string>, double>::iterator myIt1 = edgeMap.begin(); myIt1 != edgeMap.end(); myIt1++) {
			if (myIt1->first.first != comparator) {
				//cout << endl << "R : " << myIt1->first.first;

				if (booleanCreatedBecauseICanNotGetRidOfThatBracket) {
					cout << " ]";
				}
				if (!booleanCreatedBecauseICanNotGetRidOfThatBracket) {
					cout << endl << endl << endl << "Adjacency List: " << endl;
				}
				cout << endl << myIt1->first.first << "[ ";
				booleanCreatedBecauseICanNotGetRidOfThatBracket = 1;

			}
			cout << " (" << myIt1->first.second << "," << myIt1->second << ") ";
			comparator = myIt1->first.first;
		}
		cout << " ]" << endl << endl;

		
		
		
		for (auto elem : pageRankTracker) {
			cout << endl << elem.first << " " << elem.second << endl;
		}

		
		cout << "Input how many iterations you want to continue with, or 0 to exit: " << endl;
		cin >> userint;

		for (map <string, double>::iterator pageRankIt = pageRankTracker.begin(); pageRankIt != pageRankTracker.end(); pageRankIt++) {
			//I do this to reset the values in edgeMap, because I'm going to divide them again later
			//also because this is part of the algorithm technically
			for (map < pair<string, string>, double>::iterator edgeMapIt = edgeMap.begin(); edgeMapIt != edgeMap.end(); edgeMapIt++) {

				if (edgeMapIt->first.first == pageRankIt->first) {
					edgeMapIt->second = pageRankIt->second;
				}

			}

		}
		for (map <string, double>::iterator pageRankIt = pageRankTracker.begin(); pageRankIt != pageRankTracker.end(); pageRankIt++) {
			pageRankIt->second = (1 - damping); //setting everything to 1-damping so I can just add it later
		}


	}
	
	/*
	for (auto elem : pageRankTracker) {
		cout << endl << elem.first << " " << elem.second << endl;
	}
	*/
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
