#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode{
  element item;
  struct QueueNode *link;
}QueueNode;

typedef struct{
  QueueNode *front, *rear;
}Queuetype;

void error(char *message){
  fprintf(stderr,"%s\n",message);
  exit(1);
}

void init(Queuetype *q){
  q->front = q->rear = NULL;
}



int is_empty(Queuetype *q){
  return (q->front == NULL);
}

void enqueue(Queuetype *q, element item){
QueueNode * temp = (QueueNode *)malloc(sizeof(QueueNode));
  if(temp == NULL) error("메모리 할당 오류");
  else{
    temp->link = NULL;
    temp->item = item;
    if(is_empty(q)){
      q->front = temp;
      q->rear = temp;
    }else{
      q->rear->link = temp;
      q->rear = temp;
    }
  }
}

element dequeue(Queuetype *q){
  element temp;
  if(is_empty(q)) error("큐가 비어있음.");
  else{
    temp = q->front->item;
    q->front = q->front->link;
    if(q->front == NULL) q->rear = NULL;
  }
  return temp;
}

element peek(Queuetype *q){
  if(is_empty(q)) error("큐가 비어있음");
  else{
    return q->front->item;
  }
}

void main(){
  Queuetype q;
  init(&q);
  enqueue(&q, 1);
  enqueue(&q, 2);
  enqueue(&q, 3);
  printf("dequeue()=%d\n",dequeue(&q));
  printf("dequeue()=%d\n",dequeue(&q));
  printf("dequeue()=%d\n",dequeue(&q));
}