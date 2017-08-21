#include "CaseDiaryCurrent.h"

struct node
{
	struct node *lChild;
	struct node *rChild;
	int bal;
	void *data;
};

void inOrderInt(struct node*);
void preOrderInt(struct node*);
void inOrderDb(struct node*);
void inOrderChar(struct node*);
void preOrderChar(struct node*);
void preOrderDb(struct node*);

struct node* right_rotate(struct node**);
struct node* left_rotate(struct node**);

void insert_left_bal(struct node**);
void insert_right_bal(struct node**);
void insert_left_check(struct node**,int*);
void insert_right_check(struct node**,int*);

void delete_left_bal(struct node**,int*);
void delete_right_bal(struct node**,int*);
void delete_left_check(struct node**,int*);
void delete_right_check(struct node**,int*);

int insertion(struct node**,void*,int);
int deletion(struct node**,void*,int);

void allocateInt(void **ptr,int size)
{
	*ptr=malloc(size*sizeof(int));
}

void allocateDouble(void **ptr,int size)
{
	*ptr=malloc(size*sizeof(double));
}

void allocateChar(void **ptr,int size)
{
	*ptr=malloc(size*sizeof(char*));
}

int integerComp(int *p1,int *p2)
{
	if(*p1>*p2)
		return 1;
	else
		return 0;
}

int doubleComp(double *p1,double* p2)
{
	if(*p1>*p2)
		return 1;
	else
		return 0;
}

int characterComp(char *p1,char *p2)
{
	while(*p1!='\0' && *p2!='\0')
	{
		if(!strcmp(p1,p2))
			return 0;
		else
			return 1;
	}
	return EXIT_SUCCESS;
}

void deleteTree(struct node **p,int iType)
{
	if(!*p)
		return;
	deleteTree(&(*p)->lChild,iType);
	deleteTree(&(*p)->rChild,iType);
	if(iType==2)
		free((*p)->data);
	free(*p);
}

/*
   int function_C(struct node *ptr, void *data,int n,int iType)
   {
   int i = (n+1)/2,j=2;
   if(compare(iType))
   }*/

int (*compare[])()={integerComp,doubleComp,characterComp};
void (*allocation[])(void**,int)={allocateInt,allocateDouble,allocateChar};
void (*inOrderPrint[])(struct node*)={inOrderInt,inOrderDb,inOrderChar};
void (*preOrderPrint[])(struct node*)={preOrderInt,preOrderDb,preOrderChar};

//iType - Data Type of the item to be inserted into the tree
//data - The actual data to be inserted

static double get_nanos(void)
{
	struct timespec now={0,0};
	clock_gettime(CLOCK_MONOTONIC_RAW,&now);
	return (double)now.tv_sec+(double)now.tv_nsec/BILLION;
}

int SearchAVLChar(struct node **ptr,void *data,int iType)
{
	if(!(*ptr))
		return 0;
	if((*compare[iType])((*ptr)->data,data,iType))
		SearchAVLChar(&(*ptr)->lChild,data,iType);
	else
	{
		printf("Found %s\n",(char*)(*ptr)->data);
		SearchAVLChar(&(*ptr)->lChild,data,iType);
		SearchAVLChar(&(*ptr)->rChild,data,iType);
	}
	return 0;
}

void TimeTaken(struct node *root,int iType,int dim)
{
	double t1=0,t2=0;
	char *str = malloc(10);
	if(!dim)
	{
		t1 = get_nanos();
		printf("Root : %s\n",(char*)root->data);
		t2 = get_nanos();
		printf("Time taken for Retrival at root : %.9lf",t2-t1);
		printf("\n\nGetting data from middle\n\n");
		//Change this strcpy data to check for a specific data at the middle
		strcpy(str,"003290208");
		t1 = get_nanos();
		SearchAVLChar(&root,str,iType);
		t2 = get_nanos();
		printf("Time taken for Retrival from the middle of the tree : %.9lf",t2-t1);
		printf("\n\nGetting data from leaf region(last insert)\n");
		//Change this strcpy data to check for a specific data at the end
		strcpy(str,"000000060");
		t1 = get_nanos();
		SearchAVLChar(&root,str,iType);
		t2 = get_nanos();
		printf("Time taken for Retrival at end : %.9lf",t2-t1);
	}
}

