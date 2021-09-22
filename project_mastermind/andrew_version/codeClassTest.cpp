#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class code{
    public:
        code(int length, int range);            //default, constructor saves values for n and m and generates random code

        void printSequence() const;		//this function prints out the contents of the sequence vector, and will mostly be used for debugging
        void printGuess() const; 		//this function prints out the contents of the guess vector
	void printChecker() const;		//this function prints out the contents of the checker vector

        void codeGen();                         //this funcion generates n random numbers in the range [0, m-1] and stores them into the sequence vector
        void userInput();                       //prompts the user to enter an integer in each cell of the guess vector

        int checkCorrect();			//returns # of correct digits in the correct location
        int checkIncorrect();			//returns # of correct digits in the incorrect location

    private:
        int n;                  //length of the code
        int m;                  //range of digits, [0, m-1]

        vector<int> sequence;   //this vector stores the actual code part of the code object. Named it this to hopefully avoid confusion
	vector<int> guess;	//this vector stores the user's guess.
	vector<bool> checker;	//this vector is used to check whether or not the right numbers are in the right place
};

/***************************************************************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Class Implementation~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
 ***************************************************************************************************************/

//constructor: stores data for n and m, and then calls codeGen func
code::code(int length, int range){
    n = length;
    m = range;

    codeGen(); 
}

//this function prints out the sequence vector:
void code::printSequence() const{
    for(int i = 0; i < n; i++){
        cout<<sequence[i]<<", "; //This prints each of the items of the sequence vector followed by a comma then a space
    }

    cout<<"\n"; //I save this for after the for loop bc I want to print out the code as 1 line
                //The way this is set up, the program will create a new line after the whole code is printed
}

//this function prints out the guess vector:
void code::printGuess() const{
    for(int i = 0; i < n; i++){
        cout<<guess[i]<<", "; //This prints each of the items of the guess vector followed by a comma then a space
    }

    cout<<"\n"; 
}

//this function prints out the checker vector:
void code::printChecker() const{
	if(!checker.empty()){
		for(int i = 0; i < n; i++){
			cout<<checker[i]<<", ";
		}
	}

	cout<<"\n"; 
}

//this function generates a random code:
void code::codeGen(){
    for(int i = 0; i < n; i++){
        sequence.push_back(rand() % m); //this is will push_back a random integer or range [0, m-1]
                                        //and will do it n times
    }
}

//this function mainly exists for the convenience of the user, calling it allows the user to manually input values for the sequence in the console
void code::userInput(){
    guess.clear();	//If you don't do this, you won't be able to input new numbers bc of the pushback

    int temp; //temporary variable that will store the user inputs before passing its value into a location in sequence

    for(int i = 0; i < n; i++){
        cout<<"Enter a number between 0 and "<<m-1<<": "; //the max digit in any 1 index of the sequence is equal to m-1, so I just shove it in there
        cin>>temp;

	guess.push_back(temp);	//turns out, if you don't push_back, computer can get mad and give a seg fault 
    }
}

//this function compares the sequence and guess vectors in order to determine the number of correct numbers in the correct location
int code::checkCorrect(){
	checker.clear();	//without doing this, the checker never actually gets updated

	int numCorrect = 0;	//temporary variable that stores the number of correct guesses

	//This for loop looks at where each correct guess is located:
	for(int i = 0; i < n; i++){
		if(sequence[i] == guess[i]){
			checker.push_back(1);	//Using 1 and 0 instead of true/false bc... I really don't know
			numCorrect++;
		}
		else{
			checker.push_back(0);
		}
	}

	return numCorrect;
}

//this function compares the sequence and guess in order to find the number of right numbers in WRONG locations,
//without counting indexes already accounted for by the checkCorrect function.
int code::checkIncorrect(){
	int numIncorrect = 0;	//temp variable, stores # of right numbers in the wrong place

	//This function relies on the checker vector being filled out, so if it's empty I need to fill it out!
	if(checker.empty()){
		checkCorrect();	
	}

	/* the first loop steps through each index of the guesses, then the we check *
	 * that we only examine a guess if it is not correct and in the right place  *
	 * and then, in the second loop we step through the sequence vector	     */
	for(int i = 0; i < n; i++){
	if(checker[i] == 0){
		for(int j = 0; j < n; j++){
		if(guess[i] == sequence[j] && checker[j] == 0){	//don't want to check cells where we already know that it's correct
			numIncorrect++;

			break;		
			/* After there is 1 match, we break and move onto the next guess.		*
			 * Essentially, here I am trying to avoid duplicates. For example,		* 
			 * if the sequence is 1,0,1 and the guess is 0,1,2,				*
			 * I don't want it to see the 1 in the guess, and the two 1's in the sequence,  *
			 * and then tell the user they have 2 correct numbers in the wrong place.	*/
		}
		}
	}	
	}

	return numIncorrect;
}

/****************************************************************************************************************/

//main function that will just be used to test this stuff:
int main(){
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

		while(playing){
			codemaker.userInput();		//taking in user input

			cout<<"Number of correct numbers in the correct place: "<<codemaker.checkCorrect()<<"\n";	//checking for correctness!
			cout<<"Number of correct numbers in the incorrect place: "<<codemaker.checkIncorrect()<<"\n";	//checking for incorrectness!
				
			//These lines are for debugging:
			cout<<"Secrect code: ";
			codemaker.printSequence();

			cout<<"Checker     : ";
			codemaker.printChecker();

			cout<<"User's guess: ";
			codemaker.printGuess();

			//the game ends when the guess and the sequence are identical because when this happens,
			//the number of correct numbers in the correct place should equal the length of the sequence:
			if(codemaker.checkCorrect() == length) {
				playing = false;	//Or, the game can just end with you running out of turns
				cout<<"Congrats! You win! Pog! \n";
			}
			else if(turns_passed > 10){
				playing = false;
				cout<<"You lose... yikes... \n";
			}
		}

	return 0;
	}
