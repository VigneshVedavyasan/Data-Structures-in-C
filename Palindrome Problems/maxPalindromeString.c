
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int min(int a, int b) {

  int r = a;
  if(a < b)
    r = b;
  return r;
}

void findMaximumPalindromicString(char* text) {

  int n = strlen(text);
  if(n==0)
    return;
  n = 2*n+1;
  int l[n];
  l[0] = 0;
  l[1] = 1;
  int maxLPSLength = 0, i=0, diff=-1, R = 2, C = 1, iMirror, start = -1, end = -1;
  int maxLPSCenterPosition = 0;
  for(i = 2 ; i < n ; i++ ) {

    iMirror = 2 * C - i;
    l[i] = 0;
    diff = R - i;
    if(diff > 0)
      l[i] = min( l[iMirror], diff);
    while(((i+l[i]) < n) && ((i-l[i]) > 0) &&
        (((i+l[i]+1)%2 == 0) || (text[i+l[i]+1] == text[i-l[i]-1]))) {
      l[i]++;
    }
    if(maxLPSLength < l[i]) {
      maxLPSLength = l[i];
      maxLPSCenterPosition = i;
    }

    if((l[i]+i) > R) {
      R = l[i]+i;
      C = i;
    }
  }
  start = (maxLPSCenterPosition - maxLPSLength)/2;
  end = maxLPSLength + start -1;
  printf("%d,%d\n",start,end);
  for(i = start ; i < end ; i++ ) {
    printf("%c",text[i]);
  }
  printf("\n");
}

int main() {

  char *text = (char*)malloc(14*sizeof(char));
  strncpy(text,"abcbabcbabcba",14);
  findMaximumPalindromicString(text);
  return 0;
}

