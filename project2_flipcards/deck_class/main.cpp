#include <iostream>
#include <stdlib.h>
#include "deck.h"

using namespace std;

int main()
{
	//create new deck object pointer:
	deck *myDeck = new deck;
	cout << "Default deck: \n";
	cout << myDeck << endl;

	//Do stiff with that deck object:
	myDeck->shuffle();
	cout << "Shuffled deck: \n";
	cout << myDeck << endl;

	//clean up:
	delete myDeck;
	return 0;
}
