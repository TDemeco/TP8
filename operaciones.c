#include <stdio.h>

#define NAN (0.0/0.0)

float suma (float a, float b)
{
    return a+b;                                                                 //Devuelve el resultado de la suma.
}

float resta (float a, float b)
{
    return a-b;                                                                 //Devuelve el resultado de la resa.
}

float prod (float a, float b)
{
    return a*b;
}

float divi (float a, float b)
{
    if (b == 0)                                                                //Si el divisor es 0, devuelve un NaN.
    {
        return NAN;
    }
    
    else
    {
       return a/b;                                                              //Si no lo es, devuelve el resultado de la division.
    }
    
}

float expo (float a, float b)                                                   //El exponente sera tomado como un numero natural
{
    if ((int) b > 0)                                                            //Si el exponente es mayor a 1, devuelve el resultado de la exponenciacion.
    {
        float c  = a;
        
        while ((int) b > 1)                                                     //Si el exponente es mayora 1
        {
            a *= c;                                                             //Lo multiplica por si mismo N veces.
            --b;
        }
        
        return a;                                                               //Si el exponente es 1, devuelve el mismo numero.
    }
    
    else if ((int) b < 0)                                                       //Si el exponente es menor a 0
    {
        float c = a;
        
        while ((int) b < 1)                                                     //Lo divide por si mismo N+1 veces
        {
            a /= c;
            
            ++b;
            
        }
        
        return a;
    }
    
    else if (a != 0)                                                            //Si el exponente es 0 y la base es diferente de 0, devuelve 1;
    {
        return 1;
    }
    
    else                                                                        //Si el exponente es 0 y la base tambien, devueleve un NaN.
    {
        return NAN;
    }
}