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
		mastermind();
		mastermind(int &n, int &m);

		//member functions:
		void printSecretCode();
		void playGame();

		code humanGuess();

		response getResponse();

		bool isSolved();
	
	private:
		//sasdsa
		//
		code secretCode;

		int n;	//length of the secret code
		int m;	//range of numbers of secret code
};

mastermind::mastermind()
{
	n = 5;
	m = 10;

	secretCode(n, m);
}

mastermind::mastermind(int &n, int &m)
{
	secretCode(n, m);
}

mastermind::printSecrectCode()
{
	secretCode.printSequence();
}

mastermind::humanGuess()
{
	code tmpCode(n, m);
	tmpCode.userInput();

	return tmpCode;
}

mastermind::getResponse()
{
	//stuff goes here
	return something;
}

mastermind::isSolved()
{
	//stuff goes here
	return someBool;
}

mastermind::playGame()
{
	//gamers
}

#endif
