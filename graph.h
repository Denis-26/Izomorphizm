#ifndef GRAPH_H
#define GRAPH_H
#include <fstream>
#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
#include <algorithm>
#define C 20
using namespace std;
class Graph
{
public:              //Поля
    int M[C][C];  //Главная матрица.

    int count;
    int color1[C];
    int ribs;
    int v;
    int G;        //Является ли граф деревом?
    int pasport[C];
    int distance1[C];

public:              //Функции

    int CompCon();
    bool bipartitle();
    Graph(string string1);
    void Pasport();
    int ShortestCircle();
    int diamGraph();
    int Deikstra(int start);
};

#endif
