#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum{
    Clubs,
    Diamonds,
    Heart,
    Spade
}Cards;

typedef struct node{
    int points;
    Cards type;
    struct node *left, *right; 
}Node;

typedef struct{
    struct node *left, *right; 
}Table;

int heart_traverse(Node* head){
    if(head){
        return head->points+heart_traverse(head->left)+heart_traverse(head->right);
    }
    return 0;
}


int final_traverse(Node* head){
    if(head){
        if(head->type==Heart) return head->points+final_traverse(head->left)+final_traverse(head->right);
        else return final_traverse(head->left)+final_traverse(head->right);
    }
    return 0;
}

void free_table(Node* head){
    if(head){
        free_table(head->left);
        free_table(head->right);
        free(head);
    }
}

int main(){
    Table* table = malloc(sizeof(Table));
    table->left = table->right = NULL;
    char draw_card[10];
    while(1){
        scanf("%s",draw_card);
        if(!strcmp(draw_card,"Spade")) break;
        if(!strcmp(draw_card,"Clubs")){
            if(!table->left){
                table->left = malloc(sizeof(Node));
                table->left->points = 1;
                table->left->type = Clubs;
                table->left->left = table->left->right = NULL;
            }
            else if(!table->right){
                table->right = malloc(sizeof(Node));
                table->right->points = 1;
                table->right->type = Clubs;
                table->right->left = table->right->right = NULL;
            }
        }
        else if(!strcmp(draw_card,"Diamond")){
            if((!table->left)&&(!table->right)) continue;
            if(!table->left){
                Node* temp = malloc(sizeof(Node));
                temp->right = table->right;
                table->right = temp;
                temp->type = Diamonds;
                temp->points = 3;
                temp->left = NULL;
            }
            else if(!table->right){
                Node* temp = malloc(sizeof(Node));
                temp->left = table->left;
                table->left = temp;
                temp->type = Diamonds;
                temp->points = 3;
                temp->right = NULL;
            }
            else{
                if(table->left->points>table->right->points){
                    Node* temp = malloc(sizeof(Node));
                    temp->right = table->right;
                    table->right = temp;
                    temp->type = Diamonds;
                    temp->points = 3;
                    temp->left = NULL;
                }
                else{
                    Node* temp = malloc(sizeof(Node));
                    temp->left = table->left;
                    table->left = temp;
                    temp->type = Diamonds;
                    temp->points = 3;
                    temp->right = NULL;                    
                }
            }
        }
        else if(!strcmp(draw_card,"Heart")){
            if((!table->left)||(!table->right)) continue;
            Node* temp = malloc(sizeof(Node));
            temp->left = table->left;
            temp->right = table->right;
            table->left = temp;
            table->right = NULL;
            temp->type = Heart;
            temp->points = heart_traverse(temp->left) - heart_traverse(temp->right);
        }
    }
    int ans = final_traverse(table->left) + final_traverse(table->right);
    printf("%d\n",ans);
    free_table(table->left);
    free_table(table->right);
    free(table);
}