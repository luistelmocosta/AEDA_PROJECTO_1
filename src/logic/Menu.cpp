#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "Campeonato.h"
#include "Utilities.h"

void initMenu(){

	cout << "# Campeonatos Polidesportivos #" << endl << endl;

	while(campeonato->getNome()=="" || campeonato->getPais()==""){
		collectCampInfo();
	}

	clearScreen();
	dataBaseMenu();

}

void collectCampInfo(){
	string nomeC, dataC, paisC;

	cout << "Insira o nome do Campeonato a criar: ";
	cin >> nomeC;
	cout << "Insira a data de inicio do Campeonato: ";
	cin >> dataC;
	cout << "Insira o pais-anfitriao do Campeonato: ";
	cin >> paisC;
	cout << endl;

	campeonato->setNome(nomeC);
	campeonato->setData(dataC);
	campeonato->setPais(paisC);
}


/*
 * 	#DATABASE
 */

void dataBaseMenu(){
	int input;

	cout << "1. Utilizar Base Dados existente" << endl;
	cout << "2. Criar Base Dados" << endl;
	cin >> input;

	clearScreen();

	if(input==1){
		readDB();
		mainMenu();
	}
	else if(input==2)
		criaDBMenu();
	else dataBaseMenu();

}

int readDB(){
	string FICHEIRO_ATLETAS = "txt_data/Atletas_default.txt";
	string FICHEIRO_EQUIPAS = "txt_data/Equipas_default.txt";
	string FICHEIRO_PROVAS = "txt_data/Provas_default.txt";

	try{
		campeonato->readFileAtletas(FICHEIRO_ATLETAS);
		campeonato->readFileEquipas(FICHEIRO_EQUIPAS);
		campeonato->readFileProvas(FICHEIRO_PROVAS);
	}
	catch (ErroNoFicheiro &e){
		cout << "Tentativa de abrir o ficheiro falhou.\n";
	}

	return 0;
}

void criaDBMenu(){

	int input;

	cout << "1. Criar Equipa" << endl;
	cout << "2. Criar Atleta" << endl;
	cout << "3. Criar Prova" << endl;
	cout << "4. Avancar" << endl;

	cin >> input;

	switch(input){

	case 1: criaEquipaMenu();
	criaDBMenu();
	break;

	case 2: criaAtletaMenu();
	criaDBMenu();
	break;

	case 3:criaProvaMenu();
	criaDBMenu();
	break;

	case 4: mainMenu();
	break;

	default: cout << "Opcao invalida." << endl;
	}

}


/*
 * 	#MAINMENU
 */

void mainMenu(){
	int input;

	cout << "1. Gerir Equipas" << endl;
	cout << "2. Gerir Atletas" << endl;
	cout << "3. Gerir Provas" << endl;
	cout << "4. Ver Calendario" << endl;
	cout << "5. Classificacoes" << endl;
	cout << "6. Sair" << endl;

	cin >> input;

	clearScreen();

	switch(input){
	case 1: gerirEquipaMenu();
	break;

	case 2: gerirAtletaMenu();
	break;

	case 3: gerirProvaMenu();
		break;

	case 4:
		break;

	case 5:
		break;

	case 6: break;

	default: mainMenu();
	break;

	}
}


/*
 * 	#EQUIPAS
 */

void criaEquipaMenu(){
	string nome, pais, pat;

	cout << "==Criador Equipas==" << endl;

	cout << "Nome da Equipa: " << endl;
	cin >> nome;

	cout << "Pais da Equipa: " << endl;
	cin >> pais;

	cout << "Patrocinador da Equipa: " << endl;
	cin >> pat;

	Equipa *e = new Equipa(nome, pais, pat);
	campeonato->inserirEquipa(*e);

	clearScreen();

}

