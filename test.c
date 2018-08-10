#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
  printf("Please Enter the number of numbers you want to enter: ");
  int num_num;
  scanf("%d",&num_num);
  int i=0;
  int flag=0;
  int flag1=0;
  float num_arr[num_num];
  float temp;
  char number[50];
  char zero[50];
  sprintf(zero, "%d",0);
  for(i=0;i<num_num;i++){
    if(flag1==0)
      printf("Please enter element number %d: ",i+1);
      flag1=0;
    fgets(number, 50, stdin);
    for(int j=0;j<strlen(number);j++){
      if(48>(int)number[j] || (int)number[j]>57){
        if((int)number[j]!=10){
            flag=1;
        }
      }
    }
    if(strcmp("\n",number)==0){
      i=i-1;
      flag1=1;
    }
    else if(flag==0){
      temp=atof(number);
      num_arr[i]=temp;
    }else{
      i=i-1;
      printf("Enter a valid number\n");
      flag=0;
    }
  }
  for(i=0;i<num_num;i++){
    printf("%f\n",num_arr[i]);
  }
}
