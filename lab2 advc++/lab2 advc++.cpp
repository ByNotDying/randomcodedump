// lab2 advc++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*// for conversion of hex to decimal, then to binary
string h = "84B062548848";
	long long int d = stoll(h, 0, 16);

	//cout << stoll(h, 0, 16) << endl;
	//cout << d << endl;

	string binary = bitset<48>(d).to_string(); //to binary
	cout << binary << endl;

	string barcode;
	string productName;
	barcode.resize(9);
	productName.resize(5);

	//
	int k = 0;
	for (int i = 0; i < binary.size(); i++) {
		if (k == 9) {
			cout << barcode << endl;
			k = 0; }
		barcode[k] = binary[i];
		k++;
	}
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <memory>
#include <regex>
#include <bitset>
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

struct Barcode : public Node{
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
	string getAscii(){
		return asciiName;
	}
	void changeAscii(string text){
		asciiName = text;
	}
};

struct Price : public Node{
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
	Product(string name, float price) : B(make_shared<Barcode>(name)), P(make_shared<Price>(price))  {}
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

int hashFunc(string bitstring) { // You might notice that this isn't a real hash function. It is, however, quite efficient for the purposes of this lab.
	return stoi(bitstring, nullptr, 2);
}

int getHash(string bitstring) { // this is also not an actual hash table lookup function. 
	return stoi(bitstring, nullptr, 2);
}

int dumbHashfunc(string bitstring) {
	int tempInt;
	 tempInt = stoi(bitstring, nullptr, 2);
	 return tempInt % 33;
}

/*
int hashFunc(string const& s) {//djb2 bernstein ctrl+c/v'ed from stackoverflow.com
	unsigned long hash = 5381;
	for (auto c : s) {
		hash = (hash << 5) + hash + c; 
		// hash * 33 + c 
	}
	return hash;
}
*/



//assorted regex functions
//<Product>\n\t<Barcode>([0-1]+)</Barcode>\n\t<Price>([0-9,.]+)</Price>\n<\/Product>/g
//<Product>\n\t<Barcode>([0-1]{9}[0-1]{9}[0-1]{9}[0-1]{9}[0-1]{9})[0-1]{3}</Barcode>\n\t<Price>([0-9,.]+)</Price>\n<\/Product>/g
//Cart([0-9]{3}).+([0-z]{12})[,\n]/gs
//Cart([0-9]{3})\n([0-z,]+)/g
//Cart([0-9]{3})\n(?:([0-z,]{12})[,\n])+

int main()
{
	// reading and parsing productprice.xml
	string fileName;
	fileName = "ProductPrice.xml";
	ifstream ifs{ fileName };
	string xmlContent{ istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	regex reg ("<Product>\n\t<Barcode>([0-1]{9}[0-1]{9}[0-1]{9}[0-1]{9}[0-1]{9}[0-1]{3})</Barcode>\n\t<Price>([0-9,.]+)</Price>\n<\/Product>");
	smatch matches;

	//test data below
	/*
	string proString = matches.str(1);
	string barString = matches.str(2);
	float barFloat = stof(matches.str(2));
	Product testproduct(proString, barFloat);
	*/
	/*
	cout << matches.str(1) << "\n";
	cout << matches.str(2) << "\n";
	cout << test2 << endl;
	cout << float2 << endl;
	*/
	// end of test data

	string proString; // this is the product name, as in the barcode.
	string barString;
	float barFloat; // this is the price.  ...it's a little confusing.
	int i = 1;
	vector<Product> pricelist;
	//vector<Product> pricelist(1000);
	string::const_iterator searchStart = (xmlContent.begin());
	while ( regex_search ( searchStart, xmlContent.cend(), matches, reg) ) {
		proString = matches.str(i);
		barString = matches.str(i + 1); // pretty sure this line is useless
		barFloat = stof(matches.str(i+1));
		//cout << proString << " " << barString << endl;

		pricelist.push_back(Product(proString, barFloat));
		//	pricelist.at(dumbHashFunc(barFloat)) = Product(entryChar, entryCode);

		searchStart = matches.suffix().first;
	}
	
	
	for_each(pricelist.begin(), pricelist.end(), [&pricelist](Product k) {
		cout << k.getBarcode() << " " << k.getPrice() << endl;
		});

	//cout << pricelist.at(i).getBarcode() << " " << pricelist.at(i).getPrice() << endl;
	//for_each(pricelist.begin(), pricelist.(end), [&](int i) { cout << pricelist.at(i).B->price });


	
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
'0'\
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


vector<entry39> dict39(513); // 2^9 = 512, so I set it to 513 for access to index 513. 
//cout<< dict39.max_size(); //119304647 :\
//I got excited because I thought I could make a vector size 111000000, and "hash" the index of everything to its barcode.
//It threw an error cause the program didn't have 10gb of memory but then I realized I could do essentially the same thing with a vector size 512.
//actually, 511 but 513 just to be safe.


char entryChar;
string entryCode;
regex reg5("'(.)'[.\n\s]*([0-9]{9})");
//regex reg("<Product>\n\t<Barcode>([0-1]{9}[0-1]{9}[0-1]{9}[0-1]{9}[0-1]{9}[0-1]{3})</Barcode>\n\t<Price>([0-9,.]+)</Price>\n<\/Product>");
smatch fubarmatches;
string::const_iterator fubarsearchStart = (fubar.begin());

//I should really make this into a template vector<T> createVector() function
while (regex_search(fubarsearchStart, fubar.cend(), fubarmatches, reg5)) {
	entryChar = fubarmatches.str(1)[0];
	entryCode = fubarmatches.str(2);
	cout << entryChar << " " << entryCode << endl;

	//dict39.push_back(entry39(entryChar, entryCode));
	dict39.at(hashFunc(entryCode)) = entry39(entryChar, entryCode);
	fubarsearchStart = fubarmatches.suffix().first;
}

for_each(dict39.begin(), dict39.end(), [&dict39](entry39 bvc) {
	cout << bvc.character << " " << bvc.barcodeString << " " << bvc.barcodeBitset << endl;
});


	
	//reading and parsing Carts.csv
	ifs.close();
	fileName = "Carts.csv";
	ifs.open(fileName);
	string csvContent{ istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
	//cout << csvContent << endl;
	regex reg2("Cart([0-9]{3})\n,*(?:(?:[0-z,]{12})[,\n]*)*");
	regex reg3("([0-z,]{12})[,\n]");
	//regex reg2("Cart([0-9]{3})[\s\S]+([0-z]{12})[,\n]"); //original regex statement
	smatch matches1;
	smatch matches2;

	searchStart = csvContent.begin();
	string::const_iterator searchStart1 = csvContent.begin();


	list<Product> testCart;
	string letter;
	string barcode;
	string h;
	string binary;
	string asdfasdf;
	long long int d = 0;
	float tempPrice = 0;
	float cartPrice = 0;
	while (regex_search(searchStart, csvContent.cend(), matches1, reg2)) {
		cout << "Cart # : " << matches1.str(1) << " ";

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


			for_each(pricelist.begin(), pricelist.end(), [&pricelist, &binary, &cartPrice, &dict39](Product k) {
				
				if (k.getBarcode() == binary) {

					cout << "Ascii Representatin of Barcode : ";
					int susfu;
					susfu = 0;
					for (susfu = 0; susfu < k.getBarcode().size(); susfu = susfu + 9) {
						cout << dict39.at(getHash(k.getBarcode().substr(susfu, 9))).character; //also not how you get hash values, but I'm 100% sure my table will never run into collisions

					}


					/*
					for (susfu = 0; susfu < k.getBarcode().size(); susfu = susfu + 9) {
						//cout << k.getBarcode().substr(susfu, 9);
						for_each(dict39.begin(), dict39.end(), [&dict39, &k, &susfu](entry39 snafu) { // replace dict array with hash and you should be good
							if (snafu.barcodeString == k.getBarcode().substr(susfu, 9)) {
								cout << snafu.character;
							}
						});
					}
					*/
					
					/*
					for_each(dict39.begin(), dict39.end(), [&dict39, &k, &susfu](entry39 snafu) {
						if (snafu.barcodeString == k.getBarcode().substr(susfu, 9)) {
							cout << snafu.character;
						}
						susfu = susfu + 9;
					});
					*/


					cout << " Price : " << k.getPrice() << endl;
					cartPrice += k.getPrice();

					cout << "Barcode : " << k.getBarcode() << endl << endl;



				}


			});


			searchStart = matches2.suffix().first;

		}
		
		cout << endl;
		cout << "Cart " << matches1.str(1) << " ";
		cout << "has a total Price of : " << cartPrice << endl << endl << endl;
		searchStart = matches1.suffix().first;
	}
	
	
	

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

/*At this point, we already have the list of products and prices as a vector, vector<Products> pricelist. It shouldn't be difficult to change the container type of the products if needed.
	It contains Products, which is a class of class type node, and two nodes called Barcode and Price, which each contain their prices.
	tbh I kind of feel like there's something seriously wrong with my implementation because we never use the Node-iness of them at all, and all my binaries are stored as strings.
	but whatever. It'll work easier.
	Anyways, Barcode contains the binary representation as string name, and as a precaution I've also given them string asciiNames which can be used to store ascii versions of the binary
	If the need should arrive, of course.

	My current plan, if I am able to do all lookups using only the binary names, is to just iterate through vector<Product> pricelist each time a I need to look up a price.
	This is incredibly inefficient, but its the easiest to implement for now, and can probably be easily modified.
	My backup plan is to just do all lookups by converting the string to int, then comparing numerical values of the ints. Because of the nature of code 3of9, I should be able to quickly
	from a table of increasing numerical values and prices. This is probably risky because data like 000000111 will be turned into 111 (one-hundred evelen and one) but it should work.
	I should even be able to skip through certain parts of the list based on how large the number is.
	I will probably need to make this anyways to translate barcodes into characters quickly.
	The issue with both of these plans is that they don't really use any real hashing.
	My last resort, and the way the lab was probably intended to be done, is to just convert the binary barcodes to letters, hash the strings, and put them into a hash table.
	I would then, of course, call the hash table to look up the price of each item every time I want to find a price.

	The more pressing issue right now is that I need to set up the carts. "Process" sounds like jargon I don't know about, and I was asked to process the csv file.
	I'm just going to assume the best case for me and hope that Process just means find the price of the whole cart and its items and print them out.
	The more foreboding possibility is that I need to save that data in a format I don't know about.
	Anyways, to do either, I will need to use REGEX.

	To be honest, converting the table of barcodes and prices to text and prices seems really redundant to me when I can look up the hex values much more easily.

	The PROPER thing to do regarding all of this is to ask the professor about all this, but he always seems to be absent whenever I am finally able to formulate my questions properly.

	So, here's what I have so far.
	I have two regex statements, but one is just a ghetto appended version of the other.
	My first idea was to just capture entire carts/lines as a string and then process that string, but then I realized it might be easier to capture each item with regex and process single items.
	I think my first idea might have have been better in theory, but I can't figure out a proper implementation. Also, the csv has weird commas added into it to make this implementation very difficult.
	Anyways, I have a loop that prints cart number and items out, I just need to find a way to make the loop print out the required associated data.
	So, all it needs to do is print out the price of each item, save each items price, and then print out the price of the whole cart.
	The big issue for me so far, is that I need to make the price of each item reset each time I get to a new cart.

	Right now I think I'll try using the first capture group, which keeps the cart number.
	Possible strategies might include finding out when the number changes and then resetting the cart price when I detect a change in cart number.
	Otherwise, I could use a range based option, scan all items in the csv from the current location to the next match, and then add the numbers before a loop exit that resets the cart price.
	Once I'm done with that, switching to other implementations should be a cinch, so I should be 100% making sure I can do this first anyways.

	I just tried doing the cart number change thing, but it looks like actually, it'll just be easier to do the range based option because its kinda already implemented in my loop to print.
	I will need to create and use functions for it, though.

	update: I just managed to grab prices and calculate the price of the cart. I think. I haven't checked.

	The big roadblock I'm hitting is how I'm supposed to convert barcodes into text.

	*/
