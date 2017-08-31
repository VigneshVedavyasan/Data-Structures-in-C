#ifndef CASEDAIRYCURRENT_H
#define CASEDAIRYCURRENT_H

#include<stdio.h>
#include<string.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>

#define VARCHAR 30
#define CASEID 10
#define DATE_TIME 20
#define CD_ACTIVITY_MINOR 4
#define MAX_CURRENTCASEDIA_HEADER 18006130
#define MAX_DIM 9
#define BILLION 1000000000L

typedef struct CurrentCaseDiary
{
	double SeqEventGlobal;
	double SeqFormId;
	char CaseId[CASEID];
	char CDActivityMinor[CD_ACTIVITY_MINOR];
	char CreationDateTime[DATE_TIME];
	char DTResolved[DATE_TIME];
	char DTBeginValidity[DATE_TIME];
	char DTEndValidity[DATE_TIME];
	char IdWorkerUpdate[VARCHAR];

}CURRENTCASEDIARY;

typedef struct CurrentCaseDiaryHeader
{
	int CurrentBlockCount;
	CURRENTCASEDIARY oCurrentCaseDiaryBlock[MAX_CURRENTCASEDIA_HEADER];

}CURRENTCASEDIARYHEADER;

typedef struct DBRoot
{
	CURRENTCASEDIARYHEADER oCurrentCaseDiaryHeader;
}DBROOT;

typedef unsigned long long ticks;
extern DBROOT oDBRoot;
extern int AvlTree();

#endif
