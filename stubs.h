#ifndef STUBS_H
#define STUBS_H

int add_operation(char o, float (*a) (float, float));
float calc_res(float x, float y, char op);
int get_input(float* ,float* , char*);
float suma (float,float);
float resta (float,float);
float producto (float,float);
float division (float,float);
float exponenciacion (float,float);
int check_errors(int);

#endif /* STUBS_H */

