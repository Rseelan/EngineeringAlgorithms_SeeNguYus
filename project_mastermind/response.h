#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "codeClass.h"

using namespace std;

//Declaration of response class. This class stores the number of correct and
//incorect numbers of the user's guess for the secret code.
class response 
{
	public:
		//constructors:
		response();				//default, no input
		response(code secretCode, code guess);	//pass code objects to check

		//member functions:
		void set(int x, int y);		//set numCorrect and numIncorrect manually
		void setNumCorrect(int x);	//set numCorrect manually
		void setNumIncorrect(int y);	//set numIncorrect manually

		int getNumCorrect() const;	//returns just numCorrect
		int getNumIncorrect() const;	//returns just numIncorrect

		//friend functions:
		friend ostream& operator<< (ostream& ostr, const response& r);
		friend bool operator == (const response &lhs, const response &rhs);

	private:
		int numCorrect;
		int numIncorrect;
};

/******************************************************************************
 *   			Function Definitions	  			      *
 *****************************************************************************/
response::response()
//when there is no input, default to setting both numCorrect and Incorrect to 0
//so that the values can be manually set later.
{
	numCorrect = 0;
	numIncorrect = 0;
}

response::response(code secretCode, code guess)
//overload constructor to pass code objects and store the number of correct and 
//incorrect numbers based on the secret code and guess inputs.
{
	numCorrect = secretCode.checkCorrect(guess);
	numIncorrect = secretCode.checkIncorrect(guess);
}

void response::set(int x, int y)
//This function allows the user to manually set the values numCorrect and
//numIncorrect whenever they want.
{
	numCorrect = x;
	numIncorrect = y;
}

void response::setNumCorrect(int x)
//sets numCorrect
{
	numCorrect = x;
}

void response::setNumIncorrect(int y)
//sets numIncorrect
{
	numIncorrect = y;
}

int response::getNumCorrect() const
//returns only the number of correct numbers
{
	return (numCorrect);
}

int response::getNumIncorrect() const
//returns only the number of incorrect numbers
{
	return (numIncorrect);
}

ostream& operator<< (ostream& ostr, const response& r)
//overloading the built in '<<' operator to be able to cout a response
{
	ostr << r.numCorrect << ',' << r.numIncorrect;
	return ostr;
}

bool operator == (const response &lhs, const response &rhs)
//overloading the built in '==' operator to be able to compare responses
{
	return ((lhs.getNumCorrect() == rhs.getNumCorrect()) && (lhs.getNumIncorrect() == rhs.getNumIncorrect()));
}

/******************************************************************************/

#endif
