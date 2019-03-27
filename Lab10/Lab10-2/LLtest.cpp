// Lab 10-2 application program
// Author: Michael Carr
// Data: Fall 2018
// Description: This program is designed to test the LList class using LT.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "LList.hpp"

using namespace std;

int main (){
  LList<int> intList;
  LList<string> stringList;
  cout << "Integer list: " << intList << endl;
  cout << "String list: " << stringList << endl;

  intList.InsertLast (-1);
  intList.InsertFirst (10);
  stringList.InsertFirst ("Hello");
  stringList.InsertLast ("World");
  cout << "Integer list: " << intList << endl;
  cout << "String list: " << stringList << endl;

  intList.SetDirection (BACKWARDS);
  stringList.SetDirection (BACKWARDS);
  cout << "Integer list: " << intList << endl;
  cout << "String list: " << stringList << endl;
  intList.SetDirection (FORWARD);
  stringList.SetDirection (FORWARD);
  cout << "Integer list: " << intList << endl;
  cout << "String list: " << stringList << endl;

  LList<int> intList2;
  LList<string> stringList2;

  intList2 = intList;
  stringList2 = stringList;

  if (intList == intList2)
    cout << "Int lists are the same" << endl;

  else
    cout << "Int lists are not the same" << endl;

  if (stringList == stringList2)
    cout << "String lists are the same" << endl;

  else
    cout << "String lists are not the same" << endl;

    stringList.InsertFirst("Why");
    intList.InsertLast(222);
    
    if (intList == intList2)
    cout << "Int lists are the same" << endl;

  else
    cout << "Int lists are not the same" << endl;

  if (stringList == stringList2)
    cout << "String lists are the same" << endl;

  else
    cout << "String lists are not the same" << endl;

  return 0;
}
