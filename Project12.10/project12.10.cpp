#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;
typedef int Info;
struct Node
{
	Node* left,
		* right;
	Info info;
};
struct Elem // елемент стеку,
{ // в якому зберігаються
	Elem* link; // батьківські вузли
	Node* info;
};
Node* BinarySearchInsert(Node*& root, Info value, bool& found);
void PrintTree(Node* root, int level);
void SaveToFile(fstream& f, Node* root);
void LoadFromFile(fstream& f, Node*& root);
void Push(Elem*& top, Node* node);
Node* Pop(Elem*& top);
Node* Find(Node* root, Info value);
void RightRotation(Node*& root);
void LeftRotation(Node*& root);
int Height(Node* root);
int BFactor(Node* root);
void BalanceHeight(Node*& root);
Node* FindMax(Node* root);
Node* BinarySearchDelete(Node* root, Info val);
void DeleteTree(Node*& root, Node* node);
Node* DeleteFibonachi(Node* root, int max_fibonachi_value);
int Count(Node* root);

const int END = -1;
int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	int N;
	cout << "Enter nodes count: "; cin >> N;
	Node* root = NULL;
	Info value;
	bool found = false;
	int before = 0;
	int after = 0;
	int count = 0;
	fstream f;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних та збереження в файл" << endl;
		cout << " [2] - вивід дерева на екран" << endl;
		cout << " [3] - видалити піддерева та вивести дерево на екран" << endl;
		cout << " [4] - кількість видалених вузлів : " << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			for (int i = 0; i < N; i++)
			{
				cout << "value: "; cin >> value;
				BinarySearchInsert(root, value, found);
			}
			before = Count(root);
			f.open("tree.txt", ios::out);
			SaveToFile(f, root);
			f.close();
			break;
		case 2:
			f.open("tree.txt", ios::in);
			LoadFromFile(f, root);
			f.close();
			BalanceHeight(root);
			cout << endl;
			PrintTree(root, 0);
			break;
		case 3:
			cout << "max value Fibonachi: "; cin >> value;
			DeleteFibonachi(root, value);
			BalanceHeight(root);
			cout << endl;
			PrintTree(root, 0);
			break;
		case 4:
			 after = Count(root);
			 count = before - after;
			 cout << "кількість видалених вузлів " << count << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
Node* BinarySearchInsert(Node*& root, Info value, bool& found)
{
	if (root == NULL)
	{
		root = new Node;
		root->info = value;
		root->left = NULL;
		root->right = NULL;
		found = false;
		return root;
	}
	else
		if (value == root->info)
		{
			found = true;
			return root;
		}
		else
			if (value < root->info)
				return BinarySearchInsert(root->left, value, found);
			else
				return BinarySearchInsert(root->right, value, found);
}

void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << "   ";
		cout << root->info << endl;
		PrintTree(root->left, level + 1);
	}
}
void SaveToFile(fstream& f, Node* root)
{
	if (root != NULL)
	{
		f << root->info << endl;
		SaveToFile(f, root->left);
		SaveToFile(f, root->right);
	}
	else
		f << END << endl;
}
void LoadFromFile(fstream& f, Node*& root)
{
	Node* newNode, * current;
	Elem* top = NULL;
	Info c;
	if (!(f >> c)) 
	{
		root = NULL;
		return;
	}
	current = new Node; 
	current->info = c;
	current->left = NULL;
	current->right = NULL;
	root = current; 

	Push(top, current); 
	do
	{
			while (f >> c && c != END) 
			{
				newNode = new Node;
				newNode->info = c;
				newNode->left = NULL;
				newNode->right = NULL;
				current->left = newNode; 
				current = current->left; 

				Push(top, current); 
			}

		while (f >> c)
			if (c == END) 
			{
				if (top != NULL)
					current = Pop(top); 
			}
			else
				break;
		if (f.eof()) break;
		if (top != NULL) 
		{
			current = Pop(top); 
			newNode = new Node;
			newNode->info = c;
			newNode->left = NULL;
			newNode->right = NULL;
			current->right = newNode; 
			current = current->right; 
			Push(top, current); 
		}
	} while (!f.eof()); 
}
void Push(Elem*& top, Node* node)
{
	Elem* tmp = new Elem;
	tmp->info = node;
	tmp->link = top;
	top = tmp;
}
Node* Pop(Elem*& top)
{
	Elem* tmp = top->link;
	Node* node = top->info;
	delete top;
	top = tmp;
	return node;
}
Node* Find(Node* root, Info value)
{
	if (root == NULL || value == root->info)
		return root;
	if (value < root->info)
		return Find(root->left, value);
	else
		return Find(root->right, value);
}
void RightRotation(Node*& root) {
	Node* tmp1 = root->left;
	Node* tmp2 = tmp1->right;
	tmp1->right = root;
	root->left = tmp2;
	root = tmp1;
}
void LeftRotation(Node*& root) {
	Node* tmp1 = root->right;
	Node* tmp2 = tmp1->left;
	tmp1->left = root;
	root->right = tmp2;
	root = tmp1;
}
int Height(Node* root) {
	if (root == NULL
		)
		return 0;
	int hL = Height(root
		->left);
	int hR = Height(root
		->right);
	return (hL > hR ? hL : hR) + 1;
}
int BFactor(Node* root) {
	return Height(root
		->right)
		- Height(root
			->left);
}
void BalanceHeight(Node
	*& root)
{
	if (root != NULL
		)

	{
		while (BFactor(root) >= 2)

		{
			if (BFactor(root
				->right) < 0)
				RightRotation(root
					->right);
			LeftRotation(root);

		}
		while (BFactor(root) <=
			-2)

		{
			if (BFactor(root
				->left) > 0)
				LeftRotation(root
					->left);
			RightRotation(root);

		}
		BalanceHeight(root
			->left);
		BalanceHeight(root
			->right);

	}
}
Node* FindMax(Node* root) {
	if (root
		->right != NULL
		)
		return FindMax(root
			->right);
	else
		return root;
}
Node* BinarySearchDelete(Node* root, Info value)
{
	if (NULL == root) return NULL;
	if (root->info == value)
	{
		if (NULL == root->left && NULL == root->right)
		{
			delete root;
			return NULL;
		}
		if (NULL == root->right && root->left != NULL)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}
		if (NULL == root->left && root->right != NULL)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		root->info = FindMax(root->left)->info;
		root->left = BinarySearchDelete(root->left, root->info);
		return root;
	}
	if (value < root->info)
	{
		root->left = BinarySearchDelete(root->left, value);
		return root;
	}
	if (value > root->info)
	{
		root->right = BinarySearchDelete(root->right, value);
		return root;
	}
	return root;
}
Node* DeleteFibonachi(Node* root, int max_fibonachi_value)
{
	int value_fibonachi = 0;
	int previous_value;
	int old_value;
	while (value_fibonachi <= max_fibonachi_value)
	{
		
		Node* node = Find(root, value_fibonachi);
		if (node !=NULL)
		{
			DeleteTree(root, node);
		}
		
		old_value = value_fibonachi;
		if (value_fibonachi == 0)
		{
			value_fibonachi = 1;
		}
		else
		{
			value_fibonachi = value_fibonachi + previous_value;
		}
		previous_value = old_value;
	}
	return root;
}
void DeleteTree(Node*& root, Node* node)
{
	if (node != NULL)
	{
		DeleteTree(root, node->left);
		DeleteTree(root, node->right);
		root = BinarySearchDelete(root, node->info);
	}
}
int Count(Node* root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + Count(root->left) + Count(root->right);
}