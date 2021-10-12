/******************************************************************************
 * Project 2a		   Group members:				      *
 * 			   Rohan Seelan - seelan.r@northeastern.edu	      *
 * 			   Andrew Nguyen - nguyen.andrew@northeastern.edu     *
 * 			   Arbid Ysuuf - yusuf.ar@northeastern.edu            *
 * 								     	      *
 * This program contains the declaration of the deck class as well as the     *
 * implementation of the shuffle function. Prints both the default deck and   *
 * the shuffled deck and then clears the memory space.                        *
 ******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include "deck.h"

using namespace std;

int main()
{
	//Create a deck pointer:
	deck *myDeck = new deck;
	cout << "Default deck: \n";
	cout << myDeck << endl;

	//Shuffle the deck::
	myDeck->shuffle();
	cout << "Shuffled deck: \n";
	cout << myDeck << endl;

	//clean up:
	delete myDeck;
	return 0;
}
