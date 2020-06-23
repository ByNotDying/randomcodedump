//this is lab 3, resubmitted
//I had to comment out a line with "mtx.unlock()" because it broke the lab
//Also changed regex a little bit to acommadate errors in the the csv

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <memory>
#include <regex>
#include <bitset>
#include <thread>
#include <queue>
#include <mutex>


using namespace std;

struct Barcode;
struct Price;

struct Node {
	int dummy;
};

struct entry39 {
public:
	char character;
	string barcodeString;
	bitset<9> barcodeBitset;
	entry39() {
		character = 0;
		barcodeString = '0';
		barcodeBitset.set();
	}
	entry39(char character, string string) {
		this->character = character;
		this->barcodeString = string;
		this->barcodeBitset = bitset<9>(this->barcodeString);
	}
};

struct Barcode : public Node {
private:
	string name;
	string asciiName;
public:
	Barcode() {
		dummy = 0;
		this->name = "";
	}
	Barcode(string name) {
		this->name = name;
	}
	string getBarcode() {
		return name;
	}
	string getAscii() {
		return asciiName;
	}
	void changeAscii(string text) {
		asciiName = text;
	}
};

struct Price : public Node {
	float price;
	Price() {
		dummy = 0;
		this->price = 0;
	}
	Price(float price) {
		dummy = 0;
		this->price = price;
	}
	float getPrice() {
		return price;
	}
};

struct Product : public Node { //also contains assorted hash functions
private:
	shared_ptr<Barcode> B;
	shared_ptr<Price>  P;
public:
	Product() {
		B = nullptr;
		P = nullptr;
		dummy = 0;
	}
	Product(string name, float price) : B(make_shared<Barcode>(name)), P(make_shared<Price>(price)) {}
	shared_ptr<Barcode> getBarcodeNode() {
		return B;
	}
	shared_ptr<Price> getPriceNode() {
		return P;
	}
	string getBarcode() {
		return B->getBarcode();
	}
	float getPrice() {
		return P->getPrice();
	}
};

struct cart {

	deque <string> items;
	int number;

	cart() {
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

	string getFirst() {
		return items.front();
	}
	void popFirst() {
		items.pop_front();
		return;
	}


	void makeCart(regex reg2, regex reg3, smatch matches1, smatch matches2, string::const_iterator searchStart, string::const_iterator searchStart1, string csvContent) { //those parameters tho

		string letter;
		string barcode;
		string h;
		string binary;
		long long int d = 0;

		searchStart1 = matches1.suffix().first;

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

			this->items.push_back(binary);

			//cout << this->items.back() << " , ";

			searchStart = matches2.suffix().first;
		}
		searchStart = matches1.suffix().first;
	}
};

int hashFunc(string bitstring) { // You might notice that this isn't a real hash function. It is, however, quite efficient for the purposes of this lab.
	return stoi(bitstring, nullptr, 2);
}

int getHash(string bitstring) { // this is also not an actual hash table lookup function. 
	return stoi(bitstring, nullptr, 2);
}

mutex mtx;

void processCart(deque<cart> const& lane, vector<entry39> dict39, vector<Product> pricelist) {

	float cartPrice = 0;
	for_each(lane.begin(), lane.end(), [&pricelist, &cartPrice, &dict39, &lane](cart j) {
		//mtx.lock(); // lock/unlock here will process entire carts at once instead
		//cout << "Cart # : " << j.getNumber() << " running on thread id: " << this_thread::get_id() << endl;
		cartPrice = 0;

		for_each(j.items.begin(), j.items.end(), [&pricelist, &cartPrice, &dict39, &j](string l) {

			for_each(pricelist.begin(), pricelist.end(), [&pricelist, &cartPrice, &dict39, &j, &l](Product k) {
				if (k.getBarcode() == l) {
					mtx.lock();
					cout << "Cart # : " << j.getNumber() << " running on thread id: " << this_thread::get_id() << endl;

					cout << "Ascii Representatin of Barcode : ";
					int susfu;
					susfu = 0;
					for (susfu = 0; susfu < k.getBarcode().size(); susfu = susfu + 9) {
						cout << dict39.at(getHash(k.getBarcode().substr(susfu, 9))).character;
					}

					cout << " Price : " << k.getPrice() << endl;
					cartPrice += k.getPrice();

					cout << "Barcode : " << k.getBarcode() << endl << endl;
					mtx.unlock();

				}
				});

			});

		cout << "Cart # " << j.getNumber() << " has a total price of: " << cartPrice << endl << endl << endl;


		});


	//mtx.unlock(); // lock unlock here will process entire carts at once instead, this is the one line I forgot to comment out
	return;

}

