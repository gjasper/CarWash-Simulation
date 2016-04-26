#include <iostream>
using namespace std;

#include "lavacar.h"

int main()
{

    Simulacao sim;

    sim.settempoTotal();
    sim.setTECAleatorio();


	cout << "\n\ntecAleatorio "<<sim.getTECAleatorio();
	getch();


    sim.setTSLavaAleatorio();
    sim.setTSEnceraAleatorio();


    sim.simula();
	
	cout << "Result\n\n";
	mediaTamanhoFila();
	taxaMediaOcupacaoServidor();
	tempoMedioFila();
	tempoMedioSistema();
	contadorEntidades();

    /*
    char resp;

    while(1>0){

        do{ resp = getch(); }while (resp < '1' || resp > '6');
        system("cls");
        switch (resp){
            case '1': sim.inicializa();break;
            case '6': return 1;
        }
    }
    */
}
