#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
using namespace std;

class char_stack
{
private:
	struct node
	{
		char data;
		node* next;
	};

private:
	typedef node node_t;
	typedef node_t* node_ptr_t;

private:
	node_ptr_t top_node;

public:
	char_stack()
		: top_node(NULL)
	{

	}

	~char_stack()
	{
		while (!empty())
			pop();
	}

	void push(char data)
	{
		node_ptr_t new_node = new node_t;
		new_node->data = data;
		new_node->next = top_node;
		top_node = new_node;
	}

	void pop()
	{
		node_ptr_t tmp = top_node->next;
		delete top_node;
		top_node = tmp;
	}

	char top() const
	{
		return top_node->data;
	}

	bool empty() const
	{
		return !top_node;
	}
};

// -----------------------
bool check_func(const char* s)
{
	const char* left = "([{";
	const char* right = ")]}";

	char_stack stack;

	for (size_t i = 0; s[i] != '\0'; ++i)
	{
		if (strchr(left, s[i]))
		{
			stack.push(s[i]);
		}

		else
		{
			if (strchr(right, s[i]))
			{
				if (stack.empty())
					return false;

				switch (stack.top())
				{
				case '(':
					if (s[i] != ')')
						return false;
					break;

				case '[':
					if (s[i] != ']')
						return false;
					break;

				case '{':
					if (s[i] != '}')
						return false;
					break;
				}

				stack.pop();
			}
		}
	}
	return stack.empty();
}

int _tmain(int argc, _TCHAR* argv[])
{
	char s[256];
	int i;

	do
	{
		cout << "MENU:" << endl;
		cout << "1. Input from file" << endl;
		cout << "2. Input from klav" << endl;
		cout << "0. Exit" << endl;
		cin >> i;
		switch (i)
		{
		case 1:
		{
			ifstream ifile("input.txt");
			int ind = 0;
			ifile >> s;

			cout << boolalpha << check_func(s) << endl;
			break;
		}
		case 2:
		{
			cout << "INPUT STRING:" << endl;
			cin >> s;
			if (!cin) return 1;
			cout << boolalpha << check_func(s) << endl;
			break;
		}
		case 0:
		{
			exit(0);
			break;
		}
		}
	} while (i != 0);



	return 0;
}
