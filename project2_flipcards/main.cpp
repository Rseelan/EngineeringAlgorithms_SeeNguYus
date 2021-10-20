/******************************************************************************
 * Project 2b		   Group members:				      *
 * 			   Rohan Seelan - seelan.r@northeastern.edu	      *
 * 			   Andrew Nguyen - nguyen.andrew@northeastern.edu     *
 * 			   Arbid Ysuuf - yusuf.ar@northeastern.edu            *
 * 								     	      *
 * This program utilizes the functions found in the deck class and the card   *
 * class from the respective header files in order to implement the function  *
 * "playGame()" which allows the user to play a digital version of flip cards *
 ******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include "deck.h"

using namespace std;

//this function starts the game by initializing the decks and keeping track 
//of player's inputs and the player's score:
void playGame()
{
	int userInput;
	int score = 0;

	card selectedCard(0, 'X'); //card with placeholder values

	bool isPlaying = true;

	deck deck1 = deck(52);	//create standard 52 card deck
	deck deck2 = deck(0);	//stores top 24 cards from deck1

	//----------------initial decks--------------------//
	cout << "Initial deck values: \n";
	cout << "Deck's content: \n";
	cout << deck1;

	cout << "Top 24 cards (have not dealt any cards yet): \n";
	cout << deck2;
	//-------------------------------------------------//



	//----------------shuffle deck1--------------------//
	deck1.shuffle();
	cout << "Decks after shuffling: \n";
	cout << "Deck's content: \n";
	cout << deck1;

	cout << "Top 24 cards (have not dealt any cards yet): \n";
	cout << deck2;
	//-------------------------------------------------//



	//dealing 24 cards from deck 1. Storing them into deck 2 so that we 
	//can access those cards later when we're playing the game:
	for (int i = 0; i < 24; i++)
	{
		deck2.replace(deck1.deal());
	}

	//----------------deal 24 cards--------------------//
	cout << "Decks after dealing: \n";
	cout << "Deck 1's content: \n";
	cout << deck1;

	cout << "Top 24 cards: \n";
	cout << deck2;
	//-------------------------------------------------//



	//--------------------playing the game--------------------//
	cout << "Starting game: \n";
	cout << "Enter a number from 1 to 24 to select a card. \n";
	cout << "Enter 0 to quit the game \n";

	while(isPlaying)
	{
		cout << "The top 24 cards are: \n";
		cout << deck2;

		cout << "Your current score is: " << score << endl;
		cout << "Please enter a card number: \n";
		cin  >> userInput;
		cout << endl;

		//quitting the game:
		if(userInput == 0)
		{
			isPlaying = false;
			break;
		}

		if(deck2.returnIsFlipped(userInput) == true)
		{
		    cout << "This card has already been picked." << endl;
		}
		else
		{
			deck2.cardFlip(userInput);
			selectedCard.setValue(deck2.returnCardValue(userInput));
			selectedCard.setSuit(deck2.returnCardSuit(userInput));

			cout << "Your card is the " << selectedCard << endl << endl;

			//examine card value:
			switch(selectedCard.getValue()){
				case 1:
					score = score + 10;
					break;
				case 11: case 12: case 13:
					score = score + 5;
					break;
				case 8: case 9: case 10: 
					score = score + 0;
					break;
				case 7:
					score = score / 2;
					break;
				case 2: case 3: case 4: case 5: case 6:
					score = 0;
					break;
				default :
					cout << "Please provide a valid user input: " << endl;
			} //end switch statement

			//examine suits
			if(char tempChar = selectedCard.getSuit() == 'H')
			{
				score++;
			}
		}
	} //end "isPlaying" while loop
}

//main function, calls playGamer(). That's about it.
int main()
{
	playGame();
	return 0;
}
