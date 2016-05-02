#ifndef LAVACAR_H_INCLUDED
#define LAVACAR_H_INCLUDED

//Seen by Ayslan Zoletti at 10:43Seen by Fernando (pau no cu) Gaya at 10:44


#include <iomanip>
#include <list>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>

#include "funcoes_probabilidade.h"


#define TAM 100000


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

	float tempoPause;

	bool tecAleatorio;
	bool tsLavaAleatorio;
	bool tsEnceraAleatorio;
	//1
	float accFilaLavaOcupada;
	float accFilaEnceraOcupada;
	//2
	float contLavaOcupado;
	float contEnceraOcupado;
	float contEntidadesSistema;
	float contEntidadesEncera;
	//3
	float accTempFilaLava;
	float accTempFilaEncera;
	//4
	float accTempSimulacao;
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
	//1
	void mediaTamanhoFila();
	//2
	void taxaMediaOcupacaoServidor();
	//3
	void tempoMedioFila();
	//4
	void tempoMedioSistema();
	//5
	void contadorEntidades();
	//animacao
	void animacao();
	void pause (float delay1);
	void gotoxy(int x, int y);
	void settempoPause();
};

void Simulacao :: insereListaEventos(Evento evt){

    listaEventos.push_front(evt);

}

void Simulacao :: insereListaEntidades(Entidade ent){

    listaEntidades.push_back(ent);

}

