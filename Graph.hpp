//
//  Graph.hpp
//  index13(paper 210sub)
//
//  Created by 孟令凯 on 2021/6/9.
//
#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include "string"
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
struct point{
    int vertex;
    float value;
};

struct point2{
    int vertex;
    int value;
    int cycle;
    int flow;
};

using namespace std;
class Graph{
private:
    string str;//图数据
    unsigned int n,m,edge_m;
    int max_degree;
    int *max_degree_num;
    int *degree;//每个点邻居数目
    int *pstart,*out_pstart,*in_pstart; //offset of neighbors of nodes 节点相邻点偏移量
    unsigned int *out_edges,*in_edges; //adjacent ids of edges 相邻边
    unsigned int *edges;
    unsigned int *reverse; //the position of reverse edge in edges 反向边在边中的位置
    point **core_order_c2, **core_order_f2, *neighbor_order_c2, *neighbor_order_f2;
   
    
    point2 *edge, *neighbor;//out-0, in-1, re-2
    int *edge_start, *neighbor_start;
    
public:
    Graph(const char *_dir);
    ~Graph();
    void readGraph();
    void creatIndex();
private:
    void getDegree();
    void getTti();
    int judgeTri(int re_num, int a, int b, int c);
    unsigned int binary_search(const unsigned int *array, int b, int e, int val) ;
    void initReverse();
    void getNeighborOrder();
    void getCoreOrder();
    void writeIndex();
    int BinarySearch(int *a, int value, int n);
    int BinarySearch2(int *a, int value, int b, int e);
    int BinarySearch3(vector<int> a, int value);
    unsigned int BinarySearch4(unsigned int *a,unsigned int value, unsigned int b, unsigned int e);
    int BinarySearch_edge_nei(point2 *a, int value, unsigned int b, unsigned int e);
    
    
};
#endif /* Graph_hpp */




