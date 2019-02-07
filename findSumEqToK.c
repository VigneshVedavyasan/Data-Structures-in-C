#include<stdio.h>

void merge(int A[],int temp[],int left,int mid,int right) {

	int left_end = mid-1, tmp_pos = left, size = right-left+1,i;
	while((left <= left_end) && (mid <= right)) {
		if(A[left] <= A[mid]) {
			temp[tmp_pos] = A[left];
			tmp_pos++;
			left++;
		} else {
			temp[tmp_pos] = A[mid];
			tmp_pos++;
			mid++;
		}
	}
	while(left <= left_end) {
		temp[tmp_pos] = A[left];
		tmp_pos++;
		left++;
	}
	while(mid <= right) {
		temp[tmp_pos] = A[mid];
		tmp_pos++;
		mid++;
	}
	for(i=0;i<=size;i++) {
		A[right] = temp[right];
		right--;
	}
}
void mergeSort(int A[],int temp[],int low,int high) {

	int mid;
	if(high > low) {
		mid = (low+high)/2;
		mergeSort(A,temp,low,mid);
		mergeSort(A,temp,mid+1,high);
		merge(A,temp,low,mid+1,high);
	}
}
void findSumEqToK(int A[],int n,int k) {

	int i,j,temp,tempArr[9];
	mergeSort(A,tempArr,0,n-1);
	for(i=0,j=n-1;i<j;) {
		temp = A[i] + A[j];
		if(temp == k) {
			printf("Elements found : %d , %d\n",A[i],A[j]);
			return;
		} else if(temp < k) {
			i = i + 1;
		} else {
			j = j - 1;
		}
	}
}

int main() {

	int A[]={3,5,7,2,4,1,9,8,6};
	findSumEqToK(A,sizeof(A)/sizeof(A[0]),10);
	return 0;
}
