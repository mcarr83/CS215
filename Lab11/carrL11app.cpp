//Name: Michael Carr
//Decription: This will add up all fractions from input file

#include <iostream>
#include <fstream>
#include "LList2.hpp"
#include "Fraction.h"

using namespace std;

fraction fract = 0;

void Fract (const fraction & F);

int main ()
{
	ifstream input ("Lab11.in");
	fraction one;
	LList2 <fraction> FL;
	while (input >> one)
		FL.InsertLast (one);
	cout << "The fractions are: ";
	cout << FL << endl;


	FL.Forward(Fract);

	cout << "The total is " << fract << endl;

	return 0;
}

void Fract (const fraction & F){
  fract = fract + F;

}
