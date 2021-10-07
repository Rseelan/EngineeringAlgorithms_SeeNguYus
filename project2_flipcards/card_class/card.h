#ifndef CODE_H
#define CODE_H

#include <iostream>

using namespace std;

class card
{
public:
	card(int val = 0, string suit = "unsigned");

	void setValue(int x);
	void setSuit(string x);
	
	int getValue();
	string getSuit();

	friend ostream& operator<< (ostream& ostr, const card& c);

private:
	int value;
	string suit;
};

card::card(int valIn = 0, string suitIn = "unsigned")
{
	value = valIn;
	suit = suitIn;
}

void card::setValue(int x)
{
	value = x;
}

void card::setSuit(string x)
{
	suit = x;
}

int card::getValue()
{
	return value;
}

string card::getSuit()
{
	return suit;
}

ostream& operator<< (ostream& ostr, const card& c)
{
	ostr << c.value << ', ' << c.suit << endl;
	return ostr;
}

#endif
