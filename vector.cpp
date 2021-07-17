#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T> class Vector{
    private:
        size_t currentCapacity;
        size_t currentSize;
        T* vec;
    public:
        Vector(size_t);
        Vector(size_t,T);
        Vector();
        size_t capacity();
        size_t size();
        void push(T);
        void pop();
        T front();
        T back();
        T operator[](size_t);
        void sort(int,int);
        ~Vector();
        protected:
        int partition(int,int);
};

/*.............................................................................
 * Vector() -- Constructor that initializes vector with capacity 1            *
 * Args: No arguments                                                         *
 * Returns : None                                                             *
 * ...........................................................................*/
template <class T>
Vector<T>::Vector(){
    currentCapacity = 1;
    currentSize=0;
    vec = new T[1];   
}

/*.............................................................................
 * Vector(size_t c) --  Constructor that initializes vector with capacity c   *
 * Args: Capacity with which vector need to be initialized                    *
 * Returns : None                                                             *
 * ...........................................................................*/
template <class T>
Vector<T>::Vector(size_t c){
    currentCapacity = c;
    vec = new T[c];
    currentSize=0;
}

/*................................................................................................................
 * Vector(size_t c, T x) --  Constructor that initializes vector with capacity c and inserts element x c times   *
 * Args: Value to be inserted and capacity                                                                       *
 * Returns : None                                                                                                *
 * ..............................................................................................................*/
template <class T>
Vector<T>::Vector(size_t c, T x){
    currentCapacity = c;
    vec = new T[c];
    for(size_t i=0;i<c;i++){
        vec[i]=x;
    }
    currentSize=c;
}

/*.............................................................................
 * capacity --  Gives capacity of vector                                      *
 * Args: None                                                                 *
 * Returns : Capacity of vector                                               *
 * ...........................................................................*/
template <class T>
size_t Vector<T>::capacity(){
    return currentCapacity;
}

/*.............................................................................
 * size --  Gives size of vector                                              *
 * Args: None                                                                 *
 * Returns : Size of vector                                                   *
 * ...........................................................................*/
template <class T>
size_t Vector<T>::size(){
    return currentSize;
}

/*.............................................................................
 * push --  Pushes input value into vector                                    *
 * Args: Value to be pushed                                                   *
 * Returns : None                                                             *
 * ...........................................................................*/
template <class T>
void Vector<T>::push(T x){
    if(currentSize<currentCapacity){
        vec[currentSize]=x;
        currentSize++;
    }//if capacity is more than size
    else{
        size_t oldCap=currentCapacity;
        currentCapacity=currentCapacity*2;//double capacity
        T* newVec=new T[currentCapacity];
        for(size_t i=0;i<oldCap;i++){
            newVec[i]=vec[i];
        }//copying elements
        newVec[oldCap]=x;
        delete vec;
        vec=new T[2*currentCapacity];
        vec=newVec;//pointing it back
        currentSize++;
    }
    return;
}

/*.............................................................................
 * pop --  Pops the top element of vector                                     *
 * Args: None                                                                 *
 * Returns : None                                                             *
 * ...........................................................................*/
template <class T>
void Vector<T>::pop(){
    if(currentSize>0){
        vec[currentSize-1]=0;
        currentSize--;
    }
    return;
}

/*.............................................................................
 * front -- Returns the first element of the vector                           *
 * Args: None                                                                 *
 * Returns : Front element of vector if non-empty, else -1                    *
 * ...........................................................................*/
template <class T>
T Vector<T>::front(){
    if(currentSize==0){
        return -1;
    }
    return vec[0];
}

/*.............................................................................
 * back -- Returns the last element of the vector                             *
 * Args: None                                                                 *
 * Returns : Last element of vector if non-empty, else -1                     *
 * ...........................................................................*/
template <class T>
T Vector<T>::back(){
    if(currentSize==0){
        return -1;
    }
    return vec[currentSize-1];
}

/*.............................................................................
 * operator[] -- Returns the element of the vector with input index           *
 * Args: Index of element to be returned                                      *
 * Returns : Returns element with input index if it is assigned, -1 otherwise *
 * ...........................................................................*/
template <class T>
T Vector<T>::operator[](size_t i){
    if(currentSize<i+1){//if element is assigned
        return -1;
    }
    return vec[i];
}

