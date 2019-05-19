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

float div (float a, float b)
{
    if ((b == 0)                                                                //Si el divisor es 0, devuelve un NaN.
    {
        return (0/0);
    }
    
    else
    {
       return a/b;                                                              //Si no lo es, devuelve el resultado de la division.
    }
    
}

float exp (float a, float b)                                                    //El exponente sera tomado como un numero natural
{
    if (b > 0)                                                                  //Si el exponente es mayor a 1, devuelve el resultado de la exponenciacion.
    {
        while (b > 1)
        {
            a *= a;
            --b;
        }
        return a;                                                               //Si el exponente es 1, devuelve el mismo numero.
    }
    
    else if (a != 0)                                                            //Si el exponente es 0 y la base es diferente de 0, devuelve 1;
    {
        return 1;
    }
    
    else                                                                        //Si el exponente es 0 y la base tambien, devueleve un NaN.
    {
        return (0/0);
    }
}