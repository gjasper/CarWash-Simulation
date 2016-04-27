#ifndef LAVACAR_H_INCLUDED
#define LAVACAR_H_INCLUDED

#include <iomanip>

#include <list>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#include "probability_functions.h"

class Entidade{
private:
    long unsigned int tempChegada;
	long unsigned int tempLavaInicioServico;
	long unsigned int tempLavaFinalServico;
	long unsigned int tempEnceraInicioServico;
	long unsigned int tempEnceraFinalServico;
	bool foiLavado;
	bool foiEncerado;
	bool solicitouEnceramento;
	long unsigned int id;

public:
     void settempChegada(long unsigned int vlr){tempChegada = vlr;};
     long unsigned int gettempChegada(){return tempChegada;};
	 void settempLavaInicioServico(long unsigned int vlr){tempLavaInicioServico = vlr;};
     long unsigned int gettempLavaInicioServico(){return tempLavaInicioServico;};
	 void settempLavaFinalServico(long unsigned int vlr){tempLavaFinalServico = vlr;};
     long unsigned int gettempLavaFinalServico(){return tempLavaFinalServico;};
	 void settempEnceraInicioServico(long unsigned int vlr){tempEnceraInicioServico = vlr;};
     long unsigned int gettempEnceraInicioServico(){return tempEnceraInicioServico;};
	 void settempEnceraFinalServico(long unsigned int vlr){tempEnceraFinalServico = vlr;};
     long unsigned int gettempEnceraFinalServico(){return tempEnceraFinalServico;};
	 void setfoiLavado(bool vlr){foiLavado = vlr;};
     long unsigned int getfoiLavado(){return foiLavado;};
	 void setfoiEncerado(bool vlr){foiEncerado = vlr;};
     long unsigned int getfoiEncerado(){return foiEncerado;};
	 void setsolicitouEnceramento(bool vlr){solicitouEnceramento = vlr;};
     long unsigned int getsolicitouEnceramento(){return solicitouEnceramento;};
};

class Evento{
private:
    long unsigned int tempo;
	char tipo;
	bool foiProcessado;
	long unsigned int idEntidade;

public:
     void setTempo(long int);
     long unsigned int getTempo();
	 void setTipo(char);
     char getTipo();
     void setFoiProcessado(bool);
     bool getFoiProcessado();
	 void setidEntidade(long unsigned int vlr){idEntidade = vlr;};
     long unsigned int getidEntidade(){return idEntidade;};
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
	std::list<Entidade> listaEntidades;

	Evento eventoAtual;

	long unsigned int countEntidades;

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
	void trataEventoFim();

	void defineTempoChegada();
	void defineTempoServLava(bool solicitaEnc);
	void defineTempoServEncera();

    void insereListaEventos(Evento evt);
    void insereListaEntidades(Entidade ent);

	void simula();
};

void Simulacao :: insereListaEventos(Evento evt){

    listaEventos.push_front(evt);

}

void Simulacao :: insereListaEntidades(Entidade ent){

    listaEntidades.push_front(ent);

}

void Simulacao :: inicializa(){

	srand (time(NULL));

	relogio = 0;

	countEntidades = 0;

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

	insereListaEventos(eventoAux);

}

void Simulacao :: avancaTempo(){

	eventoAtual.setTempo(gettempoTotal()+1);
	//system("CLS");
    //cout << "\n\n\nEventos na lista:";

    for (std::list<Evento>::iterator it=listaEventos.begin(); it != listaEventos.end(); ++it){
        if(((*it).getTempo() <= eventoAtual.getTempo())&& !(*it).getFoiProcessado()){
			eventoAtual = (*it);
		}

        //cout << "\nTipo: " <<(*it).getTipo()<< "\tTempo: " <<(*it).getTempo()<< "\tFoi processado: " <<(*it).getFoiProcessado();
    }

	for (std::list<Evento>::iterator it=listaEventos.begin(); it != listaEventos.end(); ++it){
		if((eventoAtual.getTempo() == (*it).getTempo())&&(eventoAtual.getTipo() == (*it).getTipo())){
			(*it).setFoiProcessado(true);
			//cout << "\n\nEvento " <<(*it).getTipo()<<","<<(*it).getTempo()<<" sera processado";
		}
    }


	relogio = eventoAtual.getTempo();
    /*cout 	<< "\n"
			<< "\nES(Lava)	: " <<lavaOcupado
			<< "\nES(Encera)	: " <<enceraOcupado
			<< "\nEF(Lava)	: " <<filaLavaOcupada
			<< "\nEF(Encera)	: " <<filaEnceraOcupada;
	getch();
	*/
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
		}
		avancaTempo();
	}
	trataEventoFim();

}

