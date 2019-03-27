//Name: Michael Carr
//Program: Test print

#include <iostream>
#include "LList2.hpp"

using namespace std;

void PrintValue (const int & value);
void PrintValueString (const string & value);

int main () {

  LList2 <int> L;
  L.InsertFirst(-1);
  L.InsertFirst(45);
  L.InsertLast(12);
  L.Forward(PrintValue);
  L.Backward(PrintValue);
  L.DeleteFirst();
  L.Forward(PrintValue);
  L.Backward(PrintValue);
  L.DeleteLast();
  L.Forward(PrintValue);
  L.Backward(PrintValue);

  LList2 <string> LS;
  LS.InsertFirst("two");
  LS.InsertFirst("one");
  LS.InsertLast("three");
  LS.Forward(PrintValueString);
  LS.Backward(PrintValueString);
  LS.DeleteFirst();
  LS.Forward(PrintValueString);
  LS.Backward(PrintValueString);
  LS.DeleteLast();
  LS.Forward(PrintValueString);
  LS.Backward(PrintValueString);
  
 
  return 0;
}

void PrintValue (const int & value){

  cout << "The value in the list is " << value << endl;
}


void PrintValueString (const string & value){

  cout << "The value in the list is " << value << endl;
}
