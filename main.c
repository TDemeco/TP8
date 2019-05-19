#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "stubs.h"

unsigned char operators[MAX_OPERATORS];                                         //Arreglo de operadores
float (* actions [MAX_OPERATORS] ) (float, float);                              //Arreglo con las direcciones de las funciones de cada operando

int main(void) 
{
    int error_code;                                                             //Variable utilizada para validar entrada de datos
    float operando1, operando2;                                                 //Variables usadas para almacenar los operandos
    char operador;                                                              //Variables usadas para almacenar el operador
                                                                                /*Agrega a los 2 arreglos las operaciones; por un lado guarda el simbolo de la 
                                                                                operacion y por otro guarda la direccion de la que se encuentra dicha funcion.*/
    add_operation ('+', suma);                                                  
    add_operation ('-', resta);
    add_operation ('*', prod);
    add_operation ('/', divi);
    add_operation ('^', expo);
   
    error_code=get_input(&operando1,&operando2,&operador);                      //Almacena en su debido lugar los datos que ingrese el usuario y guarda el "codigo de error"
    
    if (check_errors(error_code)!= 0)
    {                                                                           //Verifica la salida de get input,verificando si hubo o no errores.
       return 1;
    }                                                   
    
    
    printf("\n= %f\n", calc_res(operando1,operando2,operador));                 //Imprime en pantalla el resultado de la operacion a realizar.
    return 0;
}

int add_operation(unsigned char o, float (*a) (float, float))
{   
    static int numops = 0;                                                      //Define una variable para el numero de operaciones en los arreglos.

    if ((a != NULL) && numops < MAX_OPERATORS)                                  //Si no llego al maximo, y la direccion es correcta, continua.
    {
        operators [numops] = o;                                                 //Guarda el simbolo en el arreglo.

	actions [numops] = a;                                                   //Guarda la direccion de la funcion en el arreglo.
	
	numops++;                                                               //Aumenta el numero de operaciones.
        
        return NOERROR;                                                              //Idica que la funcion se realizao correctamente
    }
    
    else 
    {
        return 2;                                                               //Indica que la funcion no pudo ser realizada
    }
}


int check_errors(int error_code)
{
    switch (error_code)
    {
        case 0: 
            return 0; break;
        case 1:
            printf("Error, dato invalido");
            return 1; break;     
    }
}
