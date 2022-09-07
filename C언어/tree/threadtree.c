#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct TreeNode{
  int data;
  struct TreeNode *left, *right;
  int thread;
}TreeNode;



TreeNode* find_successor(TreeNode *p){
  TreeNode *q=p->right;
  if(q==NULL||p->thread == 1) return q;
  while(q->left != NULL) q = q->left;
  return q;
}

void inorder_thread(TreeNode *root){
  TreeNode *q = root;
  while(q->left) q= q->left;
  
  do{
printf("%c",q->data); 
q = find_successor(q);
}while(q);
  
}

void thread_insert_right(TreeNode *p){
  TreeNode *q;
  q->right = p->right; q->thread = p->thread;
  q->left = NULL;
  p->right = q; p->thread = 0;
}

int main(){
  TreeNode b1 = {'A',NULL,NULL,1};
  TreeNode b2 = {'B',NULL,NULL,1};
  TreeNode b3 = {'C',&b1,&b2,0};
  TreeNode b4 = {'D',NULL,NULL,1};
  TreeNode b5 = {'E',NULL,NULL,0};
  TreeNode b6 = {'F',&b4, &b5, 0};
  TreeNode b7 = {'G', &b3, &b6, 0};
  TreeNode *ThreadTree = &b7;

  b1.right = &b3;
  b2.right = &b7;
  b4.right = &b6;
  inorder_thread(ThreadTree);
  printf("\n");
  return 0;
}