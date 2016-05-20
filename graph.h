#ifndef GRAPH_H
#define GRAPH_H
#include <fstream>
#include <iostream>
#include <queue>
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
    int ShortestCircle();
    int diamGraph();
    void Deikstra(int start);
    void init(string str);
    
};

#endif
