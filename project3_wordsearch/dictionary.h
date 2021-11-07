#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class Heap{

    public:

        //function declarations
        int parent(int n);

        int left(int n);

        int right(int n);

        int getItem(int n);


        //functions regarding sorting of heap
        void Max_Heapify(vector<T> &A, int heapsize, int i);

        void buildMaxHeap(vector<T> &A, int heapsize);

        void heapsort(vector <T> &A, int heapsize);

        void InitializeMaxHeap(vector <T> & sample);


        //print out contents of vector
        void printarray(vector <T> A, int heapsize);


    private:

        vector<T> heapArray;

        int heapsize = 0;

        int l,r;

};

//returns the parent index
template <typename T>
int Heap<T>::parent(int n){

    return (n)/2;

}

//returns the left leaf index
template <typename T>
int Heap<T>::left(int n){

    return n*2 + 1;

}

//returns the right leaf index
template <typename T>
int Heap<T>::right(int n){

    return (n*2)+2;

}

//returns the item in the heap given an index
template <typename T>
int Heap<T>::getItem(int n){

    return heapArray[n];

}

//heapfiy function that uses recursion for swapping of nodes to make sure max heap property is met
template <typename T>
void Heap<T>::Max_Heapify(vector<T> &A, int heapsize, int i){

    //set largest node to the given index
    int largest = i;

    //depending on the datatype, temp is used in the swapping of two nodes
    T temp;
    

    l = left(i);
    r = right(i);

    //If left child is larger than root
    if ((l < heapsize) && (A[l] > A[largest])){

        largest = l;

    }

    //if right child is larger than root
    if ((r < heapsize) && (A[r] > A[largest])){

        largest = r;

    }

    //if largest is not root
    if (largest != i){

        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        //Recursively call on the max_heapify function to make sure the sub tree meets the max heap property
        Max_Heapify(A, heapsize, largest);

    }

}

//Build heap
template <typename T>
void Heap<T>::buildMaxHeap(vector<T> &A, int heapsize){

    //set starting point of for loop to what size of the vector is
    int a = A.size();

    for (int i = (heapsize/2)-1; i >= 0; i--){

        //call on max_heapify function
        Max_Heapify(A, heapsize, i);


    }

}

//sorting algorithm for heaps
template <typename T>
void Heap<T>::heapsort(vector <T> &A, int heapsize){

    //build heap
    buildMaxHeap(A, heapsize);

    //variable used for swapping of data depends on what datatype is specified
    T temp;


    for (int i = heapsize-1; i > 0; i--){
        
        //swap A[0] with A[i]
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        //Call on Max_Heapify function
        Max_Heapify(A, i, 0);

    }


}

//call on the heap sorting algorithm and print out results
template <typename T>
void Heap<T>::InitializeMaxHeap(vector <T> & list){


    int heapSize = list.size();

    //sort a list
    heapsort(list, heapSize);

    //print heap
    printarray(list, heapSize);


}

//print out contents of heap
template <typename T>
void Heap<T>::printarray(vector <T> A, int heapsize){
            
    for (int i = 0; i< heapsize; i++){
        cout<<"New Array is "<<A[i]<<endl;
    }

}


class dictionary
{
    public:
        dictionary(string filename);

        void readDict(string filename); //reads dictionary file
        
        //sorting algorithms:
        void selectSort();
        void quickSort(int left, int right);
        void HeapSortWrapper();

        int getLength();    //gets length of the dictionary

        string searchDict(string x);    //looks up words from the dictionary

        //overloaded output function:
        friend ostream& operator<<(ostream& ostr, const dictionary& dict);


    private:

        vector<string> words;

        int partition(int sublist, int pivot);  //ONLY used in quicksort func
};

/****************************Function Implementation***************************/

//constructor
dictionary::dictionary(string filename)
{
    readDict(filename);
}