void* allocateMem(CURRENTCASEDIARY *pCurrentCaseDiary,void *data,int dim,int iType)
{
	switch(dim)
	{
		case 0:
			(*allocation[iType])(&data,CASEID);
			strcpy(data , pCurrentCaseDiary->CaseId);
			break;
		case 1:
			(*allocation[iType])(&data,CD_ACTIVITY_MINOR);
			strcpy(data , pCurrentCaseDiary->CDActivityMinor);
			break;
		case 2:
			(*allocation[iType])(&data,CD_ACTIVITY_MINOR);
			strcpy(data , pCurrentCaseDiary->CreationDateTime);
			break;
		case 3:
			(*allocation[iType])(&data,1);
			data = &pCurrentCaseDiary->SeqEventGlobal;
			break;
		case 4:
			(*allocation[iType])(&data,DATE_TIME);
			strcpy(data , pCurrentCaseDiary->DTResolved);
			break;
		case 5:
			(*allocation[iType])(&data,VARCHAR);
			strcpy(data , pCurrentCaseDiary->IdWorkerUpdate);
			break;
		case 6:
			(*allocation[iType])(&data,DATE_TIME);
			strcpy(data , pCurrentCaseDiary->DTBeginValidity);
			break;
		case 7:
			(*allocation[iType])(&data,DATE_TIME);
			strcpy(data , pCurrentCaseDiary->DTEndValidity);
			break;
		case 8:
			(*allocation[iType])(&data,1);
			data = &pCurrentCaseDiary->SeqFormId;
			break;
	}
	return data;
}

long HeightOfTree(struct node *ptr)
{
	long lH=0,rH=0;
	if(ptr->lChild)
		lH = HeightOfTree(ptr->lChild);
	if(ptr->rChild)
		rH = HeightOfTree(ptr->rChild);
	if(lH > rH)
		return lH+1;
	else
		return rH+1;
}

int insertIntoAVL(struct node **root,int iType,int dim)
{
	long i=0;
	int h=0,recordSize=oDBRoot.oCurrentCaseDiaryHeader.CurrentBlockCount;
	void *data;
	double BeginTime,EndTime;
	CURRENTCASEDIARY *pCurrentCaseDiary = NULL;
	do
	{
		pCurrentCaseDiary = &oDBRoot.oCurrentCaseDiaryHeader.oCurrentCaseDiaryBlock[oDBRoot.oCurrentCaseDiaryHeader.CurrentBlockCount-i];
		data=allocateMem(pCurrentCaseDiary,data,dim,iType);
		if(i==oDBRoot.oCurrentCaseDiaryHeader.CurrentBlockCount/2)
			BeginTime = get_nanos();
		insertion(root,data,iType);
		if(i==oDBRoot.oCurrentCaseDiaryHeader.CurrentBlockCount/2)
		{
			EndTime = get_nanos();
			printf("Time taken for Insertion : %.9lf\n",EndTime-BeginTime);
		}
		i++;
	}while(oDBRoot.oCurrentCaseDiaryHeader.CurrentBlockCount-i);
	i=0;
	TimeTaken(*root,iType,dim);
	printf("Before Delete\n");
	while(recordSize>>=1)
		h++;
	printf("Height of the tree should be less than or equal to %d\n",h+1);
	printf("Actual Height of the tree : %ld\n",HeightOfTree(*root));
	deleteTree(root,iType);
	printf("After Deletion\n");
	return 0;
}

int AvlTree()
{
	int dim=0;
	struct node *r1=NULL,*r2=NULL,*r3=NULL,*r4=NULL,*r5=NULL,*r6=NULL,*r7=NULL,*r8=NULL,*r9=NULL;
	insertIntoAVL(&r1,2,dim);
	dim++;
	insertIntoAVL(&r2,2,dim);
	dim++;
	insertIntoAVL(&r3,2,dim);
	dim++;
	insertIntoAVL(&r4,1,dim);
	dim++;
	insertIntoAVL(&r5,2,dim);
	dim++;
	insertIntoAVL(&r6,2,dim);
	dim++;
	insertIntoAVL(&r7,2,dim);
	dim++;
	insertIntoAVL(&r8,2,dim);
	dim++;
	insertIntoAVL(&r9,1,dim);
	//TimeTaken(r1,2);
	/*
	   TimeTaken(r2,2);
	   TimeTaken(r3,2);
	   TimeTaken(r4,1);
	   TimeTaken(r5,2);
	   TimeTaken(r6,2);
	   TimeTaken(r7,2);
	   TimeTaken(r8,2);
	   TimeTaken(r9,1);*/
	//printf("\nTotal Search Time in AVL : %.9lf nanosec\n",EndTime-BeginTime);
	return 0;
}


/*void swap(void *ptr1,void *ptr2,int width)
  {
  void *temp=malloc(width);
  memcpy(temp,ptr1,width);
  memcpy(ptr1,ptr2,width);
  memcpy(ptr2,temp,width);
  free(temp);
  }*/

