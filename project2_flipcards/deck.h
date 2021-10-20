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

		//these two functions allow you to grab the data from
		//individual cards in the linked list:
		int returnCardValue(int x);
		char returnCardSuit(int x);

		void shuffle();	//randomizes order of the cards

		void replace(card newBottomCard); //puts a new card on bottom of deck

		card deal();	//deals out a card from the top of the deck

		//overloaded << operator:
		friend ostream& operator<<(ostream &ostr, const deck &deckOut);

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

//Function goes to a specific card in the linked list given by x and returns
//its value datamember
int deck::returnCardValue(int x)
{
	int cardValue;
	node<card> *tempValue = front; //temp list equal to front

	for(int i = 1; i != x; i++)
	{
		tempValue = tempValue->next;
	}

	cardValue = tempValue->nodeValue.getValue();
	return cardValue;
}

char deck::returnCardSuit(int x)
{
	char cardSuit;
	node<card> *tempValue = front; //temp list equal to front

	for(int i = 1; i != x; i++)
	{
		tempValue = tempValue->next;
	}

	cardSuit = tempValue->nodeValue.getSuit();
	return cardSuit;
}

//This function shuffles the deck, randomizing the order of cards while keeping
//them connected as a linked list, by randomly choosing pairs of cards in the 
//deck, and then swapping them:
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

	//index is set to an extremely high value to shuffle as many times possible
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

			//perform the swap but set our temp to be the front of our linked list after
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

//This function returns the top card of the deck, which is the value of front,
//and then removes that card from the deck:
card deck::deal()
{
	//create a temporary card object that stores the front card:
	card topCard(front->nodeValue.getValue(), front->nodeValue.getSuit());

	//remove the first card from the original deck:
	front = front->next;

	return topCard;
}

//This function passes a card and places it at the bottom of the deck:
void deck::replace(card newBottomCard)
{
	//eventually, this node will point to the bottom of the deck:
	node<card> *bottom = front;	

	//check if the deck is empty:
	if(bottom != NULL)
	{
		//In this loop, we find the last node in front:
		while (bottom->next != NULL)
		{
			bottom = bottom->next;
		}

		bottom->next = new node<card>(newBottomCard, NULL);
	}
	else
	{
		//executes if front = NULL, because in that case, there are no
		//cards in the deck, so bottom->next will seg fault
		front = new node<card>(newBottomCard, front);
	}
}

//overloading iostream's << operator to print out the contents of a deck object:
ostream& operator<<(ostream &ostr, const deck &d)
{
	node<card> *tmpList = d.front;
	
	int counter = 0; //keeps track of # of cards printed

	//in this for loop, we will be printing the deck in rows of 13:	
	while(tmpList != NULL)
	{
		cout << tmpList->nodeValue << ", ";
		tmpList = tmpList->next; //delete tmpList's front

		//I wanted to do this in a ternary statement, but I needed to
		//execute two commands when counter reaches 12. sadness.
		if(counter < 12)
		{
			counter++;
		}
		else
		{
			//print empty line for added readability:
			cout << endl << endl;	

			//reset counter:
			counter = 0;		
		}
	} //end while loop

	cout << endl << endl;	

	return ostr;
}
/*****************************************************************************/

#endif
