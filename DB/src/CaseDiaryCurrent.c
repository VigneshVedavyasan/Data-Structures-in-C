#include "CaseDiaryCurrent.h"

#ifndef O_LARGEFILE
#define O_LARGEFILE 0
#endif
#define BUFFERSIZE 4096
#define LINES 18006119

DBROOT oDBRoot;
long MasterIter = 0;
int CreateHeader(void* Header,int iSize,void** pNode)
{
	int iCBC = *(int*)Header;
	Header = ((char*)Header)+sizeof(int);
	*pNode = ((char*)Header+(iCBC*iSize));
	return EXIT_SUCCESS;
}

static double get_nanos(void)
{
	struct timespec now={0,0};
	clock_gettime(CLOCK_MONOTONIC_RAW,&now);
	return (double)now.tv_sec+(double)now.tv_nsec/BILLION;
}

/* Using the inbuild CPU clock rate generator 
 * to get the time as any GNU gettime,time function in 
 * Intel architecture is unrealiable 
 * for nanosecond calculations
 
static __inline__ long getticks(void)
{
	unsigned a,d;
	asm("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return (((ticks)a) | (((ticks)d) << 32));
}*/

int PrintDatabase(CURRENTCASEDIARYHEADER *pCurrentCaseDiaryHeader)
{
	CURRENTCASEDIARY *pCurrentCaseDiary = &pCurrentCaseDiaryHeader->oCurrentCaseDiaryBlock[oDBRoot.oCurrentCaseDiaryHeader.CurrentBlockCount-1];
	printf("Struct size : %ld",sizeof(CURRENTCASEDIARY));
	printf("\nTotal data set rows inserted : %d\n",oDBRoot.oCurrentCaseDiaryHeader.CurrentBlockCount);
	printf("\nCaseId : %s",pCurrentCaseDiary->CaseId);
	printf("\nCDActivityMinor : %s",pCurrentCaseDiary->CDActivityMinor);
	printf("\nCreationDateTime : %s",pCurrentCaseDiary->CreationDateTime);
	printf("\nSeqEventGlobal : %lf",pCurrentCaseDiary->SeqEventGlobal);
	printf("\nDTResolved : %s",pCurrentCaseDiary->DTResolved);
	printf("\nIdWorkerUpdate : %s",pCurrentCaseDiary->IdWorkerUpdate);
	printf("\nDTBeginValidity : %s",pCurrentCaseDiary->DTBeginValidity);
	printf("\nDTEndValidity : %s",pCurrentCaseDiary->DTEndValidity);
	printf("\nSeqFormId : %lf\n",pCurrentCaseDiary->SeqFormId);
	return EXIT_SUCCESS;
}

//Splits Integer
int AssignInteger(int *pInteger, char **pPtr)
{
	*pInteger = 0;
	for(;**pPtr!=',' && **pPtr!='\n';(*pPtr)++)
	{
		if(((**pPtr-'0')>=0) && ((**pPtr-'0')<=9))
		{
			(*pInteger) = (*pInteger)*10;
			(*pInteger)+=(**pPtr-'0');
		}
	}
	return EXIT_SUCCESS;
}

/*Splits Double
int AssignDouble(double *pDouble, char **pPtr)
{
	*pDouble = 0;
	for(;**pPtr!=',' && **pPtr!='\n' && **pPtr!='.';(*pPtr)++)
	{
		if(((**pPtr-'0')>=0) && (**pPtr-'0')<=9)
		{
			(*pDouble) = (*pDouble)*10;
			(*pDouble)+=((**pPtr)-'0');
		}
	}
	(*pPtr)++;
	return 0;
}
*/

//Splits Double
int AssignDouble(double *pDouble, char **pPtr,long *iter)
{
	*pDouble=0;
	sscanf(*pPtr,"%lf",pDouble);
	for(;**pPtr!=',' && **pPtr!='\n';(*pPtr)++,(*iter)++);
	(*pPtr)++;
	(*iter)++;
	return EXIT_SUCCESS;
}

//Splits String
int AssignString(char *pString,char **pPtr,long *iter)
{
	int i=0;
	for(;*(*pPtr+i)!=',';i++);
	strncpy(pString,*pPtr,i+1);
	*iter=(*iter)+i+1;
	*(pString+i)='\0';
	for(;**pPtr!=',';(*pPtr)++);
	(*pPtr)++;
	return EXIT_SUCCESS;
}

