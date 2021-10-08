#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

class card
{
public:
	card(int val = 0, char suit = 'X');

	void setValue(int x);
	void setSuit(char x);

	int getValue();
	char getSuit();

	friend ostream& operator<< (ostream& ostr, const card& c);

private:
	int value;
	char suit;
};

card::card(int valIn = 0, char suitIn = 'X')
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
	ostr << c.value << ', ' << c.suit << endl;
	return ostr;
}

#endif
