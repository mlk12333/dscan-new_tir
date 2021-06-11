//
//  main.cpp
//  index13(paper 210sub)
//
//  Created by 孟令凯 on 2021/6/9.
//

#include <iostream>
#include "string"
#include <fstream>
#include "Graph.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    if(argc<2) return 1;
    // insert code here...
    string str = "/Users/milk/test_data/zata/soc-LiveJournal1";
    argv[0] = &str[0];
    clock_t startTime,endTime;
    
    Graph *graph = new Graph(argv[1]);
    
//    vector<int> a;
//    for(int i = 0;i<10;i++) a.push_back(i);
//
//    a.erase(std::remove(a.begin(),a.end(),3),a.end());
//
//    for(int i = 0;i<a.size();i++) cout<<a[i]<<" ";
    startTime = clock();//计时开始
    graph->readGraph();
    endTime = clock();//计时结束
    cout << "The read graph time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    graph->creatIndex();
    
//    graph->creatIndex();
//
//    graph->creatIndex();
       
    return 0;
}





