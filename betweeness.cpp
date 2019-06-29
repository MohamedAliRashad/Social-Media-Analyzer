//
//  main.cpp
//  graphs
//
//  Created by MAK on 5/20/19.
//  Copyright © 2019 MAK. All rights reserved.
//

#include <iostream>
#include <queue>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include <iomanip> 
#include<list> 
using namespace std;

//const int NULL_EDGE = 0;
    class GraphType {
private:
    int numVertices;
    int maxVertices;
    int * vertices;
    int **edges;
    bool* marks;
public:
    GraphType(int);
    ~GraphType();
    void AddEdge(int, int, int);
    int WeightIs(int,int);
    void DepthFirstSearch(int start_vert,int end_vert);
     void BreadsFirstSearch(int start_vert,int end_vert);
    void ClearMarks();
    void GetToVertices(int, queue<int>&);
    bool IsMarked(int num){
        
        return marks[num] ? true:false;
    }
    void MarkVertex(int x){
        
        marks[x]=true;
    }
    int Closeness(int);
     int betweenness();
};

int main() {







int nodes_num,vert_num;
int s,d,w;
cin>>nodes_num>>vert_num;

GraphType g(nodes_num);

for (int i = 0; i < vert_num; ++i)
{  cin>>s>>d>>w;
    g.AddEdge(s,d,w);
}
g.betweenness();


    return 0;
}


 GraphType::GraphType(int maxV) {
    numVertices = maxV;
    maxVertices = maxV; 
    vertices = new int[maxV];
    edges = new  int * [maxV];
    for(int i = 0; i < maxV; i++)
    edges[i] = new int[maxV];

    marks = new bool[maxV];
    
    for (int i = 0; i < maxV; ++i)
    {
        for (int j = 0; j < maxV; ++j)
        {
            edges[i][j]=-1;
        }
    }



}


  GraphType::~GraphType() {
    delete [] vertices;
    for(int i = 0; i < maxVertices; i++)
    delete [] edges[i];
    delete [] edges;
    delete [] marks;
    }

void GraphType::AddEdge(int fromVertex,int toVertex,int weight)
{
    edges[fromVertex][toVertex] = weight;
    edges[toVertex][fromVertex] = weight;
}

int GraphType:: WeightIs(int fromVertex, int toVertex)
{
    return edges[fromVertex][toVertex];
}

 void GraphType :: ClearMarks(){
    
    for (int i=0 ; i< numVertices; i++) {
        marks[i]=false;
    }
}



void GraphType :: GetToVertices(int vertex,queue<int>& adjvertexQ)
{

    for( int toIndex = 0; toIndex < numVertices; toIndex++)
        if(edges[vertex][toIndex] != -1)
         adjvertexQ.push(toIndex);
}


void GraphType ::DepthFirstSearch(int start_vert,int end_vert){
    
        
    stack<int>st;
    queue<int>qe;
    
    bool found = false;
    
    int vertex;
    int item;
    
    ClearMarks();
    MarkVertex(start_vert);
    st.push(start_vert);
    
    do{
        
        vertex=st.top();
        st.pop();
        
        if(vertex == end_vert)
            found = true;
        
        else{
            
                GetToVertices(vertex,qe);
                while(!qe.empty()) {
                    item = qe.front();
                    qe.pop();
                    if(!IsMarked(item)){
                        MarkVertex(item);
                        st.push(item);
                    }
                    
                }
                
                
            
        }
    }while( !st.empty()  && !found);
    
    if(!found)
        cout << "Path not found" << endl;
    else
        cout<<"founded"<<endl;
    
}



