#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
void merge(float arr[], int left, int middle, int right){
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 =  right - middle;
    float L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1+ j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(float arr[], int left, int right){
    if (left < right){
        int middle = left+(right-left)/2;
        //recursively breaking array and sorting
        mergeSort(arr, left, middle);
        mergeSort(arr, middle+1, right);
        merge(arr, left, middle, right);
    }
}


int main(){
  //Getting Input
  printf("Please Enter the number of numbers you want to enter: ");
  int num_num;
  int flag=0;
  int flag1=0;
  char num_char[50];
  while(1){
    scanf("%s",num_char);
    for(int j=0;j<strlen(num_char);j++){
      if(48>(int)num_char[j] || (int)num_char[j]>57){
        if((int)num_char[j]!=10){
            flag=1;
        }
      }
    }
    if(strcmp("\n",num_char)==0){
      flag1=1;
    }
    else if(flag==0){
      num_num=atoi(num_char);
      break;
    }else{
      printf("Enter a valid number\n");
      flag=0;
      printf("Please Enter the number of numbers you want to enter: ");
    }
  }
  int i=0;
  flag=0;
  flag1=0;
  float num_arr[num_num];
  float temp;
  char number[50];
  char zero[50];
  sprintf(zero, "%d",0);
  int flagfd,flagfm;
  for(i=0;i<num_num;i++){
    if(flag1==0)
      printf("Please enter element number %d: ",i+1);
      flag1=0;
    flagfd=0;
    flagfm=0;
    fgets(number, 50, stdin);
    for(int j=0;j<strlen(number);j++){
      if(48>(int)number[j] || (int)number[j]>57){
        if((int)number[j]==45){
          flagfm+=1;
        }
        if((int)number[j]==46){
          flagfd+=1;
        }
        if((int)number[j]!=10 && (int)number[j]!=46 && (int)number[j]!=45){
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
  //Calculation of Mean
  float sum=0;
  for(i=0;i<num_num;i++){
    sum+=num_arr[i];
  }
  float mean=sum/num_num;
  printf("Mean(rounded of to 2 digits): %.2f\n",mean);
  sum=0;
  //Calculation of Standard Deviation
  float tbs;
  for(i=0;i<num_num;i++){
    tbs=mean-num_arr[i];
    tbs=tbs*tbs;
    sum+=tbs;
  }
  float standard_deviation;
  standard_deviation=sum/num_num;
  standard_deviation=sqrt(standard_deviation);
  printf("Standard Deviation(rounded of to 2 digits): %.2f\n",standard_deviation);
  //Calculation of Median
  //Sorting of the array
  float sorted_arr[num_num];
  for(i=0;i<num_num;i++){
    sorted_arr[i]=num_arr[i];
  }
  mergeSort(sorted_arr,0,num_num-1);
  float median;
  if(num_num%2==0){
    median=(sorted_arr[num_num/2]+sorted_arr[(num_num/2)-1])/2;
  }else{
    median=sorted_arr[num_num/2];
  }
  printf("Median: %f\n",median);
}
