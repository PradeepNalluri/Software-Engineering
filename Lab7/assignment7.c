#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define pi 3.14159
//proxy:mean
float mean(float* array,int size){
  float sum=0;
  for(int i=0;i<size;i++){
    sum=sum+array[i];
   }
  return sum/size;
}
//proxy:isint
int isint(char* string){
  int size=strlen(string);
  for(int i=0;i<size;i++){
    int check=string[i]-'0';
    if(check>9 || check<-3){
      return 0;
    }
  }
  return 1;
}
//proxy:beta0
float beta0(float x_mean,float y_mean,float betaone){
  return y_mean-(x_mean*betaone);
}
//proxy:beta1
float beta1(float* x,float* y,int length,float x_mean,float y_mean){
  float prodxy=0;
  int xsquare=0;
  for(int i=0;i<length;i++){
    prodxy=prodxy+x[i]*y[i];
    xsquare=xsquare+x[i]*x[i];
  }
  float numerator=prodxy-(length*x_mean*y_mean);
  float denominator=xsquare-(length*x_mean*x_mean);
  return numerator/denominator;
}
//proxy:gama
float gama(float n){
  float g=0.0;
  if(n==1){
    return 1.0;
  }
  else if(n==0.5){
    return sqrt(pi);
  }
  else{
    g= (float)(n-1)*gama(n-1);
  }
  return g;
}
//proxy:simpson
float simpson(float* ys,float a,float b,int n,int tails){
  float delta_x=(b-a)/n;
  float odd_sum=0;
  float even_sum=0;
  for(int i=1;i<n-1;i+=2){
    odd_sum+=ys[i];
  }
  for(int i=2;i<n-1;i+=2){
    even_sum+=ys[i];
  }
  float righthalf=ys[0]+ys[n-1]+(4*odd_sum)+(2*even_sum);
  float lefthalf=delta_x/3.0;
  if(tails==1){
  return lefthalf*righthalf+0.5;
  }
  else{
    return 2*lefthalf*righthalf;
  }
}
//proxy:function_output
float function_output(float t,int n){
  float gama_nby2=gama(n/2.0);
  float gama_np1by2=gama((n+1)/2.0);
  float lefthalf=gama_np1by2/(gama_nby2*sqrt(n*pi));
  //printf("denom is %f and n is %d\n",gama_nby2*sqrt(n*pi),n);
  float right_denominator=pow(1+((t*t)/n),(n+1)/2.0);
  float righthalf=1.0/(right_denominator);
  //printf("right half is %f\n",righthalf);
  return lefthalf*righthalf;
}
//proxy:findarea
float findarea(float a, float b,int dof){
  int count=1;
  int flag=0;
  float oldtfun=0;
  float tfun=0;
  int n=4;
  int tails=2;
  while(1){
    float xs[n];
    float ys[n];
    xs[0]=a;
    xs[n-1]=b;
    ys[0]=function_output(a,dof);
    ys[n-1]=function_output(b,dof);
    //printf("y[0] is %f y[n-1] is %f\n",ys[0],ys[n-1]);
    float divide=(b-a)/n;
    for(int i=1;i<n-1;i++){
      xs[i]=xs[i-1]+divide;
      ys[i]=function_output(xs[i],n);
    }
    tfun=simpson(ys,a,b,n,tails);///////////////////////////////////////
    if(flag>1 && fabs(oldtfun-tfun)<0.001){
      break;
    }
    else{
      //printf("oldtfun is %f new tfun is  %f\n",oldtfun,tfun);
      oldtfun=tfun;
      flag++;
      count++;
      n=4*count;
    }
  }
return tfun;
}
//proxy:std2
float std2(float* loce,float* da,float length,float beta0,float beta1,float unregrate){
  float projected=0;
  for(int i=0;i<length;i++){
    projected=projected+pow(da[i]-(beta1*loce[i])-beta0,2);
  }
  float lefthalf=pow(projected/(length-2.0),0.5);
  float loce_mean=mean(loce,length);
  float lh_sum=0;

  for(int i=0;i<length;i++){
    lh_sum=lh_sum+(pow(loce[i]-loce_mean,2));
  }
  float righthalf=pow((1+(1.0/length)+(((beta1*unregrate+beta0)-loce_mean))/lh_sum),0.5);
  return lefthalf*righthalf;
}
//proxy:main
int main(){
  float inita=0;
  float initb=10;
  int count=0;
  float area;
  float temp=0;
  int num_train;
  char LOCE[6];
  char DA[6];
  char CI[6];
  float ci[2]={0.7,0.9};
  float raw_estimates[3];
  char num_dataset[5];
  char unregressed[9];
  float tval[2];
  printf("Enter the no. of test cases:");
  scanf("%s",num_dataset);
  while(!isint(num_dataset)){
    printf("Enter a valid number!\n");
    printf("Enter the no. of test cases:");
    scanf("%s",num_dataset);
  }
  num_train=atof(num_dataset);
  if(num_train==0){
    exit(1);
  }
  float loce[num_train];
  float da[num_train];

  while(count<num_train){
    printf("enter LOCE_%d  value:",count+1);
    scanf("%s",LOCE);
    while(!isint(LOCE)){
      printf("Enter a valid number\n");
      printf("enter LOCE_%d  value:",count+1);
      scanf("%s",LOCE);
    }
    temp=atof(LOCE);
    loce[count]=temp;
    printf("enter DA_%d  value:",count+1);
    scanf("%s",DA);
    while(!isint(DA)){
      printf("Enter a valid number!\n");
      printf("enter DA_%d  value:",count+1);
      scanf("%s",DA);
    }
    temp=atof(DA);
    //printf("Temp is %f",temp);
    da[count]=temp;
    count++;
  }
  count=0;
  while(count<3){
    printf("Enter the raw estimate value %d:",count+1);
    scanf("%s",unregressed);
    while(!isint(unregressed)){
      printf("Enter a valid number!");
      scanf("%s",unregressed );
    }
    temp=atoi(unregressed);
    raw_estimates[count]=temp;
    count++;
  }
  float loce_mean=mean(loce,num_train);
  float da_mean=mean(da,num_train);
  float betaone=beta1(loce,da,num_train,loce_mean,da_mean);
  float betazero=beta0(loce_mean,da_mean,betaone);
//  printf("betaone is %f and betazero is %f\n",betaone,beta0(loce_mean,da_mean,betaone));
  //printf("area is %f\n",findarea(0,2.262));
  for(int i=0;i<2;i++){
  while(1){
    area=findarea(inita,initb,num_train-1);
    //printf("area is %f\n",area);
    if(fabs(area-ci[i])<0.001){
      break;
    }
    else{
      float delta=(initb-inita)/2;
      float leftarea=findarea(inita,initb-delta,num_train-1);
      float rightarea=findarea(inita+delta,initb,num_train-1);
      if(leftarea>ci[i]){
        inita=inita;
        initb=initb-delta;
      }
      else if(rightarea>ci[i]){
        inita=inita+delta;
        initb=initb;
      }
      else{
        inita=inita;
        initb=initb+delta;
      }
    }
  }
  tval[i]=initb;
  printf("inita is %f and initb is %f\n",inita,initb);
}
printf("Beta one is %f\n",betaone);
printf("Beta zero is %f\n",betazero);
float range=0;
float expected=0;
for(int i=0;i<3;i++){
  printf("For the unregrate %d value %f :\n",i+1,raw_estimates[i]);
  float std=std2(loce,da,num_train,betazero,betaone,raw_estimates[i]);
  for(int j=0;j<2;j++){
    range=tval[j]*std;
    printf("range is %f\n",range);
    expected=(betaone*raw_estimates[i]+betazero);
    printf("\tfor the %f percent confidence interval the LPI is %f\n",ci[j]*100,expected-range);
    printf("\tfor the %f percent confidence interval the UPI is %f\n",ci[j]*100,range+expected);
  }
}
}
