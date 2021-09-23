/******************************************************************************
 * Project 1a				   Group members:								  *
 * 							   Rohan Seelan - seelan.r@northeastern.edu       *
 * 							   Andrew Nguyen - nguyen.andrew@northeastern.edu *
 * 							   Arbid Ysuuf - yusuf.ar@northeastern.edu        *
 * 																			  *
 * This program contains the declaration of the code class, the code class's  *
 * member functions, as well as a main function that implements a rough		  *
 * version of the mastermind game.										      *
******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

//Declaring the basic code class:
class code
{
    public:
        code(int length, int range); //default constructor saves values for n and m and generates random code

        void printSequence() const; //this function prints out the contents of the sequence vector
        void printGuess() const;	//this function prints out the contents of the guess vector
		void printChecker() const;	//this function prints out the contents of the checker vector

        void codeGen();             //this funcion generates code and stores it into the sequence vector
        void userInput();           //prompts the user to enter an integer in each cell of the guess vector

        int checkCorrect();			//returns # of correct digits in the correct location
        int checkIncorrect();		//returns # of correct digits in the incorrect location

    private:
        int n;                  //length of the code
        int m;                  //range of digits, [0, m-1]

        vector<int> sequence;   //this vector stores the secrect code. Named it this to hopefully avoid confusion
		vector<int> guess;		//this vector stores the user's guess
		vector<bool> checker;	//this vector is used to check whether or not the right numbers are in the right place
};

/******************************************************************************
 * 							  Class Implementation							  *
 ******************************************************************************/

//constructor: stores data for n and m, and then calls codeGen func
code::code(int length, int range)
{
    n = length;
    m = range;

    codeGen(); 
}

//The three printing functions, printSequence(), printGuess() and printChecker(),
//all follow the same logic and form.
void code::printSequence() const
{
    for(int i = 0; i < n; i++)
	{
		//print each of the items of the sequence vector followed by a comma then a space
        cout<<sequence[i]<<", "; 
    }

    cout<<"\n";
}

//this function prints out the guess vector:
void code::printGuess() const
{	
    for(int i = 0; i < n; i++)
	{
        cout<<guess[i]<<", "; 
    }

    cout<<"\n"; 
}

//this function prints out the checker vector:
void code::printChecker() const
{
	//Sometimes, the checker vector is not empty, so here I check to make sure it's not:
	if(!checker.empty())
	{
		for(int i = 0; i < n; i++)
		{
			cout<<checker[i]<<", ";
		}
	}

	cout<<"\n"; 
}

//this function generates a random code:
void code::codeGen()
{
    for(int i = 0; i < n; i++)
	{
        sequence.push_back(rand() % m); //this is will push_back a random integer or range [0, m-1]
    }
}

//this function allows the user to manually input values for the guess vector:
void code::userInput()
{
	//If you don't do this, you won't be able to input new numbers bc of the pushback:
    guess.clear();	

    int temp; //temporary variable that will store the user inputs

    for(int i = 0; i < n; i++)
	{
        cout<<"Enter a number between 0 and "<<m-1<<": ";
        cin>>temp;

		//checking if temp is within the acceptable range:
		while (temp > (m-1) || temp < 0)
		{
			cout<<"Your input was not valid, dude! \n Please input a number between 0 and "<<m-1<<":";
			cin>>temp;
		}
		
		//I recall getting a seg fault from guess[i] = temp, so I'm playing it safe:
		guess.push_back(temp);	 
    } //end for loop
}

//this function compares the sequence and guess vectors in order to determine the number of correct numbers in the correct location
int code::checkCorrect()
{
	checker.clear();	//without doing this, the checker never actually gets updated

	int numCorrect = 0;	//temporary variable that stores the number of correct guesses

	//This for loop looks at where each correct guess is located:
	for(int i = 0; i < n; i++)
	{
		//here, we will be editing the checker vector.
		//push back 1 into the indexes where there is the correct number,
		//push back 0 into the indexes with incorrect number:
		if(sequence[i] == guess[i])
		{
			checker.push_back(1);	//Using 1 and 0 instead of true/false for literally no reason
			numCorrect++;
		}
		else{
			checker.push_back(0);
		}
	} //end for loop

	return numCorrect;
}

//this function compares the sequence and guess in order to find the number of right numbers in WRONG locations,
//without counting indexes already accounted for by the checkCorrect function.
int code::checkIncorrect()
{
	int numIncorrect = 0;	//temp variable, stores # of right numbers in the wrong place

	//This function relies on the checker vector being filled out, so if it's empty I need to fill it out!
	if(checker.empty())
	{
		checkCorrect();	//the check vector gets filled out in the checkCorrect function
	}

	/* the first loop steps through each index of the guesses, then the we check *
	 * that we only examine a guess if it is not correct and in the right place  *
	 * and then, in the second loop we step through the sequence vector	     	 */
	for(int i = 0; i < n; i++)
	{
		if(checker[i] == 0)
		{
			for(int j = 0; j < n; j++)
			{
				//don't want to check cells where we already know that it's correct:
				if(guess[i] == sequence[j] && checker[j] == 0)
				{	
					numIncorrect++;

					/* After there is 1 match, we break and move onto the next guess.			   *
			 	 	* Here, I am trying to avoid duplicates. For example, if the sequence is 1,0,1 * 
			 	 	* and the guess is 0,1,2, I don't want it to see the 1 in the guess, and the   *
			 	 	* two 1's in the sequence, because then, it will tell the user that they have  *
			 	 	* 3 correct numbers in the wrong place, when they reall have 2				  */
					break;		
				} //end if
			} //end for loop
		} //end if
	} //end nested monstrosity

	return numIncorrect;
}

/****************************************************************************************************************/

//main function that will just be used to test this stuff:
int main()
{
	int turns_passed = 0;	//This is the number of turns that have elapsed. When it reaches 10, the game ends
	bool playing = true;	//This boolean is used to turn off the game when the user wins or loses

	//Initializing the game:
	int length;
	int range;

	cout<<"How long do you want the code to be?";
	cin>>length;

	cout<<"What would you like the range of digits to be?";
	cin>>range;

	code codemaker(length, range);	//creating the code object (the constructor convenienty makes the secret code too!)

	while(playing)
	{
		codemaker.userInput();		//taking in user input

		cout<<"Number of correct numbers in the correct place: "<<codemaker.checkCorrect()<<"\n";		//checking for correctness!
		cout<<"Number of correct numbers in the incorrect place: "<<codemaker.checkIncorrect()<<"\n";	//checking for incorrectness!
			
		//These lines are for debugging:
		cout<<"Secrect code: ";
		codemaker.printSequence();

		//If we wanted, we could print out the checker vector.
		//I only used this while debugging:
		//
		//cout<<"Checker     : ";
		//codemaker.printChecker();

		cout<<"User's guess: ";
		codemaker.printGuess();

		//the game ends when the guess and the sequence are identical because when this happens,
		//the number of correct numbers in the correct place should equal the length of the sequence:
		if(codemaker.checkCorrect() == length)
		{
			playing = false;	//Or, the game can just end with you running out of turns
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
