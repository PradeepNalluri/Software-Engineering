#include<stdio.h>
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
  printf("Mean: %.2f\n",sum/num_num);
}
