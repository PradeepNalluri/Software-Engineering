#include<stdio.h>
#include<stdlib.h>
int main(int argc, char const *argv[]) {
  char filename[50];
  printf("Please enter the name of the file with extention:");
  scanf("%s",filename);
  FILE *inputf;
  inputf = fopen(filename,"r");
  if(inputf==NULL){
   printf("\"%s\" File NOT FOUND! Please enter a valid file name\n",filename);
   exit(1);
 }
 char c;
 int count=0;
 while ((c = fgetc(inputf)) != EOF) {
   if(c=='\n'){
     count+=1;
   }
}
  printf("The number of lines in the file are: %d\n",count);
  return 0;
}
