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
		mastermind();				//default, no input
		mastermind(int length, int range);	//manually set n and m

		//member functions:
		code humanGuess();	//return code object with player's guess

		response getResponse(code guess);	//return response object based on player guess

		bool isSolved(response guessResponse);	//checks if the secret code has been found
	
		void printSecretCode();	//prints the secret code to console
		void playGame();	//starts the game

	private:
		int n;			//length of the secret code
		int m;			//range of numbers of secret code

		code secretCode;	//stores the secret code
		code userGuess;		//stores user's guesses

		response answer;	//stores a response for a correct guess
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
	userGuess.initializeCode(n, m);

	answer.set(n, 0); //the answer should have n correct #s and 0 incorrect
}

mastermind::mastermind(int length, int range)
//When values for n and m are supplied, make a secrect code of length n, where
//the range of each number in the code is [0, m-1]:
{
	n = length;
	m = range;

	secretCode.initializeCode(n, m);
	userGuess.initializeCode(n, m);

	answer.set(n, 0); //the answer should have n correct #s and 0 incorrect
}

code mastermind::humanGuess()
//this function allows the user to input a guess, and that guess is stored as a
//code object so, I have the data member userGuess, and I call its input method
//in order to store the user's input so I can use it later.
{
	userGuess.userInput();
	return userGuess;
}

response mastermind::getResponse(code guess)
//In this function we return a response object based on a user guess and the
//secret code:
{
	response tmpResponse(secretCode, guess);
	return tmpResponse;
}

bool mastermind::isSolved(response guessResponse)
//function checks if the given response object is identical to the private 
//member answer:
{
	return answer == guessResponse;
}

void mastermind::printSecretCode()
//The code class already has a perfectly good print function, so here we just 
//call that method for the secretCode object:
{
	cout << "The secret code is: \n";
	secretCode.printSequence();
}

void mastermind::playGame()
//this functions controls the gameplay. Calling it will print out the secret
//code, and then prompt the user to enter their guess, and then print out their
//guess, as well as the number of correct and incorrect numbers they inputted.
//When the turnCounter reaches 10, or isSolved returns true, the game ends!
{
	//intialize turnCounter:
	int turnCounter = 0;

	while (turnCounter < 10) //once turnCounter = 10, game ends
	{
		printSecretCode();

		//update the userGuess code object:
		humanGuess();	

		cout << "You guess was: \n";
		userGuess.printSequence();

		if (isSolved(getResponse(userGuess)))
		{
			cout << "Congrats! You win! \n";
			break; //make sure to actually stop playing
		}
		else
		{
			turnCounter++;	//advance turn counter 

			//Tell players how many numbers they got right/wrong.
			//Also, tells them how many turns are left:
			cout << "numCorrect, numIncorrect = ";
			cout << getResponse(userGuess) << "\n" << "\n";
			cout << "You have " << 10 - turnCounter << " turns remaining! \n \n";
		}
	} //end while loop

	if(turnCounter == 10)
	{
		cout<<"You lose... yikes... \n";
	}
}

/******************************************************************************/

#endif
