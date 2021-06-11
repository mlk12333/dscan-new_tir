//
//  Graph.cpp
//  index13(paper 210sub)
//
//  Created by 孟令凯 on 2021/6/9.
//

#include "Graph.hpp"
#include <algorithm>
#include "math.h"

Graph::Graph(const char *_dir){
    this->str = string(_dir);
    n = m = edge_m = max_degree = 0;
    degree = NULL;
    pstart = NULL;
    out_pstart = NULL;
    in_pstart = NULL;
    edges= NULL;
    out_edges= NULL;
    in_edges= NULL;
    reverse= NULL;
//    core_order_c= NULL;
//    core_order_f= NULL;
//    neighbor_order_c= NULL;
//    neighbor_order_f= NULL;
    core_order_c2= NULL;
    core_order_f2= NULL;
    neighbor_order_c2= NULL;
    neighbor_order_f2= NULL;
    max_degree_num = NULL;
    edge= NULL;
    neighbor= NULL;
    edge_start= NULL;
    neighbor_start= NULL;
}
Graph::~Graph(){
    if(degree!=NULL){
        delete [] degree;
        degree = NULL;
    }
    if(pstart!=NULL){
        delete [] pstart;
        pstart = NULL;
    }
    if(out_pstart!=NULL){
        delete [] out_pstart;
        out_pstart = NULL;
    }
    if(in_pstart!=NULL){
        delete [] in_pstart;
        in_pstart = NULL;
    }
    if(edges!=NULL){
        delete [] edges;
        edges = NULL;
    }
    if(out_edges!=NULL){
        delete [] out_edges;
        out_edges = NULL;
    }
    if(in_edges!=NULL){
        delete [] in_edges;
        in_edges = NULL;
    }
    if(reverse!=NULL){
        delete [] reverse;
        reverse = NULL;
    }
    if(core_order_c2!=NULL){
        for (int i = 0; i < max_degree; i++) {
//            for (int j = 0; j < max_degree_num[i]; j++) {
//                delete[] core_order_c[i][j];
//                core_order_c[i][j] = NULL;
//            }
            delete[] core_order_c2[i];
            core_order_c2[i] = NULL;
         }
         delete[] core_order_c2;
         core_order_c2 = NULL;
    }
    if(core_order_f2!=NULL){
        for (int i = 0; i < max_degree; i++) {
//            for (int j = 0; j < max_degree_num[i]; j++) {
//                delete[] core_order_f[i][j];
//                core_order_f[i][j] = NULL;
//            }
            delete[] core_order_f2[i];
            core_order_f2[i] = NULL;
         }
         delete[] core_order_f2;
         core_order_f2 = NULL;
    }
   
    if(neighbor_order_f2!=NULL){
//        delete[] neighbor_order_f[0];
//        for (int i = 0; i < edge_m; i++) {
//            neighbor_order_f[i] = NULL;
//        }
        delete[] neighbor_order_f2;
        neighbor_order_f2 = NULL;
    }
    if(max_degree_num!=NULL){
        delete [] max_degree_num;
        max_degree_num = NULL;
    }
    
    if(neighbor_order_c2!=NULL){
        delete[] neighbor_order_c2;
        neighbor_order_c2 = NULL;
    }
    
    if(edge!=NULL){
        delete[] edge;
        edge = NULL;
    }
    
    if(neighbor!=NULL){
        delete[] neighbor;
        neighbor = NULL;
    }
    if(edge_start!=NULL){
        delete[] edge_start;
        edge_start = NULL;
    }
    
    if(neighbor_start!=NULL){
        delete[] neighbor_start;
        neighbor_start = NULL;
    }
}

