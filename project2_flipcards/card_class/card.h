#include <iostream>

using namespace std;

class card
{
public:
	card();

	void setValue(int x);
	void setSuit(string x);
	
	int getValue();
	string getSuit();

	friend ostream& operator<< (ostream& ostr, const card& c);

private:
	int value;
	string suit;
};

card::card()
{
	value = 0;
	suit = "unsigned";
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