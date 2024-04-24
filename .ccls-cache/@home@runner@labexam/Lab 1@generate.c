#include<stdio.h>
#include<stdlib.h>

int main(){
  for(int i=0; i<1000; i++){
    printf("%d\t",rand()%1000);
  }
}