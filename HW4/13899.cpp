#include<iostream>
#include<vector>
#include<string.h>
#include<cmath>
using namespace std;

typedef enum{
    SOURCE, SPY, CIV, HQ
}nodetype;

typedef struct{
    int messages;
    double distance;
    int id;
}info;

class node{
    public:
        int id;
        bool passed = false;
        nodetype type;
        vector<info> connection;
        vector<int> path;
        string name; 
        node(nodetype type, int id, string& name){
            this->type = type;
            this->id = id;
            this->name = name;
        }
        node(node& n){
            this->type = n.type;
            this->id = n.id;
            this->name = n.name;
        }
};

vector<node*> nodes;

double* dist_list;
int* msg_list;

int startpos, endpos;

bool* passed;

void Dijkstra(int n){
    for(int k=0;k<n;k++){
        int min = 1e9;
        int id = 0;
        for(int i=0;i<n;i++)
            if(!nodes[i]->passed && dist_list[i]<min){
                min = dist_list[i];
                id = i;
                if(!min) break;
            }
        if(min==1e9||id==(endpos-1)) return;
        nodes[id]->passed = true;
        for(int i=0;i<nodes[id]->connection.size();i++){
            int id2 = (nodes[id]->connection[i].id)-1;
            if(dist_list[id2]==1e9||dist_list[id2]>(dist_list[id] + nodes[id]->connection[i].distance)){
                dist_list[id2] = dist_list[id] + nodes[id]->connection[i].distance;
                msg_list[id2] = msg_list[id] + nodes[id]->connection[i].messages;
                nodes[id2]->path = nodes[id]->path;
                nodes[id2]->path.push_back(id+1);
            }
            else if(dist_list[id2]<(dist_list[id] + nodes[id]->connection[i].distance)) continue;
            else{
                nodes[id]->path.push_back(id+1);
                nodes[id2]->path.push_back(id2+1);
                int size = nodes[id]->path.size();
                if(nodes[id2]->path.size()<size) size = nodes[id2]->path.size();
                int j;
                for(j=0;j<size;j++){
                    if(nodes[id2]->path[j]<nodes[id]->path[j])break;
                    else if(nodes[id2]->path[j]>nodes[id]->path[j]){
                        msg_list[id2] = msg_list[id] + nodes[id]->connection[i].messages;
                        nodes[id2]->path = nodes[id]->path;
                        nodes[id2]->path.push_back(id+1);                        
                        break;
                    }
                }
                nodes[id]->path.pop_back();
                nodes[id2]->path.pop_back();
            }
        }
    }
}

int main(){
    string op, type, name;
    int id1, id2;
    double msg;
    int counter = 0;
    while(cin>>op){
        if(op=="ANALYZE") break;
        else if(op=="INSERT"){
            cin>>type>>name;
            if(type=="SOURCE"){
                node* tmp = new node(SOURCE, ++counter, name);
                nodes.push_back(tmp);
                startpos = counter;
            }
            else if(type=="SPY"){
                node* tmp = new node(SPY, ++counter, name);
                nodes.push_back(tmp);
            }
            else if(type=="HQ"){
                node* tmp = new node(HQ, ++counter, name);
                nodes.push_back(tmp);
                endpos = counter;
            }
            else if(type=="CIV"){
                node* tmp = new node(CIV, ++counter, name);
                nodes.push_back(tmp);
            }
        }
        else{
            cin>>id1>>id2>>msg;
            if(nodes[id1-1]->type==SOURCE&&nodes[id2-1]->type==SPY) continue;
            if(nodes[id1-1]->type==SPY&&nodes[id2-1]->type==SOURCE) continue;
            if(nodes[id1-1]->type==SPY&&nodes[id2-1]->type==SPY) continue;
            if(nodes[id1-1]->type==CIV&&nodes[id2-1]->type==HQ) continue;
            if(nodes[id1-1]->type==HQ&&nodes[id2-1]->type==CIV) continue;
            else if(msg<=0) continue;
            else{
                info info1, info2;
                info1.distance = info2.distance = round(100000/msg)/100;
                info1.id = id2; info2.id = id1;
                info1.messages = info2.messages = (int)msg;
                nodes[id1-1]->connection.push_back(info1);
                nodes[id2-1]->connection.push_back(info2);
            }
        }
    }
    dist_list = new double[counter];
    msg_list = new int[counter];
    for(int i=0;i<counter;i++) {dist_list[i] = 1e9; msg_list[i] = 0;}
    dist_list[startpos-1] = 0;
    Dijkstra(counter);
    for(int i=0;i<nodes[endpos-1]->path.size();i++) std::cout<<nodes[nodes[endpos-1]->path[i]-1]->name<<" -> ";
    std::cout<<nodes[endpos-1]->name<<endl;
    std::cout<<msg_list[endpos-1]<<endl<<dist_list[endpos-1]<<endl;
    delete [] dist_list;
    delete [] msg_list;
    for(int i=0;i<nodes.size();i++) delete nodes[i];
    return 0;
}