// this is unused
void processCartItem(cart j, vector<entry39> dict39, vector<Product> pricelist) { 

	float cartPrice = 0;

	for_each(pricelist.begin(), pricelist.end(), [&pricelist, &cartPrice, &dict39, &j](Product k) {

		if (k.getBarcode() == j.getFirst()) {

			cout << "Ascii Representatin of Barcode : ";
			int susfu;
			susfu = 0;
			for (susfu = 0; susfu < k.getBarcode().size(); susfu = susfu + 9) {
				cout << dict39.at(getHash(k.getBarcode().substr(susfu, 9))).character;
			}

			cout << " Price : " << k.getPrice() << endl;
			cartPrice += k.getPrice();

			cout << "Barcode : " << k.getBarcode() << endl << endl;

		}

		});
}

int main()
{
	//2 lanes for now

	vector<Product> pricelist;
	string fileName;

	//test1 thread begin
	//thread test1([&pricelist, &fileName]() {


		// reading and parsing productprice.xml
		//string fileName;
	fileName = "ProductPrice.xml";
	ifstream ifs{ fileName };
	string xmlContent{ istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	regex reg("<Product>\n\t<Barcode>([0-1]{9}[0-1]{9}[0-1]{9}[0-1]{9}[0-1]{9}[0-1]{3})</Barcode>\n\t<Price>([0-9,.]+)</Price>\n<\/Product>");
	smatch matches;

	string proString; // this is the product name, as in the barcode.
	string barString;
	float barFloat; // this is the price.  ...it's a little confusing.
	int i = 1;
	//int kaka = 0;
	//bool bhbh = 0;
	//vector<Product> pricelist;
	//vector<Product> pricelist(400);
	string::const_iterator productPriceSearchStart = (xmlContent.begin());
	while (regex_search(productPriceSearchStart, xmlContent.cend(), matches, reg)) {
		proString = matches.str(i);
		barString = matches.str(i + 1); // pretty sure this line is useless
		barFloat = stof(matches.str(i + 1));

		pricelist.push_back(Product(proString, barFloat));

		/*
		kaka = 0;
		while (!bhbh) {
			if (pricelist.at(dumbHashFunc(proString) + kaka).getBarcodeNode() == nullptr) {
				pricelist.at(dumbHashFunc(proString)) = Product(proString, barFloat);
				bhbh = 1;
			}
			kaka++;
		}
		bhbh = 0;
		*/

		productPriceSearchStart = matches.suffix().first;
	}


	for_each(pricelist.begin(), pricelist.end(), [&pricelist](Product k) {
		cout << k.getBarcode() << " " << k.getPrice() << endl;
		/*
		if (k.getBarcodeNode() != nullptr) {
			cout << k.getBarcode() << " " << k.getPrice() << endl;
		}
		*/
		});


	ifs.close();
	//cout << pricelist.size();


	//test1 thread end
	//});
	//test1.join();



	//cout << pricelist.size();

	string fubar = "' '\
011000100\
\
'-'\
010000101\
\
'+'\
010001010\
\
'$'\
010101000\
\
'%'\
000101010\
\
'*'\
010010100\
\
'.'\
110000100\
\
'/'\
010100010\
\
'0'\
000110100\
\
'1'\
100100001\
\
'2'\
001100001\
\
'3'\
101100000\
\
'4'\
000110001\
\
'5'\
100110000\
\
'6'\
001110000\
\
'7'\
000100101\
\
'8'\
100100100\
\
'9'\
001100100\
\
'A'\
100001001\
\
'B'\
001001001\
\
'C'\
101001000\
\
'D'\
000011001\
\
'E'\
100011000\
\
'F'\
001011000\
\
'G'\
000001101\
\
'H'\
100001100\
\
'I'\
001001100\
\
'J'\
000011100\
\
'K'\
100000011\
\
'L'\
001000011\
\
'M'\
101000010\
\
'N'\
000010011\
\
'O'\
100010010\
\
'P'\
001010010\
\
'Q'\
000000111\
\
'R'\
100000110\
\
'S'\
001000110\
\
'T'\
000010110\
\
'U'\
110000001\
\
'V'\
011000001\
\
'1'\
111000000\
\
'X'\
010010001\
\
'Y'\
110010000\
\
'Z'\
011010000\
";

	vector<entry39> dict39(513); // 2^9 = 512, so I set it to 513 for access to index 512. 

	char entryChar;
	string entryCode;
	regex reg5("'(.)'[.\n\s]*([0-9]{9})");
	smatch fubarmatches;
	string::const_iterator fubarsearchStart = (fubar.begin());


	while (regex_search(fubarsearchStart, fubar.cend(), fubarmatches, reg5)) {
		entryChar = fubarmatches.str(1)[0];
		entryCode = fubarmatches.str(2);
		cout << entryChar << " " << entryCode << endl;

		dict39.at(hashFunc(entryCode)) = entry39(entryChar, entryCode);
		fubarsearchStart = fubarmatches.suffix().first;
	}

	//createVector(fubar, reg5, dict39);

	for_each(dict39.begin(), dict39.end(), [&dict39](entry39 bvc) {
		cout << bvc.character << " " << bvc.barcodeString << " " << bvc.barcodeBitset << endl;
		});



	//reading and parsing Carts.csv
	fileName = "Carts.csv";
	ifstream ifs2;
	ifs2.open(fileName);
	string csvContent{ istreambuf_iterator<char>(ifs2), istreambuf_iterator<char>() };
	//cout << csvContent << endl;
	regex reg2("Cart([0-9]{3})\n,*(?:(?:[0-z,]{12})[,\n]*)*");
	regex reg3("([0-z,]{12})[,\n]");
	smatch matches1;
	smatch matches2;

	string::const_iterator searchStart = csvContent.begin();
	string::const_iterator searchStart1 = csvContent.begin();

	cart testcart;

	//let us assume a costco with exactly four open lanes
	deque<cart> lane1; // a queue of carts, containing items
	float lane1Price; // this isn't the price of the whole lane, just the current item in the lane
	deque<cart> lane2;
	float lane2Price;
	deque<cart> lane3;
	float lane3Price;
	deque<cart> lane4;
	float lane4Price;

	string letter;
	string h;
	string binary;

	while (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

		thread threadmakelane1([&lane1, &searchStart, &searchStart1, &csvContent, &matches1, &matches2, &reg2, &reg3]() {
			if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {
				lane1.push_back(stoi(matches1.str(1)));	// add a cart
				cout << "Making Cart # : " << lane1.back().getNumber() << " onto Lane 1" << endl;
				lane1.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent); //fill the cart with items
				//cout << endl << endl;

				searchStart = matches1.suffix().first;
			}
		});

		thread threadmakelane2([&lane2, &searchStart, &searchStart1, &csvContent, &matches1, &matches2, &reg2, &reg3]() {
			if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

				lane2.push_back(stoi(matches1.str(1)));
				cout << "Making Cart # : " << lane2.back().getNumber() << " onto Lane 2" << endl;
				lane2.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent);
				//cout << endl << endl;

			}
		});


		thread threadmakelane3([&lane3, &searchStart, &searchStart1, &csvContent, &matches1, &matches2, &reg2, &reg3]() {
			if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

				lane3.push_back(stoi(matches1.str(1)));
				cout << "Making Cart # : " << lane3.back().getNumber() << " onto Lane 3" << endl;
				lane3.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent);
				//cout << endl << endl;

				searchStart = matches1.suffix().first;
			}
		});

		thread threadmakelane4([&lane4, &searchStart, &searchStart1, &csvContent, &matches1, &matches2, &reg2, &reg3]() {
			if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

				lane4.push_back(stoi(matches1.str(1)));
				cout << "Making Cart # : " << lane4.back().getNumber() << " onto Lane 4" << endl;
				lane4.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent);
				//cout << endl << endl;

				searchStart = matches1.suffix().first;
			}
		});

	}

	
	/*
	while (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

		if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {
			lane1.push_back(stoi(matches1.str(1)));	// add a cart
			cout << "Making Cart # : " << lane1.back().getNumber() << " onto Lane 1" << endl;
			lane1.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent); //fill the cart with items
			//cout << endl << endl;

			searchStart = matches1.suffix().first;
		}

		if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

			lane2.push_back(stoi(matches1.str(1)));
			cout << "Making Cart # : " << lane2.back().getNumber() << " onto Lane 2" << endl;
			lane2.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent);
			//cout << endl << endl;

			searchStart = matches1.suffix().first;
		}


		if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

			lane3.push_back(stoi(matches1.str(1)));
			cout << "Making Cart # : " << lane3.back().getNumber() << " onto Lane 3" << endl;
			lane3.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent);
			//cout << endl << endl;

			searchStart = matches1.suffix().first;
		}

		if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

			lane4.push_back(stoi(matches1.str(1)));
			cout << "Making Cart # : " << lane4.back().getNumber() << " onto Lane 4" << endl;
			lane4.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent);
			//cout << endl << endl;

			searchStart = matches1.suffix().first;
		}


	}
	*/


	float cartPrice = 0;


	thread threadlane1(processCart, lane1, dict39, pricelist);
	thread threadlane2(processCart, lane2, dict39, pricelist);
	thread threadlane3(processCart, lane3, dict39, pricelist);
	thread threadlane4(processCart, lane4, dict39, pricelist);
	threadlane1.join();
	threadlane2.join();
	threadlane3.join();
	threadlane4.join();

	return 0;
}

