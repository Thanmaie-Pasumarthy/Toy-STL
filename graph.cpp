#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int vertices;
    int adjMatrix[100][100];
    int dfsVisit[100];
    public:
        void constructor(int);
        void setVertices(int);
        void operator +=(pair<int ,int >);
        void operator -=(pair<int ,int >);
        int dfsCheck(int);
        int detectCycle();
        int components();
        int reach(int,int);
};

/*.............................................................................
 * constructor -- Initializes the graph                                       *
 * Args: Number of vertices                                                   *
 * Returns : None                                                             *
 * ...........................................................................*/
void Graph::constructor(int vertices){
    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++){
            adjMatrix[i][j]=0;//initialized to 0
        }
    }
    for(int i=0;i<vertices;i++){
        dfsVisit[i]=-1;//initialized to -1
    }
    return;
}

/*.............................................................................
 * setVertices -- Sets input number to vertices                               *
 * Args: Number of vertices                                                   *
 * Returns : None                                                             *
 * ...........................................................................*/
void Graph::setVertices(int numOfVertices){
    vertices=numOfVertices;
}

/*.............................................................................
 * operator += -- Adds edge to the matrix                                     *
 * Args: Pair of vertices between which edge should be added                  *
 * Returns : None                                                             *
 * ...........................................................................*/
void Graph::operator+=(pair <int,int> Addpair){
    int u=Addpair.first;
    int v=Addpair.second;
    adjMatrix[u][v]=1;
    adjMatrix[v][u]=1;
    return;
}

/*.............................................................................
 * operator -= -- Deletes edge from the graph                                 *
 * Args: Pair of vertices between which edge should be deleted                *
 * Returns : None                                                             *
 * ...........................................................................*/
void Graph::operator-=(pair <int,int> Delpair){
    int u=Delpair.first;
    int v=Delpair.second;
    adjMatrix[u][v]=0;
    adjMatrix[v][u]=0;
    return;
}

/*.............................................................................
 * dfsCheck -- Performs dfs starting from input vertex                        *
 * Args: Vertex from which dfs need to be started                             *
 * Returns : 1 if it has cycle in that connected component 0 otherwise        *
 * ...........................................................................*/
int Graph::dfsCheck(int u){
    /*......................................................*
     * dfsVisit[i] is -1 if i is not yet started processing *
     *                0 if it is in processing              *
     *                1 if the processing is done           *
     *......................................................*/
    dfsVisit[u]=0;
    for(int j=0;j<vertices;j++){
        if(adjMatrix[u][j]){
            if(dfsVisit[j]==-1){//if not visited
                dfsCheck(j);//recursive function
            }
            else if(dfsVisit[j]){//if already visited
                return 1;//has cycle
            }
        }
    }
    dfsVisit[u]=1;
    return 0;
}

/*.............................................................................
 * detectCycle -- Detects if the graph has a cycle                            *
 * Args: None                                                                 *
 * Returns : 1 if graph has cycle 0 otherwise                                 *
 * ...........................................................................*/
int Graph::detectCycle(){
    for(int i=0;i<vertices;i++){
        if(dfsVisit[i]==-1){//not yet processed
            int hasCycle=dfsCheck(i);
            if(hasCycle){
                for(int i=0;i<vertices;i++){
                    dfsVisit[i]=-1;
                }//after completition again set to initial values
                return 1;//Has cycle
            }
        }
    }
    for(int i=0;i<vertices;i++){
        dfsVisit[i]=-1;//after completition again set to initial values
    }
    return 0;
}

/*.............................................................................
 * components -- computes number of connected components in graph             *
 * Args: None                                                                 *
 * Returns : Number of components of the graph                                *
 * ...........................................................................*/
int Graph::components(){
    int visited[vertices];
    stack<int> SComp;
    int noOfComponents=0;
    for(int i=0;i<vertices;i++){
        visited[i]=-1;
    }
    int count=0;
    while(count<vertices){
        noOfComponents++;//every time we eneter the loop number of components increase
        int i =0;
        for(i=0;i<vertices;i++){
            if(visited[i]==-1){
                SComp.push(i);
                visited[i]=0;
                break;
            }
        }//search for unvisited vertex
        while(!SComp.empty()){
            int presentVar=SComp.top();
            SComp.pop();
            for(int i=0;i<vertices;i++){
                if(adjMatrix[presentVar][i]){
                    if(visited[i]==-1){
                        SComp.push(i);
                        visited[i]=0;
                    }
                }
            }
            visited[presentVar]=1;
            count++;
        }//Do exhaustive dfs starting from one vertex
    }
    return noOfComponents;
}

/*.............................................................................
 * reach -- Check if there is a path between two input vertices               *
 * Args: Both the vertices between which path needs to be found               *
 * Returns : 1 if there is a path 0 otherwise                                 *
 * ...........................................................................*/
int Graph::reach(int u, int v){
    int visited[vertices];
    stack<int> SReach;
    for(int i=0;i<vertices;i++){
        visited[i]=-1;
    }
    SReach.push(u);
    visited[u]=0;//start dfs from u
    while(!SReach.empty()){
        int presentVar=SReach.top();
        SReach.top();
        for(int i=0;i<vertices;i++){
            if(adjMatrix[presentVar][i]){
                if(visited[i]==-1){
                    if(i==v){
                        return 1;//if v is found in dfs then reach is 1
                    }
                    SReach.push(i);
                    visited[i]=0;//else continue searching
                }
            }
        }
        visited[presentVar]=1;
    }
    return 0;
}

/*.............................................................................
 * main -- Takes input and prints result in required format                   *
 * Args: None                                                                 *
 * Returns : None                                                             *
 * ...........................................................................*/
int main() {
    Graph G;
    int n,m;
    cin>>n;
    G.constructor(n);
    G.setVertices(n);
    cin>>m;
    for(int i=0;i<m;i++){
        string queryGraph;
        cin>>queryGraph;
        if(queryGraph=="add"){
            int u,v;
            cin>>u>>v;
            pair<int,int> pAdd;
            pAdd.first=u;
            pAdd.second=v;
            G+=pAdd;
        }
        if(queryGraph=="del"){
            int u,v;
            cin>>u>>v;
            pair<int,int> pDel;
            pDel.first=u;
            pDel.second=v;
            G-=pDel;
        }
        if(queryGraph=="cycle"){
            int cycleDetect=G.detectCycle();
            cout<<cycleDetect<<endl;
        }
        if(queryGraph=="components"){
            int noOfComp=G.components();
            cout<<noOfComp<<endl;
        }
        if(queryGraph=="reach"){
            int u,v;
            cin>>u>>v;
            int canReach=G.reach(u,v);
            cout<<canReach<<endl;
        }
    }//Queries based on graph operations
    return 0;
}
