#include <iostream>
#include <ctime>
#include "graph.h"
#include <algorithm>
#include <fstream>
int EqualPasports(int *pasport1, int *pasport2);
void Swap(int k, int j, Graph *matrix);
bool Equal(Graph *graph1, Graph *graph2);
int perm(Graph *graph1, Graph *graph2);
const int A11 = 12;
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
    int idx[graph1->v] = {0};
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

int main()                                //ГЛАВНАЯ ФУНКЦИЯ. 
{
	string tests[16] = {"1","11","2","22","3","33","4","44","5","55","6","66","7","77"};
	Graph graph1;
	Graph graph2;    

    for (int j = 1; j<14; j+=2)
    {

		string s1 = tests[j]+".in";
	    string s2 = tests[j-1]+".in";
		
		float duration;
    	clock_t start, finish;
    	start = clock();

		graph1.init(s1);
	    graph2.init(s2);
    	
	    if ((graph2.v > 10) && ((graph1.ribs != graph2.ribs) || (!EqualPasports(graph1.v, graph1.pasport, graph2.pasport)) || (graph1.bipartitle() != graph2.bipartitle()) || ((graph1.G > 0 && graph2.G > 0) && (graph1.ShortestCircle() != graph2.ShortestCircle())) || (graph1.CompCon() != graph2.CompCon()) || (graph1.diamGraph() != graph2.diamGraph())))
    	{
			finish = clock();
	        std::cout << "Test: " << tests[j-1] << " NO: ";
	    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
	    	std::cout << "Time: " << duration << std::endl;
	        continue;
    	}
    	if (perm(&graph1, &graph2))                                        //Перебор всех вариантов матриц смежности.
	    {
	    	finish = clock();
	        std::cout << "Test: " << tests[j-1] << " YES: ";
	    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
	    	std::cout << "Time: " << duration << std::endl;
	    	continue;
	    }
	    finish = clock();
		std::cout << "Test: " << tests[j-1] << " NO: ";
    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
    	std::cout << "Time: " << duration << std::endl;
	}
    return 0;
}