/*
//createVector is UNUSED
template <typename T>
vector<T> createVector(string s, regex r, vector<T>& vec) {

	char entryChar;
	string entryCode;
	//regex r1("'(.)'[.\n\s]*([0-9]{9})");
	smatch smatches;
	string::const_iterator stringStart = (s.begin());


	while (regex_search(stringStart, s.cend(), smatches, r)) {
		entryChar = smatches.str(1)[0];
		entryCode = smatches.str(2);
		cout << entryChar << " " << entryCode << endl;

		//this is too class specific. I have multiple hash functions. Entry39 and Product take different variable types in their constructors, as well, though that can be dealt with.
		//still, this is kinda too hard for me figure out how to do right now.
		//also, the code is already there and only used once, so there's no real point in this
		vec.at(hashFunc(entryCode)) = T(entryChar, entryCode);
		stringStart = smatches.suffix().first;
	}

	return vec;
}


	while (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

		thread threadmakelane1([&lane1, &searchStart, &searchStart1, &csvContent, &matches1, &matches2, &reg2, &reg3]() {
			if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {
				lane1.push_back(stoi(matches1.str(1)));	// add a cart
				cout << "Making Cart # : " << lane1.back().getNumber() << " onto Lane 1" << endl;
				lane1.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent); //fill the cart with items
				//cout << endl << endl;

				searchStart = matches1.suffix().first;
			}
		});

		thread threadmakelane2([&lane2, &searchStart, &searchStart1, &csvContent, &matches1, &matches2, &reg2, &reg3]() {
			if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

				lane2.push_back(stoi(matches1.str(1)));
				cout << "Making Cart # : " << lane2.back().getNumber() << " onto Lane 2" << endl;
				lane2.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent);
				//cout << endl << endl;

			}
		});


		thread threadmakelane3([&lane3, &searchStart, &searchStart1, &csvContent, &matches1, &matches2, &reg2, &reg3]() {
			if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

				lane3.push_back(stoi(matches1.str(1)));
				cout << "Making Cart # : " << lane3.back().getNumber() << " onto Lane 3" << endl;
				lane3.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent);
				//cout << endl << endl;

				searchStart = matches1.suffix().first;
			}
		});

		thread threadmakelane4([&lane4, &searchStart, &searchStart1, &csvContent, &matches1, &matches2, &reg2, &reg3]() {
			if (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {

				lane4.push_back(stoi(matches1.str(1)));
				cout << "Making Cart # : " << lane4.back().getNumber() << " onto Lane 4" << endl;
				lane4.back().makeCart(reg2, reg3, matches1, matches2, searchStart, searchStart1, csvContent);
				//cout << endl << endl;

				searchStart = matches1.suffix().first;
			}
		});

	}
	
*/
