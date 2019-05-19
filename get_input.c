#include <stdio.h>
#include "get_input.h"
#define NOERROR 0
#define ERROR 1
#define MAX_OPERATORS 5


enum {INIT, NUM1, NUM2, NUMDECIMAL};

int get_input (float * operando1, float * operando2, unsigned char * operador)
{
    extern unsigned charoperators [];
    float * punt1 = operando1;
    float * punt2 = operando2;
    unsigned char * puntop = operador;
    float decimal = 0;
    int cantdecimales = 0;
    char c, flagneg = 0;
    char state = INIT;
    
    *punt1 = 0;
    *punt2 = 0;
    
    while ((c=getchar())!=' ')
    {
        switch (state)
        {
            case INIT:
                
                if (c=='+')
                {
                    state = NUM1;
                }
                else if (c=='-')
                {
                    flagneg = 1;
                    state = NUM1;
                }
                else if (c>='0' && c<='9')
                {
                    c -= '0';
                    *punt1 += c;
                    state = NUM2;
                }
                else
                {
                    return ERROR;
                }
                break;
                
            case NUM1:
                
                if (c>='0' && c<='9')
                {
                    c -= '0';
                    if (flagneg)
                    {
                        *punt1 -= c;
                    }
                    else
                    {
                        *punt1 += c;
                    }
                    state = NUM2;
                }
                else
                {
                    return ERROR;
                }
                break;
                
            case NUM2:
                
                if (c=='.')
                {
                    state = NUMDECIMAL;
                }
                else if (c>='0' && c<='9')
                {
                    *punt1 *= 10;
                    c -= '0';
                    state = NUM2;
                    
                    if (flagneg)
                    {
                        *punt1 -= c;
                    }
                    else
                    {
                        *punt1 += c;
                    }
                }
                else
                {
                    return ERROR;
                }
                break;
                
            case NUMDECIMAL:
                
                if (c>='0' && c<='9')
                {
                    c -= '0';
                    decimal *= 10;
                    decimal += c;
                    cantdecimales += 1;
                    
                }
                else
                {
                    return ERROR;
                }
                break;
                
        }
    }
    
    for ( ; cantdecimales != 0; cantdecimales--)                                //Si tengo numeros decimales, me dirijo a sumarselos al operando 1.
    {
        decimal /= 10;                                                          //Divido por 10 la variable decimal, tantas veces como decimales fueron ingresados.
    }
    
    if (flagneg)                                                                //Luego, en decimal tendremos el valor menor a 1 que debo agrega al operando.
    {
        *punt1 -= decimal;                                                      //Si el operando era negativo, debo restarle los numeros decimales a este.
    }
    else
    {
        *punt1 += decimal;                                                      //De no ser asi, el operando era positivo, por lo que se los debo sumar.
    }
    
    int i;
    
    for (i=0; c != operators[i]; i++)                                           //Reviso si la operacion esta dentro de las operaciones realizables.
    {
        if (i > MAX_OPERATORS)                                                  //Si ya pase por todas las operaciones y no estaba la ingresada
        {
            return ERROR;                                                       //Tiro error, ya que no puedo realizar esa operacion (o no es valida).
        }
    }
    
    *puntop = c;                                                                //Si la operacion es valida, la guardo en el operador para luego realizarla.
    
    if (c=getchar() != ' ')                                                     //Si luego de la operacion, no se ingreso un espacio
    {
        return ERROR;                                                           //Se debe indicar error, ya que se ingreso algo invalido (Por ejemplo, "*+", o "+-", etc).
    }
    
    flagneg = 0;                                                                //Como me preparo a analizar el proximo operando, debo reiniciar el flag de negatividad
    decimal = 0;                                                                //Tambien debo reiniciar el numero decimal que debo agregar
    cantdecimales = 0;                                                          //Y la cantidad de decimales que posee el numero.
    state = INIT;                                                               //Y por ultimo reiniciar el indicador de estado actual.
    
    while ((c=getchar())!='\n')
    {
        switch (state)
        {
            case INIT:
                
                if (c=='+')
                {
                    state = NUM1;
                }
                else if (c=='-')
                {
                    flagneg = 1;
                    state = NUM1;
                }
                else if (c>='0' && c<='9')
                {
                    c -= '0';
                    *punt2 += c;
                    state = NUM2;
                }
                else
                {
                    return ERROR;
                }
                break;
                
            case NUM1:
                
                if (c>='0' && c<='9')
                {
                    c -= '0';
                    if (flagneg)
                    {
                        *punt2 -= c;
                    }
                    else
                    {
                        *punt2 += c;
                    }
                    state = NUM2;
                }
                else
                {
                    return ERROR;
                }
                break;
                
            case NUM2:
                
                if (c=='.')
                {
                    state = NUMDECIMAL;
                }
                else if (c>='0' && c<='9')
                {
                    *punt2 *= 10;
                    c -= '0';
                    state = NUM2;
                    
                    if (flagneg)
                    {
                        *punt2 -= c;
                    }
                    else
                    {
                        *punt2 += c;
                    }
                }
                else
                {
                    return ERROR;
                }
                break;
                
            case NUMDECIMAL:
                
                if (c>='0' && c<='9')
                {
                    c -= '0';
                    decimal *= 10;
                    decimal += c;
                    cantdecimales += 1;
                    
                }
                else
                {
                    return ERROR;
                }
                break;
                
        }
    }
    
    for ( ; cantdecimales != 0; cantdecimales--)                                //Si tengo numeros decimales, me dirijo a sumarselos al operando 1.
    {
        decimal /= 10;                                                          //Divido por 10 la variable decimal, tantas veces como decimales fueron ingresados.
    }
    
    if (flagneg)                                                                //Luego, en decimal tendremos el valor menor a 1 que debo agrega al operando.
    {
        *punt2 -= decimal;                                                      //Si el operando era negativo, debo restarle los numeros decimales a este.
    }
    else
    {
        *punt2 += decimal;                                                      //De no ser asi, el operando era positivo, por lo que se los debo sumar.
    }
    return NOERROR;
}