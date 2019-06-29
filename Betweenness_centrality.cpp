#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <string>

#define INF 99999

using namespace std;

float Betweenness(vector<vector<int>> S, int V)
{
    float Result = 0;
    for (int i = 0; i < S.size(); i++){
        if (S[i][0] == INF)
            continue;
        for (int j = 0; j < S[i].size(); j++){
            if (S[i][j] == V && V != i){
                // cout << i << endl;
                Result += 1 / (float) S[i].size() + (1 / (float) S[i].size()) * Betweenness(S, i);
            }
        }
    }
    return Result;
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

void printPath(vector<vector<vector<vector<int>>>> p, vector<vector<int>> S)
{
    int N = S.size();
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (S[i][j] == INF || i == j)
                continue;
            for (int m = 0; m < p[i][j].size(); m++)
            {
                cout << i << " -> ";
                for (int k = 0; k < p[i][j][m].size(); k++)
                {
                    cout << p[i][j][m][k] << " -> ";
                }
                cout << j << endl;
            }
        }
    }
}

int main(void)
{
    int NumVer, NumEdg;
    // fstream f1;
    // f1.open("graph2.txt", ios::in);
    // if (!f1.is_open())
    // {
    //     cout << "some thing wrong" << endl;
    //     exit(1);
    // }
    // f1 >> NumVer >> NumEdg;
    cin >> NumVer >> NumEdg;

    vector<vector<int>> Distance(NumVer, vector<int>(NumVer, INF));

    for (int i = 0; i < NumVer; i++)
    {
        Distance[i][i] = 0;
    }

    for (int i = 0; i < NumEdg; i++)
    {
        int node1, node2, edge;
        cin >> node1 >> node2 >> edge;
        if (node1 == node2)
            continue;
        if (Distance[node1][node2] > edge)
            Distance[node1][node2] = Distance[node2][node1] = edge;
    }

    // for (int i = 0; i < NumEdg; i++)
    // {
    //     int node1, node2, edge;
    //     f1 >> node1 >> node2 >> edge;
    //     if (node1 == node2)
    //         continue;
    //     if (Distance[node1][node2] > edge)
    //         Distance[node1][node2] = Distance[node2][node1] = edge;
    // }
    // printMatrix(Adj);

    // vector<vector<vector<int>>> path(NumVer, vector<vector<int>>(NumVer));
    // vector<vector<vector<vector<int>>>> path(NumVer, vector<vector<vector<int>>>(NumVer));
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

    // printMatrix(Sequence);

    for (int k = 0; k < NumVer; k++)
    {
        for (int i = 0; i < NumVer; i++)
        {
            for (int j = i + 1; j < NumVer; j++)
            {
                if (Distance[i][k] + Distance[k][j] == Distance[i][j] && i != j && i != k && j != k)
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

    // for (int i = 0; i < NumVer; i++)
    // {
    //     for (int j = i + 1; j < NumVer; j++){
    //         int m = i + 1;
    //         while(Sequence[i][j][0] != j){
    //             int x = Sequence[i][j][0];
    //         }
    //     }
    // }


    // cout << Result << endl;
    // printPath(path, shortest_path);
    // printMatrix(Sequence);
    for (int i = 0; i < NumVer; i++){
        float Result = 0;
        for (int j = 0; j < NumVer; j++){
            Result += Betweenness(Sequence[j], i);
        }
        cout << Result << endl;
    }
    // vector<vector<int>> x = Sequence[0];
    // cout << Betweenness(x, 2) << endl;
    // cout << Betweenness(x, 3) << endl;
    // f1.close();
    return 0;
}
