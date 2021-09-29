#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "codeClass.h"
#include "response.h"

using namespace std;

class mastermind
{
	public:
		//constructors:
		mastermind();			//default, no input
		mastermind(int length, int range);	//manually set n and m

		//member functions:
		code humanGuess();		//return code object with player's guess

		response getResponse(code guess); //return response object based on player guess

		bool isSolved(response checkGuess); //checks if the secret code has been found
	
		void printSecretCode();		//prints the secret code to console
		void playGame();		//starts the game

	private:
		int n;			//length of the secret code
		int m;			//range of numbers of secret code

		code secretCode;	//stores the secret code
};

/******************************************************************************
 *   			Function Definitions	  			      *
 *****************************************************************************/

mastermind::mastermind()
//When there are no inputs to accompany the initialization of a mastermind
//object, the length of the secret code is automatically set to 5 numbers and
//the range of each number is automatically set to [0, 9]
{
	n = 5;
	m = 10;

	secretCode.initializeCode(n, m);
}

mastermind::mastermind(int length, int range)
//When values for n and m are supplied, make a secrect code of length n, where
//the range of each number in the code is [0, m-1]:
{
	n = length;
	m = range;

	secretCode.initializeCode(n, m);
}

code mastermind::humanGuess()
//this function allows the user to input a guess, and that guess is stored as a
//code object. So, I initialize a temporary code object called tmpCode, and 
//store the user's input into it, before returning the object:
{
	code tmpCode;
	tmpCode.initializeCode(n, m);
	tmpCode.userInput();

	return tmpCode;
}

response mastermind::getResponse(code guess)
//In this function we return a response object based on a user guess and the
//secret code. We then return the response object, which contains the number
//of correct and incorrect guesses:
{
	response tmpResponse(secretCode, guess);
	return tmpResponse;
}

bool mastermind::isSolved(response checkGuess)
{
	bool someBool = false;

	cout << "this function is a work in progress... \n";

	return someBool;
}

void mastermind::printSecretCode()
//The code class already has a perfectly good print function, so here we just 
//call that method for the secretCode object:
{
	secretCode.printSequence();
}

void mastermind::playGame()
{
	cout << "Oh hey, this isn't done yet, please don't read this! \n";
}

/******************************************************************************/

#endif
