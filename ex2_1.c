#include<stdio.h>
#include<stdlib.h>
struct LinkedList{
	int info;
	struct LinkedList *link;
	};
struct LinkedList* create(struct LinkedList *);
struct LinkedList* insert(struct LinkedList *);
int getCount(struct LinkedList *);
void main()
{
	struct LinkedList *start=NULL;
	int choice,i,c;
	printf("Enter the choice\n1. Create an linked list\n2. Create node\n3. Print the number of nodes");
	do
	{
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
				printf("LinkedList count is %d",i);
			break;
		}
		printf("To continue press 1");
		scanf("%d",&c);
	}while(c==1 && printf("Enter the choice\n1. Create an linked list\n2. Create node\n3. Print the number of nodes"));
	free(start);
}
struct LinkedList *create(struct LinkedList *start)
{
	int data;
	if(start==NULL)
	{
		start=(struct LinkedList*)malloc(sizeof(struct LinkedList));
		printf("Enter the value of the linkedlist\n> ");
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
		printf("There is no Linked List! Creating a new Linked List!\n> ");
		start=create(start);
		return start;
	}
	else
	{
		int data;
		struct LinkedList *ptr=start;
		struct LinkedList *temp=(struct LinkedList*)malloc(sizeof(struct LinkedList));
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
	printf("\n1.If you need the count of elements in Linked List\n2.To know count of a single element\n> ");
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
