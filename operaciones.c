#include <stdio.h>
#include "operaciones.h"

#define NAN (0.0/0.0)

double calc_res(double operando1, double operando2, unsigned char operador)
{
    if(operador == '+')                                                         //Calcula la suma.
    {
        return suma(operando1,operando2);
    }
    
    else if(operador == '-')
    {
        return resta(operando1,operando2);                                      //Calcula la resta.
    }
    
    else if(operador == '*')                                                    //Calcula multiplicación.
    {
        return prod(operando1,operando2);
    }
    
    else if(operador == '/')                                                    //Calcula división.
    {
        return divi(operando1,operando2);
    }
    
    else                                                                        //Calcula exponente.
    {
        return expo(operando1,operando2);
    }
    
}


double suma (double a, double b)                                                //Funcion que realiza la suma de dos operandos de tipo double.
{
    return a+b;                                                                 //Devuelve el resultado de la suma.
}

double resta (double a, double b)                                               //Funcion que realiza la resta de dos operandos de tipo double, en el orden en el que son pasados.
{
    return a-b;                                                                 //Devuelve el resultado de la resa.
}

double prod (double a, double b)                                                //Funcion que realiza el producto de dos operandos de tipo double.
{
    return a*b;                                                                 //Devuelve el resultado de la multiplicacion.
}

double divi (double a, double b)                                                //Funcion que realiza la division de dos operandos de tipo double, siendo el primero el dividendo y el segundo el divisor.
{
    if (b == 0)                                                                 //Si el divisor es 0,
    {
        return NAN;                                                             //La funcion dara error de punto flotante.
    }
    
    else
    {
       return a/b;                                                              //Si no lo es, devuelve el resultado de la division.
    }
    
}

double expo (double a, double x)                                                //Funcion que recibe dos operandos y eleva el primero a la potencia del segundo.
{
    int b;                                                                      //Primero, tomara el segundo operando como un numero entero. (Por lo tanto, si recibe un numero decimal lo truncará)
    b = (int)x;                                                                 //Realiza el truncado y lo guarda en una variable de tipo int para operar con ella.
    double temp;                                                                //Defino una variable temporal de tipo double donde ire guardando los resultados parciales.
    
    if (b > 0)                                                                  //Si el exponente es positivo.
    {
        a = a;                                                                  //Trabajare con el operando recibido
        b = b;                                                                  //Y con el exponente recibido.
    }
    else if (b < 0)                                                             //Si el exponente es negativo
    {
        a = (1/a);                                                              //Trabajare con la inversa del operando.
        b = -b;                                                                 //Y convertire el exponente a positivo para realizar los calculos.
    }
    else {                                                                      //Si el exponente es 0
        return 1;                                                               //Devuelvo el numero 1 (Se considera 0^0 como 1 por convencion matematica).
    }
    
    for (temp = 1; b > 0; b--)                                                  //Realizo el calculo exponencial.
    {
            temp *= a;                                                          //Multiplico a la variable temporal por a tantas veces como el exponente lo indique.
    }
    return temp;
    
}