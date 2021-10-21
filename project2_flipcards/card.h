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

	card(const card& c1); // Pass card object into copy constructor

	// Member functions:
	void setValue(int x);	// Set value manually
	void setSuit(char x);	// Set suit manually

	int getValue();		// Returns value of card
	char getSuit();		// Returns suit of card
	
	void flip();		// Flips boolean isFlipped
    bool getIsFlipped();	// returns boolean isFlipped

	void operator=(const card& rhs); // Overloaded assignment operator

	// Friend function:
	friend ostream& operator<< (ostream& ostr, const card& c);

private:
	int value;
	char suit;
	bool isFlipped;
};

/****************************Function Implementation***************************/

card::card(int valIn, char suitIn)
// Constructor sets value and suit of each card.
{
	value = valIn;
	suit = suitIn;
	isFlipped = false;
}

card::card(const card& c1)
// Copy constructor takes card object as its parameter.
{
	value = c1.value;
	suit = c1.suit;
	isFlipped = c1.isFlipped;
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

void card::flip()
// Flips boolean isFlipped from false to true.
{
    isFlipped = true;
}

bool card::getIsFlipped()
// Returns isFlipped.
{
    return isFlipped;
}

void card::operator=(const card& rhs)
// Overloading the assignment operator to be able to create a card object.
{
	value = rhs.value;
	suit = rhs.suit;
}

ostream& operator<< (ostream& ostr, const card& c)
// Overloading the '<<' operator to be able to cout value and suit.
{
	//check what the card value is before printing:
	switch(c.value)
	{
	case 1:
		cout << "Ace of ";
		cout << c.suit;
		break;
	case 11:
		cout << "Jack of ";
		cout << c.suit;
		break;
	case 12:
		cout << "Queen of ";
		cout << c.suit;
		break;
	case 13:
		cout << "King of ";
		cout << c.suit;
		break;
	default:
		cout << c.value << " of " << c.suit;
	} //end switch

	return ostr;
}

/*****************************************************************************/

#endif
