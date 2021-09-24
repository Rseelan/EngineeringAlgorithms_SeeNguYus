/******************************************************************************
 * Project 1a		   Group members:				      *
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
using namespace std;

class code
//the basic code class
{
    public:
	//default constructor saves values for n and m and generates random code
        code(int length, int range); 

        void printSequence() const;	//prints the contents of the sequence vector
        void printGuess() const;	//prints the contents of the guess vector
		void printChecker() const;	//prints the contents of the checker vector

        void codeGen();			//generates the secret code
        void userInput();		//records user input into the guess vector

        int checkCorrect();		//looks for correct digits in the correct location
        int checkIncorrect();	//looks for correct digits in the incorrect location

    private:
        int n;                  //length of the code
        int m;                  //range of digits, [0, m-1]

        vector<int> sequence;   //stores the secrect code
		vector<int> guess;		//stores the user's guess
		vector<bool> checker;	//used to keep track of where checkCorrect has already looked
};

/******************************************************************************
 *   			Class Implementation	  			      *
 *****************************************************************************/

code::code(int length, int range)
//constructor: stores data for n and m, and then calls codeGen func
{
    n = length;
    m = range;

    codeGen(); 
}

void code::printSequence() const
//Three printing functions, printSequence(), printGuess() and printChecker(),
//all follow the same logic and form.
{
    for(int i = 0; i < n; i++)
	{
	//print each of the items of the sequence vector followed by a comma then a space
        cout << sequence[i] << ", "; 
    }

    cout << "\n";
}

void code::printGuess() const
//this function prints out the guess vector:
{	
    for(int i = 0; i < n; i++)
	{
        cout << guess[i] << ", "; 
    }

    cout << "\n"; 
}

void code::printChecker() const
//this function prints out the checker vector:
{
	//Sometimes, the checker vector is not empty, so make sure it's not:
	if(!checker.empty())
	{
		for(int i = 0; i < n; i++)
		{
			cout << checker[i] << ", ";
		}
	}

	cout << "\n"; 
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
    //If you don't do this, you won't be able to input new numbers bc of the pushback:
    guess.clear();	

    int temp; //temporary variable that will store the user inputs

    for(int i = 0; i < n; i++)
	{
        cout << "Enter a number between 0 and " << m - 1 << ": ";
        cin >> temp;

		//checking if temp is within the acceptable range:
		while (temp > (m - 1) || temp < 0)
		{
			cout << "Your input was not valid, dude! \n";
			cout << "Please input a number between 0 and " << m - 1 << ":";
			cin >> temp;
		}
		
		//I have gotten seg fault from guess[i] = temp, so I'm playing it safe:
		guess.push_back(temp);	 
    } //end for loop
}

int code::checkCorrect()
//this function compares the sequence and guess vectors in order to determine 
//the number of correct numbers in the correct location
{
	checker.clear();	//without this, the checker never gets updated

	int numCorrect = 0;	//temporary variable, stores # of correct guesses

	//This for loop looks at where each correct guess is located:
	for(int i = 0; i < n; i++)
	{
		//here, we will be editing the checker vector.
		//push back 1 into the indexes where there is the correct number,
		//push back 0 into the indexes with incorrect number:
		if(sequence[i] == guess[i])
		{
			//Again, using push_back because seg faults put the fear of god in me
			checker.push_back(1);
			numCorrect++;
		}
		else{
			checker.push_back(0);
		}
		//Using 1 and 0 instead of true/false for the checker boolean vector.
		//Why? It's because I, Andrew Nguyen despise the english language.
	} //end for loop

	return numCorrect;
}

int code::checkIncorrect()
//this function compares the sequence and guess in order to find the number of
//right numbers in WRONG locations without counting indexes already accounted
//for by the checkCorrect function.
{
	int numIncorrect = 0;	//temp variable stores # incorrect guesses

	//This function relies on the checker vector being filled out:
	if(checker.empty())
	{
		//the check vector gets filled out in the checkCorrect function:
		checkCorrect();	
	}

	/* the first loop steps through each index of the guesses, then the we check *
	 * that we only examine a guess if it is not correct and in the right place  *
	 * and then, in the second loop we step through the sequence vector	    */
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

					/* After there is 1 match, we break and move onto the next guess.	       *
			 	 	* Here, I am trying to avoid duplicates. For example, if the sequence is 1,0,1 * 
			 	 	* and the guess is 0,1,2, I don't want it to see the 1 in the guess, and the   *
			 	 	* two 1's in the sequence, because then, it will tell the user that they have  *
			 	 	* 3 correct numbers in the wrong place, when they reall have 2		      */

					break;		
				} //end if
			} //end for loop
		} //end if
	} //end nested monstrosity

	return numIncorrect;
}

/******************************************************************************/

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
