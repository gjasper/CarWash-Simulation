//Uniforme: S= Minimo + (Maximo - Minimo)*AleatorioEntre0e1
//Triangular: x(é saida da uniforme) -- SE (Min<= X < Moda) = 2(x-Min)/(Max-Min)*(Moda-Min) || SE (X = Moda) = 2/(Max-Min) || SE (Moda< X <= Max) = 2(Max-x)/(Max-Min)*(Moda-Min)
//Normal: S = (1/sqrt(2*pi*desviopadrão^2))*exp(-((x-media)^2)/(2*desviopadrao^2))
//Exponencial S = (1/media)*exp(-x/media)


#include <time.h>

float distribuicaoUniforme (float minimo, float maximo){
    float x = 0, saida = 0;
        x = rand()%101; //aleatorio entre 0.00 e 1.00
        saida = minimo + (maximo-minimo)*x;
    return saida;
}

float distribuicaoTriangular (float minimo, float maximo, float moda){
    float x = 0, saida = 0;
        x = rand()%101; //aleatorio entre 0.00 e 1.00
        if(minimo <= x < moda){
            saida = 2*(x-minimo)/((maximo-minimo)*(moda-minimo));
        }else if(x == moda){
            saida = 2/(maximo-minimo);
            } else if(moda < x <= maximo){
                saida = 2*(maximo - x)/((maximo-minimo)*(moda - minimo));
                }
    return saida;
}

float distribuicaoNormal (float media){
    float x = 0, saida = 0;
        x = rand()%101; //aleatorio entre 0.00 e 1.00
        //saida = (1/media)*exp(-(x/media));
    return saida;
}

float distribuicaoExponencial (float media, float desviopadrao){
    float x = 0, saida = 0;
        x = rand()%101; //aleatorio entre 0.00 e 1.00
        //saida = (1/sqrt(2*3.1415*(desviopadrao^2)))*exp(-((x-media)^2)/(2*(desviopadrao^2)));
    return saida;
}