void gerirEquipaMenu(){

	int input;

	cout << "1. Ver Equipas" << endl;
	cout << "2. Criar Equipa" << endl;
	cout << "3. Modificar Equipa" << endl;
	cout << "4. Apagar Equipa" << endl;
	cout << "5. Voltar atras" << endl;

	cin >> input;

	switch(input){

	case 1: clearScreen();
	verEquipas();
	gerirEquipaMenu();
	break;

	case 2: clearScreen();
	criaEquipaMenu();
	gerirEquipaMenu();
	break;

	case 3: clearScreen();
	modificaEquipaMenu();
	gerirEquipaMenu();
	break;

	case 4: clearScreen();
	apagaEquipaMenu();
	gerirEquipaMenu();
	break;

	case 5: clearScreen();
	mainMenu();
	break;

	default: break;
	}

}

void verEquipas(){
	campeonato->imprimeEquipas();
}

void modificaEquipaMenu(){

	int pos;
	string input;

	cout << "Insira o nome da equipa a alterar: " << endl;
	cin >> input;

	pos=campeonato->findEquipa(input);

	if(pos<0)
		throw EquipaInexistente(input);
	else{
		campeonato->getEquipas()[pos]->imprime();
		cout << "Insira o campo que pretende alterar: " << endl;
		cin >> input;

		if(input=="Nome" || input=="nome"){
			cout << "Insira o nome que pretende atribuir: " << endl;
			cin >> input;
			campeonato->getEquipas()[pos]->setNome(input);
		}
		else if(input=="Pais" || input=="pais"){
			cout << "Insira o pais que pretende atribuir: " << endl;
			cin >> input;
			campeonato->getEquipas()[pos]->setPais(input);
		}
		else if(input=="Patrocinador" || input=="patrocinador"){
			cout << "Insira o patrocinador que pretende atribuir: " << endl;
			cin >> input;
			campeonato->getEquipas()[pos]->setPatrocinador(input);
		}
		else if(input=="Pontuacao" || input=="pontuacao"){
			float pont;
			cout << "Insira a pontuacao que pretende atribuir: " << endl;
			cin >> pont;
			campeonato->getEquipas()[pos]->setPontuacao(pont);
		}
		else cout << "Campo invalido!" << endl;

	}
}

void apagaEquipaMenu(){

	string input;

	cout << "Insira o nome da equipa a eliminar: " << endl;
	cin >> input;

	if(campeonato->eliminarEquipa(input)){
		cout << "Equipa " << input << " eliminada com sucesso." << endl;
	}
	else cout << "Nao foi possivel apagar a equipa " << input << "." << endl;

}


/*
 * 	#ATLETAS
 */

void criaAtletaMenu(){
	info i;
	string equipa;

	cout << "==Criador Atletas==" << endl;

	cout << "Nome: " << endl;
	cin >> i.nome;

	cout << "Pais: " << endl;
	cin >> i.pais;

	cout << "Idade: " << endl;
	cin >> i.idade;

	cout << "Altura: " << endl;
	cin >> i.altura;

	cout << "Peso: " << endl;
	cin >> i.peso;

	cout << "Equipa: " << endl;
	cin >> equipa;

	Atleta *a = new Atleta();
	a->setInfo(i);
	a->setNEquipa(equipa);

	if(campeonato->findEquipa(equipa) > -1){
		campeonato->getEquipas()[campeonato->findEquipa(equipa)]->inserirAtleta(*a);
	}

	campeonato->inserirAtleta(*a);

	clearScreen();

}

void gerirAtletaMenu(){

	int input;

	cout << "1. Ver Atletas" << endl;
	cout << "2. Criar Atleta" << endl;
	cout << "3. Modificar Atleta" << endl;
	cout << "4. Apagar Atleta" << endl;
	cout << "5. Voltar atras" << endl;

	cin >> input;

	switch(input){

	case 1: clearScreen();
	verAtletas();
	gerirAtletaMenu();
	break;

	case 2: clearScreen();
	criaAtletaMenu();
	gerirAtletaMenu();
	break;

	case 3: clearScreen();
	modificaAtletaMenu();
	gerirAtletaMenu();
	break;

	case 4: clearScreen();
	apagaAtletaMenu();
	gerirAtletaMenu();
	break;

	case 5: clearScreen();
	mainMenu();
	break;

	default: gerirAtletaMenu();
	break;
	}

}

