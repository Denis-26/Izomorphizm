#include "graph.h"
#include <cstring>
void Graph::init()
{
    cin >> v;
    init(v);
}
void Graph::init(int n)
{
    v = n;
    ribs = 0;
    memset(M, 0, sizeof(M));
    for (int i = 0; i < v; ++i)
    {
        pasport[i] = 0;
        color1[i] = 0;
        for (int j = 0 ; j < v; ++j)
        {
            cin >> M[i][j];
            if (M[i][j])
            {
                ribs++;
                pasport[i]++;
            }
        }
    }
    ribs/=2;
    G = ribs - v + 1;       
}

int Graph::CompCon()
{
    bool used[C] = {};
    int indx, count1 = 1;
    for (int j = 0; j < v; ++j)
    {
        if (used[j])
            continue;
        else
            count1++;
        queue<int> q;
        q.push(j);
        used[j] = true;
        while (!q.empty())
        {
            indx = q.front();
            q.pop();
            for (int i = 0; i < v; ++i)
                if (M[indx][i] && !used[i])
                {
            	    q.push(i);
            	    used[i] = true;
                }
        }
    }
    //cout << "ComCon " << count1 << endl;
    return count1;
}
bool Graph::bipartitle()
{
    queue<int> q;
    int indx;
    for(int k = 0; k < v; ++k)
    {
        if (color1[k])
            continue;
        color1[k] = 1;
        q.push(k);
        while(!q.empty())
        {
            indx = q.front();
            q.pop();
            for (int i = 0; i < v; ++i)
            {
                if (M[indx][i] && !color1[i])
                    color1[i] = 3 - color1[indx];
                else if (color1[i] == color1[indx])
                {
    				//cout << "Bipart - 0" << endl;
    				return 0;	
                }
            }
        }
    }
    //cout << "Bipart - 1" << endl;
    return 1;
}

int Graph::ShortestCircle()
{
    int indx, count1 = 0, min1 = 10000000, V[C];
    for (int k = 0; k < v-2; ++k)
    {
        memset(V, -1, v*sizeof(int));
        bool used[C] = {};                                 
        count1 = 0;
        queue<int> q;
        q.push(k);
        V[k] = 0;
        while(!q.empty())
        {
            indx = q.front();
            q.pop();
            used[indx] = true;
            for(int i = 0; i < v; ++i)
            {
                if (M[indx][i] && !used[i])
                {
                    if (V[i] != -1)
                    {
                        count1 = V[i]+V[indx]+1;
                        if (count1 < min1)
                            min1 = count1;
                        if (min1 == 3)
                            return 3;
                        goto label;
                    }
                    else
                    {
                        V[i] = V[indx]+1;
                        q.push(i);
                    }
                }
            }
        }
label:;
    }
    //cout << "Circle " << min1 << " ";
    return min1;
}
void Graph::Deikstra(int start)  
{
    int indx;
    bool used[C] = {};
    for (int i = 0; i < v; ++i)
        distance1[i] = 1000000000;
    queue<int> q;
    q.push(start);
    distance1[start] = 0;
    while(!q.empty())
    {
        indx = q.front();
        q.pop();
        if (used[indx])
       		continue;
        used[indx] = true;
        for (int i = 0; i < v; ++i)
        {
            if (M[indx][i] && !used[i])
            {
            	if (distance1[indx]+1 < distance1[i])
        			distance1[i] = distance1[indx]+1;
        		q.push(i);
            }
        }
    }
}
int Graph::diamGraph()
{ 
	int max1 = 0;
	for (int k = 0; k < v; ++k)
	{
		Deikstra(k);
		for (int j = 0; j < v; ++j)
			if (distance1[j] > max1)
				max1 = distance1[j];
	}
	//cout << max1 << " ";
	return max1;
}
