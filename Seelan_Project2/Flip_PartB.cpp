#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "d_node.h"

using namespace std;

//complete deck linked list implementation and shuffle function

class Card {

    public:
    
        Card();
        Card(int x, string y);


        void setvalue(int x);
        int getvalue();

        void setSuit(string s);
        string getSuit();


        friend ostream& operator<<(ostream& os, const Card& CD){
            os << CD.value << ' ' << CD.suit;
            return os; 
        }

    private:
        int value;
        string suit;

};

Card::Card(){

    value = 0;
    suit = "NA";
}

Card::Card(int x, string y){
    value = x;
    suit = y;
}

void Card::setvalue(int x){
    value = x;
}

int Card::getvalue(){
    return value;
}

void Card::setSuit(string s){
    suit = s;
}
string Card::getSuit(){
    return suit;
}

class Deck{
    public:

        //constructor of Deck class
        Deck(){

            //allocate a new node for frontcard1 to contain
            frontcard1 = new node<Card>();

            //head2 serves as a temporary "head" for each suit
            head2 = frontcard1;

            //logic for changing the suit 
            for (int j = 0; j<4; j++){

                // if (j == 0){
                //     suitVar = "Clubs";  
                // }
                // else if(j == 1){
                //     suitVar = "Diamonds";
                // }

                // else if(j == 2){
                //     suitVar = "Hearts";

                // }
                // else {
                //     suitVar = "Spades";
                // }

                switch(j){
                    
                    case 0:
                    suitVar = "Clubs";
                    break;
                    case 1:
                    suitVar = "Diamonds";
                    case 2:
                    suitVar = "Hearts";
                    break;
                    case 3:
                    suitVar = "Spades";
                    break;

                }

                //logic for implementing the "head" of each suit is a bit different to what's in the for loop
                Card cardtemp(1, suitVar);
                head2->nodeValue = cardtemp;

                t = head2;

                //n represents the node we are on. t is a temporary node variable used.
                for (int i = 2; i<14; i++){
                    
                    //allocate a new node
                    n = new node<Card>();
                    Card cardtemp(i, suitVar);

                    //populate value of node
                    n-> nodeValue = cardtemp;

                    //update the "next" parameter of a t node
                    t->next = n;

                    //move t to our next node, n
                    t = n;

                }
                
                //allocate a new node to represent head 2
                head2 = new node<Card>();

                //have t point to the new "head" in our next suit
                t->next = head2;

                }

            //end our linked list
            n->next = NULL;
            
        }

        Card deal();
        void replace(Card backCard);

        //shuffle function declarations
        void shuffle();
        void shuffle3Times();

        //print out our entire linked list
        friend ostream& operator<<(ostream &ostr, const Deck DeckObj);

        //print contents of linked list
        void printList(node<Card>* temp){

            while (temp != NULL) {
                cout << temp->nodeValue <<endl;
                temp = temp->next;
            }

        }

        void printList2(){

            t2 = frontcard2;

            while (t2 != NULL) {
                cout << t2->nodeValue <<endl;
                t2 = t2->next;
            }

        }

        //return a card's value

        int returnCardValue(int x);
        string returnCardSuit(int x);


    private:

        //absolute head of our linked list
        node<Card> *frontcard1;
        node<Card> *frontcard2 = new node<Card>();

        //nodes used to create linked list
        node<Card> *head2;
        node<Card> *n;
        node<Card> *t;
        node<Card> *t2 = frontcard2;
        node<Card> *topCard;

        string suitVar;

};

Card Deck::deal(){

    //temp variable so we can store our front card
    topCard = frontcard1;

    //store contents of our front card into a card object
    Card cardFrontTemp(topCard->nodeValue.getvalue(), topCard->nodeValue.getSuit());

    //"remove the first card from our original deck"
    frontcard1 = frontcard1 ->next;

    //return card object
    return cardFrontTemp;
}


void Deck::replace(Card backCard){
    

    if(t2->nodeValue.getvalue() == 0){
        t2->nodeValue = backCard;
    }
    else{
        n = new node<Card>();
        t2->next = n;
        t2 = n;
        t2->nodeValue = backCard;

    }

}