struct node* right_rotate(struct node **ptr)
{
	struct node *aptr;
	aptr=(*ptr)->lChild;
	(*ptr)->lChild=aptr->rChild;
	aptr->rChild=*ptr;
	return aptr;
}

struct node* left_rotate(struct node **ptr)
{
	struct node *aptr;
	aptr=(*ptr)->rChild;
	(*ptr)->rChild=aptr->lChild;
	aptr->lChild=*ptr;
	return aptr;
}

void insert_left_bal(struct node **ptr)
{
	struct node *aptr=NULL,*bptr=NULL;
	aptr=(*ptr)->lChild;
	if(aptr->bal==1)
	{
		(*ptr)->bal=0;
		aptr->bal=0;
		*ptr=right_rotate(ptr);
	}
	else
	{
		bptr=aptr->rChild;
		switch(bptr->bal)
		{
			case -1:
				(*ptr)->bal=0;
				aptr->bal=1;
				break;
			case 0:
				(*ptr)->bal=0;
				aptr->bal=0;
				break;
			case 1:
				(*ptr)->bal=-1;
				aptr->bal=0;
				break;
		}
		bptr->bal=0;
		(*ptr)->lChild=left_rotate(&aptr);
		*ptr=right_rotate(ptr);
	}
}

void insert_right_bal(struct node **ptr)
{
	struct node *aptr=NULL,*bptr=NULL;
	aptr=(*ptr)->rChild;
	if(aptr->bal==-1)
	{
		aptr->bal=0;
		(*ptr)->bal=0;
		*ptr=left_rotate(ptr);
	}
	else
	{
		bptr=aptr->lChild;
		switch(bptr->bal)
		{
			case -1:
				(*ptr)->bal=1;
				aptr->bal=0;
				break;
			case 0:
				(*ptr)->bal=0;
				aptr->bal=0;
				break;
			case 1:
				(*ptr)->bal=0;
				aptr->bal=-1;
				break;
		}
		bptr->bal=0;
		(*ptr)->rChild=right_rotate(&aptr);
		*ptr=left_rotate(ptr);
	}
}

void insert_left_check(struct node **ptr,int *ptaller)
{
	switch((*ptr)->bal)
	{
		case -1:
			//was previously right heavy
			(*ptr)->bal=0;//now balanced
			*ptaller=0;
			break;
		case 0:
			//was previously balanced
			(*ptr)->bal=1;//now left heavy
			break;
		case 1:
			//was previously left heavy
			(*ptr)->bal=0;//now unbalanced
			insert_left_bal(ptr);
			*ptaller=0;
			break;
	}
}

void insert_right_check(struct node **ptr,int *ptaller)
{
	switch((*ptr)->bal)
	{
		case -1:
			//previously right heavy
			(*ptr)->bal=0;//unbalanced
			insert_right_bal(ptr);
			*ptaller=0;
			break;
		case 0://previously balanced
			(*ptr)->bal=-1;//now right heavy
			break;
		case 1://previously left heavy
			(*ptr)->bal=0;//now balanced
			*ptaller=0;
			break;
	}
}

void delete_left_bal(struct node **ptr,int *pShorter)
{
	struct node *aptr,*bptr;
	aptr=(*ptr)->lChild;
	if(aptr->bal==0)
	{
		(*ptr)->bal=1;
		aptr->bal=-1;
		*pShorter=0;
		*ptr=right_rotate(ptr);
	}
	else if(aptr->bal==1)
	{
		aptr->bal=0;
		(*ptr)->bal=0;
		*ptr=right_rotate(ptr);
	}
	else
	{
		bptr=aptr->rChild;
		switch(bptr->bal)
		{
			case -1:
				(*ptr)->bal=0;
				aptr->bal=1;
				break;
			case 0:
				(*ptr)->bal=0;
				aptr->bal=0;
				break;
			case 1:
				(*ptr)->bal=-1;
				aptr->bal=0;
				break;
		}
		bptr->bal=0;
		(*ptr)->lChild=left_rotate(&aptr);
		*ptr=right_rotate(ptr);
	}		
}

