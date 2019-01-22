
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
  int maxLPSLength = 0;
  int i=0;//currentRightPosition 
  int iMirror;//currentLeftPosition 
  int diff=-1;
  int R = 2; //centerRightPosition
  int C = 1;//centerPosition
  int start = -1, end = -1;
  int maxLPSCenterPosition = 0;
  for(i = 2 ; i < n ; i++ ) {

    /* get currentLeftPosition iMirror for currentRightPosition i
     */
    iMirror = 2 * C - i;
    l[i] = 0;
    diff = R - i;
    /* If currentRightPosition i is within centerRightPosition R 
     */
    if(diff > 0)
      l[i] = min( l[iMirror], diff);
    
    /* Attempt to expand palindrome centered at currentRightPosition i 
     * Here for odd positions, we compare characters and  
     * if match then increment LPS Length by ONE 
     * If even position, we just increment LPS by ONE without  
     * any character comparison 
     */
    while(((i+l[i]) < n) && ((i-l[i]) > 0) &&
        (((i+l[i]+1)%2 == 0) || (text[(i+l[i]+1)/2] == text[(i-l[i]-1)/2]))) {
      l[i]++;
    }

    /* If palindrome centered at currentRightPosition i
     * expand beyond centerRightPosition R,
     * adjust centerPosition C based on expanded palindrome.
     */
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
  for(i = start ; i <= end ; i++ ) {
    printf("%c",text[i]);
  }
  printf("\n");
}

/* Driver function */
int main() {

  char *text = (char*)malloc(14*sizeof(char));
  strncpy(text,"abcbabcbabcba",14);
  findMaximumPalindromicString(text);
  return 0;
}

