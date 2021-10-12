#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

class card
{
public:
	card(int valIn = 0, char suitIn = 'X');

	void setValue(int x);
	void setSuit(char x);

	int getValue();
	char getSuit();

	friend ostream& operator<< (ostream& ostr, const card& c);

private:
	int value;
	char suit;
};

/****************************Function Implementation***************************/

card::card(int valIn, char suitIn)
{
	value = valIn;
	suit = suitIn;
}

void card::setValue(int x)
{
	value = x;
}

void card::setSuit(char x)
{
	suit = x;
}

int card::getValue()
{
	return value;
}

char card::getSuit()
{
	return suit;
}

ostream& operator<< (ostream& ostr, const card& c)
{
	//for some reason the ',' in this line gives an error:
	//ostr << c.value << ', ' << c.suit << endl;
	
	ostr << c.value << c.suit;
	return ostr;
}
/*****************************************************************************/

#endif