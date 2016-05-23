#include <iostream>
#include <ctime>
#include "graph.h"
#include <algorithm>
#include <fstream>
#include <cstring>
int EqualPasports(int *pasport1, int *pasport2);
void Swap(int k, int j, Graph *matrix);
bool Equal(Graph *graph1, Graph *graph2);
int perm(Graph *graph1, Graph *graph2);
bool tmp[C];
void Swap(int k, int j, Graph *matrix)       //Функция замены строк и столбцов.
{
    memcpy(tmp, matrix->M[k], sizeof(tmp));
    memcpy(matrix->M[k], matrix->M[j], sizeof(tmp));
    memcpy(matrix->M[j], tmp, sizeof(tmp));
    /*long long *a = (long long*) matrix->M[k];
    long long *b = (long long*) matrix->M[j];
    long long c = a[0];
    a[0] = b[0];
    b[0] = c;
    c = a[1];
    a[1] = b[1];
    b[1] = c;*/

    bool swap;
    swap = matrix->M[0][k];
    matrix->M[0][k] = matrix->M[0][j];
    matrix->M[0][j] = swap;
    swap = matrix->M[1][k];
    matrix->M[1][k] = matrix->M[1][j];
    matrix->M[1][j] = swap;
    swap = matrix->M[2][k];
    matrix->M[2][k] = matrix->M[2][j];
    matrix->M[2][j] = swap;
    swap = matrix->M[3][k];
    matrix->M[3][k] = matrix->M[3][j];
    matrix->M[3][j] = swap;
    swap = matrix->M[4][k];
    matrix->M[4][k] = matrix->M[4][j];
    matrix->M[4][j] = swap;
    swap = matrix->M[5][k];
    matrix->M[5][k] = matrix->M[5][j];
    matrix->M[5][j] = swap;
    swap = matrix->M[6][k];
    matrix->M[6][k] = matrix->M[6][j];
    matrix->M[6][j] = swap;
    swap = matrix->M[7][k];
    matrix->M[7][k] = matrix->M[7][j];
    matrix->M[7][j] = swap;
    swap = matrix->M[8][k];
    matrix->M[8][k] = matrix->M[8][j];
    matrix->M[8][j] = swap;
    swap = matrix->M[9][k];
    matrix->M[9][k] = matrix->M[9][j];
    matrix->M[9][j] = swap;
    swap = matrix->M[10][k];
    matrix->M[10][k] = matrix->M[10][j];
    matrix->M[10][j] = swap;
    swap = matrix->M[11][k];
    matrix->M[11][k] = matrix->M[11][j];
    matrix->M[11][j] = swap;
    swap = matrix->M[12][k];
    matrix->M[12][k] = matrix->M[12][j];
    matrix->M[12][j] = swap;
}
int EqualPasports(int v, int *pasport1, int *pasport2)
{
	sort(pasport1, pasport1+v);
	sort(pasport2, pasport2+v);
    if(memcmp(pasport1, pasport2, sizeof(v)))
	   return 0;
    else
        return 1;
}
bool Equal(Graph *graph1, Graph *graph2)        //Проверка матриц Графов на схожесть
{
    if(memcmp(graph1->M, graph2->M, sizeof(graph2->M)))
        return 0;
    else
        return 1;
}
int perm(Graph *graph1, Graph *graph2)     //Генерация всех перестановок
{
    int idx[C] = {};
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
	
    if ((graph2.v > 11) && ((graph1.ribs != graph2.ribs) || (!EqualPasports(graph1.v, graph1.pasport, graph2.pasport)) || (graph1.bipartitle() != graph2.bipartitle()) || ((graph1.G > 0 && graph2.G > 0) && (graph1.ShortestCircle() != graph2.ShortestCircle())) || (graph1.CompCon() != graph2.CompCon()) || (graph1.diamGraph() != graph2.diamGraph())))
	{
		finish = clock();
		duration = (float)(finish - start) / CLOCKS_PER_SEC;
		TIME+=duration;

        cout << duration << endl;
        cout << "NO\n";
	}
	else if (perm(&graph1, &graph2))                                        //Перебор всех вариантов матриц смежности.
    {
    	finish = clock();
		duration = (float)(finish - start) / CLOCKS_PER_SEC;
		TIME+=duration;

        cout << duration << endl;
        cout << "YES\n";
    }
    else
    {
    	finish = clock();
		duration = (float)(finish - start) / CLOCKS_PER_SEC;
		TIME+=duration;

		cout << duration << endl;
        cout << "NO\n";
    }
    return 0;
}
