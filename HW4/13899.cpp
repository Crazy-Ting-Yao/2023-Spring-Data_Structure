#include <string.h>
#include <cmath>
#include <iostream>
#include <vector>

typedef enum { SOURCE, SPY, CIV, HQ } nodetype;

typedef struct {
    int messages, id;
    double distance;
} info;

std::vector<double> dist_list;

class node {
   public:
    static unsigned int counter, startpos, endpos;

    int id;
    bool passed = false;
    unsigned int message_carried = 0;
    nodetype type;
    std::string name;

    std::vector<info> connection;
    std::vector<int> path;

    node(nodetype type, std::string& name) {
        this->type = type;
        if (type == SOURCE)
            startpos = counter;
        else if (type == HQ)
            endpos = counter;
        this->id = counter++;
        this->name = name;
        dist_list.push_back(1e9);
    }
};

std::vector<node*> nodes;

unsigned int node::counter = 0;
unsigned int node::startpos = 0;
unsigned int node::endpos = 0;

void Dijkstra() {
    for (int k = 0; k < node::counter; k++) {
        int min = 1e9, id = 0;
        for (int i = 0; i < node::counter; i++)
            if (!nodes[i]->passed && dist_list[i] < min) {
                min = dist_list[i];
                id = i;
            }
        if (min == 1e9 || id == (node::endpos)) return;
        nodes[id]->passed = true;
        for (int i = 0; i < nodes[id]->connection.size(); i++) {
            int id2 = (nodes[id]->connection[i].id);
            double new_dist = dist_list[id] + nodes[id]->connection[i].distance;
            unsigned int new_messages = nodes[id]->message_carried + nodes[id]->connection[i].messages;
            if (dist_list[id2] < new_dist) continue;
            else if (dist_list[id2] == 1e9 || dist_list[id2] > new_dist) {
                dist_list[id2] = new_dist;
                nodes[id2]->message_carried = new_messages;
                nodes[id2]->path = nodes[id]->path;
                nodes[id2]->path.push_back(id2);
            } 
            else {
                int size = nodes[id]->path.size();
                if (nodes[id2]->path.size() < size) size = nodes[id2]->path.size();
                for (int j = 0; j < size; j++) {
                    if (nodes[id2]->path[j] < nodes[id]->path[j]) break;
                    else if (nodes[id2]->path[j] > nodes[id]->path[j]) {
                        nodes[id2]->message_carried = new_messages;
                        nodes[id2]->path = nodes[id]->path;
                        nodes[id2]->path.push_back(id2);
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    std::string op, type, name;
    int id1, id2;
    double msg;
    while (std::cin >> op) {
        if (op == "ANALYZE")
            break;
        else if (op == "INSERT") {
            std::cin >> type >> name;
            if (type == "SOURCE")
                nodes.push_back(new node(SOURCE, name));
            else if (type == "SPY")
                nodes.push_back(new node(SPY, name));
            else if (type == "HQ")
                nodes.push_back(new node(HQ, name));
            else if (type == "CIV")
                nodes.push_back(new node(CIV, name));
        } 
        else {
            std::cin >> id1 >> id2 >> msg;
            id1--; id2--;
            if (nodes[id1]->type == SOURCE && nodes[id2]->type == SPY) continue;
            if (nodes[id1]->type == SPY && nodes[id2]->type == SOURCE) continue;
            if (nodes[id1]->type == SPY && nodes[id2]->type == SPY) continue;
            if (nodes[id1]->type == CIV && nodes[id2]->type == HQ) continue;
            if (nodes[id1]->type == HQ && nodes[id2]->type == CIV) continue;
            if (msg <= 0) continue;
            else {
                info info1, info2;
                info1.distance = info2.distance = round(100000 / msg) / 100;
                info1.id = id2;
                info2.id = id1;
                info1.messages = info2.messages = (unsigned int)msg;
                nodes[id1]->connection.push_back(info1);
                nodes[id2]->connection.push_back(info2);
            }
        }
    }
    dist_list[node::startpos] = 0;
    nodes[node::startpos]->path.push_back(node::startpos);
    Dijkstra();
    for (int i = 0; i < nodes[node::endpos]->path.size() - 1; i++)
        std::cout << nodes[nodes[node::endpos]->path[i]]->name << " -> ";
    std::cout << nodes[node::endpos]->name << std::endl;
    std::cout << nodes[node::endpos]->message_carried << std::endl
              << dist_list[node::endpos] << std::endl;
    for (int i = 0; i < nodes.size(); i++) delete nodes[i];
    return 0;
}