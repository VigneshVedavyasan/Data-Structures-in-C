#include<stdio.h>
#include<stdlib.h>

struct LinkedList{
	int info;
	struct LinkedList *link;
	};

/* Credits Geeksforgeeks.com */
struct LinkedList *reverse(int k,struct LinkedList *head)
{
    struct LinkedList* ptr = head;
    struct LinkedList* next = NULL;
    struct LinkedList* prev = NULL;
    int count = 0;

    /*reverse first k nodes of the linked list */
    while (ptr != NULL && count < k)
    {
        next  = ptr->link;
        ptr->link = prev;
        prev = ptr;
        ptr = next;
        count++;
    }

    /* next is now a pointer to (k+1)th node
       Recursively call for the list starting from ptr.
       And make rest of the list as next of first node */
    if (next !=  NULL)
       head->link = reverse(k,next);

    /* prev is new head of the input list */
    return prev;
}
void display(struct LinkedList* head)
{
    while(head!=NULL)
    {
        printf("%d -> ",head->info);
        head=head->link;
    }
}
struct LinkedList* create(struct LinkedList *);
struct LinkedList* insert(struct LinkedList *);
int getCount(struct LinkedList *);
void main()
{
	struct LinkedList *start=NULL;
	int choice,i,k;
	do
	{
	    printf("Enter the choice\n1. Create an linked list\n2. Create LinkedList\n3. Print the number of LinkedLists\n4.Reverse the LinkedList by an integer\n5.Display\n6.Exit  >");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				start=create(start);
			break;
			case 2:
				start=insert(start);
			break;
			case 3:
				i=getCount(start);
				printf("\nLinkedList count is %d",i);
			break;
			case 4:
			    printf("\nEnter the number of elements to be reversed");
			    scanf("%d",&k);
                start=reverse(k,start);
                break;
            case 5:
                printf("\n > ");
                display(start);
                break;
            case 6:
                exit(0);
                break;
		}
	}while(1);
	free(start);
}
struct LinkedList *create(struct LinkedList *start)
{
	int data;
	if(start==NULL)
	{
		start=(struct LinkedList*)malloc(sizeof(struct LinkedList));
		printf("Enter the value of the LinkedList\n > ");
		scanf("%d",&data);
		start->info=data;
		start->link=NULL;
		return start;
	}
	else
	{
		printf("LinkedList already exists!\n");
		return start;
	}
}
struct LinkedList *insert(struct LinkedList *start)
{
	if(start==NULL)
	{
		printf("There is no Linked List! Creating a new Linked List!\n > ");
		start=create(start);
		return start;
	}
	else
	{
		int data;
		struct LinkedList *ptr=start;
		struct LinkedList *temp=(struct LinkedList*)malloc(sizeof(struct LinkedList));
        printf("Enter the value of the LinkedList\n > ");
		scanf("%d",&data);
		temp->info=data;
		temp->link=NULL;
		while(ptr->link!=NULL)
			ptr=ptr->link;
		ptr->link=temp;
		return start;
	}
}

int getCount(struct LinkedList *start)
{
	int count=0,p,q;
	struct LinkedList *ptr=start;
	printf("\n1.If you need the count of elements in Linked List\n2.To know count of a single element\n > ");
	scanf("%d",&p);
	switch(p)
	{
		case 1:
			while(ptr!=NULL)
			{
				ptr=ptr->link;
				count++;
			}
			return count;
		case 2:
			printf("\nEnter the element you need to count in List: ");
			scanf("%d",&q);
			while(ptr!=NULL)
			{
				if(ptr->info!=q)
					ptr=ptr->link;
				else
				{
					count++;
					ptr=ptr->link;
				}
			}
			return count;
	}
}
