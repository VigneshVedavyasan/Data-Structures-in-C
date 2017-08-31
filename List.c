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
int insert_At_End(struct node**,void *);
int insert_At_Start(struct node**,void*);
int search_data(struct node *,int*);

int insert_At_Start(struct node **ptr,void *data)
{
	struct node *temp=malloc(sizeof(struct node));
	temp->data=data;
	temp->next=*ptr;
	*ptr=temp;
	return EXIT_SUCCESS;
}

int insert_At_Middle(struct node **ptr,void *data,int pos)
{
	if(*ptr && pos)
		insert_At_Middle(&(*ptr)->next,data,pos-1);
	if(*ptr && !pos)
	{
		insert_At_Start(ptr,data);
		return EXIT_SUCCESS;
	}
	else if(!*ptr)
	{
		insert_At_End(ptr,data);
	}
	return EXIT_SUCCESS;
}

int insert_At_End(struct node **ptr,void *data)
{
	if(*ptr)
		insert_At_End(&(*ptr)->next,data);
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

int search_data(struct node *ptr,int *ch)
{
	char name[25];
	int sapCode,iType,count=1;
	struct Employee *emp;
	*ch=1;
	
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
					printf("Name : %s\n",emp->name);
					printf("SAP ID : %d\n\n",emp->sapID);
					return EXIT_SUCCESS;
				}
				count++;
				ptr=ptr->next;
			}
			return EXIT_SUCCESS;
			break;
		case 2 :
			printf("SAP ID : ");
			scanf("%d",&sapCode);
			while(ptr)
			{
				emp = ptr->data;
				if((*compare[0])(&emp->sapID,&sapCode))
				{
					printf("\nRecord found at index : %d\n",count);
					printf("Name : %s\n",emp->name);
					printf("SAP ID : %d\n\n",emp->sapID);
					return 1;
				}
				count++;
				ptr=ptr->next;
			}
			return EXIT_SUCCESS;
			break;
		default:
			*ch=0;
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
	if((*compare[2])(emp->name,name))
	{
		if(prev==NULL && (*ptr)->next!=NULL)	//First Element deletion
			*ptr=temp->next;
		else if(prev!=NULL && (*ptr)->next!=NULL)	//Middle Element deletion
			(*prev)->next=(struct node*)(*ptr)->next;
		else if(prev==NULL && (*ptr)->next==NULL)	//When only one element exists
		{
			free(emp);
			free(*ptr);
			*ptr=NULL;
			return EXIT_SUCCESS;
		}
		else
			(*prev)->next=NULL;	//Last Element deletion
		printf("\n Deleted Record : %s\n",emp->name);
		free(emp);
		if(temp->next)
			temp->next=NULL;
		free(temp);
		return EXIT_SUCCESS;
	}
	else if((*ptr)->next)
		DeleteName(&(*ptr)->next,ptr,name);
	else
		puts("SAP ID doesn\'t exists");
	return EXIT_FAILURE;
}

int DeleteSap(struct node **ptr,struct node **prev,int sapCode)
{
	struct node *temp=*ptr;
	struct Employee *emp=temp->data;
	
	if((*compare[0])(&emp->sapID,&sapCode))
	{
		if(prev==NULL && (*ptr)->next!=NULL)	//First Element deletion
			*ptr=temp->next;
		else if(prev!=NULL && (*ptr)->next!=NULL)	//Middle Element deletion
			(*prev)->next=(struct node*)(*ptr)->next;
		else if(prev==NULL && (*ptr)->next==NULL)	//When only one element exists
		{
			free(emp);
			free(*ptr);
			*ptr=NULL;
			return EXIT_SUCCESS;
		}
		else
			(*prev)->next=NULL;	//Last Element deletion
		printf("\n Deleted Record : %s\n",emp->name);
		free(emp);
		if(temp->next)
			temp->next=NULL;
		free(temp);
		return EXIT_SUCCESS;
	}
	else if((*ptr)->next)
		DeleteSap(&(*ptr)->next,ptr,sapCode);
	else
		puts("SAP ID doesn\'t exists");
	return EXIT_FAILURE;
}

int remove_element(void **ptr)
{
	char name[25];
	int iType,sapCode;
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

int intial_insert(struct node **start,void *data)
{
	allocateMem(&data);
	strcpy(((struct Employee*)data)->name,"Arun");
	((struct Employee*)data)->sapID = 21;
	insert_At_End(start,data);

	allocateMem(&data);
	strcpy(((struct Employee*)data)->name,"Balaji");
	((struct Employee*)data)->sapID = 22;
	insert_At_End(start,data);
	
	allocateMem(&data);
	strcpy(((struct Employee*)data)->name,"Karthik");
	((struct Employee*)data)->sapID = 23;
	insert_At_End(start,data);
	return EXIT_SUCCESS;
}

int insertion(struct node **start,void *data)
{
	int choice,pos;
	printf("\n0. Exit\n1. Insert at the begining\n2. Insert at the middle\n3. Insert at the end\nEnter the Choice > ");
	do
	{
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				allocateMem(&data);
				printf("Enter the name of Employee > ");
				scanf("%s",((struct Employee*)data)->name);
				printf("Enter the sap code or the employee >");
				scanf("%d",&((struct Employee*)data)->sapID);
				insert_At_Start(start,data);
				break;
			case 2:
				allocateMem(&data);
				printf("Enter the name of Employee > ");
				scanf("%s",((struct Employee*)data)->name);
				printf("Enter the sap code or the employee >");
				scanf("%d",&((struct Employee*)data)->sapID);
				printf("Enter the position in the LL > ");
				scanf("%d",&pos);
				insert_At_Middle(start,data,pos-1);
				break;
			case 3:
				allocateMem(&data);
				printf("Enter the name of Employee > ");
				scanf("%s",((struct Employee*)data)->name);
				printf("Enter the sap code or the employee >");
				scanf("%d",&((struct Employee*)data)->sapID);
				insert_At_End(start,data);
				break;
			default:
				printf("\n0. Exit\n1. Insert at the begining\n2. Insert at the middle\n3. Insert at the end\nEnter the Choice > ");
		}
	}while(choice&&printf("\n0. Exit\n1. Insert at the begining\n2. Insert at the middle\n3. Insert at the end\nEnter the Choice > "));
	return EXIT_SUCCESS;
}

int main()
{
	int choice;
	void *data=NULL;
	struct node *start=NULL;
	intial_insert(&start,data);
	printf("Enter a Choice,\n1. Insert\n2. Search\n3. Print\n4. Delete\n___Any other key to exit___\n\t>");
	do{
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				insertion(&start,data);
				break;
			case 2:
				search_data(start,&choice);
				break;
			case 3:
				puts("\n");
				Print(start);
				puts("\n");
				break;
			case 4:
				if(!start)
					printf("No Record exists to delete!\n");
				else
					remove_element((void**)&start);
				break;
		}
	}while(choice<5 && choice>0 && printf("Enter a Choice,\n1. Insert\n2. Search\n3. Print\n4. Delete\n___Any other key to exit___\n\t>"));
	return EXIT_SUCCESS;
}