
#include<stdio.h>
#include<stdbool.h>

#define DIR 8

int isSafe(int M[][5], int R, int C, int i, int j) {
  
  if(i >= R || i < 0 || j >= C || j < 0) 
    return 0;
  else
    return M[i][j];
}

void getConnectedArea(int M[][5], int R, int C, int i, int j, int *maxSize, int size, bool visited[][5]) {

  int k = 0,newi,newj,val = 0;
  if(R <= i || C <= j)
    return;

  size++;
  visited[i][j] = true;

  if(*maxSize < size)
    *maxSize = size;

  int dir[DIR][2] = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};

  for(k=0;k<DIR;k++) {

    newi = i+dir[k][0];
    newj = j+dir[k][1];
    val = isSafe(M,R,C,newi,newj);
    if(val > 0 && (visited[newi][newj] == false))
      getConnectedArea(M,R,C,newi,newj,maxSize,size,visited);
  }
  visited[i][j]=false;
}

int getMaxConnArea(int M[][5], int R, int C) {

  int i,j,size=0;
  bool visited[R][C];

  for(i=0;i<R;i++) {
    for(j=0;j<C;j++) {
      if(M[i][j]==1)
        getConnectedArea(M,R,C,i,j,&size,0,visited);
    }
  }

  return size;

}

int main() {
  int A[5][5] = {{0,1,0,0,0},{0,0,0,0,1},{0,1,1,1,0},{0,1,1,1,0},{1,0,0,1,0}};
  int i,j;
  printf("\nA:\n");
  for(i=0;i<5;i++) {
    for(j=0;j<5;j++) {
      printf(" %d",A[i][j]);
    }
    printf("\n");
  }
  printf("\nsize = %d\n",getMaxConnArea(A,5,5));
  return 0;
}

