#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int* findMaxProduct(int,int,int*,int);

void findSecondRecursive(int n, int *A,long long *res) {
	int *firstCompared;
	firstCompared = calloc(n,sizeof(int));
	firstCompared = findMaxProduct(0, n-1, A, n); //n-1 comparisons;
	int *secondCompared;
	secondCompared = calloc(n,sizeof(int));
	secondCompared = findMaxProduct(2, (*firstCompared)-1, firstCompared, n); //log2(n)-1 comparisons.
	//Total comparisons: n+log2(n)-2;
	*res = (long long)*(secondCompared+1)*(*(firstCompared+1));
}

int* findMaxProduct(int low, int high, int *A, int n) {
	if(low == high) {
		int *compared = calloc(n,sizeof(int));
		*compared = 2;
		*(compared+1) = A[low];
		return compared;
	}
	int *compared1 = calloc(n,sizeof(int));
	compared1 = findMaxProduct(low, low+(high-low)/2, A, n);
	int *compared2 = calloc(n,sizeof(int));
	compared2 = findMaxProduct(low+(high-low)/2+1, high, A, n);
	if(*(compared1+1) > *(compared2+1)) {
		int k = (*compared1) + 1;
		*compared1 = k;
		*(compared1+(k-1)) = *(compared2+1);
		return compared1;
	}
	int k = (*compared2) + 1;
	*compared2 = k;
	*(compared2+(k-1)) = *(compared1+1);
	return compared2;
}

int main() {
	int *A;
	int n,i;
	long long product;
	scanf("%d",&n);
	A = calloc(n,sizeof(int));
	for(i=0;i<n;i++) {
		scanf("%d",(A+i));
	}
	findSecondRecursive(n,A,&product);
	printf("%lld", product);
	return 0;
}
