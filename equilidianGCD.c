#include<stdio.h>

int eqGcd(int a, int b) {
  if(b==0)
    return a;
  return eqGcd(b,a%b);
}

int main() {
  int a,b,result;
  scanf("%d",&a);
  scanf("%d",&b);
  if(a>b)
    result = eqGcd(a,b);
  else 
    result = eqGcd(b,a);
  printf("%d",result);
  return 0;
}
