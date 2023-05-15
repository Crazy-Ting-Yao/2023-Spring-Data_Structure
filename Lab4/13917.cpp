#include <string.h>
#include <cmath>
#include <iostream>
#include <vector>

typedef struct {
    int id;
    int distance;
}info;

typedef struct{
    bool passed;
    std::vector<info> connection;
}node;

int tt;
node* nodes;
int* dist_list;

void Dijkstra(int end) {
    for (int k = 0; k < tt; k++) {
        int min = 1e9, id = 0;
        for (int i = 0; i < tt; i++)
            if (!nodes[i].passed && dist_list[i] < min) {
                min = dist_list[i];
                id = i;
            }
        if (min == 1e9 || id == end) return;
        nodes[id].passed = true;
        for (int i = 0; i < nodes[id].connection.size(); i++) {
            int id2 = (nodes[id].connection[i].id);
            int new_dist = dist_list[id] + nodes[id].connection[i].distance;
            if (dist_list[id2] > new_dist) dist_list[id2] = new_dist;
        }
    }
}

int main() {
    std::string op;
    int distance;
    int id1, id2;
    std::cin>>op;
    std::cin>>tt;
    info info1, info2;
    nodes = new node[tt];
    dist_list = new int[tt];
    while (true) {
        if (op == "INSERT_DISTANCE"){
            std::cin>>id1>>id2>>distance;
            info1.id = id2-1;
            info2.id = id1-1;
            info1.distance = info2.distance = distance;
            nodes[id1-1].connection.push_back(info1);
            nodes[id2-1].connection.push_back(info2);           
        }
        else if (op == "TERMINATE") break;
        else if (op == "CALCULATE"){
            std::cin>>id2;
            for(int i=0;i<tt;i++){
                nodes[i].passed = false;
                dist_list[i] = 1e9;
            }
            dist_list[0] = 0;
            Dijkstra(id2-1);
            std::cout<<dist_list[id2-1]<<std::endl;
        }
    }
    delete [] nodes;
    delete [] dist_list;
    return 0;
}