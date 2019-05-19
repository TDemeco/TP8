#include <stdio.h>
#include "get_input.h"

float operando1, operando2;
char operador;

int get_input (&operando1, &operando2, &operador){
    
    float * punt1 = &operando1;
    float * punt2 = &operando2;
    float * puntop = &operador;
    char c;
    char state = INIT;
    
    while ((c=getchar())!=' ')
    {
        switch (state)
        {
            case INIT:
                if (c=='+')
                {
                    state = NUM1;
                    break;
                }
                else if (c=='-')
                {
                    flagneg = 1;
                    state = NUM1;
                    break;
                }
                else if (c>='0' && c<='9')
                {
                    c -= '0';
                    *punt1 += c;
                    state = NUM2;
                    break;
                }
                else
                {
                    return ERROR;
                }
        }
    }
