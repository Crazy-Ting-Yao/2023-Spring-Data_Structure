#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int first;
typedef struct node {
    int star;
    struct node* left;
    struct node* right;
}Node;

void preorder(Node* root) {
    if(root == NULL) {
        return;
    }
    if(first == 0){
        printf("%d*", root->star);
        first = 1;
    }
    else printf(" %d*", root->star);
    preorder(root->left);
    preorder(root->right);
    free(root);
}

int main(){
    Node* world = malloc(sizeof(Node));
    world->left = NULL;
    world->right = NULL;
    char command[10];
    int attack=0;
    scanf("%s",command);
    while(strcmp(command,"TheEnd")) {
        if(!strcmp(command,"Summon")){
            int star=1;
            scanf(" %s",command);
            scanf(" %d",&star);
            scanf(" %s",command);
            if(star<=4){
                if(world->left == NULL){
                    world->left = malloc(sizeof(Node));
                    world->left->star = star;
                    world->left->right = world->left->left = NULL;
                } 
                else{
                    world->right = malloc(sizeof(Node));
                    world->right->star = star;
                    world->right->right = world->right->left = NULL;
                }
            }
            else if(star<=6){
                if(world->left == NULL){
                    Node* temp = world->right;
                    world->right = malloc(sizeof(Node));
                    world->right->right = world->right->left = NULL;
                    world->right->star = star;
                    world->right->right = temp;
                } 
                else if(world->right == NULL){
                    Node* temp = world->left;
                    world->left = malloc(sizeof(Node));
                    world->left->right = world->left->left = NULL;
                    world->left->star = star;
                    world->left->left = temp;
                }
                else if(world->left->star<=world->right->star){
                    Node* temp = world->left;
                    world->left = malloc(sizeof(Node));
                    world->left->right= NULL;
                    world->left->star = star;
                    world->left->left = temp;
                }
                else{
                    Node* temp = world->right;
                    world->right = malloc(sizeof(Node));
                    world->right->left = NULL;
                    world->right->star = star;
                    world->right->right= temp;
                }
            }
            else{
                Node* temp = malloc(sizeof(Node));
                temp->star = star;
                temp->left = world->left;
                temp->right = world->right;
                world->left = temp;
                world->right = NULL;
            }
        }
        else{
            if(world->left){
                attack += world->left->star;
            }
            if(world->right){
                attack += world->right->star;
            }
        }
        scanf("%s",command);
    }
    preorder(world->left);
    preorder(world->right);
    printf("\n%d\n",attack);
    free(world);
}

