#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;



//Code Class
class Code {

  public:

    Code (int digits, int range)
    {
        n = digits;
        m = range;
    }

    Code (){

        n = 0;
        m = 0;
    }

    void Random();
    void UserInput();
    //int checkCorrect();
    //int checkIncorrect();
    int checkCorrectTempVar = 0;
    void playgame();
    void printCheckArray();
    void PrintCheckCorrect();
    void PrintCheckIncorrect();
    void MainGame();
    int checkIncorrectTally = 0;
    int checkCorrectTally = 0;
    void ResetCheckArray();
    void PrintCodeStorer();
    
    int n;
    int m;

    vector<int> UserGuess{4,5,6,7};
    vector<int> CodeStorer;
    vector<int> CheckArray;

};

//Response Class
class Response {

    public:

        Response(int x, int y){
            
            numCorrect = x;
            numIncorrect = y;

        }

        Response(){
            numCorrect = 0;
            numIncorrect = 0;

        }

        void set(int &x, int &y);
        void setCorrect (int &x);
        void setIncorrect (int &y);
        int get();
        int get_numCorrect();
        int get_numIncorrect();

        friend ostream& operator<< (ostream& ostr, const Response& r);
        friend bool operator == (const Response &lhs, const Response &rhs);

        int numCorrect;
        int numIncorrect;
};

//Mastermind Class
class Mastermind {
    public:
        Mastermind (){
            int a = 0;
            n = 5;
            m = 10;
            SecretCode.n = n;
            SecretCode.m = m;
            answer.setCorrect(n);
            answer.setIncorrect(a);

        }
        Mastermind (int digits, int range){
            int a = 0;
            n = digits;
            m = range;
            SecretCode.n = n;
            SecretCode.m = m;
            answer.setCorrect(n);
            answer.setIncorrect(a);

        }

        Code humanGuess();
        Response getResponse(Code guessCode);
        void playGame();
        Code SecretCode;
        Code checkCorrect(Code guessCode);
        bool isSolved(Response answer, Response r);
        Response answer;
        

    private:
        int n;
        int m;
        void PrintSecretCode();
};




//Code class declarations
void Code::ResetCheckArray(){
  for (int i = 0; i < n; i++){
    CheckArray[i] = 0;
  }
}


void Code::PrintCodeStorer(){
  cout<<"The Secret Code is: ";
  for (int i = 0; i < n; i++){
    cout<<CodeStorer[i];
    }
  cout<<endl;
}

void Code::Random(){
  int x;
  
  for (int i = 0; i < n; i++){ 
    x = rand() % m;
    cout<<x<<endl;
    CodeStorer.push_back(x);
    //CheckArray[i] = 0;
  }
}


//Mastermind class declarations
Code Mastermind::humanGuess(){

    Code guessCode(n, m);
    int var;
    for (int i = 0; i < n; i++){

        cout<< "Please enter an integer between 0 and "<<m<<": ";
        cin >> var;
        guessCode.CodeStorer.push_back(var);
        cout<<endl;

    }

    return guessCode;
    
}

Response Mastermind::getResponse(Code guessCode){
    
    Response responseObj(guessCode.checkCorrectTally, guessCode.checkIncorrectTally);
    return responseObj;
}

void Mastermind::PrintSecretCode(){

    SecretCode.PrintCodeStorer();
}

Code Mastermind::checkCorrect(Code guessCode){
    
    
    guessCode.checkCorrectTally = 0;
    guessCode.checkIncorrectTally = 0;
    int temp = 0;

    vector <int> CheckArray(n, 0); 

    for(int i = 0; i < n; i++){

        
        if (guessCode.CodeStorer[i] == SecretCode.CodeStorer[i]){
            guessCode.checkCorrectTally++;
            CheckArray[i] = 1;

        }

    }

    for (int i = 0; i < n; i++){
        for (int j = 0;j < n; j++){
            if ((SecretCode.CodeStorer[j] == guessCode.CodeStorer[i]) && (temp != SecretCode.CodeStorer[j]) && (CheckArray[j] == 0)){
                temp = SecretCode.CodeStorer[j];
                guessCode.checkIncorrectTally++;
                break;
            }
        }   
    }

    cout<<"Check Correct yields: "<<guessCode.checkCorrectTally<<endl;
    cout<<"Check Incorrect yields: "<<guessCode.checkIncorrectTally<<endl;
    return guessCode;
}

bool Mastermind::isSolved(Response answer, Response r){

    // if (r.numCorrect == n){
    //     return true;
    // }
    // else {

    //     return false;
    // }

    if (answer == r){
        return true;
    }

    else {

        return false;
    }

}

void Mastermind::playGame(){

    SecretCode.Random();
    
    
    int i = 0;

    while(i < 10){

        i++;
        PrintSecretCode();

        if (isSolved(answer, getResponse(checkCorrect(humanGuess()))) == true){
            cout<<"Game Won"<<endl;
            break;

        }
    }

    if (i == 10){

        cout<<"Game Lost"<<endl;

    }

}


//global stuff
ostream& operator<< (ostream& ostr, Response r){
   ostr << r.numCorrect << ',' << r.numIncorrect;
   return ostr;
}

// bool operator == (Response lhs, Response rhs){
//   return ((lhs.get_numCorrect() == rhs.get_numCorrect()) && (lhs.get_numIncorrect() == rhs.get_numIncorrect()));
// }

bool operator == (Response lhs, Response rhs){
  
  if((lhs.numCorrect == rhs.numCorrect) && (lhs.numIncorrect == rhs.numIncorrect)){
      return true;
  }
  else{
      return false;
  }
}



int main(){

    Mastermind MainGame(4, 10);

    MainGame.playGame();

    return 0;

}