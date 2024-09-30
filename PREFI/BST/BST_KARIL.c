#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int elem;
    struct node *left;
    struct node *right;
}*Tree;

void insert(Tree *T, int number){
    Tree *trav, temp;

    for(trav = T; *trav != NULL && (*trav)->elem != number;){
        trav = ((*trav)->elem < number) ? &(*trav)->right : &(*trav)->left;
    }
    if(*trav == NULL){
        temp = (Tree)calloc(1, sizeof(struct node));
        temp->elem = number;
        *trav = temp;
    }
}

void displayTree(Tree T){
    if(T != NULL){
        printf("%d " ,T->elem);
        displayTree(T->left);
        displayTree(T->right);
    }
}


void deleteNode(Tree *T, int number){
    Tree *trav, temp;

    for(trav = T; *trav != NULL && (*trav)->elem != number;){
        trav = ((*trav)->elem < number) ? &(*trav)->right : &(*trav)->left;
    }

    if(*trav != NULL){
        
        // first two if conditions are if you're deleting a node with only one child.
        if((*trav)->left == NULL){
            *trav = (*trav)->right;
            free((*trav)->right);
        }else if((*trav)->right == NULL){
            *trav = (*trav)->left;
            free((*trav)->left);
        }else{
            // else condition is for when you have two children and you need to do
            temp = (*trav)->right;
            while(temp->left != NULL){
                temp = temp->left;
            }
            (*trav)->elem = temp->elem;
            (*trav)->left = temp->left;
            free(temp);
        }
    }
}

int main(){

    Tree T = NULL;

    int arr[] = {10,30,5,18,1,25,22,15,6};

    for(int i = 0; i < 9; i++){
        insert(&T, arr[i]);
    }

    deleteNode(&T, arr[5]);

    displayTree(T);

}

