#include<stdio.h>
#include<stdlib.h>
//Proxy main
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
 int count2=0;
 int count3=0;
 while ((c = fgetc(inputf)) != EOF) {
   if(c=='\n' && count2!=0){
     count+=1;
     count2=0;
   }
   else if(c=='\n' && count2==0){
     count3+=1;
   }
   else{
     count2+=1;
   }
}
  printf("The number of lines in the file which are not blank are: %d\n",count);
  printf("The number of lines in the file which are blank are: %d\n",count3);
  printf("Total number of lines in the file are: %d\n",count+count3);
  return 0;
}
//proxy
