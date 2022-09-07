#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct TreeNode{
  struct TreeNode *left;
  struct TreeNode *right;
  int data;
}TreeNode;

typedef TreeNode* element;

typedef struct QueueNode{
  struct QueueNode *next;
  element data;
}QueueNode;

typedef struct QueueType{
  QueueNode * front;
  QueueNode * rear;  
}QueueType;


void error(char *message){
  fprintf(stderr,"%s\n",message);
  exit(1);
}

void init(QueueType *q){
  q->front = q->rear = NULL;
}

int is_empty(QueueType *q){
  if(q->front==NULL) return 1;
  else return 0;
}

int max_t(int a, int b, int c){
  if(a>b){
    if(b>c) return a;
    else if(a>c) return a;
    else return c;
  }
  else{
    if(b>c) return b;
    else if(a>c) return b;
    else return c;
  } 
}

void enqueue(QueueType *q, element data){
  QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
  if(temp == NULL){ error("메모리 할당 오류");
  }else{
    temp->data = data;
    temp->next = NULL;
    if(is_empty(q)){
      q->front = temp;
      q->rear = temp;
    }else{
      q->rear->next = temp;
      q->rear = temp;
    }
  }
}

element dequeue(QueueType *q){
  element temp;
  if(is_empty(q)) error("큐가 비어있음.");
  else{
    temp = q->front->data;
    q->front = q->front->next;
    if(q->front == NULL) q->rear = NULL;
  }
  return temp;
}


void preorder(TreeNode *root){
  if(root){
    printf("%d ",root->data);
    preorder(root->left); preorder(root->right);
  }
}

void inorder(TreeNode *root){
  if(root){
    inorder(root->left); printf("%d ",root->data);
    inorder(root->right);
  }
}

void postorder(TreeNode *root){
  if(root){
    postorder(root->left); postorder(root->right);
    printf("%d ",root->data);
  }
}

void level_order(TreeNode *ptr){
  QueueType* q = (QueueType*)malloc(sizeof(QueueType));
  init(q);
  if(!ptr) return;
  enqueue(q,ptr);
  while(!is_empty(q)){
    ptr = dequeue(q);
    printf("%d ",ptr->data);
    if(ptr->left) enqueue(q,ptr->left);
    if(ptr->right) enqueue(q,ptr->right);
  }
}

int eval(TreeNode *root){
  int op1, op2;
  if(root == NULL) return 0;
  if(root->left == NULL && root->right == NULL) return root->data;
  op1 = eval(root->left);  op2 = eval(root->right);
  switch(root->data){
    case '+': return op1 + op2; case '-': return op1 - op2;
    case '*': return op1 * op2; case '/': return op1 / op2;
  }
}

int get_node_count(TreeNode *node){
  int count = 0;
  if(node != NULL){
    count = 1+ get_node_count(node->left)+get_node_count(node->right);
  }
  return count;
}

int get_leaf_count(TreeNode *node){
  int count = 0;
  if(node != NULL){
    if(node->left == NULL && node->right == NULL) return 1;
    else count = get_leaf_count(node->left)+get_leaf_count(node->right);
  }
  return count;
}

int get_max(TreeNode *root){
  int max,left,right = 0;
  if(root){
    right = get_max(root->right);
    left = get_max(root->left);
    max = max_t(right,left,root->data);
  }else return 0;
  return max;
}


int main(void) {
  TreeNode *n1, *n2, *n3, *n4, *n5, *n6;
  n1 = (TreeNode *)malloc(sizeof(TreeNode));
  n2 = (TreeNode *)malloc(sizeof(TreeNode));
  n3 = (TreeNode *)malloc(sizeof(TreeNode));
  n4 = (TreeNode *)malloc(sizeof(TreeNode));
  n5 = (TreeNode *)malloc(sizeof(TreeNode));
  n6 = (TreeNode *)malloc(sizeof(TreeNode));
  n1->data = 10; n1->left = n2; n1->right = n3;
  n2->data = 20; n2->left = n4; n2->right = n5;
  n3->data = 30; n3->left = n6; n3->right = NULL;
  n4->data = 40; n5->data = 50; n6->data = 60;
  n4->right = NULL; n4->left = NULL; n5->right = NULL; n5->left = NULL; n6->right = NULL; n6->left = NULL;
  preorder(n1);
  printf("\n");
  inorder(n1);
  printf("\n");
  postorder(n1);
  printf("\n");
  level_order(n1);
  printf("\n");
  printf("%d",get_max(n1));
  return 0;
} 