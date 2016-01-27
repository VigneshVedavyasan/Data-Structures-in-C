#include<stdio.h>
#include<stdlib.h>
#define MAX 10

int pop(int top,int A[MAX])
{
    A[top]=0;
    top--;
    return top;
}

int push(int top,int data,int A[MAX])
{
    ++top;
    A[top]=data;
    return top;
}

int *topValue(int A[MAX],int top)
{
    return A[top];
}

int isEmpty(int top)
{
    if(top==-1)
        return 1;
    return 0;
}

void display(int top,int *A)
{
    int i=0;
    for(i=0;i<=top;i++)
        printf("\n %d",A[i]);
}
int main()
{
    int A[MAX]={0},choice,top=-1,data;
    while(1)
    {
        printf("\nEnter Choice\n1. Push\n2. Pop\n3. Top\n4. Is it Empty? \n5. Display Elements\n6. Exit > ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("\n Enter the Integer to be insert : ");
            scanf("%d",&data);
            top=push(top,data,A);
            display(top,A);
            break;
        case 2:
            if(isEmpty(top))
                printf("The array is empty");
            else
                top=pop(top,A);
            display(top,A);
            break;
        case 3:
            if(isEmpty(top))
                printf("The array is empty");
            else
                printf("\n%d",topValue(A,top));
            break;
        case 4:
            if(isEmpty(top))
                printf("The array is empty");
            else
                printf("The array has elements");
            break;
        case 5:
            display(top,A);
            break;
        case 6:
            exit(0);
            break;
        }
    }

}
