#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

// Declaration of the card class. Stores the value and suit of each card in the deck.
class card
{
public:
	// Constructor:
	card(int valIn = 0, char suitIn = 'X');	// Pass default value and suit in

	// Member functions:
	void setValue(int x);	// Set value manually
	void setSuit(char x);	// Set suit manually

	int getValue();		// Returns value of card
	char getSuit();		// Returns suit of card

	// Friend function:
	friend ostream& operator<< (ostream& ostr, const card& c);

private:
	int value;
	char suit;
};

/****************************Function Implementation***************************/

card::card(int valIn, char suitIn)
// Constructor sets value and suit of each card.
{
	value = valIn;
	suit = suitIn;
}

void card::setValue(int x)
// Allows user to manually set value of a card.
{
	value = x;
}

void card::setSuit(char x)
// Allows user to manually set suit of a card.
{
	suit = x;
}

int card::getValue()
// Returns value of a card.
{
	return value;
}

char card::getSuit()
// Returns suit of a card.
{
	return suit;
}

ostream& operator<< (ostream& ostr, const card& c)
// Overloading the '<<' operator to be able to cout value and suit.
{
	// For some reason the ',' in this line gives an error:
	// ostr << c.value << ', ' << c.suit << endl;
	
	ostr << c.value << c.suit;
	return ostr;
}

/*****************************************************************************/

#endif
