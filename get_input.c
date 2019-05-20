#include <stdio.h>
#include "get_input.h"
#include "main.h"

enum {INIT, NUM1, NUM2, NUMDECIMAL};                                            //Ennumero los estados a utilizar en la funcion.

int get_input (double * operando1, double * operando2, unsigned char * operador)  //get_input es una funcion que recibe por teclado dos operandos y un operador, y los escribe en sus variables correspondientes.
{
    extern unsigned char operators [];                                          //Le aclaro a la funcion que el arreglo de operadores a utilizar esta en otro archivo
    double * punt1 = operando1;                                                  //Defino un puntero al primer operando
    double * punt2 = operando2;                                                  //Defino un puntero al segundo operando
    unsigned char * puntop = operador;                                          //Defino un puntero al operador, o funcion a realizar
    double decimal = 0;                                                          //Inicio una variable que contendra, si hubiese, el numero decimal a sumar
    int cantdecimales = 0;                                                      //Ademas, defino otra variable que tendra la cantidad de decimales que contiene el numero anterior
    char c, flagneg = 0;                                                        //Inicio una variable c que utilizare para recuperar los caracteres de getchar, y un flag para saber si el numero con el que trabajo es negativo.
    char state = INIT;                                                          //Por ultimo, inicializo la variable de estado de la FSM en su estado inicial.
    
    *punt1 = 0;                                                                 //Limpio el contenido del operando 1, para comenzar a trabajar.
    *punt2 = 0;                                                                 //Idem con el operando 2.
    
    while ((c=getchar())!=' ')                                                  //Como los operandos y el operador estan separados por espacios, todo lo que reciba antes del primer espacio pertenecera al operando 1.
    {
        switch (state)                                                          //Reviso en que estado esta mi FSM
        {
            case INIT:                                                          //Si es el estado inicial, puede recibir tanto un numero como el signo del operando.
                
                if (c=='+')                                                     //Si recibe el signo positivo
                {
                    state = NUM1;                                               //pasa al siguiente estado, para recibir el primer numero
                }
                else if (c=='-')                                                //Si recibe el signo negativo
                {
                    flagneg = 1;                                                //Guarda en memoria que el numero con el que esta operando es negativo
                    state = NUM1;                                               //Y pasa al estado de recibir el primer numero
                }
                else if (c>='0' && c<='9')                                      //Si lo que recibe en el estado inicial es un numero
                {
                    c -= '0';                                                   //Lo transforma de ASCII a numero decimal
                    *punt1 += c;                                                //Y se lo suma al operando
                    state = NUM2;                                               //Por ultimo, se prepara para recibir el siguiente numero
                }
                else                                                            //Si no se recibio ni un signo ni un numero en el estado inicial, se recibio un parametro invalido.
                {
                    return ERROR;                                               //Por lo tanto, devuelve error.
                }
                break;
                
            case NUM1:                                                          //Si el estado actual es el de recibir el primer numero, solo puede recibir numeros
                
                if (c>='0' && c<='9')                                           //Si lo que recibio fue un numero
                {
                    c -= '0';                                                   //Lo pasa de su formato ASCII a un formato decimal
                    if (flagneg)                                                //Y revisa si el flag de numero negativo esta encendido
                    {
                        *punt1 -= c;                                            //Si lo esta, el numero con el que opera es negativo, por lo tanto debera restarselo al operando 1.
                    }
                    else                                                        //Si el flag esta apagado, el numero con el que esta operando es positivo
                    {
                        *punt1 += c;                                            //Por lo tanto, debera sumarselo al operando 1.
                    }
                    state = NUM2;                                               //Luego, como ya recibio el primer numero, pasa al estado de esperar el siguiente numero
                }
                else                                                            //Si luego de recibir un signo, no recibe un numero, entonces recibio un parametro invalido.
                {
                    return ERROR;                                               //Por ende, devuelve un error.
                }
                break;
                
            case NUM2:                                                          //Si lo que espera recibir es el siguiente numero
                
                if (c=='.')                                                     //Y recibe el caracter punto, quiere decir que lo que sera ingresado a continuacion son los decimales del operando.
                {
                    state = NUMDECIMAL;                                         //Por lo tanto, le indica a la FSM que debe pasar al estado de numeros decimales
                }
                else if (c>='0' && c<='9')                                      //Si lo que recibe es un numero
                {
                    *punt1 *= 10;                                               //Entonces mueve el numero del operando un lugar hacia la izquieda para hacer lugar para el numero ingresado.
                    c -= '0';                                                   //Transforma el numero recibido de formato ASCII a formato decimal
                    state = NUM2;                                               //Indica que debera seguir en el estado de recibir numeros
                    
                    if (flagneg)                                                //Revisa si el operando es negativo o positivo
                    {
                        *punt1 -= c;                                            //Si es negativo, debe restar el numero recibido al operando
                    }
                    else                                                        //De lo contrario, debe ser positivo
                    {
                        *punt1 += c;                                            //Por lo que debe sumar el numero recibido al operando.
                    }
                }
                else                                                            //Si esta esperando un numero y no recibe un indicador de decimal ('.') o un numero, entonces recibio un parametro invalido.
                {
                    return ERROR;                                               //Por lo tanto, debe devolver un error
                }
                break;
                
            case NUMDECIMAL:                                                    //Si se esta operando con la parte decimal del operando, los unicos parametros validos son los numeros
                
                if (c>='0' && c<='9')                                           //Si recibe un numero
                {
                    c -= '0';                                                   //Lo pasa de formato ASCII a formato decimal
                    decimal *= 10;                                              //Mueve el numero decimal obtenido hasta ahora un lugar hacia la izquierda (Para mantener el orden de los digitos)
                    decimal += c;                                               //Y le inserta en este nuevo lugar el numero recibido del teclado
                    cantdecimales += 1;                                         //Ademas, aumenta la variable que indica la cantidad de decimales que tiene el operando.
                    
                }
                else                                                            //Si no recibe un numero, debe haber recibido un parametro invalido
                {
                    return ERROR;                                               //Por lo tanto, devuelve un error.
                }
                break;
                
        }
    }
    
    if (state == INIT && c == ' ')                                              //Si lo primero que agarra es un espacio manda error.
    {
        return ERROR;                                                           
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
    
    c=getchar();                                                                //Obtengo en la variable c el operador a utilizar.
    
    for (int i=0; c != operators[i]; i++)                                       //Reviso si la operacion esta dentro de las operaciones realizables.
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
    
    while ((c=getchar())!='\n')                                                 //Como los operandos y el operador estan separados por espacios, todo lo que reciba antes del primer espacio pertenecera al operando 2.
    {
        switch (state)                                                          //Reviso en que estado esta mi FSM
        {
            case INIT:                                                          //Si es el estado inicial, puede recibir tanto un numero como el signo del operando.
                
                if (c=='+')                                                     //Si recibe el signo positivo
                {
                    state = NUM1;                                               //pasa al siguiente estado, para recibir el primer numero
                }
                else if (c=='-')                                                //Si recibe el signo negativo
                {
                    flagneg = 1;                                                //Guarda en memoria que el numero con el que esta operando es negativo
                    state = NUM1;                                               //Y pasa al estado de recibir el primer numero
                }
                else if (c>='0' && c<='9')                                      //Si lo que recibe en el estado inicial es un numero
                {
                    c -= '0';                                                   //Lo transforma de ASCII a numero decimal
                    *punt2 += c;                                                //Y se lo suma al operando
                    state = NUM2;                                               //Por ultimo, se prepara para recibir el siguiente numero
                }
                else                                                            //Si no se recibio ni un signo ni un numero en el estado inicial, se recibio un parametro invalido.
                {
                    return ERROR;                                               //Por lo tanto, devuelve error.
                }
                break;
                
            case NUM1:                                                          //Si el estado actual es el de recibir el primer numero, solo puede recibir numeros
                
                if (c>='0' && c<='9')                                           //Si lo que recibio fue un numero
                {
                    c -= '0';                                                   //Lo pasa de su formato ASCII a un formato decimal
                    if (flagneg)                                                //Y revisa si el flag de numero negativo esta encendido
                    {
                        *punt2 -= c;                                            //Si lo esta, el numero con el que opera es negativo, por lo tanto debera restarselo al operando 2.
                    }
                    else                                                        //Si el flag esta apagado, el numero con el que esta operando es positivo
                    {
                        *punt2 += c;                                            //Por lo tanto, debera sumarselo al operando 2.
                    }
                    state = NUM2;                                               //Luego, como ya recibio el primer numero, pasa al estado de esperar el siguiente numero
                }
                else                                                            //Si luego de recibir un signo, no recibe un numero, entonces recibio un parametro invalido.
                {
                    return ERROR;                                               //Por ende, devuelve un error.
                }
                break;
                
            case NUM2:                                                          //Si lo que espera recibir es el siguiente numero
                
                if (c=='.')                                                     //Y recibe el caracter punto, quiere decir que lo que sera ingresado a continuacion son los decimales del operando.
                {
                    state = NUMDECIMAL;                                         //Por lo tanto, le indica a la FSM que debe pasar al estado de numeros decimales
                }
                else if (c>='0' && c<='9')                                      //Si lo que recibe es un numero
                {
                    *punt2 *= 10;                                               //Entonces mueve el numero del operando un lugar hacia la izquieda para hacer lugar para el numero ingresado.
                    c -= '0';                                                   //Transforma el numero recibido de formato ASCII a formato decimal
                    state = NUM2;                                               //Indica que debera seguir en el estado de recibir numeros
                    
                    if (flagneg)                                                //Revisa si el operando es negativo o positivo
                    {
                        *punt2 -= c;                                            //Si es negativo, debe restar el numero recibido al operando
                    }
                    else                                                        //De lo contrario, debe ser positivo
                    {
                        *punt2 += c;                                            //Por lo que debe sumar el numero recibido al operando.
                    }
                }
                else                                                            //Si esta esperando un numero y no recibe un indicador de decimal ('.') o un numero, entonces recibio un parametro invalido.
                {
                    return ERROR;                                               //Por lo tanto, debe devolver un error
                }
                break;
                
            case NUMDECIMAL:                                                    //Si se esta operando con la parte decimal del operando, los unicos parametros validos son los numeros
                
                if (c>='0' && c<='9')                                           //Si recibe un numero
                {
                    c -= '0';                                                   //Lo pasa de formato ASCII a formato decimal
                    decimal *= 10;                                              //Mueve el numero decimal obtenido hasta ahora un lugar hacia la izquierda (Para mantener el orden de los digitos)
                    decimal += c;                                               //Y le inserta en este nuevo lugar el numero recibido del teclado
                    cantdecimales += 1;                                         //Ademas, aumenta la variable que indica la cantidad de decimales que tiene el operando.
                    
                }
                else                                                            //Si no recibe un numero, debe haber recibido un parametro invalido
                {
                    return ERROR;                                               //Por lo tanto, devuelve un error.
                }
                break;
                
        }
    }
    
    for ( ; cantdecimales != 0; cantdecimales--)                                //Si tengo numeros decimales, me dirijo a sumarselos al operando 2.
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
    return NOERROR;                                                             //Si se llego a esta parte del programa, todo salio ok. No devuelvo error.
}