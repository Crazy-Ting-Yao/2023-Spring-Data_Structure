#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct{
    unsigned short value;
    unsigned short weight;
}Items;
Items* item;
int n,k;
unsigned min = UINT_MAX;
void recursion(int index,int val,int wgh){
    if(val>=k){
        if(wgh<min) min = wgh;
        return;
    }
    for(int i=index;i<n;i++) recursion(i+1,val+item[i].value,wgh+item[i].weight);
}
int main(){
    scanf("%d %d",&n,&k);
    item = malloc(sizeof(Items)*n);
    for(int i=0;i<n;i++) scanf("%hu %hu",&item[i].value,&item[i].weight);
    recursion(0,0,0);
    printf("%u\n",min);
    return 0;
}