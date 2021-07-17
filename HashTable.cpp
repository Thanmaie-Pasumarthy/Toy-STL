#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct ElementType {
  int consonents;//number of consonents
  int vowels;//number of vowels
};

struct HashNode{
    string Key;
    ElementType pair;
};

class HashTable 
{
    public:
        void MakeHashTable(int);
        void HashTableResize(int);
        void HashTableInsert(string, ElementType); // create your own ElementType that stores number of vowels and consonants.
        ElementType HashTableDelete(string);
        ElementType HashTableFind(string);
        void PrintSizeAndCapacity();
        int getSize();
        int getCapacity();
        void printHashTable();
  		// add other nessasary member functions.	
    private:
        HashNode** hashTable; //define your own hash node structure or class to store Key, ElementType pair
        int capacity;
        int size;
};

/*.............................................................................
 * printElementType -- Prints vowels and consonents of input elementtype      *
 * Args: An elementtype                                                       *
 * Returns : None                                                             *
 * ...........................................................................*/

void printElementType(ElementType e){
    if(e.consonents==0 && e.vowels==0)
        cout<<"Not Found\n";
    else
        cout<<"Consonants: "<<e.consonents<<" Vowels: "<<e.vowels<<"\n";
}

/*.............................................................................
 * printNode -- Prints the Key and pair of input node                         *
 * Args: A HashNode                                                           *
 * Returns : None                                                             *
 * ...........................................................................*/

void printNode(HashNode node){
    cout<<"Key is "<<node.Key<<endl;
    cout<<"Pair is ";
    printElementType(node.pair);
}

/*.............................................................................
 * findValue -- Finds the hash function value of given input key              *
 * Args: Key string                                                           *
 * Returns : Hash value of input key string                                   *
 * ...........................................................................*/

int findValue(string key){
    int length=key.size();
    int value=0;
    for(int i=0;i<length;i++){
       value=value+key[i]; //add every element value
    }
    return value;
}

/*.............................................................................
 * findPair -- Finds the corresponding elementtype of input key               *
 * Args: key string                                                           *
 * Returns : Corresponding elementtype of input key                           *
 * ...........................................................................*/

ElementType findPair(string key){
    int length=key.size();
    ElementType e;
    e.vowels=0;
    for(int i=0;i<length;i++){
        if(key[i]=='a'||key[i]=='e'||key[i]=='i'||key[i]=='o'||key[i]=='u'){
            e.vowels++;//number of vowels
        }
    }
    e.consonents=length-e.vowels;//number of consonents
    return e;
}

/*.............................................................................
 * printHashTable -- Prints the hashtable                                     *
 * Args: None                                                                 *
 * Returns : None                                                             *
 * ...........................................................................*/

void HashTable::printHashTable(){
    cout<<"Capacity: "<<capacity<<endl;
    cout<<"Size: "<<size<<endl;
    for(int i=0;i<capacity;i++){
        printNode(*(hashTable[i]));
    }
}

/*.............................................................................
 * MakeHashTable -- Creates a new hashtable of input size                     *
 * Args: Size of hashtable                                                    *
 * Returns : None                                                             *
 * ...........................................................................*/

void HashTable::MakeHashTable(int n){
    hashTable=new HashNode*[n];//new hash nodes addresses
    capacity=n;
    size=0;
    for(int i=0;i<capacity;i++){
        hashTable[i]=new HashNode;//new hash nodes
        hashTable[i]->Key = "";//initializing
        ElementType e;
        e.vowels = 0;
        e.consonents = 0;
        hashTable[i]->pair = e;
    }
}

/*............................................................................................
 * HashTableResize -- Creates a new hashtable of input size and copies elements to it        *
 * Args: Size of hashtable to be created                                                     *
 * Returns : None                                                                            *
 * ..........................................................................................*/

void HashTable::HashTableResize(int n){
    HashNode** copyTable;
    copyTable=new HashNode*[capacity];//space allocation
    copyTable=hashTable;//copying elements into it
    int oldCapacity=capacity;
    MakeHashTable(n);//new table of required size
    for(int i=0;i<oldCapacity;i++){
        if(copyTable[i]->Key.compare("")!=0){//neither empty nor deleted
            HashTableInsert(copyTable[i]->Key, copyTable[i]->pair);//insert elements
        }
    }
}

/*...........................................................................................................
 * HashTableInsert -- Inserts the input key and its elementtype if already not present in hashtable         *
 * Args: Key to be inserted and corresponding elementtype to be inserted                                    *
 * Returns : None                                                                                           *
 * .........................................................................................................*/

