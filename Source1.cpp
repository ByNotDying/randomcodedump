using namespace std;
#include <iostream>
#include <cstdlib>
#include <iomanip>
#define HEIGHT 100 

template <typename T>
class Node
{
public:
	T data;
	unsigned count;
	Node* left, * right;
	Node(T d, unsigned c)
	{
		left = right = NULL;
		data = d;
		count = c;
	}
};
template <typename T>
class Queue
{
public:
	int front, rear;
	int capacity;
	Node<T>** array;
	Queue(int c)
	{
		front = rear = -1;
		capacity = c;
		array = new Node<T> * [(capacity * sizeof(Node<T>*))];
	}
	Node<char>* Front()
	{
		if (isEmpty())
			return NULL;
		return array[front];
	}
	int hasData()
	{
		return front == rear && front != -1;
	}
	int isEmpty()
	{
		return front == -1;
	}
	int isFull()
	{
		return rear == capacity - 1;
	}
	void enQueue(Node<T>* item)
	{
		if (isFull())
			return;
		array[++rear] = item;
		if (front == -1)
			++front;
	}
	Node<char>* deQueue()
	{
		if (isEmpty())
			return NULL;
		Node<char>* temp = array[front];
		if (front == rear)
			front = rear = -1;
		else
			++front;
		return temp;
	}
};
Node<char>* minimum(Queue<char>* firstQ, Queue<char>* secondQ)
{
	if (firstQ->isEmpty())
		return secondQ->deQueue();
	if (secondQ->isEmpty())
		return firstQ->deQueue();
	if (firstQ->Front()->count < secondQ->Front()->count)
		return firstQ->deQueue();
	return secondQ->deQueue();
}
int isLeaf(Node<char>* n)
{
	return !(n->left) && !(n->right);
}
void print(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		(arr[i] == 1) ?
		cout << '.' : cout << '-';
	cout << endl;
}
Node<char>* build(char data[], int count[], int size)
{
	Node<char>* left, * right, * top;
	Queue<char>* firstQ = new Queue<char>(size);
	Queue<char>* secondQ = new Queue<char>(size);
	for (int i = 0; i < size; ++i)
		firstQ->enQueue(new Node<char>(data[i], count[i]));
	while (!(firstQ->isEmpty() && secondQ->hasData()))
	{
		left = minimum(firstQ, secondQ);
		right = minimum(firstQ, secondQ);
		top = new Node<char>('@', left->count + right->count);
		top->left = left;
		top->right = right;
		secondQ->enQueue(top);
	}
	return secondQ->deQueue();
}
void print(Node<char>* root, int arr[], int top)
{
	if (root->left != NULL)
	{
		arr[top] = 0;
		print(root->left, arr, top + 1);
	}
	if (root->right != NULL)
	{
		arr[top] = 1;
		print(root->right, arr, top + 1);
	}
	if (isLeaf(root) == true)
	{
		cout << root->data << ": ";
		print(arr, top);
	}
}
void Compress(char data[], int count[], int size)
{
	Node<char>* root = build(data, count, size);
	int arr[HEIGHT], top = 0;
	print(root, arr, top);
}
int main()
{
	char a[] = { 'y', 'u', 'o', 'i', 'a', 'e' };
	int c[] = { 5, 9, 12, 13, 16, 45 };
	int size = sizeof(a) / sizeof(a[0]);
	Compress(a, c, size);
	return 0;
}