void verAtletas(){
	campeonato->imprimeAtletas();
}

void modificaAtletaMenu(){
	unsigned int id;
	int pos;
	string input;
	float input_numb;

	cout << "Insira o id do atleta a alterar: " << endl;
	cin >> id;

	pos=campeonato->findAtleta(id);

	if(pos<0)
		throw AtletaInexistente(id);
	else{
		campeonato->getAtletas()[pos]->imprime();
		cout << "Insira o campo que pretende alterar: " << endl;
		cin >> input;

		if(input=="Nome" || input=="nome"){
			cout << "Insira o nome que pretende atribuir: " << endl;
			cin >> input;
			campeonato->getAtletas()[pos]->setNome(input);
		}
		else if(input=="Pais" || input=="pais"){
			cout << "Insira o pais que pretende atribuir: " << endl;
			cin >> input;
			campeonato->getAtletas()[pos]->setPais(input);
		}
		else if(input=="Idade" || input=="idade"){
			cout << "Insira a idade que pretende atribuir: " << endl;
			cin >> input_numb;
			campeonato->getAtletas()[pos]->setIdade(input_numb);
		}
		else if(input=="Altura" || input=="altura"){
			cout << "Insira a altura que pretende atribuir (cm): " << endl;
			cin >> input_numb;
			campeonato->getAtletas()[pos]->setAltura(input_numb);
		}
		else if(input=="Peso" || input=="peso"){
			cout << "Insira o peso que pretende atribuir (kg): " << endl;
			cin >> input_numb;
			campeonato->getAtletas()[pos]->setPeso(input_numb);
		}
		else if(input=="Pontuacao" || input=="pontuacao"){
			cout << "Insira a pontuacao que pretende atribuir: " << endl;
			cin >> input_numb;
			campeonato->getAtletas()[pos]->setPontuacao(input_numb);
		}
		else if(input=="Equipa" || input=="equipa"){
			cout << "Insira o nome da equipa que pretende atribuir: " << endl;
			cin >> input;
			campeonato->getAtletas()[pos]->setNEquipa(input);
		}
		else cout << "Campo invalido!" << endl;

	}
}

void apagaAtletaMenu(){

	unsigned int id;

	cout << "Insira o id do atleta a eliminar: " << endl;
	cin >> id;

	if(campeonato->eliminarAtleta(id)){
		cout << "Atleta com id " << id << " eliminado com sucesso." << endl;
	}
	else cout << "Nao foi possivel apagar o atleta com id " << id << "." << endl;
}


/*
 * 	#PROVAS
 *
 */

void criaProvaMenu(){

	string input;
	unsigned int durac;
	Prova *p = new Prova();

	cout << "==Criador Provas==" << endl;

	cout << "Data: " << endl;
	cin >> input;
	//TODO convert string to date

	cout << "Local: " << endl;
	cin >> input;
	p->setLocal(input);

	cout << "Duracao: " << endl;
	cin >> durac;
	p->setDuracao(durac);

	cout << "Modalidade: " << endl;
	cin >> input;
	//TODO

	cout << "Equipas Adversarias: " << endl;
	cin >> input;
	//TODO

	campeonato->getCalendario()->inserirProva(*p);

	clearScreen();
}

void gerirProvaMenu(){

	int input;

	cout << "1. Ver Provas" << endl;
	cout << "2. Criar Prova" << endl;
	cout << "3. Modificar Prova" << endl;
	cout << "4. Apagar Prova" << endl;
	cout << "5. Voltar atras" << endl;

	cin >> input;

	switch(input){

	case 1: clearScreen();
	verProvas();
	gerirProvaMenu();
	break;

	case 2: clearScreen();
	criaProvaMenu();
	gerirProvaMenu();
	break;

	case 3: clearScreen();
	modificaProvaMenu();
	gerirProvaMenu();
	break;

	case 4: clearScreen();
	apagaProvaMenu();
	gerirProvaMenu();
	break;

	case 5: clearScreen();
	mainMenu();
	break;

	default: gerirAtletaMenu();
	break;
	}
}

