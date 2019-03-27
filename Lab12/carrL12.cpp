/***************************************************/
/* Name: Michael Carr                              */
/* Filename: carrL12.cpp                           */
/***************************************************/

#include <iostream>
#include "LList2.hpp"
#include "card.h"
#include "fstream" //for inputing a file (cards.in)

using namespace std;

int main (){

  //initialize a vector of card
  LList2 <card> L1;

  //open input file
  ifstream input ("cards.in");

  //initialize card of numone
  card numOne;

  //read in cards until none left
  while (input >> numOne){
    L1.InsertLast(numOne);
  }

  //output the cards in the file
  cout << "The cards: " << L1 << endl;

  //integer for half of the deck
  int halfSize =  L1.Size()/2;
  int maxSize = L1.Size();

  //new vectors for first half of deck
  //and last half of deck
  LList2 <card> L2;
  LList2 <card> L3;

  //Initializes itr variable at the beginning of the list
  LList2<card>::Iterator itr = L1.begin();

  //Inserts half the list into L2
  for (int i = 0; i < halfSize; i++){
    L2.InsertLast(*itr);
    itr++;
  }
  //Prints out L2
  cout << "First half: " << L2 << endl;

  //Inserts the other half of the list into L3
  for (int i = halfSize; i < maxSize; i++){
    L3.InsertLast(*itr);
    itr++;
    
  }
  cout << "Second half: " << L3 << endl;

  //New deck for shuffled cards
  LList2<card> L4SD;

  //Initialized new itr variables

  LList2<card>::Iterator itr1;
  LList2<card>::Iterator itr2;

  //Starting iterator cards
  itr1 = L2.begin();
  itr2 = L3.begin();

  //putting values into L4SD using values in L3 first and then L2
  for (int i = 0; i <= halfSize; i++){
    if (itr2 != NULL){
      L4SD.InsertLast(*itr2);
      itr2++;
    }

    if (itr1 != NULL){
      L4SD.InsertLast(*itr1);
      itr1++;
    }
   }
   cout << "Shuffled cards: " << L4SD << endl;
}	 

  