void Graph::readGraph(){
    ifstream infile;   //输入流
    
    infile.open(str+"/degree.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open degree file failure"<<endl;
        exit(0);
    }
    infile>>n>>m;
    
    if(out_pstart == NULL) out_pstart = new int[n+1];
    if(in_pstart == NULL) in_pstart = new int[n+1];
    if(out_edges == NULL) out_edges = new unsigned int[m];
    if(in_edges == NULL) in_edges = new unsigned int[m];
    
     
    out_pstart[0] = 0;
    in_pstart[0] = 0;
    
    int outD, inD, starti = 0;
    
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> outD >> inD;
        out_pstart[starti+1] = outD + out_pstart[starti];
        in_pstart[starti+1] = inD + in_pstart[starti];
        starti++;
    }
    infile.close();
    
    infile.open(str+"/out_edges.txt", ios::in);
    if (!infile.is_open()){
        cout<<"Open out_edges file failure"<<endl;
        exit(0);
    }
    int mm_;
    infile >> mm_;
    int outi = 0;
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> out_edges[outi];
        outi++;
    }
    infile.close();
    
    infile.open(str+"/in_edges.txt", ios::in);
    
    if (!infile.is_open()){
        cout<<"Open in_edges file failure"<<endl;
        exit(0);
    }
    int ini = 0;
    infile >> mm_;
    while (!infile.eof())            // 若未到文件结束一直循环
    {
        infile >> in_edges[ini];
        ini++;
    }
    infile.close();
    
    cout<<"read!"<<endl;
    getDegree();
    
    cout<<"getDegree!"<<endl;
}