void delete_right_bal(struct node** ptr,int *pShorter)
{

	struct node *aptr,*bptr;
	aptr=(*ptr)->rChild;
	if(aptr->bal==0)
	{
		(*ptr)->bal=-1;
		aptr->bal=1;
		*pShorter=0;
		*ptr=left_rotate(ptr);
	}
	else if(aptr->bal==-1)
	{
		aptr->bal=0;
		(*ptr)->bal=0;
		*ptr=left_rotate(ptr);
	}
	else
	{
		bptr=aptr->lChild;
		switch(bptr->bal)
		{
			case -1:
				(*ptr)->bal=1;
				aptr->bal=0;
				break;
			case 0:
				(*ptr)->bal=0;
				aptr->bal=0;
				break;
			case 1:
				(*ptr)->bal=0;
				aptr->bal=-1;
				break;
		}
		bptr->bal=0;
		(*ptr)->rChild=right_rotate(&aptr);
		*ptr=left_rotate(ptr);
	}
}

void delete_left_check(struct node** ptr,int *pShorter)
{
	switch((*ptr)->bal)
	{
		case 0:
			(*ptr)->bal=-1;
			*pShorter=0;
			break;
		case 1:
			(*ptr)->bal=0;
			break;
		case -1:
			delete_right_bal(ptr,pShorter);
			break;
	}
}

void delete_right_check(struct node** ptr,int *pShorter)
{
	switch((*ptr)->bal)
	{
		case 0:
			(*ptr)->bal=1;
			*pShorter=0;
			break;
		case 1:
			delete_left_bal(ptr,pShorter);
			break;
		case -1:
			(*ptr)->bal=0;
			break;
	}
}

int insertion(struct node **ptr,void *data,int iType)
{
	static int taller;
	if(!*ptr)
	{
		*ptr=malloc(sizeof(struct node));
		if(!*ptr)
			exit(-1);
		(*ptr)->data=data;
		(*ptr)->lChild=NULL;
		(*ptr)->rChild=NULL;
		(*ptr)->bal=0;
		taller=1;
		return 1;
	}
	if((*compare[iType])((*ptr)->data,data))
	{
		insertion(&(*ptr)->lChild,data,iType);
		if(taller==1)
			insert_left_check(ptr,&taller);
	}
	else
	{
		insertion(&(*ptr)->rChild,data,iType);
		if(taller==1)
			insert_right_check(ptr,&taller);
	}
	return 1;
}

int deletion(struct node **ptr,void *data,int iType)
{
	struct node *succ,*temp;
	static int shorter;
	if(!*ptr)
	{
		printf("Element is not present\n");
		shorter=0;
		return 0;
	}
	if((*compare[iType])((*ptr)->data,data))
	{
		deletion(&(*ptr)->lChild,data,iType);
		if(shorter==1)
			delete_left_check(ptr,&shorter);
	}
	else if((*compare[iType])(data,(*ptr)->data))
	{
		deletion(&(*ptr)->rChild,data,iType);
		if(shorter==1)
			delete_right_check(ptr,&shorter);
	}
	else
	{
		if((*ptr)->lChild!=NULL && (*ptr)->rChild!=NULL)
		{
			succ=(*ptr)->rChild;
			while(succ->lChild)
				succ=succ->lChild;
			(*ptr)->data=succ->data;
			deletion(&(*ptr)->rChild,succ->data,iType);
			if(shorter==1)
				delete_right_check(ptr,&shorter);
			return 1;
		}
		else
		{
			temp=*ptr;
			if((*ptr)->lChild!=NULL)
				*ptr=(*ptr)->lChild;
			else if((*ptr)->rChild!=NULL)
				*ptr=(*ptr)->rChild;
			else
				*ptr=NULL;
			free(temp);
			shorter=1;
			return 1;
		}
	}
	return 0;
}

void inOrderInt(struct node *p)
{
	if(!p)
		return;
	inOrderInt(p->lChild);
	printf("%d->",*(int*)p->data);
	inOrderInt(p->rChild);
}

void preOrderInt(struct node *ptr)
{
	if(!ptr)
		return;
	printf("%d->",*(int*)ptr->data);
	preOrderInt(ptr->lChild);
	preOrderInt(ptr->rChild);
}

void inOrderDb(struct node *p)
{
	if(!p)
		return;
	inOrderDb(p->lChild);
	printf("%lf->",*(double*)p->data);
	inOrderDb(p->rChild);
}

void preOrderDb(struct node *ptr)
{
	if(!ptr)
		return;
	printf("%lf->",*(double*)ptr->data);
	preOrderDb(ptr->lChild);
	preOrderDb(ptr->rChild);
}

void inOrderChar(struct node *p)
{
	if(!p)
		return;
	inOrderChar(p->lChild);
	printf("%c->",*(char*)p->data);
	inOrderChar(p->rChild);
}

void preOrderChar(struct node *ptr)
{
	if(!ptr)
		return;
	printf("%c->",*(char*)ptr->data);
	preOrderChar(ptr->lChild);
	preOrderChar(ptr->rChild);
}