void Simulacao :: trataEventoInicio(){

	Evento eventoAux;
	Entidade entidadeAux;

	long int tempChegadaAux;

	eventoAux.setTipo('F');
	eventoAux.setTempo(gettempoTotal());
	eventoAux.setFoiProcessado(false);

	insereListaEventos(eventoAux);

	eventoAux.setTipo('C');
	if(!tecAleatorio){
		tempChegadaAux = relogio+getmediaTEC();
	}else{
		tempChegadaAux = relogio+distribuicaoNormal(getmediaTEC());
	}
	eventoAux.setTempo(tempChegadaAux);
	eventoAux.setFoiProcessado(false);
	insereListaEventos(eventoAux);
}

void Simulacao :: trataEventoChegada(){

	Evento eventoAux;
	long int tempChegadaAux, tempSaidaLavaAux;

	defineTempoChegada();

	if(!lavaOcupado){

		lavaOcupado = true;

		eventoAux.setTipo('L');
		if(!tecAleatorio){
			tempSaidaLavaAux = relogio+getmediaTSLava();
		}else{
			//
		}

		eventoAux.setTempo(tempSaidaLavaAux);
		eventoAux.setFoiProcessado(false);
		insereListaEventos(eventoAux);

	}else{
		filaLavaOcupada++;
	}


	eventoAux.setTipo('C');
	if(!tecAleatorio){
		tempChegadaAux = relogio+getmediaTEC();
	}else{
		tempChegadaAux = relogio+distribuicaoNormal(getmediaTEC());
 	    cout << "\n\nEvento C tem tempo aleatório: "<< eventoAux.getTempo()<<"\n\n";
	}


	eventoAux.setTempo(tempChegadaAux);
	eventoAux.setFoiProcessado(false);
	insereListaEventos(eventoAux);
}

void Simulacao :: defineTempoChegada(){
	Entidade entidadeAux;

	countEntidades++;
	entidadeAux.settempChegada(relogio);
	entidadeAux.settempLavaInicioServico(0);
	entidadeAux.settempLavaFinalServico(0);
	entidadeAux.settempEnceraInicioServico(0);
	entidadeAux.settempEnceraFinalServico(0);

	entidadeAux.setfoiLavado(false);
	entidadeAux.setfoiEncerado(false);
	entidadeAux.setsolicitouEnceramento(false);
	insereListaEntidades(entidadeAux);

}

void Simulacao :: trataEventoSaidaLava(){

	Evento eventoAux;
	long unsigned int numSorteado = rand() % 100;
	
	long int tempSaidaLavaAux;

	if(numSorteado<60){
		defineTempoServLava(true);
	}else{
		defineTempoServLava(false);
	}


	if(filaLavaOcupada){

		filaLavaOcupada--;

		eventoAux.setTipo('L');
		if(!tecAleatorio){
			tempSaidaLavaAux = relogio+getmediaTSLava();
		}else{
			//funcao de numero aleatorio
		}

		eventoAux.setTempo(tempSaidaLavaAux);
        eventoAux.setFoiProcessado(false);
		insereListaEventos(eventoAux);

	}else{
		lavaOcupado = 0;
	}

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
			insereListaEventos(eventoAux);

		}else{
			filaEnceraOcupada++;
		}
	}

}