void verProvas(){
	campeonato->getCalendario()->showProvas();
}

void modificaProvaMenu(){

	unsigned int aux;
	int pos;
	string input;

	cout << "Insira o id da prova a alterar: " << endl;
	cin >> aux;

	pos=campeonato->getCalendario()->findProva(aux);

	if(pos<0)
		throw ProvaInexistente(aux);
	else{
		campeonato->getCalendario()->getProvas()[pos]->print();
		cout << "Insira o campo que pretende alterar: " << endl;
		cin >> input;

		if(input=="Data" || input=="data"){
			cout << "Insira a data que pretende atribuir: " << endl;
			cin >> input;
			//TODO
			//campeonato->getCalendario()->getProvas()[pos]->setData();
		}
		else if(input=="Local" || input=="local"){
			cout << "Insira o local que pretende atribuir: " << endl;
			cin >> input;
			campeonato->getCalendario()->getProvas()[pos]->setLocal(input);
		}
		else if(input=="Modalidade" || input=="modalidade"){
			cout << "Insira a modalidade que pretende atribuir: " << endl;
			cin >> input;
			//TODO
			//campeonato->getCalendario()->getProvas()[pos]->setModalidade();
		}
		else if(input=="Duracao" || input=="duracao"){
			cout << "Insira a duracao que pretende atribuir: " << endl;
			cin >> aux;
			campeonato->getCalendario()->getProvas()[pos]->setDuracao(aux);
		}
		else cout << "Campo invalido!" << endl;

	}

}

void apagaProvaMenu(){

	unsigned int id;

	cout << "Insira o id da prova a eliminar: " << endl;
	cin >> id;

	if(campeonato->getCalendario()->findProva(id)<0)
		cout << "Prova com id " << id << " nao existe." << endl;
	else{
		campeonato->getCalendario()->eliminarProva(id);
		cout << "Prova com id " << id << " eliminada com sucesso." << endl;
	}

}

/*
 * 	#
 */

void clearScreen(){
	cout << string(50, '\n');
}

int main(){

	initMenu();

	return 0;
}




/*void Calendario::removeProva(){
	unsigned int n;
	cout << endl << "ID da prova a remover(0 para cancelar): ";
	cin >> n;

	if(n == 0)
		return;
	else if(n > provas.size() || n < 0){
		cout << endl  << "Prova nao encontrada!" << endl;
		return;
	}
	provas.erase(provas.begin()+n);
}

void Calendario::criaProvas(Campeonato &c1){

	cout << "Criador de Provas!" << endl;

	vector<Equipa*> vs;

	string input = "s";
	string restart;
	string nAtleta;
	string modN;
	bool boaMod = false;
	bool boaData = false;
	bool boaHora = false;
	bool boaDur = false;
	bool atletaEncontrado = false;
	bool provaSobrep = true;
	date d1;

	while (input == "s" || input == "sim" || input == "Sim" || input == "SIM" || input =="S"){

		while(!boaMod){

			cout << "Nome da modalidade: ";
			cin >> modN;

			/*for (unsigned int i = 0; i < getModalidades().size(); i++){
				if(getModalidades()[i] == modN)
					boaMod = true;*/
