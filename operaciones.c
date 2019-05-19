float suma (float a, float b){
    return a+b;
}

float resta (float a, float b){
    return a-b;
}

float producto (float a, float b){
    return a*b;
}

float division (float a, float b){
    return a/b;
}

float exponenciacion (float a, float b){
    if (b>0){
        while (b>1){
            a*=a;
            --b;
        }
        return a;
    }
    else if (b=0);
    return 1;
}