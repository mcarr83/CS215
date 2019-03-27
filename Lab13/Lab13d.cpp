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
	for (int i = 0; i < L1.Size(); i--)
		cout << "The value at [" << i << "] is " << L1[i] << endl;
	return 0;
}
