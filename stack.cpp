#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct ListNode{
    int elem;
    struct ListNode* next;
};

class Stack{
    private:
        ListNode L;
    public:
        void makeNull();
        void Push(int);
        int Pop();
        int Top();
        int isEmpty();
};

/*.............................................................................
 * makeNull -- initializes the stack                                          *
 * Args: None                                                                 *
 * Returns : None                                                             *
 * ...........................................................................*/
void Stack::makeNull()
{
    L.next = NULL;
}

/*.............................................................................
 * Push -- Pushes input element into stack                                    *
 * Args: element to be pushed                                                 *
 * Returns : None                                                             *
 * ...........................................................................*/
void Stack::Push(int x){
    struct ListNode* temp=L.next;
    L.next=new ListNode;
    L.next->next=temp;
    L.next->elem=x;
}

/*.............................................................................
 * Pop -- Pops the top element from the stack                                 *
 * Args: None                                                                 *
 * Returns : Popped element                                                   *
 * ...........................................................................*/
int Stack::Pop(){
    if(L.next==NULL){
        return -1;//if stack is empty
    }
    int ret=L.next->elem;
    L.next=L.next->next;
    return ret;
}

/*.............................................................................
 * Top -- Top most element of stack                                           *
 * Args: None                                                                 *
 * Returns : Top most element                                                 *
 * ...........................................................................*/
int Stack::Top(){
    if(L.next==NULL){
        return -1;//if stack is empty
    }
    return L.next->elem;
}

/*.............................................................................
 * isEmpty -- Checks if stack is empty                                        *
 * Args: None                                                                 *
 * Returns : 1 if empty 0 otherwise                                           *
 * ...........................................................................*/
int Stack::isEmpty(){
    if(L.next==NULL){
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    int Q;
    cin>>Q;
    Stack S;
    S.makeNull();
    for(int i=0;i<Q;i++){
        string Query;
        cin>>Query;
        if(Query=="push"){
            int element;
            cin>>element;
            S.Push(element);
        }
        if(Query=="pop"){
            int popped=S.Pop();
            cout<<popped<<endl;
        }
        if(Query=="top"){
            int TopElem=S.Top();
            cout<<TopElem<<endl;
        }
        if(Query=="empty"){
            int ifEmpty=S.isEmpty();
            cout<<ifEmpty<<endl;
        }
    }//Queries based on stack operations
    return 0;
}