void Graph::creatIndex(){
    clock_t startTime,endTime1,endTime2;
    startTime = clock();//计时开始
    
    getTti();
    
    
    
    endTime1 = clock();//计时结束
    cout << "The getTtie time is: " <<(float)(endTime1 - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    
    if(in_pstart!=NULL){
        delete [] in_pstart;
        in_pstart = NULL;
    }

    if(in_edges!=NULL){
        delete [] in_edges;
        in_edges = NULL;
    }
    
    getNeighborOrder();
    
    endTime1 = clock();//计时结束
    cout << "The getNeighborOrder time is: " <<(float)(endTime1 - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    if(out_edges!=NULL){
        delete [] out_edges;
        out_edges = NULL;
    }


    if(out_pstart!=NULL){
        delete [] out_pstart;
        out_pstart = NULL;
    }

    if(reverse!=NULL){
        delete [] reverse;
        reverse = NULL;
    }
    
    getCoreOrder();
    
    endTime1 = clock();//计时结束
    cout << "The index create time is: " <<(float)(endTime1 - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    //writeIndex();
    
    endTime2 = clock();//计时结束
    cout << "The write time is: " <<(float)(endTime2 - endTime1) / CLOCKS_PER_SEC << "s" << endl;
}


void Graph::getDegree(){
    if(pstart == NULL) pstart = new int[n+1];
    if(degree == NULL) degree = new int[n];
    
    if(edge_start == NULL) edge_start = new int[n+1];
    if(neighbor_start == NULL) neighbor_start = new int[n+1];
    
    edge = new point2[(long)(2*(long)m)];
    neighbor = new point2[(long)(2*(long)m)];
    
    pstart[0] = 0;
    edge_start[0] = 0;
    neighbor_start[0] = 0;
    
    if(edges == NULL)  edges = new unsigned int[(long)2*m];
//    edges = new unsigned int[(long)2*m];
    long edgesi = 0;
    
    long edge_num = 0, nei_num = 0;
    
    
    for(int i = 0;i<n;i++){
        
        int edge_strati = 0;
        int neighbor_strati = 0;
        
        int l1 = out_pstart[i+1] - out_pstart[i];
        int l2 = in_pstart[i+1] - in_pstart[i];
        int i1 = 0, i2 = 0, num = 0;
        while(i1<l1 && i2<l2){
            
            if(out_edges[out_pstart[i] + i1] == in_edges[in_pstart[i] + i2]){
                edges[edgesi] = out_edges[out_pstart[i] + i1];
                edgesi++;
                i1++;
                i2++;
                num++;
                
                if(edges[edgesi-1]>i){
                    edge[edge_num].vertex = edges[edgesi-1];
                    edge[edge_num].value = 2;
                    edge[edge_num].cycle = 0;
                    edge[edge_num].flow = 0;
                    edge_num++;
                    edge_strati++;
                }
                if( (out_pstart[i]+in_pstart[i])<(out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) || ((out_pstart[i]+in_pstart[i]) == (out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) && i<edges[edgesi-1])){
                    neighbor[nei_num].vertex = edges[edgesi-1];
                    neighbor[nei_num].value = 2;
                    neighbor[nei_num].cycle = 0 ;
                    neighbor[nei_num].flow = 0 ;
                    nei_num++;
                    neighbor_strati++;
                }
                                    
            }else if(out_edges[out_pstart[i] + i1] < in_edges[in_pstart[i] + i2]){
                edges[edgesi] = out_edges[out_pstart[i] + i1];
                edgesi++;
                i1++;
                num++;
                
                edge[edge_num].vertex = edges[edgesi-1];
                edge[edge_num].value = 0;
                edge[edge_num].cycle = 0;
                edge[edge_num].flow = 0;
                edge_num++;
                edge_strati++;
                if( (out_pstart[i]+in_pstart[i])<(out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) || ((out_pstart[i]+in_pstart[i]) == (out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) && i<edges[edgesi-1])){
                    neighbor[nei_num].vertex = edges[edgesi-1];
                    neighbor[nei_num].value = 0;
                    neighbor[nei_num].cycle = 0 ;
                    neighbor[nei_num].flow = 0 ;
                    nei_num++;
                    neighbor_strati++;
                }
            }else{
                edges[edgesi] = in_edges[in_pstart[i] + i2];
                edgesi++;
                i2++;
                num++;
                
                if((out_pstart[i]+in_pstart[i])<(out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) || ((out_pstart[i]+in_pstart[i]) == (out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) && i<edges[edgesi-1])){
                    neighbor[nei_num].vertex = edges[edgesi-1];
                    neighbor[nei_num].value = 1 ;
                    neighbor[nei_num].cycle = 0 ;
                    neighbor[nei_num].flow = 0 ;
                    nei_num++;
                    neighbor_strati++;
                }
            }
        }
        while(i1<l1){
            edges[edgesi] = out_edges[out_pstart[i] + i1];
            edgesi++;
            i1++;
            num++;
            
            edge[edge_num].vertex = edges[edgesi-1];
            edge[edge_num].value = 0;
            edge[edge_num].cycle = 0;
            edge[edge_num].flow = 0;
            edge_num++;
            edge_strati++;
            
            if( (out_pstart[i]+in_pstart[i])<(out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) || ((out_pstart[i]+in_pstart[i]) == (out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) && i<edges[edgesi-1])){
                neighbor[nei_num].vertex = edges[edgesi-1];
                neighbor[nei_num].value = 0 ;
                neighbor[nei_num].cycle = 0 ;
                neighbor[nei_num].flow = 0 ;
                nei_num++;
                neighbor_strati++;
            }
        }
        while(i2<l2){
            edges[edgesi] = in_edges[in_pstart[i] + i2];
            edgesi++;
            i2++;
            num++;
            
            if((out_pstart[i]+in_pstart[i])<(out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) || ((out_pstart[i]+in_pstart[i]) == (out_pstart[edges[edgesi-1]]+in_pstart[edges[edgesi-1]]) && i<edges[edgesi-1])){
                neighbor[nei_num].vertex = edges[edgesi-1];
                neighbor[nei_num].value = 1 ;
                neighbor[nei_num].cycle = 0 ;
                neighbor[nei_num].flow = 0 ;
                nei_num++;
                neighbor_strati++;
            }
        }
        
        if(num>max_degree) max_degree = num;
        
        degree[i] = num;
        edge_m = edge_m + num;
        pstart[i+1] = pstart[i] + num;
        
        edge_start[i+1] = edge_start[i] + edge_strati;
        neighbor_start[i+1] = neighbor_start[i] + neighbor_strati;
    }
    
//    for(unsigned int i = 0;i<n;i++){
//        for(unsigned int j = pstart[i]; j < pstart[i+1];j++){
//            cout<<edges[j]<<" ";
//        }
//        cout<<endl;
//    }
//
//    for(unsigned int i = 0;i<n;i++){
//        for(unsigned int j = edge_start[i]; j < edge_start[i+1];j++){
//            cout<<edge[j].vertex<<" "<<edge[j].value<<", ";
//        }
//        cout<<endl;
//    }
//
//    for(unsigned int i = 0;i<n;i++){
//        cout<<i<<":";
//        for(unsigned int j = neighbor_start[i]; j < neighbor_start[i+1];j++){
//            cout<<neighbor[j].vertex<<" "<<neighbor[j].value<<", ";
//        }
//        cout<<endl;
//    }
    
    reverse = new unsigned int[(long)edge_m];
    initReverse();
}

void Graph::getTti(){
    for(unsigned int edge_i = 0;edge_i<n;edge_i++){
        for(unsigned int edge_j = edge_start[edge_i]; edge_j < edge_start[edge_i+1]; edge_j++){
            int re_num = 0;
            if(edge[edge_j].value == 2) re_num++;
            int left1 = neighbor_start[edge_i], right1 = neighbor_start[edge_i+1];
            int left2 = neighbor_start[edge[edge_j].vertex], right2 = neighbor_start[edge[edge_j].vertex+1];
            while(left1<right1 && left2 < right2){
                if(neighbor[left1].vertex == neighbor[left2].vertex){
                    //cout<<"tri:"<<edge_i<<" "<<edge[edge_j].vertex<<" "<<neighbor[left1].vertex<<endl;
                    int re_num2 = re_num;
                    if(neighbor[left1].value == 2) re_num2++;
                    if(neighbor[left2].value == 2) re_num2++;
                    
                    if(re_num2 == 2){
                       // cout<<"typr:"<<6<<endl;
                        edge[edge_j].cycle = edge[edge_j].cycle + 1;
                        neighbor[left1].cycle = neighbor[left1].cycle +1;
                        neighbor[left2].cycle = neighbor[left2].cycle +1;
                        edge[edge_j].flow = edge[edge_j].flow + 3;
                        neighbor[left1].flow = neighbor[left1].flow +3;
                        neighbor[left2].flow = neighbor[left2].flow +3;
                    }else if(re_num2 == 3){
                      //  cout<<"typr:"<<7<<endl;
                        edge[edge_j].cycle = edge[edge_j].cycle + 2;
                        neighbor[left1].cycle = neighbor[left1].cycle +2;
                        neighbor[left2].cycle = neighbor[left2].cycle +2;
                        edge[edge_j].flow = edge[edge_j].flow + 6;
                        neighbor[left1].flow = neighbor[left1].flow +6;
                        neighbor[left2].flow = neighbor[left2].flow +6;
                    }else{
                        int type = judgeTri(re_num2, edge[edge_j].value, neighbor[left1].value, neighbor[left2].value);
                       // cout<<"typr:"<<type<<endl;
                        
                        if(type == 1){
                            edge[edge_j].cycle = edge[edge_j].cycle + 1;
                            neighbor[left1].cycle = neighbor[left1].cycle +1;
                            neighbor[left2].cycle = neighbor[left2].cycle +1;
                        }else if(type == 2){
                            edge[edge_j].flow = edge[edge_j].flow + 1;
                            neighbor[left1].flow = neighbor[left1].flow +1;
                            neighbor[left2].flow = neighbor[left2].flow +1;
                        }
                        else if(type == 5){
                            edge[edge_j].cycle = edge[edge_j].cycle + 1;
                            neighbor[left1].cycle = neighbor[left1].cycle +1;
                            neighbor[left2].cycle = neighbor[left2].cycle +1;
                            edge[edge_j].flow = edge[edge_j].flow + 1;
                            neighbor[left1].flow = neighbor[left1].flow +1;
                            neighbor[left2].flow = neighbor[left2].flow +1;
                        }else{
                            edge[edge_j].flow = edge[edge_j].flow + 2;
                            neighbor[left1].flow = neighbor[left1].flow +2;
                            neighbor[left2].flow = neighbor[left2].flow +2;
                        }
                    }
                    left2++;
                    left1++;
                }
                else if(neighbor[left1].vertex < neighbor[left2].vertex) left1++;
                else left2++;
            }
        }
    }
}

int Graph::judgeTri(int re_num, int a, int b, int c){
    if(re_num == 0){
        if(a == 0 && b == 1 && c == 0) return 1;
        else return 2;
    }
    else{
        if((a == 0 && b == 0) || (c == 1 && b == 1)) return 3;
        else if((a == 0 && c == 1) || (c == 0 && b == 0)) return 4;
        else return 5;
    }
}

unsigned int Graph::binary_search(const unsigned int *array, int b, int e, int val) {
#ifdef _DEBUG_
    if(e < b) printf("??? WA1 in binary_search\n");
#endif
    -- e;
    if(array[e] < val) return e+1;
    while(b < e) {
        int mid = b + (e-b)/2;
        if(array[mid] >= val) e = mid;
        else b = mid+1;
    }
#ifdef _DEBUG_
    if(array[e] < val) printf("??? WA2 in binary_search\n");
#endif
    return e;
}


int Graph::BinarySearch(int *a, int value, int n){
    int low, high, mid;
    low = 0;
    high = n-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(a[mid]==value)
            return 1;
        if(a[mid]>value)
            high = mid-1;
        if(a[mid]<value)
            low = mid+1;
    }
    return 0;
}

int Graph::BinarySearch2(int *a, int value, int b, int e){
    int low, high, mid;
    low = b;
    high = e-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(a[mid]==value)
            return 1;
        if(a[mid]>value)
            high = mid-1;
        if(a[mid]<value)
            low = mid+1;
    }
    return 0;
}
unsigned int Graph::BinarySearch4(unsigned int *a,unsigned int value,unsigned int b, unsigned int e){
    long low, high, mid;
    low = b;
    high = e-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(a[mid]==value)
            return (unsigned int)mid;
        if(a[mid]>value)
            high = mid-1;
        if(a[mid]<value)
            low = mid+1;
    }
    return m;
}

