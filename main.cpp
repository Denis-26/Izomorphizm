#include <iostream>
#include <ctime>
#include "graph.h"
#include <algorithm>
#include <iomanip>
#include <fstream>
int EqualPasports(int *pasport1, int *pasport2);
void Swap(int k, int j, Graph *matrix);
bool Equal(Graph *graph1, Graph *graph2);
int perm(Graph *graph1, Graph *graph2);
const int A11 = 13;
void Swap(int k, int j, Graph *matrix)       //Функция замены строк и столбцов.
{
    for (int i = 0; i < A11; ++i)
    {
        int swap = matrix->M[k][i];
        matrix->M[k][i] = matrix->M[j][i];
        matrix->M[j][i] = swap;
    }
    for (int i = 0; i < A11; ++i)
    {
        int swap = matrix->M[i][k];
        matrix->M[i][k] = matrix->M[i][j];
        matrix->M[i][j] = swap;
    }
}
int EqualPasports(int v, int *pasport1, int *pasport2)
{
	sort(pasport1, pasport1+v);
	sort(pasport2, pasport2+v);
	for (int i = 0; i < v; ++i)
        if (pasport1[i] != pasport2[i])
            return 0;
    return 1;
}
bool Equal(Graph *graph1, Graph *graph2)        //Проверка матриц Графов на схожесть
{
    for (int i = 0; i < graph1->v; ++i)
        for (int j = 0; j < graph1->v; ++j)
            if (graph1->M[i][j] != graph2->M[i][j])
                return 0;
    return 1;
}
int perm(Graph *graph1, Graph *graph2)     //Генерация всех перестановок
{
    int* idx = new int[graph1->v];
    for(int i=0;i<graph1->v;i++)
        idx[i]=0;
    for (int i=1; i < graph1->v;)
    {
        if (idx[i] < i)
        {
            if (Equal(graph1, graph2))
                return 1;
            Swap((i % 2 * idx[i]), i, graph1);
            idx[i]++;
            i = 1;
        }
        else
          idx[i++] = 0;
    }
    return 0;
}

int main()  
{
	double TIME = 0;
	Graph graph1;
	Graph graph2;    

	double duration;
	clock_t start, finish;
	start = clock();

	graph1.init();
    graph2.init(graph1.v);
	
    if ((graph2.v > 10) && ((graph1.ribs != graph2.ribs) || (!EqualPasports(graph1.v, graph1.pasport, graph2.pasport)) || (graph1.bipartitle() != graph2.bipartitle()) || ((graph1.G > 0 && graph2.G > 0) && (graph1.ShortestCircle() != graph2.ShortestCircle())) || (graph1.CompCon() != graph2.CompCon()) || (graph1.diamGraph() != graph2.diamGraph())))
	{
		finish = clock();
		duration = (float)(finish - start) / CLOCKS_PER_SEC;
		TIME+=duration;

        cout << setprecision(6) << duration << endl;
        cout << "NO\n";
	}
	if (perm(&graph1, &graph2))                                        //Перебор всех вариантов матриц смежности.
    {
    	finish = clock();
		duration = (float)(finish - start) / CLOCKS_PER_SEC;
		TIME+=duration;

        cout << setprecision(6) << duration << endl;
        cout << "YES\n";
    }
    else
    {
    	finish = clock();
		duration = (float)(finish - start) / CLOCKS_PER_SEC;
		TIME+=duration;

		cout << setprecision(6) << duration << endl;
        cout << "NO\n";
    }
    return 0;
}
