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
	for (itr = L1.begin(); itr != L1.end(); itr--)
		cout << "The value at *itr is " << *itr << endl;
	return 0;
}