void Simulacao :: defineTempoServLava(bool solicitaEnc){

	Entidade entidadeAtual, entidadeUltimoLavado;

	entidadeAtual.settempChegada(tempoTotal+1);
	entidadeUltimoLavado.settempLavaFinalServico(0);

	long int tempoAux = tempoTotal+1;

	for (std::list<Entidade>::iterator it=listaEntidades.begin(); it != listaEntidades.end(); ++it){
        if(((*it).gettempChegada() <= entidadeAtual.gettempChegada())&& !(*it).getfoiLavado()){
			entidadeAtual = (*it);
		}

		if((*it).gettempLavaFinalServico() >= entidadeUltimoLavado.gettempLavaFinalServico()){
			entidadeUltimoLavado = (*it);
		}
	}

	for (std::list<Entidade>::iterator it=listaEntidades.begin(); it != listaEntidades.end(); ++it){
		if(entidadeAtual.gettempChegada() == (*it).gettempChegada()){
			(*it).setfoiLavado(true);
			if(solicitaEnc)(*it).setsolicitouEnceramento(true);
			(*it).settempLavaFinalServico(relogio);

			if(entidadeUltimoLavado.gettempLavaFinalServico() > (*it).gettempChegada()){
				(*it).settempLavaInicioServico(entidadeUltimoLavado.gettempLavaFinalServico());
			}else{
				(*it).settempLavaInicioServico((*it).gettempChegada());
			}
		}
    }
}

void Simulacao :: trataEventoSaidaEncera(){

	Evento eventoAux;

	defineTempoServEncera();

	if(filaEnceraOcupada){

		filaEnceraOcupada--;

		eventoAux.setTipo('E');
		if(!tecAleatorio){
			eventoAux.setTempo(relogio+getmediaTSEncera());
		}else{
			//funcao de numero aleatorio
		}
        eventoAux.setFoiProcessado(false);

		insereListaEventos(eventoAux);

	}else{
		enceraOcupado = 0;
	}


}

void Simulacao :: defineTempoServEncera(){
	 
	Entidade entidadeAtual, entidadeUltimoEncerado;
	entidadeAtual.settempLavaFinalServico(tempoTotal+1);
	entidadeUltimoEncerado.settempLavaFinalServico(0);
	
	for (std::list<Entidade>::iterator it=listaEntidades.begin(); it != listaEntidades.end(); ++it){
        if(((*it).gettempLavaFinalServico() < entidadeAtual.gettempLavaFinalServico())&&(!(*it).getfoiEncerado())&&((*it).getsolicitouEnceramento())){
			entidadeAtual = (*it);
		}
		
		if((*it).gettempEnceraFinalServico() > entidadeUltimoEncerado.gettempEnceraFinalServico()){
			entidadeUltimoEncerado = (*it);
		}
    }
	
	for (std::list<Entidade>::iterator it=listaEntidades.begin(); it != listaEntidades.end(); ++it){
        if(((*it).gettempChegada() == entidadeAtual.gettempChegada()) && ((*it).gettempLavaInicioServico() == entidadeAtual.gettempLavaInicioServico())){
			(*it).setfoiEncerado(true);
			(*it).settempEnceraFinalServico(relogio);
			
			
			if(entidadeUltimoEncerado.gettempEnceraFinalServico() > (*it).gettempLavaFinalServico()){
				
				
				(*it).settempEnceraInicioServico(entidadeUltimoEncerado.gettempEnceraFinalServico());
			}else{
				(*it).settempEnceraInicioServico((*it).gettempLavaFinalServico());
			}			
		}
    }
}

void Simulacao :: trataEventoFim(){

    system("CLS");

	cout<<"\n    TChegada |"
		<<" TIniServ Lava |"
		<<" TFimServ Lava |"
		<<" TIniServ Ence |"
		<<" TFimServ Ence |"
		<<" Solicitou Enceramento |\n";


    for (std::list<Entidade>::iterator it=listaEntidades.begin(); it != listaEntidades.end(); ++it){
        cout<<"\n\t"<<(*it).gettempChegada()
            <<"\t"<<(*it).gettempLavaInicioServico()
            <<"\t"<<(*it).gettempLavaFinalServico()
            <<"\t"<<(*it).gettempEnceraInicioServico()
            <<"\t"<<(*it).gettempEnceraFinalServico()
            <<"\t"<<(*it).getsolicitouEnceramento();

    }

	getch();
}

void Simulacao :: setTECAleatorio(){

    cout << "\n\n\tTEC (D/A):  ";
	char resp = toupper(getch());
	if (resp == 'D')
        tecAleatorio = false;
	else{
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
