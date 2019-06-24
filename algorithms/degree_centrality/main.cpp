#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <utility>

using namespace std;


int main()
{
    int n, m;

    scanf("%i",&n); //num of vertices
    scanf("%i",&m); //num of edges

    vector<int> degree_centerality(n, 0);

    for (int i = 0; i <m; i++)
    {
        int a, b;
        scanf("%i",&a);
        scanf("%i",&b);
        if (a==b)
            degree_centerality[a]++;
        else
        {
            degree_centerality[a]++;
            degree_centerality[b]++;
        }

        scanf("%i",&a); //scan the weight
    }

    for (int i = 0; i <n; i++)
        printf("%i\n",degree_centerality[i]);

}



