#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>
#include<time.h>

#define MAX_QUEUE_SIZE 100

typedef int element;

typedef struct TreeNode{
  element key;
  struct TreeNode *left, *right;
}TreeNode;

typedef struct queue{
  element data[MAX_QUEUE_SIZE];
  int rear;
  int front;
}queue;


void error(char *message){
  fprintf(stderr, "%s\n",message);
  exit(1);
}

void init(queue *q){
  q->front=0;
  q->rear=0;
}

int is_empty(queue *q){
  return (q->front == q->rear);
}

int is_full(queue *q){
  return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}

void enqueue(queue *q, element item){
  if(is_full(q)) error("큐가 포화상태입니다.");
  q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
  q->data[q->rear] = item;
}

element dequeue(queue *q){
  if(is_empty(q)) error("큐가 공백상태입니다.");
  q->front = (q->front+1) % MAX_QUEUE_SIZE;
  return q->data[q->front];
}


void inorder(TreeNode *root){
  if(root){
    inorder(root->left); printf("%d ",root->key);
    inorder(root->right);
  }
}

void insert_node(TreeNode **root, int key){
  TreeNode *p, *t;
  TreeNode *n;

  t = *root;
  p = NULL;

  while(t != NULL){
    if(key == t->key) return;
    p = t;
    t = (key<p->key) ? p->left : p->right;
  }
  n = (TreeNode *)malloc(sizeof(TreeNode));
  if(n == NULL) return;

  n->key = key;
  n->left = n->right = NULL;

  if(p!= NULL){
    if(key < p->key) p->left = n;
    else p->right = n;
  }else *root = n;
  
}

void delete_node(TreeNode **root, int key){
  TreeNode *p, *child, *succ, *succ_p, *t;

  p = NULL;
  t = *root;

  while(t != NULL && t->key != key){
    p = t;
    t = (key <p->key) ? p->left : p->right;
  }

  if(t==NULL){
    printf("key is not in the tree");
    return ;
  }

  if((t->left == NULL)&&(t->right == NULL)){
    if(p!= NULL){
      if(p->left == t) p->left = NULL;
      else p->right = NULL;
    }
    else *root = NULL;
  }
  else if((t->left == NULL)||(t->right == NULL)){
    child = (t->left != NULL) ? t->left : t->right;
    if(p != NULL){
      if(p->left == t) p->left = child;
      else p->right = child;
    }
    else *root = child;
  }
  else{
    succ_p = t;
    succ = t->right;

    while(succ->left != NULL){
      succ_p = succ;
      succ = succ->left;
    }

    if(succ_p->left == succ) succ_p->left = succ->right;
    else succ_p->right = succ->right;

    t->key = succ->key;

    t= succ;
  }
  free(t);
}

void inorder_a(TreeNode *root,queue *q){
  
  if(root){
    inorder_a(root->left,q); 
    enqueue(q,root->key);
    inorder_a(root->right,q);
  }
}

void inorder_arr(int a[]){
  TreeNode *n = NULL;
  int i;
  queue *temp=(queue*)malloc(sizeof(queue));
  init(temp);
  
  for(i=0;i<9;i++){
    insert_node(&n,a[i]);
  }

  inorder_a(n,temp);
  
  for(i=0;i<9;i++){
   printf("%d ",dequeue(temp)); 
  }
}

int main(){
  srand(time(NULL));
  int arr[9],i;
  for(int i=0;i<9;i++){
    int random = rand() % 100;
    arr[i] = random;
  }
  
  for(i=0;i<9;i++){
    printf("%d ",arr[i]);
  }

  inorder_arr(arr);
  
  printf("\n");
  
  for(i=0;i<9;i++){
    printf("%d ",arr[i]);
  }
  
}