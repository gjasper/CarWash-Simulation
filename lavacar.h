#ifndef LAVACAR_H_INCLUDED
#define LAVACAR_H_INCLUDED

#include <iomanip>

#include <queue>
#include <list>
#include <conio.h>
#include <windows.h>

#include "probability_functions.h"


class Evento{
private:
    long unsigned int tempo;
	char tipo;
	bool foiProcessado;

public:
     void setTempo(long int);
     long unsigned int getTempo();
	 void setTipo(char);
     char getTipo();
     void setFoiProcessado(bool);
     bool getFoiProcessado();
};

void Evento :: setFoiProcessado(bool vlr){
	foiProcessado = vlr;
}

bool Evento :: getFoiProcessado(){
	return foiProcessado;
}

void Evento :: setTempo(long int vlr){
	tempo = vlr;
}

long unsigned int Evento :: getTempo(){
	return tempo;
}

void Evento :: setTipo(char vlr){
	tipo = vlr;
}

char Evento :: getTipo(){
	return tipo;
}

class Simulacao{
private:
    long unsigned int relogio;
    long unsigned int tempoTotal;

	bool estadoFilaLava;
	bool estadoFilaEncera;

	long int mediaTEC;
	long int mediaTSLava;
	long int mediaTSEncera;

	bool lavaOcupado;
	bool enceraOcupado;

	long int filaLavaOcupada;
	long int filaEnceraOcupada;

	std::list<Evento> listaEventos;

	Evento eventoAtual;


	bool tecAleatorio;
	bool tsLavaAleatorio;
	bool tsEnceraAleatorio;

public:
    void settempoTotal();
    long unsigned int gettempoTotal();

	void setmediaTEC();
	void setmediaTSLava();
	void setmediaTSEncera();
	void avancaTempo();
    void exibeListas();
	void inicializa();
	void inicializaEventos();
	long int getmediaTEC();
	long int getmediaTSLava();
	long int getmediaTSEncera();

    bool getTECAleatorio();
    bool getTSLavaAleatorio ();
    bool getTSEnceraAleatorio ();
    void setTECAleatorio();
    void setTSLavaAleatorio();
	void setTSEnceraAleatorio();

	void trataEventoInicio();
	void trataEventoChegada();
	void trataEventoSaidaLava();
	void trataEventoSaidaEncera();
	void trataEventoFim(){};


	void simula();
};

void Simulacao :: inicializa(){

	relogio = 0;

    setmediaTEC();
    setmediaTSLava();
    setmediaTSEncera();

	inicializaEventos();

	lavaOcupado = false;
	enceraOcupado = false;

	filaLavaOcupada = 0;
	filaEnceraOcupada = 0;

}

void Simulacao :: inicializaEventos(){

	Evento eventoAux;
	eventoAux.setTipo('I');
	eventoAux.setTempo(0);
	eventoAux.setFoiProcessado(false);

	listaEventos.push_front(eventoAux);


}

void Simulacao :: avancaTempo(){

	eventoAtual.setTempo(gettempoTotal()+1);
	system("CLS");
    cout << "\n\n\nEventos na lista:";

    for (std::list<Evento>::iterator it=listaEventos.begin(); it != listaEventos.end(); ++it){
        if(((*it).getTempo() <= eventoAtual.getTempo())&& !(*it).getFoiProcessado()){
			eventoAtual = (*it);
		}

        cout << "\nTipo: " <<(*it).getTipo()<< "\tTempo: " <<(*it).getTempo()<< "\tFoi processado: " <<(*it).getFoiProcessado();
    }

	for (std::list<Evento>::iterator it=listaEventos.begin(); it != listaEventos.end(); ++it){
		if((eventoAtual.getTempo() == (*it).getTempo())&&(eventoAtual.getTipo() == (*it).getTipo())){
			(*it).setFoiProcessado(true);
			cout << "\n\nEvento " <<(*it).getTipo()<<","<<(*it).getTempo()<<" foi processado";
		}
    }

	relogio = eventoAtual.getTempo();
    cout 	<< "\n"
			<< "\nES(Lava)	: " <<lavaOcupado
			<< "\nES(Encera)	: " <<enceraOcupado
			<< "\nEF(Lava)	: " <<filaLavaOcupada
			<< "\nEF(Encera)	: " <<filaEnceraOcupada;
	getch();
}

void Simulacao :: simula(){

	inicializa();
	avancaTempo();


	while(eventoAtual.getTipo()!='F'){
		switch (eventoAtual.getTipo()) {
			case 'I' : trataEventoInicio();break;
			case 'C' : trataEventoChegada();break;
			case 'L' : trataEventoSaidaLava();break;
			case 'E' : trataEventoSaidaEncera();break;
			case 'F' : trataEventoFim();break;
		}
		avancaTempo();
	}
}