void HashTable::HashTableInsert(string key, ElementType x){
    ElementType compare = HashTableFind(key);
    if(compare.consonents!=0 || compare.vowels!=0){
        return;//already present in table
    }
    int value=findValue(key);
    while(1){
        value=value%capacity;
        if(hashTable[value]->Key.compare("")==0){
            hashTable[value]->Key=key;//first key with that value
            hashTable[value]->pair=x;
            break;
        }
        value++;//open hashing
    }
    size++;
    if(2*size>capacity){
        int newCapacity = 2*capacity;//resizing when required
        HashTableResize(newCapacity);
    }
    return;
}

/*.............................................................................
 * HashTableDelete -- Deletes the input string if found in hashtable          *
 * Args: Key to be deleted                                                    *
 * Returns : Element type corresponding to input key                          *
 * ...........................................................................*/

ElementType HashTable::HashTableDelete(string key){
    ElementType ret;//return elementtype
    ret.consonents = 0;
    ret.vowels = 0;
    ElementType del;
    del.consonents = -1;//flag for deleted element position
    del.vowels = -1;
    int value=findValue(key);
    int mark=value%capacity;
    value = mark;
    if(hashTable[value]->Key.compare(key)==0){
        ElementType e = hashTable[value]->pair;//element found
        hashTable[value]->Key = "";
        hashTable[value]->pair = del;
        size--;
        if(4*size<capacity){//resizing when required
            int newCapacity=capacity/2;
            HashTableResize(newCapacity);
        }
        ret = e;
        return ret;
    }
    ElementType empty = hashTable[value]->pair;
    if(empty.vowels==0&&empty.consonents==0){//null node
        return ret;//check till null(not deleted) node is reached
    }
    value++;
    value=value%capacity;
    while(value!=mark){
        ElementType empty = hashTable[value]->pair;
        if(empty.vowels==0&&empty.consonents==0){//null node
            return ret;//check till null(not deleted) node is reached
        }
        if(hashTable[value]->Key.compare(key)==0){
            ElementType e = hashTable[value]->pair;
            hashTable[value]->Key = "";
            hashTable[value]->pair = del;
            size--;
            if(4*size<capacity){//resizing when required
                int newCapacity=capacity/2;
                HashTableResize(newCapacity);
            }
            ret = e;
            return ret;
        }
        value++;//check next  elements
        value=value%capacity;
    }
    return ret;
}

/*.............................................................................
 * HashTableFind -- Finds if the input string is present in hashtable         *
 * Args: Key to be found                                                      *
 * Returns : Element type corresponding to input key                          *
 * ...........................................................................*/


ElementType HashTable::HashTableFind(string key){
    ElementType ret;//return elementtype
    ret.consonents = 0;
    ret.vowels = 0;
    int value=findValue(key);
    int mark=value%capacity;
    value = mark;
    if(hashTable[value]->Key.compare(key)==0){
        return hashTable[value]->pair;//if found
    }
    ElementType empty = hashTable[value]->pair;
    if(empty.vowels==0&&empty.consonents==0){
        return ret;//check until null node is reached
    }
    value++;//check next ones
    value=value%capacity;
    while(value!=mark){
        empty = hashTable[value]->pair;
        if(empty.vowels==0&&empty.consonents==0){
            return ret;
        }
        if(hashTable[value]->Key.compare(key)==0){
            return hashTable[value]->pair;
        }
        value++;
        value=value%capacity;
    }
    return ret;
}

/*.............................................................................
 * PrintSizeAndCapacity -- Prints size and capacity of hashtable              *
 * Args: None                                                                 *
 * Returns : None                                                             *
 * ...........................................................................*/


void HashTable::PrintSizeAndCapacity(){
    cout<<"size ="<<size<<" capacity ="<<capacity<<"\n";
}

/*.............................................................................
 * main -- Prints the required result                                         *
 * Args: None                                                                 *
 * Returns : None                                                             *
 * ...........................................................................*/


int main() {
    int numOfOp;//number of operations to be done
    cin>>numOfOp;
    HashTable Table;
    ElementType elem;
    Table.MakeHashTable(2);//create table with size 2
    for(int i=0;i<numOfOp;i++){
        int code;
        string key;
        cin>>code;
        switch(code){
            case(1):
                cin>>key;
                elem=findPair(key);
                Table.HashTableInsert(key,elem);
                break;
            case(2):
                cin>>key;
                elem = Table.HashTableFind(key);
                printElementType(elem);
                break;
            case(3):
                cin>>key;
                Table.HashTableDelete(key);
                break;
            case(4):
                Table.PrintSizeAndCapacity();
                break;
            default:
                cout<<"Error in input\n";
                break;
        }
    }
    return 0;
}

