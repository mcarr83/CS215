#include <iostream>
#include "LList2.hpp"

using namespace std;

#define MAX 10

int main () {
  LList2 <int> L1, L2;
  for (int i = 0; i < MAX; i++){
    if (i % 2)
      L1.InsertFirst(i);
    else
      L1.InsertLast(i);

  }

  cout << "L1 in order:";
  cout << L1 << endl;
  cout << "Testing the [] operator \n";
  cout << "First the last :\n";

  for (int i = 0; i < L1.Size(); i++)
    cout << "L1[" << i << "] is " << L1[i] << endl;

  L1[3] = 7;
  cout << "Last to first : \n";
  for (int i = L1.Size()-1; i>= 0; i--)
    cout << "L1[" << i << "] is " << L1[i] << endl;

  int x = *L1.begin();
  cout << *L1.begin() << endl;

  *L1.begin() = 12;
  //cin >> *L1.begin();
 
  return 0;
}
