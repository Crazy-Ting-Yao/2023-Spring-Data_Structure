#include<iostream>
#include<string>

using namespace std;
int first;
class Node {
    friend class real_world;
    public:
        int star;
        Node* left;
        Node* right;
        Node(int star) {
            this->star = star;
            this->left = this->right = NULL;
        }
};

class real_world {
    public:
        Node* left;
        Node* right;
        real_world() {
            this->left = NULL;
            this->right = NULL;
        }
};

void preorder(Node* root) {
    if(root == NULL) {
        return;
    }
    if(first == 0){
        cout<<root->star<<"*";
        first = 1;
    }
    else cout<<" "<<root->star<<"*";
    preorder(root->left);
    preorder(root->right);
    delete root;
}

int main(){
    real_world* world = new real_world();
    string command;
    int attack=0;
    cin>>command;
    while(command != "TheEnd") {
        if(command == "Summon"){
            cin>>command;
            int star;
            cin>>star;
            cin>>command;
            if(star<=4){
                if(world->left == NULL){
                    world->left = new Node(star);
                } 
                else{
                    world->right = new Node(star);
                }
            }
            else if(star<=6){
                if(world->left == NULL){
                    Node* temp = world->right;
                    world->right = new Node(star);
                    world->right->right = temp;
                } 
                else if(world->right == NULL){
                    Node* temp = world->left;
                    world->left = new Node(star);
                    world->left->left = temp;
                }
                else if(world->left->star<=world->right->star){
                    Node* temp = world->left;
                    world->left = new Node(star);
                    world->left->left = temp;
                }
                else{
                    Node* temp = world->right;
                    world->right = new Node(star);
                    world->right->right= temp;
                }
            }
            else{
                Node* temp = new Node(star);
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
        cin>>command;
    }
    preorder(world->left);
    preorder(world->right);
    cout<<endl<<attack<<endl;
    delete world;
}