/*			boaMod = true;

			if(!boaMod)
				cout << "Nome da modalidade nao encontrad!!" << endl;

		}
		while(provaSobrep){

			string local;
			string data;
			cout << "Local da prova: ";
			cin >> local;

			while(!boaData){

				stringstream dataSs;

				cout << "Data da prova(DD-MM-AAAA): ";
				cin >> data;
				dataSs << data;
				int dia=1, mes=1, ano=1;
				char tmp;
				dataSs >> dia >> tmp >> mes >> tmp >> ano;


				if(dia < 1 || dia > 31|| mes < 1 || mes > 12 || ano < 1 || (dia > 28 && mes == 2) || (dia > 30 && mes == 4) || (dia > 30 && mes == 6) || (dia > 30 && mes == 9) || (dia > 30 && mes == 11)){
					cout << "Data invalida!";
					boaData = false;
				}

				else{

					boaData =true;

					d1.dia = dia;
					d1.mes = mes;
					d1.ano = ano;

				}
			}

			while(!boaHora){

				float hora;
				cout << "A que horas comecara a prova?(formato 24h) ";
				cin >>hora;
				if(hora < 1 || hora > 24){
					cout << "Hora invalida!" << endl;
					boaHora =false;
				}
				else{
					boaHora= true;
					d1.hora = hora;
				}

			}

			int min;
			while(!boaDur){
				cout << "Qual a duracao da prova?(Em minutos) ";
				cin >> min;
				if(min < 1){
					cout << "Duracao invalida!" << endl;
					boaDur = false;
				}
				else
					boaDur = true;
			}

			// Equipa 1
			string nEquipa;
			bool boaEquipa = false;
			while(!boaEquipa){

				cout << "Nome da primeira equipa a participar: ";
				cin.ignore();
				getline(cin, nEquipa);

				int find;
				find = c1.findEquipa(nEquipa);

				if(find != -1){

					boaEquipa = true;
				}
				else{
					cout << "Equipa nao encontrada!" << endl;
				}
			}
			vs.push_back(c1.getEquipas()[c1.findEquipa(nEquipa)]);

			boaEquipa = false;

			while (!atletaEncontrado){

				cout << "Nome do atleta da equipa " << nEquipa <<": ";

				cin.ignore();
				getline(cin,nAtleta);


				for(unsigned int i = 0; i < c1.getAtletas().size(); i++){
					if (c1.getAtletas()[i]->getNome() == nAtleta){
						atletaEncontrado = true;
						break;
					}
				}

				if (!atletaEncontrado)
					cout << "Atleta nao encontrado!" << endl;

			}
			atletaEncontrado = false;

			// Equipa 2

			while(!boaEquipa){
				cout << "Nome da segunda equipa a participar: ";
				cin.ignore();
				getline(cin,nEquipa);
				int find;
				find = c1.findEquipa(nEquipa);

				if(find != -1){
					boaEquipa = true;
				}
				else{
					cout << "Equipa nao encontrada!" << endl;
				}
			}


			vs.push_back(c1.getEquipas()[c1.findEquipa(nEquipa)]);

			while (!atletaEncontrado){

				cout << "Nome do atleta da equipa " << nEquipa <<": ";
				cin.ignore();
				getline(cin,nAtleta);

				for(unsigned int i = 0; i < c1.getAtletas().size(); i++){
					if (c1.getAtletas()[i]->getNome() == nAtleta){
						atletaEncontrado = true;
						break;
					}
				}

				if (!atletaEncontrado)
					cout << "Atleta nao encontrado!" << endl;

			}




			Modalidade *m = new Modalidade(modN,0);
			Prova* p1= new Prova(d1,local, min, vs,m);



			if(inserirProva(*p1)){
				cout << "Prova adicionada com sucesso!!" << endl;
				provaSobrep=false;
			}
			else{ // falhou por reposicao
				cout << endl << "Recomecar ou Alterar dados desta modalidade? (R/A)";
				cin >> restart;
				provaSobrep=true;
			}

			boaData = false;
			boaHora = false;
			boaDur = false;
			boaMod = false;

			if(restart == "R" || restart == "r")
				break;

		}
		provaSobrep = true;
		bool bomInput =false;

		while(!bomInput){
			cout << "Adicionar nova prova?(S/N)";
			cin >> input;
			/*if(input != "S" || input !="N" || input !="s" ||input !="n")
				cout << "Input invalido." << endl;
			else*/
/*	bomInput =true;
		}
	}

}*/