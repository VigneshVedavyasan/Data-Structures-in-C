#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

int pop(int top,char A[MAX])
{
    A[top]='\0';
    top--;
    return top;
}

int push(int top,char opening,char A[MAX])
{
    ++top;
    A[top]=opening;
    return top;
}

char topValue(char A[MAX],int top)
{
    return A[top];
}

int isEmpty(int top)
{
    if(top==-1)
        return 1;
    return 0;
}

void display(int top,char *A)
{
    int i=0;
    for(i=0;i<=strlen(A);i++)
        printf("\n %c",A[i]);
}

void main()
{
    int top=-1,c,i;
    char A[MAX]={'\0'},B[MAX]={'\0'};
    printf("Press '1' to continue");
    scanf("%d",&c);
    while(c==1)
    {
        printf("\n\nEnter the expression > ");
        scanf("%s",&B);
        for(i=0;i<strlen(B);i++)
            printf("%c",B[i]);
        for(i=0;i<strlen(B);i++)
        {
            if(B[i]=='{'||B[i]=='['||B[i]=='(')
            {
                top=push(top,B[i],A);
            }
            switch(B[i])
            {
                case '}':
                    if(isEmpty(top))
                    {
                        printf("Invalid Expression\n");
                        main();
                    }
                    else if(topValue(A,top)=='{')
                    {
                        top=pop(top,A);
                    }
                    else
                    {
                        printf("Invalid Expression\n");
                        main();
                    }
                    break;
                case ']':
                    if(isEmpty(top))
                    {
                        printf("Invalid Expression\n");
                        main();
                    }
                    else if(topValue(A,top)=='[')
                    {
                        top=pop(top,A);
                    }
                    else
                    {
                        printf("Invalid Expression\n");
                        main();
                    }
                    break;
                case ')':
                    if(isEmpty(top))
                    {
                        printf("Invalid Expression\n");
                        main();
                    }
                    else if(topValue(A,top)=='(')
                    {
                        top=pop(top,A);
                    }
                    else
                    {
                        printf("Invalid Expression\n");
                        main();
                    }
                    break;
            }
        }
        if(isEmpty(top))
        {
            printf("Valid Expression\n");
            main();
        }
    }
    exit(0);
}
