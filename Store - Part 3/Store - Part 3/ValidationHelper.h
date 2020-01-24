#pragma warning(disable:4996)
#ifndef __VALIDHELPER_H
#define __VALIDHELPER_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ALLOCATION_ERROR = 1;

class ValidationHelper
{
public:
	template<class T>
	static void AllocationCheck(T ptr) // Requires T to be a pointer.
	{
		if (!ptr)
		{
			cout << "Allocation error. Exitting program.\n\n";
			exit(ALLOCATION_ERROR);
		}
	}

	template<class T>
	static void ManageSize(vector<T>& vec) // This function receives a vector, checks if it's full and multiplies capacity
	{
		if (vec.size() == vec.capacity())
		{
			int new_size = vec.capacity() * 2;
			vec.reserve(new_size);
		}
	}

	static bool ValidName(const string& name)
	{
		char ch;
		int len = name.length();
		for (int i = 0; i < len; i++)
		{
			ch = name[i];
			switch (ch)
			{
			case '!':
				return false;
			case '@':
				return false;
			case '#':
				return false;
			case '$':
				return false;
			case '%':
				return false;
			case '^':
				return false;
			case '&':
				return false;
			case '*':
				return false;
			case '(':
				return false;
			case ')':
				return false;
			default:
				break;
			}
		}
		return true;
	}

	static bool continueCheck()
	{
		char ch;
		cin.ignore();
		cout << "Choose 'y' to continue, 'n' to stop (y\\n): ";
		cin >> ch;
		while (ch != 'y' && ch != 'n')
		{
			cout << "Please enter a valid response, smarty pants: ";
			cin >> ch;
		}
		if (ch == 'n')
			return false;
		else
			return true;
	}

};

#endif // !__VALIDHELPER_H
