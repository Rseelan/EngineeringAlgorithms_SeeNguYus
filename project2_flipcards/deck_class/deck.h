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
		deck(int numCards = 52);	//default constructor
		~deck();			//default destructor

		void shuffle();	//randomizes order of the cards

		void replace(card newBottomCard); //puts a new card on bottom of deck

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

//default constructor for deck class. This function creates a deck of cards with
//numCard cards in it. It starts with the King of Diamonds, and goes down to the
//Ace of spades. Intend to initialize a deck with either 52 or 0 cards
deck::deck(int numCards)
{
	int cardVal = 13;		//keeps track of card value. Start with king
	int suitNum = 0;		//keeps track of suit. Start with Diamond

	node<card> *nextCard;	//points to next card in front
	card tmpCard(24, 'Z');	//temp card with junk values to appease compiler

	//This for loop will count through every card in the deck set its value:
	for(int i = numCards; i > 0; i--)
	{
		//update tmpCard's values:
		tmpCard.setValue(cardVal);
		tmpCard.setSuit(suits[suitNum]);

		//push a new card node to the linked list:
		nextCard = new node<card>(tmpCard, front);	
		front = nextCard;

		//Decrease cardVal every loop until it reaches 1, and when it does,
		//reset it back to 13, and when that happens, go to the next suit:
		if (cardVal > 1)
		{
			cardVal--;
		}
		else
		{
			//If for some reason you want more than 52 cards, this will make
			//sure that suitNum doesn't exceed 3:
			suitNum < 4 ? suitNum++ : suitNum = 0;
			cardVal = 13;
		}
	} //end for loop
}

//default destructor for deck class. Frees memory from *front and *nextCard:
deck::~deck()
{
	delete front;
	cout<<"done \n";
}

//This function shuffles the deck, randomizing the order of cards while keeping
//them connected as a linked list:
//the logic of our shuffle algorithm is to randomly choose pair in the linked list and then swap them
void deck::shuffle()
{
	//three node pointers will be used to shuffle our linked list
	node<card>* temp;
	node<card>* curr;
	node<card>* prev;

	//specify parameters for choosing a node in our linked list
	int max = 50;
	int min = 0;
	int range = max - min + 1;
	int num;

	//our index is set to an extremely high value as we want to shuffle as many times possible
	for (int j = 0; j<1000; j++)
	{
		//choose a random pair to shuffle
		num = rand() % range + min;

		//if we are dealing with the head node
		if (num == 0)
		{
			//set our placeholder nodes before we swap the cards
			prev = front;
			temp = prev->next;
			curr = temp->next;

			//perform the swap but set our temp to be the absolute front of our linked list after
			prev->next = curr;
			temp->next = prev;
			front = temp;
		} //end if
		//if we are dealing with any node that isn't a header node
		//The logic for this is as follows:
		// prev node -> temp node -> curr node
		else 
		{
			temp = front;

			//traverse to the pair we want to swap
			for (int i = 0; i<num;i++)
			{
			prev = temp;
			temp = temp->next;
			}

			//set curr to the next node present after "temp"
			curr = temp->next;

			//perform the swap
			temp->next = curr->next;
			curr->next = temp;
		prev->next = curr;
		//prev node ->  curr node -> temp node
		} //end else
	} //end for loop
}

//This function passes a card and places it at the bottom of the deck:
void deck::replace(card newBottomCard)
{
	//eventually, this node will point to the bottom of the deck:
	node<card> *bottom = front;	

	//In this loop, we find the last node in front:
	while (bottom->next != NULL)
	{
		bottom = bottom->next;
	}
	
	bottom->next = new node<card>(newBottomCard, NULL);
}

//overloading iostream's << operator to print out the contents of a deck object:
ostream& operator<<(ostream &ostr, const deck *d)
{
	node<card> *tmpList = d->front;

	//in this for loop, we will be printing the deck in four rows of 13:	
	for(int i = 0; i < 4; i++)
	{
		for(int i = 0; i < 13; i++)
		{
			//check what the card value is before printing:
        		switch(tmpList->nodeValue.getValue())
			{
        	    	case 1:
        	    		cout << "Ace";
        	    		cout << tmpList->nodeValue.getSuit() << " ";
        	    		break;
        	    	case 11:
        	    		cout << "Jack";
        	    		cout << tmpList->nodeValue.getSuit() << " ";
        	    		break;
        	    	case 12:
        	    		cout << "Queen";
        	    		cout << tmpList->nodeValue.getSuit() << " ";
        	    		break;
        	    	case 13:
        	    		cout << "King";
        	    		cout << tmpList->nodeValue.getSuit() << " ";
        	    		break;
        	    	default:
        	    		cout << tmpList->nodeValue << " ";	
			} //end switch
			tmpList = tmpList->next; //delete tmpList's front
		} //end for loop
		cout << endl << endl; //print empty line for added readability
	} //end while loop

	return ostr;
}
/*****************************************************************************/

#endif
