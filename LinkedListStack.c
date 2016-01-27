
#include<stdio.h>
#include<stdlib.h>

struct ListNode {
    int info;
    struct ListNode *link;
};
struct ListNode* pop(struct ListNode *start)
{
    struct ListNode *temp=NULL;
    temp=start;
    start=start->link;
    temp->link=NULL;
    free(temp);
    return start;
}

struct ListNode* push(struct ListNode *start)
{
    struct ListNode *temp=NULL;
    temp=(struct ListNode*)malloc(sizeof(struct ListNode));
    printf("\n Enter the Integer to be insert : ");
    scanf("%d",&temp->info);
    temp->link=NULL;
    if(isEmpty(start))
        start=temp;
    else
    {
        temp->link=start;
        start=temp;
    }
    return start;
}

struct ListNode *topValue(struct ListNode *start)
{
    return start;
}

int isEmpty(struct ListNode *start)
{
    if(start==NULL)
        return 1;
    return 0;
}

void display(struct ListNode *start)
{
    struct ListNode *ptr;
    for(ptr=start;ptr!=NULL;ptr=ptr->link)
        printf("%d ",ptr->info);

}

int main()
{
    struct ListNode *start=NULL;
    int choice,data;
    while(1)
    {
        printf("\nEnter Choice\n1. Push\n2. Pop\n3. top\n4. Is it Empty? \n5. Display Elements\n6. Exit > ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            start=push(start);
            display(start);
            break;
        case 2:
            if(isEmpty(start))
                printf("The array is empty");
            else
                start=pop(start);
            display(start);
            break;
        case 3:
            if(isEmpty(start))
                printf("The array is empty");
            else
                printf("\n%d",*topValue(start));
            break;
        case 4:
            if(isEmpty(start))
                printf("The array is empty");
            else
                printf("The array has elements");
            break;
        case 5:
            display(start);
            break;
        case 6:
            exit(0);
            break;
        }
    }
}
