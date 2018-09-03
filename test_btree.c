#include<stdio.h>
#include<stdlib.h>

typedef struct TagBtreeNode{
        int n;
        int *keys;
        struct TagBtreeNode** child;
        int leaf;
}BtreeNode;

typedef struct TagBtree{
        BtreeNode* root;
        int h;
        int t;
}Btree;

int leaf(BtreeNode* bNode){

        return bNode->leaf;
}

BtreeNode* b_tree_search(Btree* btree,int key){

        BtreeNode* btreeNode;
        int i;

        btreeNode = btree->root;
        while(1){
                for(i = 0;i < btreeNode->n;i++){
                        if(btreeNode->keys[i] == key){
                                return btreeNode;//return n?
                        }
                        if(btreeNode->keys[i] > key){
                                break;
                        }
                }
                if(leaf(btreeNode)){
                        return NULL;
                }
                btreeNode = btreeNode->child[i];
        }
}

Btree* b_tree_create(int t){

        Btree* btree = malloc(sizeof(Btree));
        BtreeNode* root = malloc(sizeof(BtreeNode));

        if(!btree || !root){
                return btree;
        }
        root->n = 0;
        root->leaf = 1;
        btree->root = root;
        btree->h = 0;
        btree->t = t;
}

BtreeNode* b_tree_split(BtreeNode* x,int i,BtreeNode* y){

        int *tempkeys = malloc(sizeof(int)*n+1);
        BtreeNode** tempchild = malloc(sizeof(BtreeNode*)*(n+1));
        BtreeNode* y1,*y2;

        y1 = y;
        y1->n /= 2;

        y2 = malloc(sizeof(BTreeNode));
        y2->n = y1->n;
        y2->leaf = y1->leaf;
        y2->keys = malloc(sizeof(int)*(y2->n));
        y2->child = malloc(sizeof(BtreeNode*)*(y2->n)/2);
        memcpy()

        memcpy(tempkeys,x->keys,i);
        tempkeys[i] = y->keys[(n+1)/2];
        memcpy(temkeys+i+1,x->keys,x->n-i);
        free(x->keys);
        x->keys = tempkeys;

        memcpy(tempchild,x->child,i);
        tempchild[i+1] = ;
        memcpy(temchild+i+1,x->child,x->n-i);

        
}

int isFull(BtreeNode* btreeNode){
}

int b_tree_insert(Btree* btree,int key){

        BtreeNode* btreeNode;
        int *tempkeys;
        int  i;

        btreeNode = btree->root;
        while(1){
                if(isFull(btreeNode)){
                        node1,node2 = b_tree_split(btreeNode);
                        if(btreeNode->keys[i/2] > key){
                                btreeNode = node1;
                        }else{
                                btreeNode = node2;
                        }
                }
                for(i = 0;i < btreeNode->n;i++){
                        if(btreeNode->keys[i] == key){
                                return -1; 
                        }
                        if(btreeNode->keys[i] > key){
                                break;
                        }
                }
                if(leaf(btreeNode)){
                        tempkeys = malloc(sizeof(int)*(++btreeNode->n));
                        memcpy(tempkeys,btreeNode->keys,i);
                        tempkeys[i] = key;
                        memcpy(tempkeys+i+1,btreeNode->keys+i+1,n-i-1);
                        free(btreeNode->keys);
                        btreeNode->keys = tempkeys;
                        return 0;
                }
                btreeNode = btreeNode->child[i];
        }
}

int main(){

        return 0;
}
