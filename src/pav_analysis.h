#ifndef PAV_ANALYSIS_H
#define PAV_ANALYSIS_H

float compute_power(const float *x, unsigned int N);
float compute_am(const float *x, unsigned int N);
float compute_zcr(const float *x, unsigned int N, float fm);
float compute_power_ventanahamming(const float *x, unsigned int N);
int sgn(float x);
#endif	/* PAV_ANALYSIS_H	*/