void Simulacao :: trataEventoInicio(){

	Evento eventoAux;

	eventoAux.setTipo('F');
	eventoAux.setTempo(gettempoTotal());
	eventoAux.setFoiProcessado(false);

	listaEventos.push_front(eventoAux);


	eventoAux.setTipo('C');
	if(!tecAleatorio){
		eventoAux.setTempo(relogio+getmediaTEC());
	}else{
		eventoAux.setTempo(relogio+distribuicaoNormal(getmediaTEC()));
 	    cout << "\n\nEvento C tem tempo aleatório: "<< eventoAux.getTempo()<<"\n\n";
	}
	eventoAux.setFoiProcessado(false);

	listaEventos.push_front(eventoAux);

}

void Simulacao :: trataEventoChegada(){

	Evento eventoAux;

	if(!lavaOcupado){

		lavaOcupado = true;

		eventoAux.setTipo('L');
		if(!tecAleatorio){
			eventoAux.setTempo(relogio+getmediaTSLava());
		}else{
			//
		}
		eventoAux.setFoiProcessado(false);

		listaEventos.push_front(eventoAux);

	}else{
		filaLavaOcupada++;
	}


	eventoAux.setTipo('C');
	if(!tecAleatorio){
		eventoAux.setTempo(relogio+getmediaTEC());
	}else{
		eventoAux.setTempo(relogio+distribuicaoNormal(getmediaTEC()));
 	    cout << "\n\nEvento C tem tempo aleatório: "<< eventoAux.getTempo()<<"\n\n";
	}
	eventoAux.setFoiProcessado(false);


	listaEventos.push_front(eventoAux);

}

void Simulacao :: trataEventoSaidaLava(){

	Evento eventoAux;

	if(filaLavaOcupada){

		filaLavaOcupada--;

		eventoAux.setTipo('L');
		if(!tecAleatorio){
			eventoAux.setTempo(relogio+getmediaTSLava());
		}else{
			//funcao de numero aleatorio
		}
        eventoAux.setFoiProcessado(false);

		listaEventos.push_front(eventoAux);

	}else{
		lavaOcupado = 0;
	}

	long unsigned int numSorteado = 59;

	if(numSorteado<60){
		if(!enceraOcupado){

			enceraOcupado = true;

			eventoAux.setTipo('E');
			if(!tecAleatorio){
				eventoAux.setTempo(relogio+getmediaTSEncera());
			}else{
				//funcao de numero aleatorio
			}
			eventoAux.setFoiProcessado(false);

			listaEventos.push_front(eventoAux);

		}else{
			filaEnceraOcupada++;
		}
	}

}

void Simulacao :: trataEventoSaidaEncera(){

	Evento eventoAux;

	if(filaEnceraOcupada){

		filaEnceraOcupada--;

		eventoAux.setTipo('E');
		if(!tecAleatorio){
			eventoAux.setTempo(relogio+getmediaTSEncera());
		}else{
			//funcao de numero aleatorio
		}
        eventoAux.setFoiProcessado(false);

		listaEventos.push_front(eventoAux);

	}else{
		enceraOcupado = 0;
	}


}

void Simulacao :: setTECAleatorio(){

    cout << "\n\n\tTEC (D/A):  ";
	char resp = toupper(getch());
	if (resp == 'D')
        tecAleatorio = false;
	else{
 	    cout << "\n\nEvento C tem tempo aleatório\n\n";
		tecAleatorio = true;
	}

}

void Simulacao :: setTSLavaAleatorio(){
    cout << "\n\n\tTS Lavar (D/A):  ";
	char resp = toupper(getch());
	if (resp == 'D')
        tsLavaAleatorio = false;
	else
        tsLavaAleatorio = true;
}

void Simulacao :: setTSEnceraAleatorio(){
    cout << "\n\n\tTS Encerar (D/A):  ";
	char resp = toupper(getch());
	if (resp == 'D')
        tsEnceraAleatorio = false;
	else
        tsEnceraAleatorio = true;
}

void Simulacao :: settempoTotal(){
	cout << "\n\n\n\tDefina o tempo de simulacao: ";
	cin >> tempoTotal;
}

long unsigned int Simulacao :: gettempoTotal(){
    return tempoTotal;
}

void Simulacao :: setmediaTEC(){

	cout << "\n\n\n\tDefina a media TEC: ";
	cin >> mediaTEC;

}

void Simulacao :: setmediaTSLava(){

	cout << "\n\n\n\tDefina a media TS Lava: ";
	cin >> mediaTSLava;

}

void Simulacao :: setmediaTSEncera(){
    cout << "\n\n\n\tDefina a media TS Encera: ";
	cin >> mediaTSEncera;
}

long int Simulacao :: getmediaTEC(){
    return mediaTEC;
}

long int Simulacao :: getmediaTSLava(){
    return mediaTSLava;
}

long int Simulacao :: getmediaTSEncera(){
    return mediaTSEncera;
}
bool Simulacao :: getTECAleatorio(){
    return tecAleatorio;
}

bool Simulacao :: getTSLavaAleatorio (){
    return tsLavaAleatorio;
}

bool Simulacao :: getTSEnceraAleatorio (){
    return tsEnceraAleatorio;
}


#endif
