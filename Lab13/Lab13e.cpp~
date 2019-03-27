#include <iostream>
#include <cstdlib>
#include "LList2.hpp"

using namespace std;

int main ()
{
	LList2<int> L1;
	for (int i = 0; i < 10; i++)
		if (i % 2 == 1)		// i is odd
			L1.InsertFirst (i);
		else
			L1.InsertLast (i);
	cout << "L1 contains: " << L1 << endl;
	LList2<int>::Iterator itr;
	itr = L1.begin();
	cout << "The value at L1.begin() is " << *itr << endl;
	itr = L1.rbegin();
	cout << "The value at L1.rbegin() is " << *itr << endl;
	itr = L1.end();
	cout << "The value at L1.end() is " << *itr << endl;
	itr = L1.rend();
	cout << "The value at L1.rend() is " << *itr << endl;
	return 0;
}
