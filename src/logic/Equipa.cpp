#include <iostream>
#include <iterator>
#include "Equipa.h"


Equipa::Equipa(string n, string p, string pat): nome(n), pais(p), patrocinador(pat) {
	pontuacao=0;
	medalhas.reserve(3);
	medalhas[0]=0;
	medalhas[1]=0;
	medalhas[2]=0;
	doping=false;
}

Equipa::Equipa() {
	pontuacao=0;
	medalhas.reserve(3);
	medalhas[0]=0;
	medalhas[1]=0;
	medalhas[2]=0;
	doping=false;
}


/*
 *
 * 		GETS/SETS
 *
 */

string Equipa::getNome() const {
	return nome;
}

void Equipa::setNome(string novoNome) {
	nome=novoNome;
}

string Equipa::getPais() const {
	return pais;
}

void Equipa::setPais(string novoPais) {
	pais=novoPais;
}

string Equipa::getPatrocinador() const {
	return patrocinador;
}

void Equipa::setPatrocinador(string novoPatrocinio) {
	patrocinador=novoPatrocinio;
}

float Equipa::getPontuacao() const {
	return pontuacao;
}

void Equipa::setPontuacao(float p) {
	pontuacao = pontuacao + p;
}

vector<Atleta*> Equipa::getAtletas() const {
	return atletas;
}

Atleta* Equipa::getAtleta(unsigned int id){

	int pos = existeAtletaID(id);

	if(pos<0)
		throw AtletaInexistente(id);
	else return atletas[pos];
}

vector<unsigned int> Equipa::getMedalhas() const{
	return medalhas;
}

void Equipa::setMedalhas(vector<unsigned int> m){
	medalhas=m;
}

bool Equipa::getDoping() const{
	return doping;
}
void Equipa::setDoping(bool b){
	doping=b;
}

bool Equipa::temMedalhas(){
	for(unsigned i=0; i<medalhas.size(); i++){
		if(medalhas[i]>0)
			return true;
	}
	return false;
}

/*
 *
 * 		MANIPULAR ATLETAS
 *
 */

void Equipa::inserirAtleta(Atleta &a1){
	atletas.push_back(&a1);
}

bool Equipa::eliminarAtleta(unsigned int id){

	int pos = existeAtletaID(id);

	if(pos<0)
		return false;
	else {
		atletas.erase(atletas.begin() + pos);
		return true;
	}

}

int Equipa::existeAtleta(string nome){

	int counter=0;

	vector<Atleta*>::iterator it;

	for(it = atletas.begin(); it != atletas.end(); ++it){
		if((*it)->getNome() == nome){
			counter++;
		}
	}

	return counter;
}

int Equipa::existeAtletaID(unsigned int id){

	for(unsigned int i=0; i<atletas.size(); i++){
		if(atletas[i]->getID()==id)
			return i;
	}

	return -1;
}

void Equipa::showAtletas(){

	for(unsigned int i=0; i<atletas.size(); i++){
		atletas[i]->imprime();
	}
}


/*
 *
 * 		PRINT
 *
 */

void Equipa::imprime() {
	cout << endl;
	cout << "Nome: " << nome << endl;
	cout << "Pais: " << pais << endl;
	cout << "Patrocinador: " << patrocinador << endl;
	cout << "Pontuacao: " << pontuacao << endl;
	cout << endl;
}


/*
 *
 * 		OPERADORES
 *
 */

bool Equipa::operator<(const Equipa &e) const{ // para insertion sort


}

bool Equipa::operator==(const Equipa &e) const{
	if(medalhas[0] == e.getMedalhas()[0] && medalhas[1] == e.getMedalhas()[1] && medalhas[2] == e.getMedalhas()[2])
		return true;
	else return false;
}