//the logic of our shuffle algorithm is to randomly choose pair in the linked list and then swap them
void Deck::shuffle(){

    //three node pointers will be used to shuffle our linked list
    node<Card>* temp;
    node<Card>* curr;
    node<Card>* prev;

    //specify parameters for choosing a node in our linked list
    int max = 50;
    int min = 0;
    int range = max - min + 1;
    int num;

    //our index is set to an extremely high value as we want to shuffle as many times possible
    for (int j = 0; j<1000; j++){

        //choose a random pair to shuffle
        num = rand() % range + min;

        //if we are dealing with the head node
        if (num == 0){

            //set our placeholder nodes
            prev = frontcard1;
            temp = prev->next;
            curr = temp->next;

            //perform the swap but set our temp to be the absolute front of our linked list after
            prev->next = curr;
            temp->next = prev;
            frontcard1 = temp;

        }

        //if we are dealing with any node that isn't a header node
        //The logic for this is as follows:
        // prev node -> temp node -> curr node
        else {

            temp = frontcard1;

            //traverse to the pair we want to swap
            for (int i = 0; i<num;i++){

                prev = temp;
                temp = temp->next;

            }

            //set curr to the next node present after "temp"
            curr = temp->next;

            //perform the swap
            temp->next = curr->next;
            curr->next = temp;
            prev->next = curr;
            //prev node ->  curr node -> temp node

        }


    }

}


void Deck::shuffle3Times(){

    //call on our shuffle function 3 times
    for (int i = 0; i<4; i++){
        shuffle();

    }

}

//main thing about this overloaded operator is that it checks the Card's value within nodeValue and prints if its a normal number
//Ace, Joker, Queen, and King
ostream& operator<<(ostream &ostr, const Deck DeckObj)
{

    //our "pointer" which is used to traverse the linked list
    node<Card>* temp;

    //set temp equal to the front card of the linked list
    temp = DeckObj.frontcard1;

    //travese linked list until we reach the end 
    while (temp != NULL) {

        //check what the card value is at each traversal
        switch(temp->nodeValue.getvalue()){
            case 1:
            cout<<"Ace"<<" ";
            cout<<temp->nodeValue.getSuit()<<endl;
            break;
            case 11:
            cout<<"Joker"<<" ";
            cout<<temp->nodeValue.getSuit()<<endl;
            break;
            case 12:
            cout<<"Queen"<<" ";
            cout<<temp->nodeValue.getSuit()<<endl;
            break;
            case 13:
            cout<<"King"<<" ";
            cout<<temp->nodeValue.getSuit()<<endl;
            break;
            default :
            cout<< temp->nodeValue <<endl;

        }

        //traverse linked list
        temp = temp->next;
        }

	return ostr;
}

int Deck::returnCardValue(int x){

    int CardValue;
    int listCount = 1;
    node<Card> *tempValue;
    tempValue = frontcard2;

    while(listCount!=x){
        tempValue = tempValue->next;
        listCount++;

    }

    CardValue = tempValue->nodeValue.getvalue();
    return CardValue;

}

string Deck::returnCardSuit(int x){
    string CardSuit;
    int listCount = 1;
    node<Card> *tempValue;
    tempValue = frontcard2;

    while(listCount!=x){
        tempValue = tempValue->next;
        listCount++;

    }

    CardSuit = tempValue->nodeValue.getSuit();
    return CardSuit;

}

void PlayGame(){

    int count = 0;
    int UserInput;
    int CardValue;
    string CardSuit;
    bool state = true;
    //our constructor will print out the linked list as well
    Deck Deck1;

    cout<<"Created Deck is:"<<endl;
    //test output stream operator
    cout<<Deck1;

    cout<<endl;

    //after being shuffled three times, the shuffled linked list will be printed
    Deck1.shuffle3Times();
    cout<<"The shuffled deck is: "<<endl;
    //test output stream operator
    cout<<Deck1;

    cout<<endl;
    cout<<"Secondary deck is: "<<endl;

    for (int i=0;i<24;i++){
        Deck1.replace(Deck1.deal());
    }
    
    //The
    Deck1.printList2();
    cout<<endl;

    cout<<"Original deck is:"<<endl;
    cout<<Deck1;

    while(state){

        cout<<"The new list is:"<<endl;
        Deck1.printList2();

        cout<<"Your current score is: "<<count<<endl;
        cout<<"Please enter a card number: ";
        cin>>UserInput;
        cout<<endl;

        CardValue = Deck1.returnCardValue(UserInput);
        cout<<CardValue<<endl;
        CardSuit = Deck1.returnCardSuit(UserInput);
        cout<<CardSuit<<endl;

        //examine card value values
        switch(CardValue){
            case 0:
            state = false;
            break;
            case 1:
            count = count + 10;
            break;
            case 11: case 12: case 13:
            count = count + 5;
            break;
            case 8: case 9: case 10: 
            count = count + 0;
            break;
            case 7:
            count = count/2;
            break;
            case 2: case 3: case 4: case 5: case 6:
            count = 0;
            break;
            default :
            cout<<"Please provide a valid user input: "<<endl;
            }

            //examine suits
            if(CardSuit == "Hearts"){
                count++;
            }

            

    }

}


int main(){

    PlayGame();

    return 0;

}