
#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N) {
    int i;
    float sum=0;
    float powerdb;
    for(i=0;i<N;i++){
        sum+=x[i]*x[i];
    }
    powerdb=10*log10(sum/N);
    return powerdb;
}
float compute_power_ventanahamming(const float *x, unsigned int N) {
    float sum, sum_w=0;
    for (int i = 0; i < N; i++) {
        float w = 0.54 - 0.46 * cos(2 * M_PI * i / (N - 1));
        sum += (x[i] * w) * (x[i] * w);
        sum_w += w * w;
    }
    return 10 * log10f(sum / sum_w);
}
float compute_am(const float *x, unsigned int N) {
   int i;
   int arp=0;
   for(i=0;i<N;i++){
        arp += fabs(x[i]);
   }
    return arp/N;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    int i,zcr=0;
    
    for(i=1;i<N;i++){
        if(sgn(x[i])!=sgn(x[i-1])){
            zcr+=1;
        }
    }
    zcr=zcr*(fm/2/(N-1));
    return zcr;
}
int sgn(float x){
    if(x<0){
        return -1;
    }
    if(x==0){
        return 0;
    }
    if(x>0){
        return 1;
    }
    return 0;
}