//reads data from the dictionary file to store each word into a string vector:
void dictionary::readDict(string filename)
{
    ifstream dict(filename); //open file
    string tmp;              //create temporary sting to push into vector

    int wordNum = 0;

    if (dict.is_open())
    {
        while (!dict.eof())
        {
            dict >> tmp;    

            //append "end line" character to each string in vector so that when
            //we insert any given word in the vector into a file, it will input
            //a new line after that word:
            words.push_back(tmp);
            words[wordNum].append("\n");    

            wordNum++;
        }  
        
        dict.close();
    }
    else cout << "Unable to open file \n";
}

//sorts the dictionary using a selection sort algorithm. This function also 
//abuses ASCII encoding. Uppercase letters A-Z have ASCII values 65-90, and
//lowercase letters a-z have values 97-122:
void dictionary::selectSort()
{
    int minIndex = 0;

    string minVal;  //smallest 'value' in list
    string compVal; //'value' to be compared
    string swapVal; //'value' to be swapped

    //The algorithm:
    for (int i = 0; i < words.size(); i++)
    {
        /*** Scan for smallest element ***/
        for (int j = i + 1; j < words.size(); j++)
        {
            minVal = words[minIndex];
            
            //only executes if the ASCII code of the string in compVal
            //is smaller than the respective ASCII code of minVal:
            if(minVal > words[j])
            {
                minVal = words[j];
                minIndex = j;
            }
        } //end j-loop
    
        /*** swapping! ***/
        swapVal = words[i];

        //If I don't include this statement, it gives you wrong answers ;-;
        //This statement makes sure you only swap if minVal is actually smaller
        //than swapVal, because sometimes this function decides to be wrong...
        if (swapVal > minVal)
        {
            words[i] = minVal;
            words[minIndex] = swapVal;
        }
    } //end for loop   
}    


//returns the total number of words inside the dictionary's words vector:
int dictionary::getLength()
{
    return words.size();
}

//Private member function. SHhould only ever be used inside the quicksort func
//Used inside quick sort for partitioning the vector. Sublist integer refers
// to the last value in the left sublist created by the function
int dictionary::partition(int sublist, int pivot)
{
    int i = sublist - 1;
    // int i = sublist;

    string swap;    //variable used for swapping

    for(int j = sublist; j < pivot; j++)
        if(words[j] <= words[pivot])
        {
            i++;

            //swapping is the same as in selection sort
            swap = words[j];
            words[j] = words[i];
            words[i] = swap;
        }   

    swap = words[i + 1];
    words[i + 1] = words[pivot];
    words[pivot] = swap;

    return i + 1;
}

//sort dictionary using Quick Sort. Pivot is always rightmost value
void dictionary::quickSort(int left, int right)
{
    int s;  //refers to index where left and right sides of the list are seperated

    if(left < right)
    {
        s = partition(left, right);
        quickSort(left, s - 1);
        quickSort(s + 1, right);
    }
}



//looks up words from the dictionary:
string dictionary::searchDict(string x)
{
    int lower = 0;
    int upper = words.size() - 1;

    while (lower <= upper)
    {
        int mid = lower + ((upper - lower) / 2);  //cuts dictinary vector in half
        bool i;

        if (x == words[mid])  //checks if x is at location
        {
            i = 1;
        }

        if (i == 1)
        {
            return x;   //returns x if x is present
        }

        if (x > words[mid])   //eliminates lower half if needed
        {
            lower = mid + 1;
        }
        else   //eliminates upper half if needed
        {
            upper = mid - 1;
        }      
    }
    return "Not present";   //returns "Not present" if x is not present in dictionary
}  

//overloaded output function. Outputs the words vector into a text file:
ostream& operator<<(ostream& ostr, const dictionary& dict)
{
    ofstream fout("dict-output.txt");
    fout.clear();

    for(int i = 0; i < (dict.words).size(); i++)
    {
        fout << dict.words[i]; //output i element of dictionary words to file
    }

    fout.close();

    return ostr;
}

//sort dictionary using heapsort
void dictionary::HeapSortWrapper(){

    //copy our old dictionary to heaplist - this is currently unsorted
    vector <string> heaplist = words;
    
    //Instantiate a heap object and make sure it contains strings
    Heap<string> heap1;
    heap1.InitializeMaxHeap(heaplist);

}

/******************************************************************************/

#endif