void GraphType ::BreadsFirstSearch(int start_vert,int end_vert){
    
    queue<int>st;
    queue<int>qe;
    
    bool found = false;
    
    int vertex;
    int item;
    
    ClearMarks();
    MarkVertex(start_vert);
    st.push(start_vert);
    
    do{
        
        vertex=st.front();
        st.pop();
        
        if(vertex == end_vert)
            found = true;
        
        else{
            
                GetToVertices(vertex,qe);
                while(!qe.empty()) {
                    item = qe.front();
                    qe.pop();
                    if(!IsMarked(item)){
                        MarkVertex(item);
                        st.push(item);
                    }
                    
                }
                
                
            
        }
    }while( !st.empty()  && !found);
    
    if(!found)
        cout << "Path not found" << endl;
    else
        cout<<"founded"<<endl;
    
    
}


 int GraphType :: Closeness(int sour){
    priority_queue< pair<int , pair<int , int> > , vector<pair<int , pair<int , int> > >,
    greater< pair<int , pair<int , int> > > > nodes_q ;

    vector<int> d(numVertices, 100000000);
    vector<int> pp(numVertices, -1);
    
     nodes_q.push(make_pair(0,make_pair(sour,sour))); 

        while(!nodes_q.empty()){
            
            pair<int , pair<int , int> > p = nodes_q.top ();
            
            nodes_q.pop();
            
            int cur_node = p.second.first ;
            int cur_prev_node = p.second.second ;
            int cur_dis= p.first;
            
           
            
            if (d[cur_node] != 100000000 )
                continue ;
            
            
            pp[cur_node] = cur_prev_node;
            d[cur_node] = cur_dis;
            

            
            for (int i=0; i< numVertices; i++){
                
                if( WeightIs(cur_node,i) != -1)
                {
                    
                int next_node = i;
                int weight = WeightIs(cur_node,i);
                
                if (d[next_node] != 100000000)
                    continue ;
                nodes_q.push(make_pair(cur_dis + weight,make_pair(next_node,cur_node)));   
                
                }
            }

               


            }
            

                int dist=0;
            for (int i=0; i< numVertices; i++){

                    dist+=d[i];
                }
            
            cout<<setprecision(10)<<(double)(numVertices - 1)/dist<<"\n";

        
    
    return  -1;
}







 int GraphType ::betweenness(){

    priority_queue< pair<int , pair<int , int> > , vector<pair<int , pair<int , int> > >,
    greater< pair<int , pair<int , int> > > > nodes_q ;
   
    vector< list <pair<int ,int> > > matr(numVertices);
    for (int i = 0; i < numVertices; ++i)
    {
    vector<int> d(numVertices, 100000000);
    vector< list< int > > pp(numVertices);
    nodes_q.push(make_pair(0,make_pair(i,i))); 

        while(!nodes_q.empty()){
            
            pair<int , pair<int , int> > p = nodes_q.top ();
            
            nodes_q.pop();
            
            int cur_node = p.second.first ;
            int cur_prev_node = p.second.second ;
            int cur_dis= p.first;
            
           
            
           if (d[cur_node] == cur_dis )
            {
              pp[cur_node].push_back(cur_prev_node);
              continue;
            }
            
            if (d[cur_node] != 100000000 )
                continue ;
            
            
            pp[cur_node].push_back(cur_prev_node);
            d[cur_node] = cur_dis;
            

            
            for (int i=0; i< numVertices; i++){
                
                if( WeightIs(cur_node,i) != -1)
                {
                    
                int next_node = i;
                int weight = WeightIs(cur_node,i);
                
                if (d[next_node] != 100000000)
                    continue ;
                nodes_q.push(make_pair(cur_dis + weight,make_pair(next_node,cur_node)));   
                
                }
            }

               


            }

            for (int i = 0; i < numVertices; ++i)
            {
                double b=0;
                for ( list< int > :: iterator it = pp[i].begin(); it != pp[i].end(); ++it)
                {
               // cout<<*it<<" ";
                }
               //cout<<endl;
            }
           
            //////////////////////////////////////
            
            
            for (int k = i+1; k < numVertices; ++k)
            {   
            
                list<int> :: iterator  it;
                stack<int> st1 ,st2;
                vector<int> path(numVertices,0);
                vector<int> counter(numVertices,0);
             
                int path_num=0;
                int node;
                //path[i]=1;
                st1.push(k);
                while(!st1.empty()){
                    node=st1.top();
                    st1.pop();
                    st2.push(node);
                    for (list<int> :: iterator it = pp[node].begin() ; it != pp[node].end(); ++it){
                    
                     if(*it == i)
                        continue;

                     st1.push(*it);                        
                    
                    }
                }

                
                if (st2.empty())
                {
                    path[k]=1;
                    continue;
                }


                while(!st2.empty()){
                   
                    node=st2.top();
                    st2.pop();

                    if(pp[node].size() == 1  &&  *(pp[node].begin()) == i){
                        path[node]=1;
                        counter[node]++;
                        continue;

                        }
                    
                        int num=0;
                        
                        for (it = pp[node].begin(); it != pp[node].end(); ++it)
                        {   
                            num+=path[*it];
                        }

                        path[node]=num;
                        counter[node]++;
                        }
                        
                        for (int z = 0; z < numVertices ; z++)
                        {
                            if (z == i  || z==k)
                            continue;

                        if (path[z] != 0)
                        {
                            pair<int , int >p;
                            p.first=path[z]*counter[z];
                            p.second=path[k];
                            matr[z].push_back(p);
                        }

                        }

            }
            

            }


        

         for (int i = 0; i < numVertices; ++i)
            {
                double b=0;
                for ( list<pair<int,int> > :: iterator it = matr[i].begin(); it != matr[i].end(); ++it)
                {
                b+= (double)it->first / it->second ;
                //cout<<it->first<<"   "<<it->second<<"  ";
                }
                //cout<<endl;
                cout<<setprecision(9)<<b<<"\n";
            }


    
    return  -1;
}
