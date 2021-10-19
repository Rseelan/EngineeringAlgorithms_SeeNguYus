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
	
		Card deal(); //Deal function, it removes a card object from our "original" linked list and returns it

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
//the logic of our shuffle algorithm is to randomly choose pair in the linked list and then swap them
void Deck::shuffle()
{
    //three node pointers will be used to shuffle our linked list
    node<Card>* temp;
    node<Card>* curr;
    node<Card>* prev;

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
            prev = frontcard;
            temp = prev->next;
            curr = temp->next;

            //perform the swap but set our temp to be the absolute front of our linked list after
            prev->next = curr;
            temp->next = prev;
            frontcard = temp;
        } //end if

        //if we are dealing with any node that isn't a header node
        //The logic for this is as follows:
        // prev node -> temp node -> curr node
        else 
	{
            temp = frontcard;

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

Card Deck::deal(){

    //temp variable so we can store our front card
    topCard = frontcard;

    //store contents of our front card into a card object
    Card cardFrontTemp(topCard->nodeValue.getvalue(), topCard->nodeValue.getSuit());

    //"remove the first card from our original deck"
    frontcard = frontcard ->next;

    //return card object
    return cardFrontTemp;
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
			//check what the card value is before printing:
        		switch(tmpList->nodeValue.getValue())
			{
        	    	case 1:
        	    		cout << "Ace";
        	    		cout << tmpList->nodeValue.getSuit() << " ";
        	    		break;
        	    	case 11:
        	    		cout << "Joker";
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
        	    		cout<< tmpList->nodeValue << " ";	
			} //end switch
		} //end for loop
		cout << endl << endl; //print empty line for added readability
	} //end while loop

	return ostr;
}
/*****************************************************************************/

#endif
