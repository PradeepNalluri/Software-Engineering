#include<stdio.h>
#include <string.h>
#include<stdlib.h>
//Proxy linecounter
int linecounter(FILE* inputf){
    char buff[1024];
    int count=0;
    while (fgets(buff, 1024, inputf)) {
          printf("%s",buff);
          while (fgets(buff, 1024, inputf)){
              break;
            }
            else{
              count+=1;
            }
          }
      }
    }
    return count;
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
