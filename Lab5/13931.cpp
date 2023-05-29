#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

unsigned abs(unsigned a, unsigned b){
    if(a>b)
        return a-b;
    else
        return b-a;
}

class Data {
    public:
    unsigned v;
    unsigned prevpos;
    unsigned id;
    bool operator<(const Data& right) const {
        return v < right.v;
    }
};

class Price {
    public:
    unsigned price;
    unsigned id;
    bool operator<(const Price& right) const{
        return price < right.price;
    }   
};



int main(){
    ios::sync_with_stdio(false);
    unsigned n,m;
    cin>>n>>m;
    vector<Data> data(m);
    vector<Price> pos(m);
    vector<string> v(m);
    for(unsigned i=0;i<m;i++){
        cin>>v[i];
    }
    for (unsigned i=0;i<m;i++){
        cin>>pos[i].price;
        pos[i].id = i;
        data[i].v = 0;
        data[i].id = i;
    }
    sort(pos.begin(), pos.end());
    for(unsigned j=0;j<m;j++){
        data[pos[j].id].prevpos = j;
    }
    for (unsigned i=1;i<n;i++){
        pos.clear();
        pos.resize(m);
        for(unsigned j=0;j<m;j++){
            cin>>pos[j].price;
            pos[j].id = j;
        }
        sort(pos.begin(), pos.end());
        for(unsigned j=0;j<m;j++){
            data[pos[j].id].v += abs(data[pos[j].id].prevpos,j);
            data[pos[j].id].prevpos = j;
        }
    }
    sort(data.begin(), data.end());
    cout<<v[data[0].id]<<endl;
}