int Graph::BinarySearch3(vector<int> a, int value){
    int low, high, mid;
    low = 0;
    high = (int)a.size()-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(a[mid]==value)
            return 1;
        if(a[mid]>value)
            high = mid-1;
        if(a[mid]<value)
            low = mid+1;
    }
    return 0;
}

int Graph::BinarySearch_edge_nei(point2 *a, int value,unsigned int b, unsigned int e){
    long low, high, mid;
    low = b;
    high = e-1;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(a[mid].vertex == value)
            return (unsigned int)mid;
        if(a[mid].vertex>value)
            high = mid-1;
        if(a[mid].vertex<value)
            low = mid+1;
    }
    return m;
}

void Graph::initReverse(){
    for(unsigned int i = 0;i<n;i++){
        for(unsigned int j = pstart[i]; j<pstart[i+1];j++){
            unsigned int v = edges[j];
            if(v<i) continue;
            unsigned int reverse_edge_id = binary_search(edges, pstart[v], pstart[v+1], i);
            reverse[j] = reverse_edge_id;
            reverse[reverse_edge_id] = j;
        }
    }
}


bool comp(float* s1,float* s2){//相似度从大到小
    
    return s1[1]>s2[1];
}


bool comp2(float* s1,float* s2){//相邻点从小到大
    
    return s1[0]<s2[0];
}

