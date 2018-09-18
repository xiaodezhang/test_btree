#include<stdio.h>
#include<stdlib.h>

/* btree结点*/
typedef struct TagBtreeNode{
        int n;                         /*关键字数量*/
        int *keys;                     /*关键字数组*/
        struct TagBtreeNode** child;   /*子节点指针数组，数量为n+1*/
        int leaf;                      /*是否为叶节点*/
}BtreeNode;

/*btree指针，指向根结点*/
typedef struct TagBtree{
        BtreeNode* root;               /*根节点*/
        int h;                         /*树高度*/
        int t;                         /*最小度数 >= 2*/
}Btree;

int leaf(BtreeNode* bNode){

        return bNode->leaf;
}

BtreeNode* btree_search(Btree* btree,int key){

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

Btree* btree_create(int t){

        BtreeNode*  btree = malloc(sizeof(BtreeNode));

        if(!btree){
            return NULL;
        }
        btree->root = NULL;
        btree->h = 0;
        btree->t = t;
}

#if 0
BtreeNode* btree_split(BtreeNode* x,int i,BtreeNode* y){

        int *tempkeys = malloc(sizeof(int)*(x->n)+1);
        BtreeNode* y1,*y2;

        y1 = y;
        y1->n = y->n / 2;

        y2 = malloc(sizeof(BTreeNode));
        y2->n = y1->n;
        y2->leaf = y1->leaf;
        y2->keys = malloc(sizeof(int)*(y2->n));
        y2->child = malloc(sizeof(BtreeNode*)*(y2->n));
        for(i = y->n,j = y1->n;i >= y1->n;i--,j--){
                y2->child[j] = y->child[i];
                y1->child[j] = y->child[j];
        }

        memcpy(tempkeys,x->keys,i);
        tempkeys[i] = y->keys[(n+1)/2];
        memcpy(temkeys+i+1,x->keys,x->n-i);
        free(x->keys);
        x->keys = tempkeys;
        y = y1;
        return y2;
}
#endif

int isFull(BtreeNode* btreeNode,Btree* btree){

        return btreeNode->n ==  btree->t*2-1;
}
/**********************************************************************
 * *结点分裂
 **********************************************************************
 *return: 0 success -1 fail
 *param:
 *          node:待分裂结点
 *          node1,node2: out 传出分裂之后的两个结点
***********************************************************************/
static int node_split(BtreeNode*node,BtreeNode*node1,BtreeNode*node2){

        int j;

        node1 = malloc(sizeof(BtreeNode));
        node2 = malloc(sizeof(BtreeNode));

        if(!node1 || !node2)
                return -1;

        /*node分裂成node1,key,node2*/
        node1->n = node->n/2;
        node1->leaf = node->leaf;

        node2->n = node->n - node1->n-1;
        node2->leaf = node->leaf;

        for(j = 0;j < node1->n;j++){
                node1->keys[j] = node->keys[j];
                node1->child[j] = node->child[j];
        }
        for(j = 0;j < node2->n;j++){
                node2->keys[j] = node->keys[j+node1->n+1];
                node2->child[j] = node->keys[j+node1->n+1];
        }

        return 0;
}


/**********************************************************************
 * *树分裂函数，在结点满的情况下将结点分裂成三部分，位于中间的key上升
 * *到父结点
 **********************************************************************
 *return:node1,分裂值最小的部分，由原来父结点指向完整结点的指针指向
 *param:
*         Node:        in:需要分裂的结点
*                      out:node2,分裂值最大的部分，由父结点新增加的指针指向，
*                      新增加的指针在数组是i+1
*         parentNode： in:父结点
*                      out:新的父结点，增加了一个值和一个指针，直接插入原来的数组中
*         i:           in:parentNode->child[i] == node

***********************************************************************/
BtreeNode* btree_split(BtreeNode* node,BtreeNode* parentNode,int i){

        BtreeNode* node1,*node2,*tmpkeys,**tmpchild;
        int j;

        /*结点分裂*/
        if(node_split(node,node1,node2)!= 0)
                return NULL;

        tmpkeys = malloc(sizeof(int)*parentNode->n);
        tmpchild = malloc(sizeof(BtreeNode*)*(parentNode->n+1));

        /*父结点增加key值，增加指针指向node2 */
        memcpy(tmpkeys,parentNode->keys,i);
        memcpy(tmpkeys+i+1,parentNode->keys+i,parentNode->n-i);
        tmpkeys[i] = node->keys[node1->n];
        parentNode->keys[0] = tmpkeys[0];

        memcpy(tmpchild,parentNode->child,i+1);
        memcpy(tmpchild+i+2,parentNode->child+i+1,parentNode->n-i);
        tmpchild[i+1] = node2;
        parentNode->child[0] = tmpchild[0];

        parentNode->n++;

        free(node);
        node = node2;
        free(parentNode->keys);
        free(parentNode->child);

        return node1;
}
/**********************************************************************
 * *插入函数，唯一对根节点分裂使得树高度增加,直接分裂满的子节点，避免回溯
 **********************************************************************
 *return:0 sucess -1 fail
 *param:
 *      btree:插入树
 *      key:  待插入的值
***********************************************************************/
int btree_insert(Btree* btree,int key){

        BtreeNode* btreeNode,*node1,*node2
                ,*new_root;
        int *tempkeys;
        int  i;

        btreeNode = btree->root;
        /*根结点已满，分裂根结点，树高度增加1*/
        if(isFull(root,btree)){
                if(node_split(btreeNode,node1,node2) != 0)
                        return  -1;
                new_root = malloc(sizeof(BtreeNode));
                new_root->keys = malloc(sizeof(int));
                new_root->child = malloc(sizeof(BtreeNode*)*2);
                if(!new_root || !new_root->keys
                                ||!new_root->child)
                        return -1;
                new_root->n = 1;
                new_root->leaf = 0;
                new_root->child[0] = node1;
                new_root->child[1] = node2;
                new_root->keys[0] = node1[node1->n];
                btree->root = new_root;
                btree->h++;
        }

        while(1){
                /*查找最接近的值*/
                for(i = 0;i < btreeNode->n;i++){
                        if(btreeNode->keys[i] == key){
                                return -1;/*已经存在，直接退出*/ 
                        }
                        if(btreeNode->keys[i] > key){
                                break;
                        }
                }

                if(leaf(btreeNode)){
                        /*直接插入*/
                        tempkeys = malloc(sizeof(int)*(++btreeNode->n));
                        memcpy(tempkeys,btreeNode->keys,i);
                        tempkeys[i] = key;
                        memcpy(tempkeys+i+1,btreeNode->keys+i+1,n-i-1);
                        free(btreeNode->keys);
                        btreeNode->keys = tempkeys;
                        return 0;
                }else{
                        if(isFull(btreeNode->child[i])){
                                /*满子节点，分裂*/
                                node1,node2 = btree_split(btreeNode);
                                if(btreeNode->keys[i/2] > key){
                                        btreeNode = node1;
                                }else{
                                        btreeNode = node2;
                                }
                        }
                }
                //btreeNode = btreeNode->child[i];
        }
}

int main(){

        return 0;
}
