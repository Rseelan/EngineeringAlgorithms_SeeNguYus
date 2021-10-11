#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <stdlib.h>
#include "d_node.h"
#include "card.h"

using namespace std;

class deck
{
	public:
		deck();		//default constructor
		~deck();	//default destructor

		void shuffle();	//randomizes order of the cards

		//overloaded << operator:
		friend ostream& operator<<(ostream &ostr, const deck *deckOut);

	private:
		//the deck will be a linked list of card object nodes,
		//here front points to top card of the deck:
		node<card> *front = NULL;	

		//store all the suits as an array of characters:
		char suits[4] = {'D', 'C', 'H', 'S'};
};

/****************************Function Implementation***************************/

//default constructor for deck class. This function initializes all 52 unique
//cards that will be found in the deck. the main loop and the value loop count
//down so that when they're done, the ace of spades will be the card on top:
deck::deck()
{
	node<card> *nextCard;	//points to next card in front
	card tmpCard(24, 'Z');	//temp card with junk values to appease compiler

	//This for loop will count through every card in the deck:
	for(int i = 52; i > 0; i--)
	{
		//this loop counts through each suit:
		for(int suitNum = 0; suitNum < 4; suitNum++)
		{
			//this loop assigns card values and suits to new cards 
			//and then pushes them into the linked list:
			for(int cardVal = 13; cardVal > 0; cardVal--)
			{
				//update tmpCard's values:
				tmpCard.setValue(cardVal);
				tmpCard.setSuit(suits[suitNum]);

				//push a new card to the linked list:
				nextCard = new node<card>(tmpCard, front);	
				front = nextCard;
			} //end value loop
		} //end suit loop
	} //end main loop
}

//default destructor for deck class. Frees memory from *front and *nextCard:
deck::~deck()
{
	delete front;
	cout<<"done \n";
}

//This function shuffles the deck, randomizing the order of cards while keeping
//them connected as a linked list:
void deck::shuffle()
{
	node<card>* temp;	//linked list that stores front
	node<card>* curr;
	node<card>* prev;

	//creating a range of random numbers:
	int max = 50;
	int min = 2;
	int range = max - min + 1;

	int num;	//random number

	for (int j = 0; j<100; j++)
	{
		num = rand() % range + min;
		temp = front;

		for (int i = 0; i < num; i++)
		{
		    prev = temp;
		    temp = temp->next;	//delete top node of temp
		}

	curr = temp->next;
	temp->next = curr->next;
	curr->next = temp;
	prev->next = curr;
	}
}

//overloading iostream's << operator to print out the contents of a deck object:
ostream& operator<<(ostream &ostr, const deck *d)
{
	node<card> *tmpList = d->front;
	int checker = 0;

	//in this for loop, we will be printing the deck in four rows of 13:	
	for(int i = 0; i < 4; i++)
	{
		for(int i = 0; i < 13; i++)
		{
			//print current front val:
			ostr << tmpList->nodeValue << " ";	
			tmpList = tmpList->next; //delete tmpList's front
			}
		cout << endl << endl; //print empty line for added readability
	} //end while loop

	return ostr;
}
/*****************************************************************************/

#endif