/*.............................................................................
 * sort -- Sorts the elements in vector                                       *
 * Args: Start and end index of elements to be sorted                         *
 * Returns : None                                                             *
 * ...........................................................................*/
template <class T>
void Vector<T>::sort(int start,int end){
    if(start<end){
        int piv = partition(start,end);
        sort(start,piv-1);
        sort(piv+1,end);//Recursive calls of quick sort
    }
    return;
 }

/*.............................................................................
 * partition -- Partitions the vector with first element as pivot             *
 * Args: Start and end index of elements to be partitioned                    *
 * Returns : Partition index                                                  *
 * ...........................................................................*/
template <class T>
int Vector<T>::partition(int start,int end){
    int pivot=vec[start];
    int j=start+1;
    for(int i=start+1;i<=end;i++){
        if(vec[i]<pivot){
            int temp=vec[i];
            vec[i]=vec[j];
            vec[j]=temp;
            j++;//number of swaps took place
        }
    }//Partitioning
    vec[start]=vec[j-1];
    vec[j-1]=pivot;//placing pivot in its right place
    return j-1;
 } 

/*.............................................................................
 * ~Vector() -- Destructor function, Deletes the allocated space              *
 * Args: None                                                                 *
 * Returns : None                                                             *
 * ...........................................................................*/
template <class T>
Vector<T>::~Vector(){
    if(vec)
        delete[] vec;
}

/*.............................................................................
 * queryProcess -- Processes the input query accordingly and gives the output *
 * Args: Query to be processed and vector                                     *
 * Returns : None                                                             *
 * ...........................................................................*/
template <class T>
void queryProcess(string query,Vector<T>& v){
    if(query=="push"){
        int x;
        cin>>x;
        v.push(x);
    }
    else if(query=="pop"){
        v.pop();
    }
    else if(query=="front"){
        int frontElem=v.front();
        cout<<frontElem<<endl;
    }
    else if(query=="back"){
        int backElem=v.back();
        cout<<backElem<<endl;
    }
    else if(query=="capacity"){
        size_t capacityOfv=v.capacity();
        cout<<capacityOfv<<endl;
    }
    else if(query=="size"){
        size_t sizeOfv=v.size();
        cout<<sizeOfv<<endl;
    }
    else if(query=="sort"){
        v.sort(0,v.size()-1);
        for(size_t i=0;i<v.size();i++){
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }
    else if(query=="element"){
        int x;
        cin>>x;
        int elem=v[x];
        cout<<elem<<endl;
    }
    return;
}

/*.................................................................................
 * main -- Takes input and produces required output using queryProcess function   *
 * Args: None                                                                     *
 * Returns : None                                                                 *
 * ...............................................................................*/
int main() {
    string str;
    int cap=0;
    int elemInitialize=0;
    getline(cin, str);
    if(str.size()==7 || str.size()==6){//if vector with no arguments
        Vector<int> v;//initialize
        int numOfQueries;
        cin>>numOfQueries;
        for(int q=0;q<numOfQueries;q++){
            string query;
            cin>>query;
            queryProcess(query,v);//do the query processing
        }
        return 0;
    }
    else{
        int i=7;
        while(str[i]!=' ' && str[i]!='\0'){
            i++;
        }
        for(int j=7;j<i;j++){
            cap=cap*10+(str[j]-48);//converting to integer capacity
        }
        if(str[i]!='\0'){//it is of form vector c x
            for(size_t m=i+1;m<str.size();m++){
                elemInitialize=elemInitialize*10+(str[m]-48);
            }//converting to integer x
            Vector<int> v(cap,elemInitialize);//initialize
            int numOfQueries;
            cin>>numOfQueries;
            for(int q=0;q<numOfQueries;q++){
                string query;
                cin>>query;
                queryProcess(query,v);//processing queries
            }
            return 0;
        }
        else{//it is of form vector c
            Vector<int> v(cap);//initialize
            int numOfQueries;
            cin>>numOfQueries;
            for(int q=0;q<numOfQueries;q++){
                string query;
                cin>>query;
                queryProcess(query,v);//processing queries
            }
            return 0;
        }
    }
    return 0;
}
