//This code was writting by Rohan Seelan, Andrew Nguyen, and Arbid Yusuf. 
//It contains the implementation for the first part of the Mastermind Project. 

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Code {

  public:

    Code (int digits, int range)
    {
        n = digits;
        m = range;
    }

    void Random();


    void UserInput();

    int checkCorrect();

    int checkIncorrect();

    int checkCorrectTempVar = 0;

    void playgame();

    void printCheckArray();

    void PrintCheckCorrect();

    void PrintCheckIncorrect();

    void MainGame();

    int checkIncorrectTally = 0;

    int checkCorrectTally = 0;

    void ResetCheckArray();

    void PrintSecretCode();

  private:

    int n;
    int m;
    vector<int> secretCode;
    vector<int> UserGuess{5, 3, 2, 4};
    std::vector<int> CheckArray;

};

void Code::Random(){

  int x;

  for (int i = 0; i < n; i++){
    
    x = rand() % m;
    cout<<x<<endl;
    secretCode.push_back(x);
    CheckArray.push_back(0);
    //cout << secretCode.size() << endl;;

  }

}

void Code::printCheckArray(){
  
  cout<<"The Check Array is: ";

  for (int i = 0; i < n; i++){
      
    cout<<CheckArray[i];

    }

  cout<<endl;

}

void Code::ResetCheckArray(){

  for (int i = 0; i < n; i++){
    
    
    CheckArray[i] = 0;
    

  }
}

int Code::checkCorrect(){

  checkCorrectTally = 0;

  //for (int i = 0; i < n; i++){
    
    //CheckArray.push_back(0);
    //cout<<CheckArray[i];

  //}

  for(int i = 0; i < n; i++){
    
    if (UserGuess[i] == secretCode[i]){
      
      //CheckCorrectTempVar = UserGuess[i];
      checkCorrectTally++;
      CheckArray[i] = 1;

    }
    
  }

  //cout << "Check Correct yields: "<<checkCorrectTally<<endl;
  return checkCorrectTally;

}

void Code::UserInput(){

  int var;

  for (int i = 0; i < n; i++){

    cout<< "Please enter an integer between 0 and "<<m<<": ";
    
    cin >> UserGuess[i];
    cout<<endl;

  }

  cout << "User input complete" << endl;

}

int Code::checkIncorrect(){
    
    checkIncorrectTally = 0;
    
    int temp = 0;

    for (int i = 0; i < n; i++){
    
      for (int j = 0;j < n; j++){
        
        if ((secretCode[j] == UserGuess[i]) && (temp != secretCode[j]) && (CheckArray[j] == 0)){

          temp = secretCode[j];
          
          checkIncorrectTally++;
          break;

        }

      }
        
  }

  //cout << "Check Incorrect yields: "<<checkIncorrectTally<<endl;
  return checkIncorrectTally;

}

void Code::PrintSecretCode(){

  cout<<"The Secret Code is: ";

  for (int i = 0; i < n; i++){
      
    cout<<secretCode[i];

    }

  cout<<endl;



}

// void Code::PrintCheckCorrect(){

//   cout<<checkCorrectTally;

// }

// void Code::PrintCheckIncorrect(){

//   cout<<checkIncorrectTally;

// }

void Code::MainGame(){

  Random();
  int i = 0;
  while(i < 10){

    i++;

    UserInput();

    ResetCheckArray();

    PrintSecretCode();
    
    cout << "Check Correct yields: " << checkCorrect() << endl;
    printCheckArray();
    cout << "Check Incorrect yields: "<< checkIncorrect()<<endl;


    if (checkCorrectTally == n){
      
      cout<<"Game Won";
      break;
    } else if( i == 10){

      cout<<"Game Lost";

    }
    else{

    }

  }
  



}

int main(){

  
  Code code1(4, 9); 

  code1.MainGame();

  // code1.Random();
  // code1.printCheckArray();
  // code1.UserInput();
  // cout << "Check Correct yields: " << code1.checkCorrect() << endl;
  // code1.printCheckArray();
  // cout << "Check Incorrect yields: "<< code1.checkIncorrect()<<endl;

  return 0;
}