#include<stdio.h>
#include <string.h>
#include<stdlib.h>
//Proxy linecounter
int linecounter(FILE* inputf){
    char buff[1024],c;
    int count=0;int count2=0;int count3=0;int loc=0;int toprox=0;
    while (fgets(buff, 1024, inputf)) {
    	count=0;
      if(strstr(buff,"//Proxy") != NULL && strstr(buff,"if(strstr") == NULL) {
        char function_name[100];
        int countname=0;
        for(int i=8;i<sizeof(buff)-1;i++){
            function_name[countname]=buff[i];
            countname+=1;
        }
          while (fgets(buff, 1024, inputf)){
            if(strstr(buff,"//proxy") != NULL && strstr(buff,"if(strstr") == NULL) {
              toprox+=1;
              printf("Name of the proxy:%s",function_name);
              printf("Total LoC:%d\n",count);
              loc+=count;
              break;
            }
            else{
       //      	printf("%s\n",buff);
            	for(int j=0;j<strlen(buff);j++){
            		c=buff[j];
            		if(c=='\n' && count2!=0){
				     count+=1;
				     count2=0;
				   }
				   else if(c=='\n' && count2==0){
				     count3+=1;
				   }
				   else{
				   	 if(count2==0 && c==' '){
				   	 	continue;
				   	 }
				   	 else{
				   	 	count2+=1;
				   	 }

				   }
          }
          }
      }
    }
}
            
  printf("Number of proxies in the file are: %d\n",toprox);
    return loc;
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
  printf("The number of lines in the file are:%d\n",count);
  fclose(inputf);
  return 0;
}
//proxy
