#include <iostream>
#include <stdlib.h>
#include "d_node.h"

using namespace std;

class deck
{
	public:
		deck();		//default constructor

		void shuffle();	//randomizes order of the linked list of cards

		//overloaded << operator:
		friend ostream& operator<<(ostream &ostr, const deck *deckOut);


	private:
		//int is just a placeholder, eventually will be node<card>
		
		node<int> *front = NULL;	//points to top card of the deck
		node<int> *nextCard;		//points to next card in front
};

/****************************Function Implementation***************************/

//default constructor for deck class. This function initializes all 52 unique
//cards that will be found in the deck:
deck::deck()
{
	for(int i = 52; i > 0; i--)	//Want the first card to be 1 (ace)
	{
		nextCard = new node<int>(i, front);	//add new card to front
		front = nextCard;			//update front
	}

	//delete nextCard; //when we do this, we delete the actual list...
			   //I'm just praying for no memeory leaks ;-;
}

//This function 'shuffles the deck,' meansing that it takes the order of cards,
//1 to 52, and randomizes them, while keeping them connected as a linked list:
void deck::shuffle()
{
	cout << "This is really hard, and it's not my job! \n";
}

//overloading iostream's << operator so that we can print out the contents of a
//deck using cout<< instead of creating some kind of printDeck() void function.
//As of now, this creates a giant 52 line list in your terminal, but it should 
//be easy to change the output such that it prints the list as more of a block:
ostream& operator<<(ostream &ostr, const deck *deckOut)
{
	node<int> *tmpList = deckOut->front;
	
	//for every node in tmpList, we print out its value, and then delete it
	while(tmpList != NULL)
	{
		ostr << tmpList->nodeValue << endl;	//print current front val
		tmpList = tmpList->next;		//delete tmpList's front
	}

	//let's make sure there are no memory leaks:
	delete tmpList;

	return ostr;
}
/*****************************************************************************/

int main()
{
	deck *myDeck = new deck;
	myDeck->shuffle();
	cout << myDeck << endl;
	delete myDeck;

	cout<<"done \n";

	return 0;
}
