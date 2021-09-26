/******************************************************************************
 * Project 1b		   Group members:				      *
 * 			   Rohan Seelan - seelan.r@northeastern.edu	      *
 * 			   Andrew Nguyen - nguyen.andrew@northeastern.edu     *
 * 			   Arbid Ysuuf - yusuf.ar@northeastern.edu            *
 * 								     	      *
 * This program contains the declaration of the code class, the code class's  *
 * member functions, as well as a main function that implements a rough	      *
 * version of the mastermind game.					      *
 ******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "codeClass.h"
#include "response.h"
#include "mastermind.h"

using namespace std;

int main()
//main function that will just be used to test this stuff:
{
	//This keeps track of the number of turns that have elapsed
	int turns_passed = 0;	

	//This boolean is used to turn off the game when the user wins or loses
	bool playing = true;	

	//Initializing the game:
	int length;
	int range;

	cout<<"How long do you want the code to be?";
	cin>>length;

	cout<<"What would you like the range of digits to be?";
	cin>>range;

	code codemaker(length, range);	//creating the code object

	while(playing)
	{
		codemaker.userInput();		//taking in user input

		//these statements were too long, so I put them on different lines to
		//shorten them.
		cout<<"Number of correct numbers in the correct place: ";
		cout<<codemaker.checkCorrect()<<"\n";
		cout<<"Number of correct numbers in the incorrect place: ";
		cout<<codemaker.checkIncorrect()<<"\n";
			
		//These lines are for debugging:
		cout<<"Secrect code: ";
		codemaker.printSequence();

		//If we wanted, we could print out the checker vector:
		//cout<<"Checker     : ";
		//codemaker.printChecker();
		//But, why would we want to? That'd be crazy

		cout<<"User's guess: ";
		codemaker.printGuess();

		//the game ends when the guess and the sequence are identical,
		//Or, the game can just end with you running out of turns
		if(codemaker.checkCorrect() == length)
		{
			playing = false;	
			cout<<"Congrats! You win! Pog! \n";
		}
		else if(turns_passed > 10)
		{
			playing = false;
			cout<<"You lose... yikes... \n";
		}
	} //end while loop

	return 0;
}
