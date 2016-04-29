#include <iostream>
using namespace std;

#include "lavacar.h"

int main()
{
    system("MODE con cols=130 lines=300");


    Simulacao sim;

    char resp;

    while(1>0){
        cout << "\n\n\t\t1. Simular"
             << "\n\n\t\t2. Sair";
        do{ resp = getch(); }while (resp < '1' || resp > '2');
        system("cls");
        switch (resp){
            case '1': sim.simula();break;
            case '2': return 1;
        }
    }

}
