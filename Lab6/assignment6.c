#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define pi 3.14
//proxy:gama
float gama(float n){
  float gama_val=0.0;
  if(n==1){
    return 1.0;
  }
  else if(n==0.5){
    return sqrt(pi);
  }
  else{
    gama_val= (float)(n-1)*gama(n-1);
  }
  return gama_val;
}
//proxy:simpson_rule
float simpson_rule(float* y_values,float t,int n,int tails){
    float delta=t/n;
    float sum_odd=0;
    float sum_even=0;
    for(int i=1;i<n-1;i+=2){
      sum_odd+=y_values[i];
    }
    for(int i=1;i<n-1;i+=2){
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
//proxy:func_cal
float func_cal(float t,int n){
  float gamaby2=gama(n/2.0);
  float gamapby2=gama((n+1)/2.0);
  float left=gamapby2/(gamaby2*sqrt(n*pi));
  float denm=pow(1+((t*t)/n),(n+1)/2.0);
  float right=1.0/(denm);
  return left*right;
}
//proxy:isfloat
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
      return num_num;
    }else{
      flag=0;
      return 0;
    }
}
//proxy

//proxy:main
int main(){
    char num_tests[5];
    int num_test=0;
    float t_val;
    int degrees,tails;
    char t_string[5];
    char degrees_str[5];
    int n=4;
    while(1){
      printf("Enter the number of test cases:");
      scanf("%s",num_tests);
      if(isint(num_tests)){
        num_test=isint(num_tests);
        break;
      }
      printf("Enter a valid number.\n");
    }
    for(int num=0;num<num_test;num++){
      n=4;
      printf("For test case %d\n",num+1);
      printf("Enter the value of t:");
      scanf("%s",t_string);
      while(!isfloat(t_string)){
        printf("Enter a valid number.\n");
        printf("Enter the t value:");
        scanf("%s",t_string);
      }
      t_val=atof(t_string);
      while(1){
        printf("Enter the number of test cases:");
        scanf("%s",degrees_str);
        if(isint(degrees_str)){
          degrees=isint(degrees_str);
          break;
        }
        printf("Enter a valid number.\n");
    }
    printf("Enter the number of tails:");
    scanf("%d",&tails);
    while(1){
      if(tails==1 || tails==2){
        break;
      }
      else{
        printf("Number of tails can only be 1 or 2\n");
        printf("Enter the number of tails:");
        scanf("%d",&tails);
      }
    }
    //printf("%f\t%d\t%d\t\n",t,degrees,tails);
    int count=1;
    int flag=0;
    float t_old;
    float t_fval;
    while(1){
      float x_values[n];
      float y_values[n];
      x_values[0]=0;
      x_values[n-1]=t_val;
      y_values[0]=func_cal(0,n);
      y_values[n-1]=func_cal(t_val,n);
      for(int i=1;i<n-1;i++){
        x_values[i]=x_values[i-1]+(t_val/n);
        y_values[i]=func_cal(x_values[i],n);
      }
      t_fval=simpson_rule(y_values,t_val,n,tails);
      if(flag>1 && abs(t_old-t_fval)<0.01){
        break;
      }
      else{
        t_old=t_fval;
        flag+=1;
        count+=1;
        n=n*count;
      }
    }
    printf("The final value is: %f\n",t_fval );
  }
}
