#ifndef CODECLASS_H
#define CODECLASS_H

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class code
//the basic code class
{
	public:
		code();	//default constructor

		void initializeCode(int length, int range);	//manually set n and m 
		void codeGen();					//generates a random code
		void userInput();				//records user's input into the sequence vector
		void printSequence() const;			//prints the contents of the sequence vector

		vector<int> returnSequence() const;		//returns the sequence vector 

		int checkCorrect(code guess);	//return # of correct digits in correct location
		int checkIncorrect(code guess);	//return # of correct digits in incorrect location

	private:
		int n;                  //length of the code
		int m;                  //range of digits, [0, m-1]

		vector<int> sequence;   //stores the numbers that make up the code
		vector<bool> checker;	//used to keep track of indexes where checkers already looked
};

/******************************************************************************
 *   			Function Definitions	  			      *
 *****************************************************************************/

code::code()
//default constructor: creates a code object with an empty sequence. I am doing 
//this so that we can initialize an empty code object as part of the mastermind
//class without overloading the constructor here:
{
	n = 0;
	m = 0;
}

void code::initializeCode(int length, int range)
//stores data for n and m, and then calls codeGen func to generate a random code
{
	n = length;
	m = range;

	codeGen(); 
}

void code::codeGen()
//this function generates a random code and puts it into sequence vector:
{
	for(int i = 0; i < n; i++)
	{
		//this is will push_back a random integer or range [0, m-1]:
		sequence.push_back(rand() % m);
	}
}

void code::userInput()
//this function allows the user to manually input values for the guess vector:
{
	sequence.clear(); //clear sequence so it can be changed

	int temp; //temporary variable that will store the user inputs

	for(int i = 0; i < n; i++)
	{
		cout << "Enter a number between 0 and " << m - 1 << ": ";
		cin >> temp;

		//checking if temp is within the acceptable range:
		//NOTE: if you put a non-integer value, the program doesn't
		//know what to do, and the console bugs out.
		while (temp > (m - 1) || temp < 0)
		{
			cout << "Your input was not valid, dude! \n";
			cout << "Please input a number between 0 and " << m - 1 << ":";
			cin >> temp;
		}
		
		//I've tried both sequence[i] = temp and sequence.at(i) = temp
		//and BOTH have given me problems while push_back just works:
		sequence.push_back(temp);
	} //end for loop
}

void code::printSequence() const
//This function prints the content of the sequence vector to the screen by
//printing each item followed by a comma then a space
{
	for(int i = 0; i < n; i++)
	{
		cout << sequence[i] << ", "; 
	}

	cout << "\n";
}

vector<int> code::returnSequence () const
//returns the sequence vector in the code. Neccessary for the check correct and
//check incorrect, because those functions involve accessing the sequences of
//other code objects, which means accessing a private member from outside:
{
	return sequence;
}

int code::checkCorrect(code guess) 
//this function compares the sequence and guess vectors in order to determine 
//the number of correct numbers in the correct location
{	
	//temporary variables:
	int numCorrect = 0;				//stores # of correct guesses
	vector<int> tempVec = guess.returnSequence();	//stores guess sequence

	//need to make sure that checker is empty before trying to update it:
	checker.clear();

	//This for loop looks at where each correct guess is located:
	for(int i = 0; i < sequence.size(); i++)
	{
		//here, we will be editing the checker vector.
		//put a 1 into the indexes where there is the correct number,
		//put a 0 into the indexes where there is an incorrect number:
		if(sequence[i] == tempVec[i])
		{
			checker.push_back(1);
			numCorrect++;
		}
		else
		{
			checker.push_back(0);
		}
		//Using 1 and 0 instead of true/false for the checker boolean vector.
		//Why? It's because I, Andrew Nguyen despise the english language.
	} //end for loop

	return numCorrect;
}

int code::checkIncorrect(code guess)
//this function compares the sequence and guess in order to find the number of
//right numbers in WRONG locations without counting indexes already accounted
//for by the checkCorrect function.
{
	//temporary variables:
	int numIncorrect = 0;				//stores # incorrect guesses
	vector<int> tempVec = guess.returnSequence();	//stores guess sequence

	//This function relies on the checker vector being filled out:
	if(!checker.empty())
	{
		/***************************************************************************** 
		 * the first loop steps through each index of the guesses, then the we check *
		 * that we only examine a guess if it is not correct and in the right place  *
		 * and then, in the second loop we step through the sequence vector	     *
		 *****************************************************************************/
		for(int i = 0; i < n; i++)
		{
			if(checker[i] == 0)
			{
				for(int j = 0; j < n; j++)
				{
					//Don't want to check cells where we already know that it's correct,
					//After there is 1 match, we break and move onto the next guess:
					if(tempVec[i] == sequence[j] && checker[j] == 0)
					{	
						numIncorrect++;
						 
						//These 2 lines prevent duplicate checks:
						checker[j] = 1; 
						break;		
					} //end if
				} //end for loop
			} //end if
		} //end for loop 
	} //end if 
	else
	{
		cout<<"Error: checker vector is emtpty. Run checkCorrect() \n";
		numIncorrect = 0;
	}

	return numIncorrect;
}

/******************************************************************************/

#endif
