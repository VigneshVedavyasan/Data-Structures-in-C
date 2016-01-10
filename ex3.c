#include<stdio.h>
int main()
{
	int i,*p,arr[5]={25,30,35,40,55};
	p=arr;
	for(i=0;i<5;i++)
	{
		printf("%d ",*p);
		p++;
	}
	return 0;
}
