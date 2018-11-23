#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define pi 3.14159

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
//proxy

//Proxy mean
float mean(float* num_arr,int num_num){
  float sum=0;
  int i;
  for(i=0;i<num_num;i++){
    sum+=num_arr[i];
  }
  return sum/num_num;
}
//proxy

float deviation_std(float* a,int n)
{ float sum=0,std=0,m=0,var=0;
 int i;
  m=mean(a,n);
  for(i=0;i<n;i++)
   {
    sum=sum+pow((float)(a[i]-m),(float)2);
   }
var=sum/(float)n;
std=pow(var,0.5);
return std;
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
//proxy

// Proxy pearson
float pearson(float a[],float b[],int n){
  int i;
  float r=0,sum_1=0,sum_2=0,prod_sum=0,sum_1_sqr=0,sum_2_sqr=0;
  sum_1=mean(a,n)*n;
  sum_2=mean(b,n)*n;
  for(i=0;i<n;i++)
   {
     prod_sum=prod_sum+(a[i]*b[i]);
     sum_1_sqr=sum_1_sqr+(a[i]*a[i]);
     sum_2_sqr=sum_2_sqr+(b[i]*b[i]);
   }
 r=(n*prod_sum-(sum_1*sum_2));
 r=r/(sqrt(n*sum_1_sqr-pow(sum_1,2.0))*sqrt(n*sum_2_sqr-pow(sum_2,2.0)));

 return r;

}
//proxy

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
//proxy

//Proxy simpson_rule
float simpson_rule(int n,float delta,int tails,float* y_values){
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
// Proxy

// proxy-main
int main()
{
 int i=0,n=0,c=0;
char s1[5],s2[5];

printf("Please enter the number of entries you want : ");
scanf("%d",&n);
float a[n],b[n],b0=0,b1=0,meanx=0,meany=0;
for(;;)
{ printf("Please enter the values X%d :",c);
  scanf("%s",s1);
  if(!isint(s1))
   {
    printf("Please enter only the numericals\n\n");
   }
  else
   {
    a[c]=atof(s1);
    c++;
   }
  if(c==n)
  {
   break;
  }
}

printf("\n\n");
c=0;

for(;;)
{ printf("Please enter the values of Y%d :",c);
  scanf("%s",s2);
  if(!isint(s2))
   {
    printf("Please enter only the numericals\n\n");
   }
  else
   {
    b[c]=atof(s2);
    c++;
   }
  if(c==n)
  {//printf("dfgdf\n");
   break;
  }
}

//printf("dfgdf\n");

meanx=mean(a,n);// modified
meany=mean(b,n);// modified

b1=beta_1(a,b,n,meanx,meany);
b0=meany-(b1*meanx);
//printf("beta_1-%f",b1);
int dof=n-1;
float td=0;
float r=0,stdx=0,stdy=0;

r= pearson(a,b,n);
float std1=deviation_std(a,n);
float std2=deviation_std(b,n);
//r=b1*(std2/(float)std1);
td=(float)(fabs(r)*sqrt(dof-2.0))/(float)(sqrt(1-pow(r,2.0)));
int cou=1;  // modified
int N=4;
float v=0,ov=0;
while(1)
{
 // printf("dfgdf\n");
  float t[N+1],f[N+1];

  t[0]=0;
  t[N]=td;
f[0]= (gama((dof+1)/(float)2))/(gama(dof/(float)2) * pow((dof*pi),0.5) * pow((1+((pow(0,2.0))/(float)dof)),((dof+1)/(float)2)));// modified
f[N] = (gama((dof+1)/(float)2))/(gama(dof/(float)2) * pow((dof*pi),0.5) * pow((1+((pow(td,2.0))/(float)dof)),((dof+1)/(float)2)));

 for(i=1;i<N;i++)
  {
t[i]= t[i-1]+(td/(float)N);
f[i] = (gama((dof+1)/(float)2))/(gama(dof/(float)2) * pow((dof*pi),0.5) * pow((1+((pow(t[i],2.0))/(float)dof)),((dof+1)/(float)2)));
  }

  v=simpson_rule(N,td,2,f);
  if(fabs(v-ov)<0.001)
   { //printf("\nSanketh\n");
     printf("\nThe Probability value for the given t is : %f\n ",v);
     break;
   }

  else
   {
     ov=v;
     cou++;// modified
     N=N*cou;// modified
   }
}

float sig=1-v;
printf("\nThe r*r value is %f\n",r*r);
printf("\nThe value of sig is %f\n",sig);

if((r*r)>0.5 && sig<0.1)
 {
   printf("\n\nIt is Y\n\n");
 }

else
 {
   printf("\n\nIt is N\n\n");
 }
}
// Proxy
