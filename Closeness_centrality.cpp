//
//  main.cpp
//  graphs
//
//  Created by MAK on 5/20/19.
//  Copyright © 2019 MAK. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//const int NULL_EDGE = 0;
class GraphType
{
private:
    int numVertices;
    int maxVertices;
    int *vertices;
    int **edges;
    bool *marks;

public:
    GraphType(int);
    ~GraphType();
    void AddEdge(int, int, int);
    int WeightIs(int, int);
    void DepthFirstSearch(int start_vert, int end_vert);
    void BreadsFirstSearch(int start_vert, int end_vert);
    void ClearMarks();
    void GetToVertices(int, queue<int> &);
    bool IsMarked(int num)
    {

        return marks[num] ? true : false;
    }
    void MarkVertex(int x)
    {

        marks[x] = true;
    }
    int Closeness(int);
};

int main()
{
    char node[10], vert[10];
    char sour[10], dist[10], wight[10];
    int s, d, w;
    fstream f1;
    f1.open("graph.txt", ios::in);
    if (!f1.is_open())
        cout << "some thing wrong" << endl;
    f1.getline(node, 50, ' ');
    f1.getline(vert, 50);
    int nodes_num = stoi(node);
    int vert_num = stoi(vert);

    GraphType g(nodes_num);

    for (int i = 0; i < vert_num; ++i)
    {
        f1.getline(sour, 50, ' ');
        f1.getline(dist, 50, ' ');
        f1.getline(wight, 50);
        s = stoi(sour);
        d = stoi(dist);
        w = stoi(wight);
        g.AddEdge(s, d, w);
    }
    f1.close();
    for (int i = 0; i < nodes_num; ++i)
    {
        g.Closeness(i);
    }

    return 0;
}

GraphType::GraphType(int maxV)
{
    numVertices = maxV;
    maxVertices = maxV;
    vertices = new int[maxV];
    edges = new int *[maxV];
    for (int i = 0; i < maxV; i++)
        edges[i] = new int[maxV];

    marks = new bool[maxV];

    for (int i = 0; i < maxV; ++i)
    {
        for (int j = 0; j < maxV; ++j)
        {
            edges[i][j] = -1;
        }
    }
}

GraphType::~GraphType()
{
    delete[] vertices;
    for (int i = 0; i < maxVertices; i++)
        delete[] edges[i];
    delete[] edges;
    delete[] marks;
}

void GraphType::AddEdge(int fromVertex, int toVertex, int weight)
{
    edges[fromVertex][toVertex] = weight;
    edges[toVertex][fromVertex] = weight;
}

int GraphType::WeightIs(int fromVertex, int toVertex)
{
    return edges[fromVertex][toVertex];
}

void GraphType ::ClearMarks()
{

    for (int i = 0; i < numVertices; i++)
    {
        marks[i] = false;
    }
}

void GraphType ::GetToVertices(int vertex, queue<int> &adjvertexQ)
{

    for (int toIndex = 0; toIndex < numVertices; toIndex++)
        if (edges[vertex][toIndex] != -1)
            adjvertexQ.push(toIndex);
}

void GraphType ::DepthFirstSearch(int start_vert, int end_vert)
{

    stack<int> st;
    queue<int> qe;

    bool found = false;

    int vertex;
    int item;

    ClearMarks();
    MarkVertex(start_vert);
    st.push(start_vert);

    do
    {

        vertex = st.top();
        st.pop();

        if (vertex == end_vert)
            found = true;

        else
        {

            GetToVertices(vertex, qe);
            while (!qe.empty())
            {
                item = qe.front();
                qe.pop();
                if (!IsMarked(item))
                {
                    MarkVertex(item);
                    st.push(item);
                }
            }
        }
    } while (!st.empty() && !found);

    if (!found)
        cout << "Path not found" << endl;
    else
        cout << "founded" << endl;
}

void GraphType ::BreadsFirstSearch(int start_vert, int end_vert)
{

    queue<int> st;
    queue<int> qe;

    bool found = false;

    int vertex;
    int item;

    ClearMarks();
    MarkVertex(start_vert);
    st.push(start_vert);

    do
    {

        vertex = st.front();
        st.pop();

        if (vertex == end_vert)
            found = true;

        else
        {

            GetToVertices(vertex, qe);
            while (!qe.empty())
            {
                item = qe.front();
                qe.pop();
                if (!IsMarked(item))
                {
                    MarkVertex(item);
                    st.push(item);
                }
            }
        }
    } while (!st.empty() && !found);

    if (!found)
        cout << "Path not found" << endl;
    else
        cout << "founded" << endl;
}

int GraphType ::Closeness(int sour)
{
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                   greater<pair<int, pair<int, int>>>>
        nodes_q;

    vector<int> d(numVertices, 100000000);
    vector<int> pp(numVertices, -1);

    nodes_q.push(make_pair(0, make_pair(sour, sour)));

    while (!nodes_q.empty())
    {

        pair<int, pair<int, int>> p = nodes_q.top();

        nodes_q.pop();

        int cur_node = p.second.first;
        int cur_prev_node = p.second.second;
        int cur_dis = p.first;

        if (d[cur_node] != 100000000)
            continue;

        pp[cur_node] = cur_prev_node;
        d[cur_node] = cur_dis;

        for (int i = 0; i < numVertices; i++)
        {

            if (WeightIs(cur_node, i) != -1)
            {

                int next_node = i;
                int weight = WeightIs(cur_node, i);

                if (d[next_node] != 100000000)
                    continue;
                nodes_q.push(make_pair(cur_dis + weight, make_pair(next_node, cur_node)));
            }
        }
    }

    int dist = 0;
    for (int i = 0; i < numVertices; i++)
    {

        dist += d[i];
        //cout<<i<<"  "<<d[i]<<endl;
    }

    cout << (float)(numVertices - 1) / dist << endl;

    return -1;
}
