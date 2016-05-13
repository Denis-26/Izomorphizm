#include <iostream>
#include <ctime>
#include "graph.h"
#include <algorithm>
using namespace std;
int N = 0; 

int EqualPasports(int *pasport1, int *pasport2);
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
int EqualPasports(int v, int *pasport1, int *pasport2)
{
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
                return 1;
            
            int swap1 = i % 2 * idx[i];
            Swap(swap1, i, graph1);
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
		
		graph1.init(s1);
	    graph2.init(s2);
    	
    	float duration;
    	clock_t start, finish;
    	start = clock();

	    if (graph2.v > 10)
    	{

    		if (graph1.ribs != graph2.ribs)         //Проверка кол-во ребер.
		    {

		        cout << "Test: " << tests[j-1] << " NO: ";
		        finish = clock();
		    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
		    	cout << "Time: " << duration << endl;
		        continue;
		    }

			graph1.Pasport();                       //Проверка паспортов графа.
		    graph2.Pasport();
		    if (!EqualPasports(graph1.v, graph1.pasport, graph2.pasport))
	    	{
	    		cout << "Test: " << tests[j-1] << " NO: ";
		        finish = clock();
		    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
		    	cout << "Time: " << duration << endl;
		    	continue;
	    	}
		    
		    int Connection1 = graph1.CompCon(), Connection2 = graph2.CompCon(); //Проверка компонент связности.
		    if (Connection1 != Connection2) 										
		    {
		         cout << "Test: " << tests[j-1] << " NO: ";
		         finish = clock();
		    	 duration = (float)(finish - start) / CLOCKS_PER_SEC;
		    	 cout << "Time: " << duration << endl;
		         continue;
		    }
		    else if (Connection1 == 1)
		    {
		    	if (graph1.diamGraph() != graph2.diamGraph()) //Проверка Диаметра графов.
		    	{
		        	cout << "Test: " << tests[j-1] << " NO: ";
		        	finish = clock();
			    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
			    	cout << "Time: " << duration << endl;
		        	continue;
		    	}
		    }

		    if (graph1.bipartitle() != graph2.bipartitle()) //Проверка на двудольность.
		    {
		        cout << "Test: " << tests[j-1] << " NO: ";
		        finish = clock();
		    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
		    	cout << "Time: " << duration << endl;
		        continue;
		    }
		    
		    bool qwerty = (graph1.G > 0 && graph2.G > 0);
	        if (qwerty && (graph1.ShortestCircle() != graph2.ShortestCircle()))
	        {
	            cout << "Test: " << tests[j-1] << " NO: ";
	            finish = clock();
		    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
		    	cout << "Time: " << duration << endl;
	            continue;
	        }
    	}
    	if (perm(&graph1, &graph2))                                        //Перебор всех вариантов матриц смежности.
	    {
	        cout << "Test: " << tests[j-1] << " YES: ";
	    	finish = clock();
	    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
	    	cout << "Time: " << duration << endl;
	    }
	    else
       	{
       		cout << "Test: " << tests[j-1] << " NO: ";
	    	finish = clock();
	    	duration = (float)(finish - start) / CLOCKS_PER_SEC;
	    	cout << "Time: " << duration << endl;
       	}
	}
    return 0;
}
