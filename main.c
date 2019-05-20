#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "operaciones.h"
#include "get_input.h"

static int add_operation(unsigned char o, double (*a) (double, double));           //Prototipos de funciones a utilizar en el main
static int check_errors(int);                                                   //Son consideradas static porque solo son usadas dentro de este archivo, y no deben ser publicas.

unsigned char operators[MAX_OPERATORS];                                         //Arreglo de operadores
double (* actions [MAX_OPERATORS] ) (double, double);                              //Arreglo con las direcciones de las funciones de cada operando

int main(void) 
{
    int error_code = 0;                                                             //Variable utilizada para validar entrada de datos
    double operando1, operando2;                                                 //Variables usadas para almacenar los operandos
    unsigned char operador;                                                     //Variables usadas para almacenar el operador
                                                                                /*Agrega a los 2 arreglos las operaciones; por un lado guarda el simbolo de la 
                                                                                operacion y por otro guarda la direccion de la que se encuentra dicha funcion.*/
    error_code += add_operation ('+', suma);
    error_code += add_operation ('-', resta);
    error_code += add_operation ('*', prod);
    error_code += add_operation ('/', divi);
    error_code += add_operation ('^', expo);
    
    if (check_errors(error_code)!= NOERROR)
    {                                                                           //Verifica la salida de get input,verificando si hubo o no errores.
       return ERROR;
    }                                                   
    
   
    error_code = get_input(&operando1,&operando2,&operador);                    //Almacena en su debido lugar los datos que ingrese el usuario y guarda el "codigo de error"
    
    if (check_errors(error_code)!= NOERROR)
    {                                                                           //Verifica la salida de get input,verificando si hubo o no errores.
       return ERROR;
    }                                                   
    
    printf("\n= %.10f\n", calc_res(operando1,operando2,operador));              //Imprime en pantalla el resultado de la operacion a realizar.
    return NOERROR;
}

static int add_operation(unsigned char o, double (*a) (double, double))
{   
    static int numops = 0;                                                      //Define una variable para el numero de operaciones en los arreglos.

    if ((a != NULL) && numops < MAX_OPERATORS)                                  //Si no llego al maximo, y la direccion es correcta, continua.
    {
        operators [numops] = o;                                                 //Guarda el simbolo en el arreglo.

	actions [numops] = a;                                                   //Guarda la direccion de la funcion en el arreglo.
	
	numops++;                                                               //Aumenta el numero de operaciones.
        
        return NOERROR;                                                         //Idica que la funcion se realizao correctamente
    }
    
    else 
    {
        return 2;                                                               //Indica que la funcion no pudo ser realizada
    }
}


static int check_errors (int error_code)                                        //La funcion verifica si hubo error en la entrada de datos.
{                                                                               //De ser asi, notifica tanto al usuario como al programa.
    switch (error_code)
    {
        case NOERROR: 
            return NOERROR;
        case ERROR:
            printf("Error, dato invalido");
            return ERROR;
        default:
            printf("Error al añadir la operacion, revise las operaciones agregadas.");
            return ERROR;
    }
}


