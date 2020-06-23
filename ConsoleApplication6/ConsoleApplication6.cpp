#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>

const int UniqueSymbols = 1 << CHAR_BIT;
const char* SampleString = "MISSISIPI^RIVER";

typedef std::vector<bool> HuffCode;
typedef std::map<char, HuffCode> HuffCodeMap;

class QNode
{
public:
	const int f;

	virtual ~QNode() {}

protected:
	QNode(int f) : f(f) {}
};

class BranchNode : public QNode
{
public:
	QNode* const left;
	QNode* const right;

	BranchNode(QNode* c0, QNode* c1) : QNode(c0->f + c1->f), left(c0), right(c1) {}
	~BranchNode()
	{
		delete left;
		delete right;
	}
};

class LeafNode : public QNode
{
public:
	const char c;

	LeafNode(int f, char c) : QNode(f), c(c) {}
};

struct NodeCmp
{
	bool operator()(const QNode* lhs, const QNode* rhs) const { return lhs->f > rhs->f; }
};

QNode* BuildTree(const int(&frequencies)[UniqueSymbols])
{
	std::priority_queue<QNode*, std::vector<QNode*>, NodeCmp> trees;

	for (int i = 0; i < UniqueSymbols; ++i)
	{
		if (frequencies[i] != 0)
			trees.push(new LeafNode(frequencies[i], (char)i));
	}
	while (trees.size() > 1)
	{
		QNode* childR = trees.top();
		trees.pop();

		QNode* childL = trees.top();
		trees.pop();

		QNode* parent = new InternalNode(childR, childL);
		trees.push(parent);
	}
	return trees.top();
}

void GenerateCodes(const QNode* node, const HuffCode& prefix, HuffCodeMap& outCodes)
{
	if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
	{
		outCodes[lf->c] = prefix;
	}
	else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
	{
		HuffCode leftPrefix = prefix;
		leftPrefix.push_back(false);
		GenerateCodes(in->left, leftPrefix, outCodes);

		HuffCode rightPrefix = prefix;
		rightPrefix.push_back(true);
		GenerateCodes(in->right, rightPrefix, outCodes);
	}
}

int main()
{
	// Build frequency table
	int frequencies[UniqueSymbols] = { 0 };
	const char* ptr = SampleString;
	while (*ptr != '\0')
		++frequencies[*ptr++];

	QNode* root = BuildTree(frequencies);

	HuffCodeMap codes;
	GenerateCodes(root, HuffCode(), codes);


	for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
	{
		std::cout << it->first << " ";
		std::copy(it->second.begin(), it->second.end(),
			std::ostream_iterator<bool>(std::cout));
		std::cout << std::endl;
	}


	return 0;
}