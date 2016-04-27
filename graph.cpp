#include "graph.h"

Graph::Graph(string string1)
{
    ifstream f(string1);
    if (f.is_open())
        cout << "File " << string1 << " is open!" << endl;
    f >> v >> v;
    ribs = 0;
    for (int i = 0; i < v; ++i)
    {
        for (int j = 0 ; j < v; ++j)
        {
            f >> M[i][j];
            if (M[i][j] == 1)
                ribs++;
        }
    }
    ribs/=2;
    G = ribs - v + 1;
    for (int i = 0; i < v; ++i)
        pasport[i] = 0;
    for (int i = 0 ; i < v; ++i)
        color1[i] = 0;
}
void Graph::Pasport()
{
    for (int i = 0; i < v; ++i)
    {
        for (int j = 0; j < v; ++j)
            if (this->M[i][j])
                pasport[i]++;
    }
    sort(pasport, pasport+v);
}

int Graph::CompCon()
{
    vector<bool> used(v, false);
    bool con_discon = true;
    int indx, count1 = 1;
    for (int j = 0; j < v; ++j)
    {
        queue<int> q;
        q.push(j);
        while (!q.empty())
        {
            indx = q.front();
            q.pop();
            if (used[indx])
                continue;
            used[indx] = true;
            con_discon = true;
            for (int i = 0; i < v; ++i)
            {
                if (this->M[indx][i])
                    q.push(i);
            }
        }
        if (con_discon)
        {
            for (int i = 0; i < v; ++i)
            {
            	if (!used[i])
                {
                    con_discon = false;;
                    count1++;
                    break;
                }
            }
        }
    }
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
        if (color1[k] == 0)
            color1[k] = 1;
        while(!q.empty())
        {
            indx = q.front();
            q.pop();
            for (int i = 0; i < v; ++i)
            {
                if (M[indx][i])
                {
                    if (color1[i] == 0)
                    {
                        if (color1[indx] == 1)
                            color1[i] = 2;
                        else if (color1[indx] == 2)
                            color1[i] = 1;
                    }
                    else if (color1[i] == color1[indx])
                    	return 0;
                }
            }
        }
        k++;
    }
    return 1;
}

int Graph::ShortestCircle()
{
    queue<int> q;
    int indx, a1 = -1, b1 = -1, count1 = 0, min1 = 10000000, V[30];
    bool used[30];
    for (int k = 0; k < v; ++k)
    {
        for (int j = 0; j < v; ++j)
        {
            V[j] = -1;
            used[j] = false;
        }
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
    cout << min1 << endl;
    return min1;
}
int Graph::Deikstra(int start)
{
    int indx;
    bool used[C];
    for (int i = 0; i < v; ++i)
    {
        used[i] = false;
        distance1[i] = 10000000;
    }
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
            if (M[indx][i])
            {
                if (M[indx][i]+distance1[indx] < distance1[i])
                    distance1[i] = distance1[indx] + M[indx][i];
                q.push(i);
            }
        }
    }
    int max1 = 0;
    int vers = 0;
    for (int i = 0; i < v; ++i)
        if (distance1[i] > max1)
        {
            max1 = distance1[i];
            vers = i;   
        }
    return vers;
}
int Graph::diamGraph()
{ 
    int result = distance1[Deikstra(Deikstra(0))];
    cout << "Diam of Graph = " << result << endl;
    return result;
}
