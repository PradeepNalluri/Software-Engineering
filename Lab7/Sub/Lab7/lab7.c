#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define pi 3.14159
//Proxy mean
float mean(float* num_arr,int num_num){
  float sum=0;
  int i;
  for(i=0;i<num_num;i++){
    sum+=num_arr[i];
  }
  return sum/num_num;
}
//Proxy isint
int isint(char* num_char){
  int num_num;
  int flag=0;
  int flag1=0;
  for(int j=0;j<strlen(num_char);j++){
      if(44>(int)num_char[j] || (int)num_char[j]>57){
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
      return num_num;
    }else{
      flag=0;
      return 0;
    }
}
//Proxy gama
float gama(float n){
  float gamma=0.0;
  if(n==1){
    return 1.0;
  }
  else if(n==0.5){
    return sqrt(pi);
  }
  else{
    gamma= (float)(n-1)*gama(n-1);
  }
  return gamma;
}
//Proxy beta_0
float beta_0(float avg_x,float avg_y,float beta_1){
  return avg_y-(avg_x*beta_1);
}
//Proxy beta_1
float beta_1(float* x,float* y,int length,float avg_x,float avg_y){
  float product_xy=0;
  int x_sq=0;
  for(int i=0;i<length;i++){
    product_xy=product_xy+x[i]*y[i];
    x_sq=x_sq+x[i]*x[i];
  }
  float num=product_xy-(length*avg_x*avg_y);
  float denom=x_sq-(length*avg_x*avg_x);
  return num/denom;
}
//Proxy simpson_rule
float simpson_rule(float* y_values,float a_val,float b_val,int n,int tails){
    float delta=(b_val-a_val)/n;
    float sum_odd=0;
    float sum_even=0;
    for(int i=1;i<n-1;i+=2){
      sum_odd+=y_values[i];
    }
    for(int i=2;i<n-1;i+=2){
      sum_even+=y_values[i];
    }
    float right=y_values[0]+y_values[n-1]+(4*sum_odd)+(2*sum_even);
    float left=delta/3.0;
    if(tails==1){
      return left*right+0.5;
    }
    else{
      return 2*left*right;
    }
}

//Proxy output_funcval
float output_funcval(float t,int n){
  float gamman_2=gama(n/2.0);
  float gamman1_2=gama((n+1)/2.0);
  float left_p=gamman1_2/(gamman_2*sqrt(n*pi));
  float right_denm=pow(1+((t*t)/n),(n+1)/2.0);
  float right_p=1.0/(right_denm);
  return left_p*right_p;
}
//Proxy area_under
float area_under(float a, float b,int degree){
  int count=1;
  int flag=0;
  float prev_t_funcvc=0;
  float t_funcv=0;
  int n=4;
  int tails=2;
  while(1){
    float x_array[n];
    float y_array[n];
    x_array[0]=a;
    x_array[n-1]=b;
    y_array[0]=output_funcval(a,degree);
    y_array[n-1]=output_funcval(b,degree);
    float divide=(b-a)/n;
    for(int i=1;i<n-1;i++){
      x_array[i]=x_array[i-1]+divide;
      y_array[i]=output_funcval(x_array[i],n);
    }
    t_funcv=simpson_rule(y_array,a,b,n,tails);
    if(flag>1 && fabs(prev_t_funcvc-t_funcv)<0.001){
      break;
    }
    else{
      prev_t_funcvc=t_funcv;
      flag++;
      count++;
      n=4*count;
    }
  }
return t_funcv;
}
//Proxy range_func
float range_func(float* loce,float* da,float length,float b_0,float b_1,float toregrate){
  float predicted=0;
  for(int i=0;i<length;i++){
    predicted=predicted+pow(da[i]-(b_1*loce[i])-b_0,2);
  }
  float left_p=pow(predicted/(length-2.0),0.5);
  float loce_mean=mean(loce,length);
  float lh_sum=0;

  for(int i=0;i<length;i++){
    lh_sum=lh_sum+(pow(loce[i]-loce_mean,2));
  }
  float right_p=pow((1+(1.0/length)+(((b_1*toregrate+b_0)-loce_mean))/lh_sum),0.5);
  return left_p*right_p;
}
//Proxy main
int main(){
  float initial_aval=0;
  float initial_bval=10;
  int count=0;
  float area;
  float temp=0;
  int num_samples;
  char locexp[6];
  char DA[6];
  char CI[6];
  float ci[2]={0.7,0.9};
  float raw_estimates[3];
  char dataset[5];
  char tb_regressed[9];
  float t_value[2];
  printf("Enter the number of test cases:");
  scanf("%s",dataset);
  while(!isint(dataset)){
    printf("Enter a valid integer\n");
    printf("Enter the number of test cases:");
    scanf("%s",dataset);
  }
  num_samples=atof(dataset);
  if(num_samples==0){
    exit(1);
  }
  float loce[num_samples];
  float da[num_samples];
  while(count<num_samples){
    printf("Enter Exepected LOC %d value:",count+1);
    scanf("%s",locexp);
    while(!isint(locexp)){
      printf("Enter a valid integer\n");
      printf("Enter Exepected LOC %d value:",count+1);
      scanf("%s",locexp);
    }
    temp=atof(locexp);
    loce[count]=temp;
    printf("Enter DA %d value: ",count+1);
    scanf("%s",DA);
    while(!isint(DA)){
      printf("Enter a valid integer\n");
      printf("Enter DA %d  value:",count+1);
      scanf("%s",DA);
    }
    temp=atof(DA);
    da[count]=temp;
    count++;
  }
  count=0;
  while(count<3){
    printf("Enter the raw estimate value %d:",count+1);
    scanf("%s",tb_regressed);
    while(!isint(tb_regressed)){
      printf("Enter a valid integer\n");
      printf("Raw Estimate value %d:",count+1);
      scanf("%s",tb_regressed );
    }
    temp=atoi(tb_regressed);
    raw_estimates[count]=temp;
    count++;
  }
  float loce_mean=mean(loce,num_samples);
  float da_mean=mean(da,num_samples);
  float betaone=beta_1(loce,da,num_samples,loce_mean,da_mean);
  float betazero=beta_0(loce_mean,da_mean,betaone);

  for(int i=0;i<2;i++){
  while(1){
    area=area_under(initial_aval,initial_bval,num_samples-1);
    if(fabs(area-ci[i])<0.001){
      break;
    }
    else{
      float delta=(initial_bval-initial_aval)/2;
      float leftarea=area_under(initial_aval,initial_bval-delta,num_samples-1);
      float rightarea=area_under(initial_aval+delta,initial_bval,num_samples-1);
      if(leftarea>ci[i]){
        initial_aval=initial_aval;
        initial_bval=initial_bval-delta;
      }
      else if(rightarea>ci[i]){
        initial_aval=initial_aval+delta;
        initial_bval=initial_bval;
      }
      else{
        initial_aval=initial_aval;
        initial_bval=initial_bval+delta;
      }
    }
  }
  t_value[i]=initial_bval;
  printf("Initial Value of a: %f and Initial Value of b: %f\n",initial_aval,initial_bval);
}
printf("Beta one: %f\n",betaone);
printf("Beta zero: %f\n",betazero);
float range=0;
float expected=0;
for(int i=0;i<3;i++){
  printf("For the %d to be regressed value is %f :\n",i+1,raw_estimates[i]);
  float std=range_func(loce,da,num_samples,betazero,betaone,raw_estimates[i]);
  for(int j=0;j<2;j++){
    range=t_value[j]*std;
    printf("Range Value: %f\n",range);
    expected=(betaone*raw_estimates[i]+betazero);
    printf("Confidence Interval: %f , UPI: %f\n",ci[j]*100,range+expected);
    printf("Confidence Interval: %f , LPI: %f\n",ci[j]*100,expected-range);
  }
}
}
