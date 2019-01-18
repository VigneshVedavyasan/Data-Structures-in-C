
#include<stdio.h>
#include<stdlib.h>

struct ListNode
{
  int info;
  struct ListNode *lChild;
  struct ListNode *rChild;
};

struct ListNode* insertElement(struct ListNode** node,int data)
{
  if((*node)==NULL)
  {
    struct ListNode* temp=(struct ListNode*)malloc(sizeof(struct ListNode));
    temp->info=data;
    temp->lChild=NULL;
    temp->rChild=NULL;
    return temp;
  }
  else if((*node)->info>=data)
    (*node)->lChild=insertElement(&((*node)->lChild),data);
  else
    (*node)->rChild=insertElement(&((*node)->rChild),data);
  return (*node);
}

void traverseInorder(struct ListNode *node, int *max, int *previous, int *num, int *count)
{

  if(node==NULL)
  {
    return;
  }
  traverseInorder(node->lChild,max,previous,num,count);
  if(node->info != *previous) {
    *count = 1;
    *previous = node->info;
  } else {
    (*count)++;
  }
  if(*max < *count) {
    *max = *count;
    *num = *previous;
  }
  traverseInorder(node->rChild,max,previous,num,count);
}

void printInorder(struct ListNode *node)
{
  if(node==NULL)
  {
    return;
  }
  printInorder(node->lChild);
  printf("%d ",node->info);
  printInorder(node->rChild);
}

void findMaxRepeatingElement(int A[], int size) {

  int i,num=0,max=-1,prev=-1,count=-1;
  struct ListNode *head = NULL;
  for(i=0;i<size;i++) {

    if(!head)
      head = insertElement(&head,A[i]);
    else
      insertElement(&head,A[i]);
  }
  printInorder(head);
  printf("\n");
  traverseInorder(head,&max,&prev,&num,&count);
  printf("Maximum repeated number is %d\n",num);
}

int main() {

  int A[] = {4,7,8,2,3,2,6,7,8,9,3,2,1};
  int size = sizeof(A)/sizeof(A[0]);
  findMaxRepeatingElement(A,size);
  return 0;
}
