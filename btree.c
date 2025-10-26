#include<stdio.h>
#include<stdlib.h>>
#include<stdbool.h>

#define M 4


typedef struct btreeNode{
    int num_of_keys;
    int keys[M-1];
    btreeNode *children[M];
    bool isLeaf;
}btreeNode;



btreeNode *createNode(bool isLeaf){
    btreeNode *newNode = (btreeNode*)malloc(sizeof(btreeNode));
    if (newNode == NULL){
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newNode->num_of_keys = 0;
    newNode->isLeaf = isLeaf;
    for (int i = 0; i < M; i++){
        newNode->children[i] = NULL;
    }
    return newNode;
}


void splitChild(btreeNode *parent, int index){
    btreeNode *child = parent->children[index];
    btreeNode *newNode = createNode(child->isLeaf);

    newNode->num_of_keys = M/2;

    for (int i = 0; i < M/2; i++){
        newNode->keys[i] = child->keys[i + M/2 - 1];
    }

    if (!child->isLeaf){
        for (int i = 0; i < M/2; i++){
            newNode->children[i] = child->children[i+M/2];
        }
    }

    child->num_of_keys = M/2 - 1;


    for (int i = parent->num_of_keys - 1; i > index; i--){
        parent->children[i+1] = parent->children[i];
    }

    parent->children[index+1] = newNode;

    

}