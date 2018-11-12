#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define len_cal 10
#define changed_code 14
#define removed_code 14
#define addition_basese_code 369
#define table_range 1.07
#define len_data 13
#define length_io 10
//Proxy average
float average(float* arr,int arr_size){
  float sum=0;
  for(int i=0;i<arr_size;i++){
    sum=sum+arr[i];
   }
  return sum/arr_size;
}
//Proxy median
float median(float* arr,int arr_size){
  int temp;
  float modif_arr[arr_size];
  for(int i=0;i<arr_size;i++){
    for(int j=i+1;j<arr_size;j++){
      if(arr[i]>arr[j]){
        temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
      }
    }
  }
  if(arr_size%2==0){
    return (arr[(arr_size-1)/2]+arr[arr_size/2])/2.0;
  }
  else{
    return arr[arr_size/2];
  }

}
//Proxy std
double std(float* arr,int arr_size){
  float avg=average(arr,arr_size);
  float sum=0;
  for(int i=0;i<arr_size;i++){
    sum=sum+(pow(arr[i]-avg,2));
  }
  float var=sum/(float)arr_size;
  return pow(var,0.5);

}
double std2(float* arr,int arr_size){
  float avg=average(arr,arr_size);
  float sum=0;
  for(int i=0;i<arr_size;i++){
    sum=sum+(pow(arr[i]-avg,2));
  }
  float var=sum/((float)arr_size-2);
  return pow(var,0.5);

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
float vs(float average,double std,int flag){
  if(flag==0){
    return average-2*std;
}
else{
  return pow(10,average-2*std);
}
}

float s(float average,double std,int flag){
  if(flag==0){
    return average-std;
}
else{
  return pow(10,average-std);
}
}
float m(float average,int flag){
  if(flag==0){
    return average;
}
else{
  return pow(10,average);
}
}
float l(float average,double std,int flag){
  if(flag==0){
    return average+std;
}
else{
  return pow(10,average+std);
}
}

float vl(float average,double std,int flag){
  if(flag==0){
    return average+2*std;
}
else{
  return pow(10,average+2*std);
}
}
int main(){
float actual_lines[20]={98,284,292,286,350,464,381,369,365,284,277,212,319,218,238,312,676,266,225,395};
float expected_lines[20]={124,360,229,321,279,352,297,263,357,311,341,153,390,260,215,468,528,232,304,459};
float duration_expected[20]={360,900,540,840,720,780,780,660,900,780,840,420,1020,660,540,1200,1260,600,780,1080};
float duration_actual[20]={300,720,720,780,900,1380,1020,960,900,720,600,480,720,540,600,660,1620,840,600,1080};
float calculation_loc[len_cal] = {93,112,79,126,68,128,141,142,58,79};
float calculation_methods[len_cal] = {5,1,1,6,1,6,3,1,6,3};
float loc_data[len_data] = {95,127,90,122,97,131,118,122,42,107,94,131,89};
float data_methods[len_data] = {5,4,6,5,5,5,3,5,4,4,6,6,5};
float loc_io[length_io] = {125,106,92,101,38,104,26,75,114,90};
float io_methods[length_io] = {5,7,10,8,5,3,5,2,2,6};
printf("Values for Calculation Proxies\n");
for(int i=0;i<len_cal;i++){
  calculation_loc[i]=calculation_loc[i]/calculation_methods[i];
}
float logrithm[len_cal];
float mean=average(calculation_loc,len_cal);
double standard_deviation	=std(calculation_loc,len_cal);
if (mean>2*standard_deviation){
  printf("vs is %f\n",vs(mean,standard_deviation,0));
  printf("s is %f\n",s(mean,standard_deviation,0));
  printf("m is %f\n",m(mean,0));
  printf("l is %f\n",l(mean,standard_deviation,0));
  printf("vl is %f\n",vl(mean,standard_deviation,0));
}
else{
  for(int i=0;i<len_cal;i++){
    logrithm[i]=log10(calculation_loc[i]);
  }
  float avg_log=average(logrithm,len_cal);
  double std_log=std(logrithm,len_cal);
  printf("vs is %f\n",vs(avg_log,std_log,1));
  printf("s is %f\n",s(avg_log,std_log,1));
  printf("m is %f\n",m(avg_log,1));
  printf("l is %f\n",l(avg_log,std_log,1));
  printf("vl is %f\n",vl(avg_log,std_log,1));
}
printf("Calculation for Data Proxies\n");
for(int i=0;i<len_data;i++){
  loc_data[i]=loc_data[i]/data_methods[i];
}
float logdata[len_data];
float data_mean=average(loc_data,len_data);
double data_std=std(loc_data,len_data);
if (data_mean>2*data_std){
  printf("vs is %f\n",vs(data_mean,data_std,0));
  printf("s is %f\n",s(data_mean,data_std,0));
  printf("m is %f\n",m(data_mean,0));
  printf("l is %f\n",l(data_mean,data_std,0));
  printf("vl is %f\n",vl(data_mean,data_std,0));
}
else{
  for(int i=0;i<len_data;i++){
    logdata[i]=log10(loc_data[i]);
  }
  float data_logrithm=average(logdata,len_data);
  double datalogstd=std(logdata,len_data);
  printf("vs is %f\n",vs(data_logrithm,datalogstd,1));
  printf("s is %f\n",s(data_logrithm,datalogstd,1));
  printf("m is %f\n",m(data_logrithm,1));
  printf("l is %f\n",l(data_logrithm,datalogstd,1));
  printf("vl is %f\n",vl(data_logrithm,datalogstd,1));
}
printf("Values for IO Proxies\n");
for(int i=0;i<length_io;i++){
  loc_io[i]=loc_io[i]/io_methods[i];
}
float log_io[length_io];
float io_avg=average(loc_io,length_io);
double iostd=std(loc_io,length_io);
if (io_avg>2*iostd){
  printf("vs is %f\n",vs(io_avg,iostd,0));
  printf("s is %f\n",s(io_avg,iostd,0));
  printf("m is %f\n",m(io_avg,0));
  printf("l is %f\n",l(io_avg,iostd,0));
  printf("vl is %f\n",vl(io_avg,iostd,0));
}
else{
  for(int i=0;i<length_io;i++){
    log_io[i]=log10(loc_io[i]);
  }
  float io_avg_log=average(log_io,length_io);
  double io_avg_std=std(log_io,length_io);
  printf("vs is %f\n",vs(io_avg_log,io_avg_std,1));
  printf("s is %f\n",s(io_avg_log,io_avg_std,1));
  printf("m is %f\n",m(io_avg_log,1));
  printf("l is %f\n",l(io_avg_log,io_avg_std,1));
  printf("vl is %f\n",vl(io_avg_log,io_avg_std,1));
}
printf("Proxy Sizing\n");
float addition_base[2]={568.52,33.85};
float new_objects[6]={188.65,44.93,120.39,67.39,80.99,663.27};
for(int i=0;i<2;i++){
  printf("Base Addition%d LOC : %f\n",i+1,addition_base[i]);
}
for(int i=0;i<6;i++){
  printf("New Objects%d LOC : %f\n",i+1,new_objects[i]);
}
printf("Size Estimates\n");

float addition_basesum=0;
for(int i=0;i<2;i++){
  addition_basesum+=addition_base[i];
}
float new_objectssum=0;
printf("Total Base Additions: %f\n",addition_basesum);
for(int i=0;i<6;i++){
  new_objectssum+=new_objects[i];
}
printf("New Objects Lines Of Code : %f\n",new_objectssum);
float estimated_loc=new_objectssum+addition_basesum+changed_code;
printf("Estimated Lines of Code : %f\n",estimated_loc);
float expected_linesaverage=average(expected_lines,20);
float actual_linesaverage=average(actual_lines,20);
float la_le_beta1=beta_1(expected_lines,actual_lines,20,expected_linesaverage,actual_linesaverage);
float el_al_b0;
float range=0;
range=std2(actual_lines,20)*table_range;

if(la_le_beta1>0.3){
  el_al_b0=beta_0(expected_linesaverage,actual_linesaverage,la_le_beta1);
  printf("B0 is %f\n",el_al_b0);
  printf("B1 is %f\n",la_le_beta1);
}
else{
  printf("B0 is %d\n",0);
  printf("B1 is %d\n",1);
  la_le_beta1=1;
  el_al_b0=0;
}
float N=(la_le_beta1*estimated_loc)+el_al_b0;
printf("N : %f",N);
float T=N+addition_basese_code-removed_code-changed_code;
printf("T : %f",T);
printf("Range is : %f\n",range);
if(la_le_beta1>0.3){
  printf("Upper Prediction Index: %f\n",N+range);
  if(N-range<1){
    printf("Lower Prediction Index: NA\n");
  }
  else{
    printf("Lower Prediction Index: %f\n",N-range);
  }
}
else{
  printf("Upper Prediction Index: NA\n");
  printf("Lower Prediction Index: NA\n");
}
printf("Duritation Estimates\n");
float percent_time[20]={14,21,3,3,57,2};
float duration=0;
float sum_act_loc=0;
float sumofda=0;
float actual_linesdabeta_0;
float expected_linesdebeta_0=0;
for(int i=0;i<20;i++){
  sum_act_loc+=actual_lines[i];
  sumofda+=duration_actual[i];
}
float productivity=(sum_act_loc/sumofda)*60;
printf("productivity is %f\n",productivity);

float act_dur_avg=average(duration_actual,20);
float actual_linesdabeta_1=beta_1(actual_lines,duration_actual,20,actual_linesaverage,act_dur_avg);

float exp_dur_avg=average(duration_expected,20);
float expected_linesdabeta_1=beta_1(expected_lines,duration_actual,20,expected_linesaverage,act_dur_avg);
if(actual_linesdabeta_1>expected_linesdabeta_1 & actual_linesdabeta_1>0.3 & expected_linesdabeta_1>0.3){
  actual_linesdabeta_0=beta_0(actual_linesaverage,act_dur_avg,actual_linesdabeta_1);
  duration=N*actual_linesdabeta_1+actual_linesdabeta_0;
  printf("actual_lines * time\n");
}
else if(expected_linesdabeta_1>actual_linesdabeta_1 & actual_linesdabeta_1>0.3 & expected_linesdabeta_1>0.3){
  expected_linesdebeta_0=beta_0(expected_linesaverage,exp_dur_avg,expected_linesdabeta_1);
  duration=N*expected_linesdabeta_1+expected_linesdebeta_0;
  printf("expected_lines * time\n");
}
else{
  duration=N;
  printf("Productivity\n");
}
printf("duration is %f\n",duration);
for(int i=0;i<6;i++){
  percent_time[i]=(percent_time[i]*duration)/100;
}
range=std2(duration_actual,20)*table_range;
printf("Range is : %f\n",range);
printf("UL : %f\n",duration+range);
printf("LL : %f\n",duration-range);
printf("Time Duration\n");
printf("Planning\t%f\n",percent_time[0]);
printf("Design\t%f\n",percent_time[1]);
printf("Code\t%f\n",percent_time[2]);
printf("Compile\t%f\n",percent_time[3]);
printf("Test\t%f\n",percent_time[4]);
printf("Postmortem\t%f\n",percent_time[5]);
}
