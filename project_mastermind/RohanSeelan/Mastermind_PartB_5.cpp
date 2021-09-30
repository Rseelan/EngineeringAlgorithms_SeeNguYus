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

        void playgame();

        void printCheckArray();

        void PrintCheckCorrect();

        void PrintCheckIncorrect();

        void MainGame();

        void ResetCheckArray();
        
        void PrintCodeStorer();

        void setn(int x){

            n = x;

        }

        void setm(int y){

            m = y;

        }

        void EditCodeStorer(int x){

            CodeStorer.push_back(x);

        }

        void reset(){

            CodeStorer.clear();

        }

        int returnCodeStorer(int i) {

            int var;
            var = CodeStorer[i];
            return var;

        }

        int returncheckCorrectTally(){

            return checkCorrectTally;

        }

        int returncheckIncorrectTally(){

            return checkIncorrectTally;

        }

        void setCheckCorrectTally(int x){
            checkCorrectTally = x;
        }

        void setCheckIncorrectTally(int x){
            checkIncorrectTally = x;
        }
    
    private:
    
        int n;
        
        int m;
        
        vector<int> CodeStorer;

        int checkIncorrectTally = 0;

        int checkCorrectTally = 0;
    

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

        void setCorrect (int x){
            
            numCorrect = x;

        }

        void setIncorrect (int y){

            numIncorrect = y;

        }

        int get();

        int get_numCorrect();

        int get_numIncorrect();

        friend ostream& operator<< (ostream& ostr, Response r);

        friend bool operator == (Response lhs, Response rhs);

    private:

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
            
            SecretCode.setn(n);
            
            SecretCode.setm(m);
            
            answer.setCorrect(n);
            
            answer.setIncorrect(a);

        }

        Mastermind (int digits, int range){
            
            int a = 0;
            
            n = digits;
            
            m = range;
            
            SecretCode.setn(n);
            
            SecretCode.setm(m);
            
            answer.setCorrect(n);
            
            answer.setIncorrect(a);

        }

        Code humanGuess();
        
        Response getResponse(Code guessCode);
        
        void playGame();
        
        Code checkCorrect(Code guessCode);
        
        bool isSolved(Response answer, Response r);

        void PrintSecretCode();
        

    private:
        
        int n;
        
        int m;

        Code SecretCode;
        
        Response answer;
        
        
};




//Code class declarations

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
    //CodeStorer[i] = x;

  }

}


//Mastermind class declarations
Code Mastermind::humanGuess(){

    Code guessCode(n, m);
    
    int var;

    guessCode.reset();
    
    for (int i = 0; i < n; i++){

        cout<< "Please enter an integer between 0 and "<<m<<": ";
        
        cin >> var;
        
        //guessCode.CodeStorer.push_back(var);
        guessCode.EditCodeStorer(var);
        
        cout<<endl;

    }

    return guessCode;
    
}

Response Mastermind::getResponse(Code guessCode){
    
    Response responseObj(guessCode.returncheckCorrectTally(), guessCode.returncheckIncorrectTally());
    
    cout<<"The response is: "<<responseObj<<endl;
    return responseObj;
}

void Mastermind::PrintSecretCode(){

    SecretCode.PrintCodeStorer();
}

Code Mastermind::checkCorrect(Code guessCode){
    
    guessCode.setCheckCorrectTally(0);
    
    guessCode.setCheckIncorrectTally(0);
    
    int temp = 0;

    int var1 = 0;
    int var2 = 0;

    vector <int> CheckArray(n, 0); 

    for(int i = 0; i < n; i++){

        
        if (guessCode.returnCodeStorer(i) == SecretCode.returnCodeStorer(i)){
            
            var1++;
            guessCode.setCheckCorrectTally(var1);
            
            CheckArray[i] = 1;

        }

    }

    for (int i = 0; i < n; i++){
        
        for (int j = 0;j < n; j++){
           
            if ((SecretCode.returnCodeStorer(j) == guessCode.returnCodeStorer(i)) && (temp != SecretCode.returnCodeStorer(j)) && (CheckArray[j] == 0)){
               
                temp = SecretCode.returnCodeStorer(j);

                var2 ++;
               
                guessCode.setCheckIncorrectTally(var2);
               
                break;
            }
        }   
    }

    
    //cout<<"Check Correct yields: "<<guessCode.checkCorrectTally<<endl;
    
    //cout<<"Check Incorrect yields: "<<guessCode.checkIncorrectTally<<endl;
    
    return guessCode;
}

bool Mastermind::isSolved(Response answer, Response r){

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

bool operator == (Response lhs, Response rhs){
  
  if((lhs.numCorrect == rhs.numCorrect) && (lhs.numIncorrect == rhs.numIncorrect)){
      
      return true;
  
  }
  
  else{
  
      return false;
  
  }

}

int main(){

    int numDigits;
    int numRange;

    cout<<"Welcome to Mastermind Part B!"<<endl;
    cout<<"Please enter the number of digits you want your secret code to be: ";
    cin>>numDigits;
    cout<<endl;
    cout<<"Please enter the maximum range of each digit ";
    cin>>numRange;
    cout<<endl;

    Mastermind MainGame(numDigits, numRange);

    MainGame.playGame();

    return 0;

}