bool comp3(point s1,point s2){//相似度从大到小
    
    return s1.value>s2.value;
}

void Graph::getNeighborOrder(){
    
    neighbor_order_c2 = new point[edge_m];
    neighbor_order_f2 = new point[edge_m];
    
    for(int i = 0;i<n;i++){
        unsigned int low_all = pstart[i], high_all = pstart[i+1];
        unsigned int low_edge = edge_start[i], high_edge = edge_start[i+1];
        unsigned int low_nei = neighbor_start[i], high_nei = neighbor_start[i+1];
        
        while(low_all<high_all && low_edge<high_edge && low_nei<high_nei){
            if(edges[low_all] == edge[low_edge].vertex && edges[low_all] == neighbor[low_nei].vertex){
                int v = edges[low_all];
                neighbor_order_c2[reverse[low_all]].value = neighbor_order_c2[low_all].value = (edge[low_edge].cycle + neighbor[low_nei].cycle + 4) / (2*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_c2[reverse[low_all]].vertex = i;
                neighbor_order_c2[low_all].vertex = v;
                
                neighbor_order_f2[reverse[low_all]].value = neighbor_order_f2[low_all].value = (edge[low_edge].flow + neighbor[low_nei].flow + 12) / (6*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_f2[reverse[low_all]].vertex = i;
                neighbor_order_f2[low_all].vertex = v;
                
                low_nei++;
                low_all++;
                low_edge++;
            }else if(edges[low_all] == edge[low_edge].vertex && edge[low_edge].value != -1){
                int v = edges[low_all];
                unsigned int nei_position = BinarySearch_edge_nei(neighbor, i, neighbor_start[v], neighbor_start[v + 1]);
                neighbor[nei_position].value = -1;
                
                neighbor_order_c2[reverse[low_all]].value = neighbor_order_c2[low_all].value = (edge[low_edge].cycle + neighbor[nei_position].cycle + 4) / (2*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_c2[reverse[low_all]].vertex = i;
                neighbor_order_c2[low_all].vertex = v;
                
                neighbor_order_f2[reverse[low_all]].value = neighbor_order_f2[low_all].value = (edge[low_edge].flow + neighbor[nei_position].flow + 12) / (6*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_f2[reverse[low_all]].vertex = i;
                neighbor_order_f2[low_all].vertex = v;
                
                low_all++;
                low_edge++;
                
            }else if(edges[low_all] == neighbor[low_nei].vertex && neighbor[low_nei].value != -1){
                int v = edges[low_all];
                unsigned int edge_position = BinarySearch_edge_nei(edge, i, edge_start[v], edge_start[v + 1]);
                neighbor[edge_position].value = -1;
                
                neighbor_order_c2[reverse[low_all]].value = neighbor_order_c2[low_all].value = (edge[edge_position].cycle + neighbor[low_nei].cycle + 4) / (2*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_c2[reverse[low_all]].vertex = i;
                neighbor_order_c2[low_all].vertex = v;
                
                neighbor_order_f2[reverse[low_all]].value = neighbor_order_f2[low_all].value = (edge[edge_position].flow + neighbor[low_nei].flow + 12) / (6*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_f2[reverse[low_all]].vertex = i;
                neighbor_order_f2[low_all].vertex = v;
                
                low_all++;
                low_nei++;
            }else{
                low_all++;
            }
        }
        
        while(low_edge<high_edge){
            if(edge[low_edge].value != -1){
                int v = edges[low_all];
                unsigned int nei_position = BinarySearch_edge_nei(neighbor, i, neighbor_start[v], neighbor_start[v + 1]);
                neighbor[nei_position].value = -1;
                
                neighbor_order_c2[reverse[low_all]].value = neighbor_order_c2[low_all].value = (edge[low_edge].cycle + neighbor[nei_position].cycle + 4) / (2*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_c2[reverse[low_all]].vertex = i;
                neighbor_order_c2[low_all].vertex = v;
                
                neighbor_order_f2[reverse[low_all]].value = neighbor_order_f2[low_all].value = (edge[low_edge].flow + neighbor[nei_position].flow + 12) / (6*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_f2[reverse[low_all]].vertex = i;
                neighbor_order_f2[low_all].vertex = v;
                
            }
            
            low_all++;
            low_edge++;
        }
        
        while(low_nei<high_nei){
            if(neighbor[low_nei].value != -1){
                int v = edges[low_all];
                unsigned int edge_position = BinarySearch_edge_nei(edge, i, edge_start[v], edge_start[v + 1]);
                neighbor[edge_position].value = -1;
                
                neighbor_order_c2[reverse[low_all]].value = neighbor_order_c2[low_all].value = (edge[edge_position].cycle + neighbor[low_nei].cycle + 4) / (2*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_c2[reverse[low_all]].vertex = i;
                neighbor_order_c2[low_all].vertex = v;
                
                neighbor_order_f2[reverse[low_all]].value = neighbor_order_f2[low_all].value = (edge[edge_position].flow + neighbor[low_nei].flow + 12) / (6*(float)pow((long)((long)(degree[i]+1) * (long)(degree[v]+1)),0.5));
                neighbor_order_f2[reverse[low_all]].vertex = i;
                neighbor_order_f2[low_all].vertex = v;
            }
            low_all++;
            low_nei++;
        }
    }
    for(int i = 0;i<n;i++){
        sort(neighbor_order_c2+pstart[i], neighbor_order_c2+pstart[i+1],comp3);
        sort(neighbor_order_f2+pstart[i], neighbor_order_f2+pstart[i+1],comp3);
    }
}

void Graph::getCoreOrder(){
    cout<<"max_degree:"<<max_degree<<endl;
    core_order_c2 = new point*[max_degree];
    core_order_f2 = new point*[max_degree];
    max_degree_num = new int[max_degree];
    
    int *core_degree = new int[n];
    int *circulate_core = new int[n];
    int circulate_corei = 0;
    
    for(int i = 0;i<n;i++){
        core_degree[i] = degree[i];
        if(degree[i] > 0)
            circulate_core[circulate_corei++] = i;
    }
    int circulate = 0;
    int corei, circulate_corei2;
    for(int i = 0;i<max_degree;i++){
        //if(i%10 == 0 && i<1000) cout<<i<<endl;
        corei = 0;
        core_order_c2[i] = new point[circulate_corei];
        core_order_f2[i] = new point[circulate_corei];
        max_degree_num[circulate] = circulate_corei;
        circulate_corei2 = circulate_corei;
        circulate_corei = 0;
        for(int j2 = 0;j2<circulate_corei2;j2++){
            int j = circulate_core[j2];
            core_order_c2[i][corei].vertex = j;
            core_order_c2[i][corei].value = neighbor_order_c2[pstart[j] + circulate].value;
            
            core_order_f2[i][corei].vertex = j;
            core_order_f2[i][corei].value = neighbor_order_f2[pstart[j] + circulate].value;
            
            core_degree[j]--;
            if(core_degree[j] > 0) circulate_core[circulate_corei++] = j;
            corei++;
                
        }
        
        sort(core_order_c2[i],core_order_c2[i]+corei,comp3);
        sort(core_order_f2[i],core_order_f2[i]+corei,comp3);
        
        circulate++;
    }
    if(core_degree!=NULL){
        delete[] core_degree; core_degree = NULL;
    }
    if(circulate_core!=NULL){
        delete[] circulate_core; circulate_core = NULL;
    }
    
}

void Graph::writeIndex(){
    ofstream fout(str+"/index/degree.txt",ios::out); //创建待写入数据文件
    fout<<n<<" "<<m<<" "<<edge_m<<" "<<max_degree<<"\n";
    for(int i = 0; i< n-1;i++) fout<<(long)degree[i]<<"\n";
    fout<<(long)degree[n-1];
    fout.close();
    
    ofstream fout2(str+"/index/nei_order_c.txt",ios::out); //创建待写入数据文件
    for(int i = 0; i< n-1;i++){
        for(int j = pstart[i]; j<pstart[i+1]; j++){
            fout2<<(long)neighbor_order_c2[j].vertex<<" "<<neighbor_order_c2[j].value<<"\n";
        }
    }
    for(int j = pstart[n-1]; j<pstart[n]-1; j++){
        fout2<<(long)neighbor_order_c2[j].vertex<<" "<<neighbor_order_c2[j].value<<"\n";
    }
    fout2<<(long)neighbor_order_c2[pstart[n]-1].vertex<<" "<<neighbor_order_c2[pstart[n]-1].value;
    fout2.close();
    
    ofstream fout3(str+"/index/nei_order_f.txt",ios::out); //创建待写入数据文件
    for(int i = 0; i< n-1;i++){
        for(int j = pstart[i]; j<pstart[i+1]; j++){
            fout3<<(long)neighbor_order_f2[j].vertex<<" "<<neighbor_order_f2[j].value<<"\n";
        }
    }
    for(int j = pstart[n-1]; j<pstart[n]-1; j++){
        fout3<<(long)neighbor_order_f2[j].vertex<<" "<<neighbor_order_f2[j].value<<"\n";
    }
    fout3<<(long)neighbor_order_f2[pstart[n]-1].vertex<<" "<<neighbor_order_f2[pstart[n]-1].value;
    fout3.close();
    
    ofstream fout4(str+"/index/core_order_c.txt",ios::out); //创建待写入数据文件
    for(int i = 0;i<max_degree-1;i++){
        fout4<<i+2<<" "<<max_degree_num[i]<<"\n";
        for(int j = 0;j<max_degree_num[i];j++){
            fout4<<(long)core_order_c2[i][j].vertex<<" "<<core_order_c2[i][j].value<<"\n";
        }
    }
    fout4<<max_degree+1<<" "<<max_degree_num[max_degree-1]<<"\n";
    for(int j = 0;j<max_degree_num[max_degree-1]-1;j++)
        fout4<<(long)core_order_c2[max_degree-1][j].vertex<<" "<<core_order_c2[max_degree-1][j].value<<"\n";
    fout4<<(long)core_order_c2[max_degree-1][max_degree_num[max_degree-1]-1].vertex<<" "<<core_order_c2[max_degree-1][max_degree_num[max_degree-1]-1].value;
    fout4.close();
    
    ofstream fout5(str+"/index/core_order_f.txt",ios::out); //创建待写入数据文件
    for(int i = 0;i<max_degree-1;i++){
        fout5<<i+2<<" "<<max_degree_num[i]<<"\n";
        for(int j = 0;j<max_degree_num[i];j++)
            fout5<<(long)core_order_f2[i][j].vertex<<" "<<core_order_f2[i][j].value<<"\n";
    }
    fout5<<max_degree+1<<" "<<max_degree_num[max_degree-1]<<"\n";
    for(int j = 0;j<max_degree_num[max_degree-1]-1;j++)
        fout5<<(long)core_order_f2[max_degree-1][j].vertex<<" "<<core_order_f2[max_degree-1][j].value<<"\n";
    fout5<<(long)core_order_f2[max_degree-1][max_degree_num[max_degree-1]-1].vertex<<" "<<core_order_f2[max_degree-1][max_degree_num[max_degree-1]-1].value;
    fout5.close();
}




