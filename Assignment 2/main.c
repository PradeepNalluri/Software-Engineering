#include<stdio.h>
#include<stdlib.h>
int main(int argc, char const *argv[]) {
  char filename[50];
  printf("Please enter the name of the file with extention:");
  scanf("%s",filename);
  FILE *inputf;
  inputf = fopen(filename,"r");
  if(inputf==NULL){
   printf("\"%s\" File NOT FOUND!\n",filename);
   exit(1);
 }
  return 0;
}