void Simulacao :: inicializa(){

	system("CLS");

	srand (time(NULL));

	listaEntidades.clear();
	listaEventos.clear();

	relogio = 0;

	countEntidades = 0;

	settempoTotal();
    setTECAleatorio();
    setTSLavaAleatorio();
    setTSEnceraAleatorio();

    setmediaTEC();
    setmediaTSLava();
    setmediaTSEncera();

	settempoPause();

	inicializaEventos();



	lavaOcupado = false;
	enceraOcupado = false;

	filaLavaOcupada = 0;
	filaEnceraOcupada = 0;
	//1
	accFilaLavaOcupada = 0;
	accFilaEnceraOcupada = 0;
	//2
	contLavaOcupado = 0;
	contEnceraOcupado = 0;
	contEntidadesSistema = 0;
	contEntidadesEncera = 0;
	//3
	accTempFilaLava = 0;
	accTempFilaEncera = 0;
	//4
	accTempSimulacao = 0;
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
		accFilaLavaOcupada += filaLavaOcupada;
		accFilaEnceraOcupada += filaEnceraOcupada;
		animacao();
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
		tempChegadaAux = relogio+dist_normal(getmediaTEC());
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
		if(!tsLavaAleatorio){
			tempSaidaLavaAux = relogio+getmediaTSLava();
		}else{
			tempSaidaLavaAux = relogio+dist_normal(getmediaTSLava());
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
		tempChegadaAux = relogio+dist_normal(getmediaTEC());
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
	//long unsigned int numSorteado = rand() % 100;
	long unsigned int numSorteado = 27;
	long int tempSaidaLavaAux;

	if(numSorteado<60){
		defineTempoServLava(true);
	}else{
		defineTempoServLava(false);
	}


	if(filaLavaOcupada){

		filaLavaOcupada--;

		eventoAux.setTipo('L');
		if(!tsLavaAleatorio){
			tempSaidaLavaAux = relogio+getmediaTSLava();
		}else{
			tempSaidaLavaAux = relogio+dist_normal(getmediaTSLava());
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
			if(!tsEnceraAleatorio){
				eventoAux.setTempo(relogio+getmediaTSEncera());
			}else{
				eventoAux.setTempo(relogio+dist_normal(getmediaTSEncera()));
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
		if(!tsEnceraAleatorio){
			eventoAux.setTempo(relogio+getmediaTSEncera());
		}else{
			eventoAux.setTempo(relogio+dist_normal(getmediaTSEncera()));
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
		<<"   TIniServ Lava |"
		<<"  TFimServ Lava  |"
		<<" TIniServ Ence |"
		<<" TFimServ Ence |"
		<<" Solicitou Enceramento |\n";


    for (std::list<Entidade>::iterator it=listaEntidades.begin(); it != listaEntidades.end(); ++it){
        cout<<"\n\t"<<(*it).gettempChegada()
            <<"\t\t"<<(*it).gettempLavaInicioServico()
            <<"\t\t"<<(*it).gettempLavaFinalServico()
            <<"\t\t"<<(*it).gettempEnceraInicioServico()
            <<"\t\t"<<(*it).gettempEnceraFinalServico()
            <<"\t\t   "<<(*it).getsolicitouEnceramento();

    }

	mediaTamanhoFila();
	taxaMediaOcupacaoServidor();
	tempoMedioFila();
	tempoMedioSistema();
    contadorEntidades();

	getch();
	system("CLS");

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

void Simulacao :: settempoPause(){

	cout << "\n\n\n\tDefina a velocidade da animacao [0.2 - 1.2]: ";
	cin >> tempoPause;

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

//1
void Simulacao :: mediaTamanhoFila(){
	cout << "\n\nNumero medio de entidades na fila de lava: " << (accFilaLavaOcupada / listaEventos.size());
	cout << "\nNumero medio de entidades na fila de encera: " << (accFilaEnceraOcupada / listaEventos.size()) << "\n";
}

//2
void Simulacao :: taxaMediaOcupacaoServidor(){
	float accTempoOciosoLava = 0;
	float accTempoOciosoEncera = 0;

	Entidade entidadeAnterior;
	entidadeAnterior.settempLavaFinalServico(0);
	entidadeAnterior.settempEnceraFinalServico(0);
	for (std::list<Entidade>::iterator it=listaEntidades.begin(); it != listaEntidades.end(); ++it){
		if((*it).gettempLavaInicioServico() > entidadeAnterior.gettempLavaFinalServico()){
			accTempoOciosoLava += (*it).gettempLavaInicioServico() - entidadeAnterior.gettempLavaFinalServico();
			//cout << "\n (*it): " << (*it).gettempLavaInicioServico() << " Anterior: "<< entidadeAnterior.gettempLavaFinalServico();
		}
		if((*it).gettempEnceraInicioServico() > entidadeAnterior.gettempEnceraFinalServico()){
			accTempoOciosoEncera += (*it).gettempEnceraInicioServico() - entidadeAnterior.gettempEnceraFinalServico();
		}
		entidadeAnterior = (*it);
	}

	cout << "\nTaxa ocupacao do servidor de lava: " << 100-(100*accTempoOciosoLava / tempoTotal);
	cout << "\nTaxa ocupacao do servidor de encera: " << 100-(100*accTempoOciosoEncera / tempoTotal);
}

//3
void Simulacao :: tempoMedioFila(){

	for (std::list<Entidade>::iterator it=listaEntidades.begin(); it != listaEntidades.end(); ++it){
		if((*it).gettempLavaInicioServico() > (*it).gettempChegada()){
			accTempFilaLava += (*it).gettempLavaInicioServico() - (*it).gettempChegada();
		}
		if((*it).gettempEnceraInicioServico() > (*it).gettempLavaFinalServico()){
			accTempFilaEncera += (*it).gettempEnceraInicioServico() - (*it).gettempLavaFinalServico();
		}
	}

	cout << "\n\nTempo medio de entidade na fila de lava: " << accTempFilaLava / listaEntidades.size();
	cout << "\nTempo medio de entidade na fila de encera: " << accTempFilaEncera / listaEntidades.size();
}

//4
void Simulacao :: tempoMedioSistema(){

	for (std::list<Entidade>::iterator it=listaEntidades.begin(); it != listaEntidades.end(); ++it){
		if((*it).gettempEnceraFinalServico() > (*it).gettempChegada()){
		//	accTempSimulacao += (*it).gettempEnceraFinalServico() - (*it).gettempChegada();
			accTempSimulacao += (*it).gettempLavaFinalServico() - (*it).gettempChegada();
		}if((*it).gettempEnceraFinalServico()!=0){
			accTempSimulacao += (*it).gettempEnceraFinalServico() - (*it).gettempLavaFinalServico();
		}
	}

	cout << "\n\nTempo medio da entidade no sistema: " << accTempSimulacao / listaEntidades.size() << "\n";
}

void Simulacao :: contadorEntidades(){ 			//AIDIIIII

	cout << "\nNumero total de entidades no sistema: " << listaEntidades.size() << "\n\n";

}

//ANIMACAO
void Simulacao :: animacao(){
    int vetAnimaLava[TAM];
    char vetAnimaEncera[TAM];
    int k = 0, j = 0;

    system("cls");
    gotoxy(9,1);
    cout << "QTD LAVA: " << filaLavaOcupada;
    gotoxy(9,2);
    cout << "        ______________";
    gotoxy(9,3);
    cout << "LAVACAO ";
    if(filaLavaOcupada!=0){
        cout << "#  _,_,_\\__  #";
        gotoxy(9,4);
        cout << "        # '-O---=O-` #";
    }else{
        cout << "#            #";
        gotoxy(9,4);
        cout << "        #            #";
    }
    for(int i = 0; i < (filaLavaOcupada-1); i++){
        vetAnimaLava[i] = 0;
    }
    for(int i = 0; i < (filaLavaOcupada-1); i++){
        gotoxy(13,1+k+(i+7));
        cout << "       _,_,_\\__   ";
        gotoxy(13,((k+1)+(i+8)));
        cout << "\t  '-O---=O-`  ";
        k++;
    }
    gotoxy(32,1);
    cout << "QTD ENCERA: " << filaEnceraOcupada;
    gotoxy(32,2);
    cout << "            ______________";
    gotoxy(32,3);
    cout << "ENCERAMENTO ";
    if(filaEnceraOcupada!=0){
        cout << "#  _,_,_\\__  #";
        gotoxy(32,4);
        cout << "            # '-O---=O-` #";
    }else{
        cout << "#            #";
        gotoxy(32,4);
        cout << "            #            #";
    }
    for(int k = 0; k < (filaEnceraOcupada-1); k++){
        vetAnimaEncera[k] = 'x';
        if(vetAnimaEncera[k]=='x'){
            gotoxy(32,1+j+(k+7));
            cout << "\t\t      _,_,_\\__   ";
            gotoxy(32,((j+1)+(k+8)));
            cout << "\t             '-O---=O-`  ";
            j++;
        }
    }
    pause(tempoPause);
}


void Simulacao :: pause (float delay1) {

   if (delay1<0.001) return; // pode ser ajustado e/ou evita-se valores negativos.

   float inst1=0, inst2=0;

   inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

   while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

   return;

}

void Simulacao :: gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

#endif
