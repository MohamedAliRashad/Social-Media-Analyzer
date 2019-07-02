#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include <algorithm> 
#include <set>

#define INF 99999

using namespace std;


float Betweenness(vector<vector<int>> S, int V)
{
    float Result = 0;
    set<int> x;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i][0] == INF)
            continue;
        for (int j = 0; j < S[i].size(); j++)
        {
            if (S[i][j] == V && V != i)
            {
                cout << i << endl;
                Result += 1 / (float)S[i].size() + Betweenness(S, i);
            }
        }
    }
    return Result;
}

set<vector<int>> paths(vector<vector<int>> S, int node){
    set<vector<int>> p;
    for (int i = 0; i < S.size(); i++){
        if (S[i][0] == INF)
            continue;
        if (S[i][0] == i){
            vector<int> x;
            x.push_back(node);
            x.push_back(i);
            p.insert(x);
        }
    }
    for (int i = 0; i < S.size(); i++){
        if (S[i][0] == INF || S[i][0] == i)
            continue;
        for (int j = 0; j < S[i].size(); j++){
            set<vector<int>>::iterator it = p.begin();
            while (it != p.end()){
                if((*it).back() == S[i][j]){
                    vector<int> y = (*it);
                    y.push_back(i);
                    p.insert(y);
                }
                it++;
            }
        }
    }
    return p;
}

void printMatrix(vector<vector<int>> G)
{
    int NVer = G.size();
    for (int i = 0; i < NVer; i++)
    {
        for (int j = 0; j < NVer; j++)
        {
            if (G[i][j] == INF)
                cout << "INF"
                     << "\t";
            else
                cout << G[i][j] << "\t";
        }
        cout << endl;
    }
}

void printMatrix(vector<vector<vector<int>>> G)
{
    int NVer = G.size();
    for (int i = 0; i < NVer; i++)
    {
        for (int j = 0; j < NVer; j++)
        {
            for (int k = 0; k < G[i][j].size(); k++)
            {
                if (G[i][j][k] == INF)
                    cout << "INF";
                else
                    cout << G[i][j][k] << ",";
            }
            cout << "\b \t";
        }
        cout << endl;
    }
}

void printPath(vector<vector<vector<int>>> p, vector<vector<int>> S)
{
    int N = S.size();
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (S[i][j] == INF || i == j)
                continue;
            cout << i << " -> ";
            for (int k = 0; k < p[i][j].size(); k++)
            {
                cout << p[i][j][k] << " -> ";
            }
            cout << j << endl;
        }
    }
}

void printPath(set<vector<int>> p)
{
    for (auto path: p)
    {
        for (auto elem: path)
        {
            cout << elem << " -> ";
        }
        cout << "\b\b\b\b    " << endl;
    }
}

