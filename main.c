#include<stdio.h>
#include<math.h>
int main(){
  printf("Please Enter the number of numbers you want to enter: ");
  int num_num;
  scanf("%d",&num_num);
  int i;
  float num_arr[num_num];
  for(i=0;i<num_num;i++){
    printf("Please enter element number %d: ",i+1);
    scanf("%f",&num_arr[i]);
  }
  float sum=0;
  for(i=0;i<num_num;i++){
    sum+=num_arr[i];
  }
  float mean=sum/num_num;
  printf("Mean(rounded of to 2 digits): %.2f\n",mean);
  sum=0;
  float tbs;
  for(i=0;i<num_num;i++){
    tbs=mean-num_arr[i];
    tbs=tbs*tbs;
    sum+=tbs;
  }
  float standard_deviation;
  standard_deviation=sum/num_num;
  standard_deviation=sqrt(standard_deviation);
  printf("Median(rounded of to 2 digits): %.2f\n",standard_deviation);

}
