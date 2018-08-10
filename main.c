#include<stdio.h>
#include<math.h>
void merge(float arr[], int left, int middle, int right){
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 =  right - middle;
    int L[n1], R[n2];
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
  scanf("%d",&num_num);
  int i;
  float num_arr[num_num];
  for(i=0;i<num_num;i++){
    printf("Please enter element number %d: ",i+1);
    scanf("%f",&num_arr[i]);
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
