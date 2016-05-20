#include "graph.h"
void Graph::init(string str)
{
	ifstream f(str);
    f >> v;
    ribs = 0;
    for (int i = 0; i < v; ++i)
    {
        pasport[i] = 0;
        color1[i] = 0;
        for (int j = 0 ; j < v; ++j)
        {
            f >> M[i][j];
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
    bool used[C] = {false};
    int con_discon[C] = {0};
    int indx, count1 = 1;
    for (int j = 0; j < v; ++j)
    {
        queue<int> q;
        q.push(j);
        if (con_discon[j])
        	continue;
        else
        	count1++;
        while (!q.empty())
        {
            indx = q.front();
            q.pop();
            if (used[indx])
                continue;
            used[indx] = true;
            for (int i = 0; i < v; ++i)
                if (M[indx][i])
                {
            	    q.push(i);
            	    con_discon[i] = 1;
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
    int k = 0;
    while(k != (v-1))
    {
        q.push(k);
        if (!color1[k])
            color1[k] = 1;
        while(!q.empty())
        {
            indx = q.front();
            q.pop();
            for (int i = 0; i < v; ++i)
            {
                if (M[indx][i] && !color1[i])
                {
                    if (color1[indx] == 1)
                        color1[i] = 2;
                    else if (color1[indx] == 2)
                        color1[i] = 1;
                }
                else if (color1[i] == color1[indx])
                {
    				//cout << "Bipart - 0" << endl;
    				return 0;	
                }
            }
        }
        k++;
    }
    //cout << "Bipart - 1" << endl;
    return 1;
}

int Graph::ShortestCircle()
{
    queue<int> q;
    int indx, a1 = -1, b1 = -1, count1 = 0, min1 = 10000000, V[30];
    bool used[30] = {false};
    for (int k = 0; k < v; ++k)
    {
        for (int j = 0; j < v; ++j)
            V[j] = -1;
        count1 = 0;
        q.push(k);
        while(!q.empty())
        {
            indx = q.front();
            q.pop();
            if (used[indx])
                continue;
            used[indx] = true;
            for(int i = 0; i < v && a1 == -1; ++i)
            {
                if (M[indx][i] && !used[i])
                {
                    if (V[i] != -1)
                    {
                        a1 = indx;
                        b1 = i;
                    }
                    else
                    {
                        V[i] = indx;
                        q.push(i);
                    }
                }
            }
        }
        while(a1!=-1)
        {
            a1 = V[a1];
            count1++;
        }
        while (b1!=-1)
        {
            b1 = V[b1];
            count1++;
        }
        if (count1-1 < min1 && (count1 -1) != -1)
            min1 = count1-1;
    }
    //cout << "Circle " << min1 << " ";
    return min1;
}
void Graph::Deikstra(int start) //переписать полностью 
{
    int indx;
    bool used[C] = {false};
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
	cout << max1 << " ";
	return max1;
}