int AvailableMemory(long *usageMem,long *usedMem,long *maxMem,long *availableMem)
{
	*maxMem = sysconf(_SC_PAGE_SIZE)*sysconf(_SC_PHYS_PAGES);
	*availableMem = sysconf(_SC_AVPHYS_PAGES)*sysconf(_SC_PAGE_SIZE);
	*usedMem = *maxMem-*availableMem;
	printf("Avaliable Memory : %ld\n",*availableMem);
	*usageMem = *availableMem/3;
	return EXIT_SUCCESS;
}

//Splits lines of Data
int SplitToStructure(CURRENTCASEDIARYHEADER *pCurrentCaseDiaryHeader,int *fd)
{
	char *pPtr,buffer[BUFFERSIZE];
	size_t bytes,Iter;
	long TotalSize = 0,chunk = 0,i = 0;
	long maxMem,availableMem,usageMem,usedMem;
	AvailableMemory(&usageMem,&usedMem,&maxMem,&availableMem);
	CURRENTCASEDIARY *pCurrentCaseDiary=NULL;
	TotalSize=lseek(*fd,0,SEEK_END);
	chunk = lseek(*fd,122,SEEK_SET);
	//Though there are 2 loops, the order of insertion of data into the flat structure is O(n)
	while(chunk < TotalSize && usageMem > chunk)
	{
		if(oDBRoot.oCurrentCaseDiaryHeader.CurrentBlockCount == 0)
		{
	                bzero(buffer,BUFFERSIZE);
	                bytes = read(*fd,buffer,BUFFERSIZE);
		}
		else
		{
			bzero(buffer,BUFFERSIZE);
			lseek(*fd,chunk,SEEK_SET);
			bytes = read(*fd,buffer,BUFFERSIZE);
		}
		if(bytes < 0)
		{
			printf("\nRead Unsuccessful\n");
			return 0;
		}
		i=0;
		pPtr = buffer;
		for(Iter=0;Iter < 24 && MasterIter < LINES;Iter++,MasterIter++)
		{
			CreateHeader(&oDBRoot.oCurrentCaseDiaryHeader,sizeof(CURRENTCASEDIARY),(void**)&pCurrentCaseDiary);
			pCurrentCaseDiary = &pCurrentCaseDiaryHeader->oCurrentCaseDiaryBlock[MasterIter];
			AssignString(pCurrentCaseDiary->CaseId, &pPtr,&i);
			AssignString(pCurrentCaseDiary->CDActivityMinor,&pPtr,&i);
			AssignString(pCurrentCaseDiary->CreationDateTime,&pPtr,&i);
			AssignDouble(&pCurrentCaseDiary->SeqEventGlobal,&pPtr,&i);
			AssignString(pCurrentCaseDiary->DTResolved,&pPtr,&i);
			AssignString(pCurrentCaseDiary->IdWorkerUpdate,&pPtr,&i);
			AssignString(pCurrentCaseDiary->DTBeginValidity,&pPtr,&i);
			AssignString(pCurrentCaseDiary->DTEndValidity,&pPtr,&i);
			AssignDouble(&pCurrentCaseDiary->SeqFormId,&pPtr,&i);
			oDBRoot.oCurrentCaseDiaryHeader.CurrentBlockCount++;
		}
		chunk = lseek(*fd,chunk+i,SEEK_SET);
	}
	PrintDatabase(pCurrentCaseDiaryHeader);
	return EXIT_SUCCESS;
}

int ReadFromFile()
{
	int fd;
	CURRENTCASEDIARYHEADER *pCurrentCaseDiaryHeader;
	pCurrentCaseDiaryHeader = &oDBRoot.oCurrentCaseDiaryHeader;
	fd=open("/home/vignesh.v/2017/January/Case_Diary_Current.txt",O_RDONLY|O_LARGEFILE);
	if(fd==-1)
	{
		printf("\nFile Open Unsuccessful\n");
		exit(-1);
	}
	SplitToStructure(pCurrentCaseDiaryHeader,&fd);
	close(fd);
	return EXIT_SUCCESS;
}

int main()
{
	double BeginTime=0,EndTime=0;
	BeginTime = get_nanos();
	ReadFromFile();
	EndTime = get_nanos();
	printf("\nTime Taken for insertion into flat structure : %.9lf sec\n",(EndTime-BeginTime));
	bzero(&BeginTime,sizeof(double));
	bzero(&EndTime,sizeof(double));
	BeginTime = get_nanos();
	AvlTree();
	EndTime = get_nanos();
	printf("\nTime Taken for AVL Insertion: %.9lf sec\n",(EndTime-BeginTime));
	return EXIT_SUCCESS;
}

