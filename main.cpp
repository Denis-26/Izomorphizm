#include <iostream>
#include <ctime>
#include "graph.h"
#include <algorithm>
using namespace std;
int N = 0; //Вот


void Swap(int k, int j, Graph *matrix);
bool Equal(Graph *graph1, Graph *graph2);
void print(Graph *graph1);
int perm(Graph *graph1, Graph *graph2);

void Swap(int k, int j, Graph *matrix)       //Функция замены строк и столбцов.
{
    for (int i = 0; i < matrix->v; ++i)
    {
        int swap = matrix->M[k][i];
        matrix->M[k][i] = matrix->M[j][i];
        matrix->M[j][i] = swap;
    }

    for (int i = 0; i < matrix->v; ++i)
    {
        int swap = matrix->M[i][k];
        matrix->M[i][k] = matrix->M[i][j];
        matrix->M[i][j] = swap;
    }
    N++;
}

bool Equal(Graph *graph1, Graph *graph2)        //Проверка матриц Графов на схожесть
{
    for (int i = 0; i < graph1->v; ++i)
        for (int j = 0; j < graph1->v; ++j)
            if (graph1->M[i][j] != graph2->M[i][j])
                return 0;
    return 1;
}


void print(Graph *graph1)                     //Вывод очередной перестановки
{
    cout << endl << endl;
    for (int i = 0; i < graph1->v; ++i)
    {
        for (int j = 0; j < graph1->v; ++j)
            cout << graph1->M[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
int perm(Graph *graph1, Graph *graph2)     //Генерация всех перестановок
{
    int idx[graph1->v];
    for(int i=0; i < graph1->v; i++)
        idx[i] = 0;
    for (int i=1; i < graph1->v;)
    {
        if (idx[i] < i)
        {
            if (Equal(graph1, graph2))
            {
                cout << "Number of permutations " << N << endl;
                return 1;
            }
            int swap1 = i % 2 * idx[i];
            Swap(swap1, i, graph1);
            //print(graph1);
            idx[i]++;
            i = 1;
        }
        else
        {
          idx[i++] = 0;
        }
    }
    return 0;
}

int main()                                //ГЛАВНАЯ ФУНКЦИЯ. 
{
    float duration;
    clock_t start, finish;
    start = clock();

    string s1 = "m.txt";
    string s2 = "m1.txt";
    Graph graph1(s1);
    Graph graph2(s2);
    cout << endl;

    graph1.Pasport();                       //Проверка паспортов графа.
    graph2.Pasport();
    for (int i = 0; i < graph1.v; ++i)
        if (graph1.pasport[i] != graph2.pasport[i])
        {
            cout << "Graphs are not isomorphic - PASPORTS are not equal" << endl;
            finish = clock();
            duration = (float)(finish - start) / CLOCKS_PER_SEC;
            cout << "Time: " << duration << endl << endl;
            return 0;
        }
    if (graph1.v != graph2.v)             //Проверка кол-во вершин.
    {
        cout << "Graphs are not isomorphic - tops are not equal" << endl;
        return 0;
    }


    if (graph1.ribs != graph2.ribs)         //Проверка кол-во ребер.
    {

        cout << "Graphs are not isomorphic - ribs are not equal" << endl << endl;
        return 0;
    }

    int Connection1 = graph1.CompCon(), Connection2 = graph2.CompCon(); //Проверка компонент связности.
    if (Connection1 != Connection2) 										
    {
         cout << "Graphs are not isomorphic - connection components are not equal" << endl << endl;
         return 0;
    }
    else if (Connection1 == 1)
    {
    	if (graph1.diamGraph() != graph2.diamGraph()) //Проверка Диаметра графов.
    	{
        	cout << "Graphs are not isomorphic - diametres are not equal" << endl;
        	return 0;
    	}
    }

    if (graph1.bipartitle() != graph2.bipartitle()) //Проверка на двудольность.
    {
        cout << "Graphs are not isomorphic - bipartitle is not equal" << endl;
        return 0;
    }


    if (graph1.G > 0 && graph2.G > 0)
    {
        if (graph1.ShortestCircle() != graph2.ShortestCircle())
        {
            cout << "Graphs are not isomorphic - shortest circles are not equal" << endl;
            return 0;
        }
    }

    if (perm(&graph1, &graph2))                                        //Перебор всех вариантов матриц смежности.
    {
        cout << "Graphs are isomorphic" << endl;
    }
    else
        cout << "Graphs are not isomorphic" << endl;



    finish = clock();
    duration = (float)(finish - start) / CLOCKS_PER_SEC;
    cout << "Time: " << duration << endl << endl;
    return 0;
}
