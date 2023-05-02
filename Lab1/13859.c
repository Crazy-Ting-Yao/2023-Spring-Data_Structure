#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
typedef struct route{
    char name[100];
    int time;
    struct route* next;
}Route;
typedef struct toast{
    int table;
    int glasses;
    struct toast* next;
}Toast;
int main(){
    char c;
    Toast *head, *tail;
    Route *outermost = NULL;
    head = tail = malloc(sizeof(Toast));
    head->next = NULL;
    while (scanf(" %c",&c)!=EOF){
        if(c=='R'){
            Route* current = malloc(sizeof(Route));
            current->next = outermost;
            outermost = current;
            scanf("%s %d",outermost->name,&outermost->time);
        }
        else if(c=='T'){
            tail->next = malloc(sizeof(Toast));
            tail = tail->next;
            scanf("%d %d",&tail->table,&tail->glasses);
        }
    }
    int latest = outermost->time;
    while(outermost->next){
        printf("%s ",outermost->name);
        Route* temp = outermost;
        outermost = outermost->next;
        free(temp);
    }
    latest-=outermost->time;
    printf("%s \n%d\n", outermost->name,latest);
    free(outermost);
    int g=0;
    Toast* temp = head;
    head = head->next;
    free(temp);
    while(head){
        g+=head->glasses;
        printf("%d ",head->table);
        Toast* temp = head;
        head = head->next;
        free(temp);
    }
    printf("\n%d\n",g);
    return 0;
}