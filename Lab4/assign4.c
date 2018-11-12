#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
//Proxy average
float mean(float* num_arr,int num_num){
  float sum=0;
  for(int i=0;i<num_num;i++){
    sum+=num_arr[i];
  }
  float mean=sum/num_num;
  return mean;
}
//proxy
//Proxy isint
int isint(char* num_char){
   int num_num;
  int flag=0;
  int flag1=0;
  for(int j=0;j<strlen(num_char);j++){
      if(47>(int)num_char[j] || (int)num_char[j]>57){
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
      return num_num+2;
    }else{
      flag=0;
      return 0;
    }
}
//proxy
//Proxy isfloat
float isfloat(char* number){
   int flagfd=0;int flagfm=0;int flag=0;int flag1=0;int temp=0;
  for(int j=0;j<strlen(number);j++){

      if(47>(int)number[j] || (int)number[j]>57){
        // printf("here%d\n",(int)number[j]);
        if((int)number[j]==45){
          flagfm+=1;
        }        if((int)number[j]==46){
          flagfd+=1;
        }
        if((int)number[j]!=10 && (int)number[j]!=46 && (int)number[j]!=45){
          flag=1;
        }
      }
    }
    if(strcmp("\n",number)==0){
      flag1=1;
    }
    else if(flag==0){
      // temp=atof(number);
      return 1;
    }else{
      flag=0;
      return 0;
    }
}
//proxy
//Proxy beta0
float beta0(float x_mean,float y_mean,float betaone){
  return y_mean-(x_mean*betaone);
}
//proxy
//Proxy beta1
float beta1(float* x,float* y,int length,float x_mean,float y_mean){
  float product=0;
  int x2=0;
  for(int i=0;i<length;i++){
    product=product+x[i]*y[i];
    x2=x2+x[i]*x[i];
  }
  float numerator=product-(length*x_mean*y_mean);
  float denominator=x2-(length*x_mean*x_mean);
  return numerator/denominator;
}
//proxy
//Proxy main
int main(){
  int t;
  int length;
  char len[5];
  int count=0;
  printf("Please Enter the number of numbers you want to enter(only non negative integers):");
  scanf("%s",len);
  length=isint(len);
  while(!length){
    printf("Enter a valid number!\n");
    printf("Please Enter the number of numbers you want to enter(only non negative integers):");
    scanf("%s",len);
    length=isint(len);
  }
  length=length-2;
  float x[length];
  float y[length];
  char str[20];
  if(length==0){
    printf("You have entered zero\n");
    exit(1);
  }

while(1){
  printf("Enter the %d number in x array:",count);
  scanf("%s",str);
  if(isfloat(str)){
    x[count]=atof(str);
    count++;
  }
  else{
    printf("Enter a valid number\n");
  }

  if(count==length){
    break;
  }
}
count=0;
while(1){
  printf("Enter the %d number in y array:",count);
  scanf("%s",str);
  if(isfloat(str)){
    y[count]=atof(str);
    count++;
  }
  else{
    printf("Enter a valid number\n");
  }
  if(count==length){
    break;
  }
}
float x_mean=mean(x,length);
float y_mean=mean(y,length);
float betaone=beta1(x,y,length,x_mean,y_mean);
printf("\nTest set 1:");
printf("The beta0 for the test case is %f\n",beta0(x_mean,y_mean,betaone));
printf("The beta1 for the test case is %f\n",betaone);
}
//proxy
