#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Employee
{
	char name[25];
	int sapID;
};

struct node
{
	void *data;
	struct node *next;
};

int integerComp(int *p1,int *p2)
{
	if(*p1==*p2)
		return 1;
	else
		return 0;
}

int doubleComp(double *p1,double* p2)
{
	if(*p1==*p2)
		return 1;
	else
		return 0;
}

int characterComp(char *p1,char *p2)
{
	if(!strcmp(p1,p2))
		return 1;
	else
		return 0;
	return EXIT_SUCCESS;
}

int (*compare[])()={integerComp,doubleComp,characterComp};
//void (*allocation[])(void**,int)={allocateInt,allocateDouble,allocateChar};
int insert_into_list(struct node**,void *);
int search_data(struct node *);

int insert_into_list(struct node **ptr,void *data)
{
	if(*ptr)
		insert_into_list(&(*ptr)->next,data);
	if(!*ptr)
	{
		*ptr=malloc(sizeof(struct node));
		if(!*ptr)
		{
			perror("Error while allocating memory\n");
			return EXIT_FAILURE;
		}
		(*ptr)->data=data;
		printf("Data inserted!\n");
		return EXIT_SUCCESS;
	}
	return EXIT_SUCCESS;
}

int search_data(struct node *ptr)
{
	char name[25];
	int sapCode,iType,count=1;
	struct Employee *emp;
	
	printf("Search by\n\n\t1. Employee Name\n\t2. SAP ID\n\t_____Anyother key to exit_____\n\t>");
	scanf("%d",&iType);
	// 0 - int; 1 - double; 2 - char;
	switch(iType)
	{
		case 1 :
			printf("Name : ");
			scanf("%s",name);
			while(ptr)
			{
				emp = ptr->data;
				if((*compare[2])(emp->name,name))
				{
					printf("\nRecord found at index : %d\n",count);
					return 1;
				}
				count++;
				ptr=ptr->next;
			}
			return 0;
			break;
		case 2 :
			printf("SAP ID : ");
			scanf("%d",&sapCode);
			while(ptr)
			{
				emp = ptr->data;
				printf("Iter : %d",emp->sapID);
				if((*compare[0])(&emp->sapID,&sapCode))
				{
					printf("\nRecord found at index : %d\n",count);
					return 1;
				}
				count++;
				ptr=ptr->next;
			}
			return 0;
			break;
	}
	return EXIT_SUCCESS;
}

int Print(struct node *ptr)
{
	struct Employee *emp;
	while(ptr)
	{
		emp=ptr->data;
		printf("\tName : %s\n",emp->name);
		printf("\tSAP ID : %d\n",emp->sapID);
		ptr=ptr->next;
	}
	return EXIT_SUCCESS;
}

int DeleteName(struct node **ptr,struct node **prev,char *name)
{
	struct node *temp=(struct node*)*ptr;
	struct Employee *emp=temp->data;
	if((*compare[2])(emp->name,name) && (*ptr)->next!=NULL)
	{
		if(prev==NULL && (*ptr)->next!=NULL)
			*ptr=temp->next;
		else if(prev!=NULL && (*ptr)->next!=NULL)
			(*prev)->next=(struct node*)(*ptr)->next;
		else if(prev==NULL && (*ptr)->next==NULL)
		{
			free(emp);
			free(temp);
		}
		else
			(*prev)->next=NULL;
		printf("\n Deleted Record : %s\n",emp->name);
		free(emp);
		if(temp->next)
			temp->next=NULL;
		free(temp);
		return EXIT_SUCCESS;
	}
	else
		DeleteName(&(*ptr)->next,ptr,name);
	return EXIT_FAILURE;
}

int DeleteSap(struct node **ptr,struct node **prev,int sapCode)
{
	struct node *temp=*ptr;
	struct Employee *emp=temp->data;
	printf("\n Current Record : %s\n",emp->name);
	if((*compare[0])(&emp->sapID,&sapCode))
	{
		if(prev==NULL && (*ptr)->next!=NULL)
			*ptr=temp->next;
		else if(prev!=NULL && (*ptr)->next!=NULL)
			(*prev)->next=(struct node*)(*ptr)->next;
		else if(prev==NULL && (*ptr)->next==NULL)
		{
			free(emp);
			free(temp);
		}
		else
			(*prev)->next=NULL;
		printf("\n Deleted Record : %s\n",emp->name);
		free(emp);
		if(temp->next)
			temp->next=NULL;
		free(temp);
		return EXIT_SUCCESS;
	}
	else
		DeleteSap(&(*ptr)->next,ptr,sapCode);
	return EXIT_FAILURE;
}

int remove_element(void **ptr)
{
	char name[25];
	int iType,sapCode;
	do
	{
		printf("Remove Record by\n\t1. Name\n\t2. SAP ID\n\t >");
		scanf("%d",&iType);
		if(iType==1)
		{
			printf("Name : ");
			scanf("%s",name);
			DeleteName((struct node **)ptr,NULL,name);
		}
		else if(iType==2)
		{
			printf("SAP ID : ");
			scanf("%d",&sapCode);
			DeleteSap((struct node **)ptr,NULL,sapCode);
		}
	}while(iType == 1 || iType == 2);
	return EXIT_SUCCESS;
}

int allocateMem(void **ptr)
{
	*ptr = malloc(sizeof(struct Employee));
	if(!*ptr)
	{
		perror("Error in Allocating memory!\n");
		exit(-1);
	}
	return EXIT_SUCCESS;
}

int main()
{
	void *data;
	struct node *start=NULL;

	allocateMem(&data);
	strcpy(((struct Employee*)data)->name,"Arun");
	((struct Employee*)data)->sapID = 21;
	insert_into_list(&start,data);

	allocateMem(&data);
	strcpy(((struct Employee*)data)->name,"Balaji");
	((struct Employee*)data)->sapID = 22;
	insert_into_list(&start,data);
	
	allocateMem(&data);
	strcpy(((struct Employee*)data)->name,"Karthik");
	((struct Employee*)data)->sapID = 23;
	insert_into_list(&start,data);
	
	puts("\n");
	Print(start);
	puts("\n");

	search_data(start);
	
	remove_element((void**)&start);

	puts("\n");
	Print(start);
	puts("\n");
	
	return EXIT_SUCCESS;
}