int main(void)
{
    int NumVer, NumEdg;
    fstream f1;
    f1.open("graph3.txt", ios::in);
    if (!f1.is_open())
    {
        cout << "some thing wrong" << endl;
        exit(1);
    }
    f1 >> NumVer >> NumEdg;

    vector<vector<int>> Distance(NumVer, vector<int>(NumVer, INF));

    for (int i = 0; i < NumVer; i++)
    {
        Distance[i][i] = 0;
    }

    for (int i = 0; i < NumEdg; i++)
    {
        int node1, node2, edge;
        f1 >> node1 >> node2 >> edge;
        if (node1 == node2)
            continue;
        if (Distance[node1][node2] > edge)
            Distance[node1][node2] = Distance[node2][node1] = edge;
    }

    vector<vector<vector<int>>> Sequence(NumVer, vector<vector<int>>(NumVer, vector<int>(1, INF)));

    for (int i = 0; i < NumVer; i++)
    {
        for (int j = i + 1; j < NumVer; j++)
        {
            vector<int> x;
            x.push_back(j);
            Sequence[i][j] = x;
        }
    }

    vector<vector<int>> Adj = Distance;
    // printMatrix(Distance);

    for (int k = 0; k < NumVer; k++)
    {
        for (int i = 0; i < NumVer; i++)
        {
            for (int j = i + 1; j < NumVer; j++)
            {
                if (Distance[i][k] + Distance[k][j] == Distance[i][j] && i != j && i != k && j != k && Adj[k][j] != INF)
                {
                    Sequence[i][j].push_back(k);
                    // Sequence[j][i] = Sequence[i][j];
                    continue;
                }
                if (Distance[i][k] + Distance[k][j] < Distance[i][j])
                {
                    vector<int> x;
                    Distance[i][j] = Distance[j][i] = Distance[i][k] + Distance[k][j];
                    x.push_back(k);
                    Sequence[i][j] = Sequence[i][j] = x;
                }
            }
        }
    }

    // for (int i = 0; i < NumVer; i++){
    //     for (int j = i + 1; j < NumVer; j++){
    //         if (Sequence[j][i].size() > 1)
    //             continue;
    //         if (Sequence[i][j][0] == j)
    //             Sequence[j][i][0] = i;
    //         else
    //         {
    //             Sequence[j][i] = Sequence[i][j];
    //         }   
    //     }
    // }
    // set<vector<int>> path = paths(Sequence[0], 0);
    // for (set<vector<int>>::iterator it = path.begin(); it != path.end(); it++){
    //     if ((*it).size() <= 2){
    //         path.erase(it);
    //     }
    // }
    // printPath(path);
    // vector<vector<int>> S = Sequence[0];
    // for (int x = 0; x < NumVer; x++){
    //     if (S[x][0] == INF || S[x][0] == x)
    //         continue;
    //     for (int k = 0; k < S[x].size(); k++){
    //         int m = S[S[x][k]][0];
    //         cout << "Here " << m << endl;
    //         if (m == INF || m == S[m][0])
    //             continue;
    //         S[x].erase(S[x].begin() + k);
    //         S[x].insert(S[x].begin() + k, S[S[x][k]].begin(), S[S[x][k]].end());
    //         vector<int>::iterator it;
    //         it = unique(S[x].begin(), S[x].end());
    //         S[x].resize( std::distance(S[x].begin(),it) );
    //     }
    // }
    // printMatrix(Sequence);
    // printMatrix(Distance);

    // printPath(paths(Sequence[0], 0));
    // for (int i = 0; i < NumVer; i++){
    //     for (int j = i + 1; j < NumVer; j++){
    //         for (int k = 0; k < Sequence[i][j].size(); k++){
    //             int m = Sequence[i][j][k];
    //             // cout << j << endl;
    //             if (m == j || Sequence[i][m][0] == m || Sequence[i][m][0] == INF)
    //                 continue;
    //             Sequence[i][j].erase(remove(Sequence[i][j].begin(), Sequence[i][j].end(), m));
    //             Sequence[i][j].insert(Sequence[i][j].begin(), Sequence[i][m].begin(), Sequence[i][m].end());
    //         }
    //     }
    // }
    // printMatrix(Sequence);
    // printPath(Sequence, Distance);

    vector<float> Result(NumVer);
    for (int i = 0; i < NumVer; i++)
    {
        set<vector<int>> x = paths(Sequence[i], i);
        for (set<vector<int>>::iterator it = x.begin(); it != x.end(); it++){
            if ((*it).size() <= 2){
                x.erase(it);
            }
        }
        for (auto z: x){
            vector<int>::iterator it = find(z.begin() + 1, z.end() - 1, )
        }
    }

    for (auto r: Result){
        cout << r << endl;
    }

    // for (int i = 0; i < NumVer; i++)
    // {
    //     float Result = 0;
    //     for (int j = 0; j < NumVer; j++){
    //         Result += Betweenness(Sequence[j], i);
    //     }
    //     cout << Result << endl;
    // }
    f1.close();
    return 0;
}
