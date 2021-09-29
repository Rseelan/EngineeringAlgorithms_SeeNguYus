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
        response(code secretCode, code guess);	//default constructor

        void set(int x, int y);		//func allows numCorrect and numIncorrect to be set manually

        int get() const;		//returns numCorrect and numIncorrect
        int get_numCorrect() const;	//returns just numCorrect
        int get_numIncorrect() const;	//returns just numIncorrect

        //friend Response operator<<(Response const &);
        friend ostream& operator<< (ostream& ostr, const response& r);
        friend bool operator == (const response &lhs, const response &rhs);

    private:
        int numCorrect;
        int numIncorrect;
};

/******************************************************************************
 *   			Function Definitions	  			      *
 *****************************************************************************/

response::response(code secretCode, code guess)
//Default constructor passes a code object and stores the number of correct
//and incorrect numbers. This means that responses rely on code objects!
{
	numCorrect = secretCode.checkCorrect(guess);
	numIncorrect = secretCode.checkIncorrect(guess);
}

void response::set(int x, int y)
//This functions allows the user to manually set the values numCorrect and
//numInccorect whenever they want.
{
    numCorrect = x;
    numIncorrect = y;

}

int response::get() const
//returns the number of correct and incorrect numbers
{
    return (numCorrect, numIncorrect);

}

int response::get_numCorrect() const
//returns only the number of correct numbers
{

    return (numCorrect);
}

int response::get_numIncorrect() const
//returns only the number of incorrect numbers
{
    return (numIncorrect);

}

//response operator<<(response const &obj){

    //cout<<obj.get()<<endl;

//}

ostream& operator<< (ostream& ostr, const response& r)
//overloading the built in '<<' operator to be able to cout a response
{
    ostr << r.numCorrect << ',' << r.numIncorrect;
    return ostr;
}

bool operator == (const response &lhs, const response &rhs)
//overloading the built in '==' operator to be able to compare responses
{
    return ((lhs.get_numCorrect() == rhs.get_numCorrect()) && (lhs.get_numIncorrect() == rhs.get_numIncorrect()));
}

/******************************************************************************/

#endif
