#include<stdio.h>
#include <string.h>
#include<stdlib.h>
//Proxy linecounter
int linecounter(FILE* inputf){
    char buff[1024];
    int count=0;
    while (fgets(buff, 1024, inputf)) {
      if(strstr(buff,"//Proxy") != NULL) {
        char function_name[100];
        int countname=0;
        for(int i=8;i<strlen(buff)-1;i++){
            function_name[countname]=buff[i];
            countname+=1;
        }

          while (fgets(buff, 1024, inputf)){
            if(strstr(buff,"//proxy") != NULL) {
              printf("The numbe of lines in Proxy %s are:%d\n",function_name,count);
              break;
            }
            else{
              count+=1;
            }
          }
      }
    }
    return 0;
  }
//proxy
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
  int count=linecounter(inputf);
  printf("The number of lines in the file which are not blank are: %d\n",count);
  return 0;
}
//proxy
