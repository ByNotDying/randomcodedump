
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

struct QNode {
private:
	char item;
	int frequency;
public:
	shared_ptr<QNode> next;
	void addOneFrequency() { 
		this->frequency = this->frequency + 1;
	}
	void changeFrequency(int frequency) {
		this->frequency = frequency;
	}
	void changeChar(char item) {
		this->item = item;
	}
	char itemVal() const{
		return item;
	}
	int freqVal() const{
		return frequency;
	}
	QNode() {
		item = NULL;
		frequency = 0;
		next = nullptr;
	}
	QNode(char item) {
		this->item = item;
		frequency = 1;
		next = nullptr;
	}
	QNode(char item, int frequency) {
		this->item = item;
		this->frequency = frequency;
		next = NULL;
	}
};

struct PriorityQueue {
	shared_ptr<QNode> head;
	PriorityQueue() {
		head = nullptr;
	}
	void findChar(char targetChar) const{//used for testing. prints the frequency, value, and position of the character in the queue. might be more useful if modified into a function that returned a pointer.
		shared_ptr<QNode> iNode;
		int tracker = 0; //to keep track of place in list
		for (iNode = head; iNode != nullptr; iNode = iNode->next) {
			tracker++; // increment tracker
			if (iNode->itemVal() == targetChar) {
				cout << "item: " << iNode->itemVal() << " " << endl;
				cout << "freq: " << iNode->freqVal() << " " << endl;
				cout << "posi: " << tracker << " " << endl;
				cout << endl;
			}
		}
		
		//cout << head->itemVal();
		/*
		if (head->itemVal() == targetChar) {
			cout << "yes";
		}
		*/
		return;
	}
	void addNode(char addChar) {// using mostly for testing, need to reimplement as inc/add function. fuse with findChar
		if (head == nullptr) {
			head = make_shared<QNode>(addChar); 
		}
		else {
			shared_ptr<QNode> newNode = make_shared<QNode>(addChar);
			newNode->next = head;
			head = newNode;
		}
	}
	void findAddIncrement(char addChar){// findChar+addNode. look for node, if found, increment. else, make the node.
		if (head == nullptr) {
			head = make_shared<QNode>(addChar);
		}
		else {
			shared_ptr<QNode> iNode;
			shared_ptr<QNode> swapNode;
			bool found = false; //marks whether or not if you found a node with the value
			for (iNode = head; iNode != nullptr; iNode = iNode->next) {
				if (iNode->itemVal() == addChar) {
					iNode->addOneFrequency();
					found = true; //indicates that we have found the marker
				}
				if (iNode->next == nullptr && found == false) {
					shared_ptr<QNode> newNode = make_shared<QNode>(addChar);
					newNode->next = head;
					head = newNode;
				}
			}
			
		}

	}
	void orderQueue() {
		shared_ptr<QNode> iNode;
		int swapVal;
		int swapFreq;
		if (head == nullptr) {
			return;
		}
		for (iNode = head; iNode != nullptr; iNode = iNode->next) {
			if (iNode->next == nullptr) {
				return;
			}
			else if (iNode->freqVal() > iNode->next->freqVal()) {//if the frequency of current node is now larger than next node...
				
				swapVal = iNode->itemVal();
				swapFreq = iNode->freqVal();
				cout << iNode->itemVal();
				cout << iNode->freqVal();
				cout << iNode->next->itemVal();
				cout << iNode->next->freqVal();
				cout << endl;
				
				iNode->changeChar(iNode->next->itemVal());
				iNode->changeFrequency(iNode->next->freqVal());
				iNode->next->changeChar(swapVal);
				iNode->next->changeFrequency(swapFreq);

				swapVal = iNode->itemVal();
				swapFreq = iNode->freqVal();
				cout << iNode->itemVal();
				cout << iNode->freqVal();
				cout << iNode->next->itemVal();
				cout << iNode->next->freqVal();
				cout << endl;

			}
		}
	}
	void printQueue() const{
		shared_ptr<QNode> iNode;
		int tracker = 0; //to keep track of place in list
		for (iNode = head; iNode != nullptr; iNode = iNode->next) {
			tracker++; // increment tracker
				cout << "item: " << iNode->itemVal() << " " << endl;
				cout << "freq: " << iNode->freqVal() << " " << endl;
				cout << "posi: " << tracker << " " << endl;
				cout << endl;
		}

	}
	void deleteFront(){
		// I would call a delete but I think it's not needed with shared_ptr????
		if (head == nullptr) {
			return;
		}
		head = head->next;
		return;
	}

	shared_ptr<QNode> getFront() const {
		return head;
	}

	shared_ptr<QNode> popFront() {
		if (head == nullptr) {
			return nullptr;
		}
		shared_ptr<QNode> headcopy = head;
		head = head->next;
		return headcopy;
	}


};

struct BranchNode : public QNode
{
//private:
public:
	shared_ptr<QNode> left;
	shared_ptr<QNode> right;

	//BranchNode(QNode* c0, QNode* c1) : QNode(c0->f + c1->f), left(c0), right(c1) {}
	/*Algorithm HuffmanTree( FQ )
while FQ.size() > 1 do
QLeft = FQ.front()
FQ.pop()
QRight = FQ.front()
FQ.pop()
node = new Branch(QLeft,QRight)
Insert node into FQ
return FQ*/

	BranchNode(QNode * l, QNode * r) {


	}

};

class LeafNode : public QNode
{
public:

	LeafNode(char item, int frequency) : QNode(item, frequency) {}
};

void bitExtract(string sfile, vector<bitset<1>> & sBitVec, vector<bitset<8>> & eBitVec)
{
	ifstream ifs;
	ifs.open(sfile);
	char c;

	int i = 0;
	while (ifs.get(c)) {
		eBitVec.push_back(c);
		//cout << eBitVec.at(i);
		for (int s = 7; s >= 0; s--) {
			sBitVec.push_back((c >> s) & 1);
			cout << ((c >> s) & 1);
		}
		cout << " ";
		i++;
		if (ifs.eof())
		{
			cout << endl;
			return;
		}
	}
	cout << endl;
	return;
}




int main()
{
	//shared_ptr<vector<bitset<1>>> sBitVec = make_shared<vector<bitset<1>>>();
	//shared_ptr<vector<bitset<8>>> eBitVec = make_shared<vector<bitset<8>>>();

	vector < bitset<1> > sBitVec;
	vector < bitset<8> > eBitVec;

	bitExtract("Mississippi.bin", sBitVec, eBitVec);

	/*
	for (int i = 0; i < eBitVec.size(); i++) {
		cout << eBitVec.at(i);
		cout << " ";
	}
	cout << endl;
	int asdf = 0;
	for (int i = 0; i < sBitVec.size(); i++) {
		++asdf;
		cout << sBitVec.at(i);
		if (asdf == 8) {
			cout << " ";
			asdf = 0;
		}
	}
	cout << endl;
	*/




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
