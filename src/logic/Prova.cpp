#include "Prova.h"

int Prova::newID = 0;

Prova::Prova(date d, string l, unsigned int dur, vector <Equipa*> v, Modalidade* modal):id(newID++){

	/*fstream fich;

	fich.open("Provas.txt", ios::in);

	if(fich.is_open()){

		while(!fich.eof()){
			getline(fich, nome);
			// le resto
			if(fich.eof())
				break;

			Prova p;
			getline(fich, nome);

			provas.push_back(x);
		}
	}
	else
		throw UnableOpenFile(filename);
	fich.close();
	 */

	data = d;
	local = l;
	duracao = dur;
	mod = modal;

	for (unsigned int i = 0; i < v.size(); i++){
		this->vs.push_back(v[i]);
	}
}

int Prova::getId()const {
	return id;
}

date Prova::getData() const {
	return data;
}

string Prova::getLocal() const {
	return local;
}

unsigned int Prova::getDuracao() const {
	return duracao;
}

vector<Equipa*> Prova::getAdversarios() const {
	return vs;
}

Modalidade* Prova::getModalidade() const {
	return mod;
}

void Prova::setModalidade(Modalidade* modal) {
	this->mod=modal;
}

Equipa* Prova::getVencedor() const {
	return vencedor;
}



void Prova::setParticipantes (Atleta* a1, Atleta* a2){
	vs[0]->inserirAtleta(*a1);
	vs[1]->inserirAtleta(*a2);
}

Atleta* Prova::getParticipante(int i) const{

	vector <Atleta*> atletasVec = vs[i]->getAtletas();
	int position;


	for(unsigned int j=0; j < atletasVec.size(); j++){

		vector <Modalidade*> modAtleta = atletasVec[j]->getModalidades();

		position = sequentialSearch(modAtleta, this->mod);
		if(position !=-1){
			return vs[i]->getAtletas()[j];
		}
	}

	throw ParticipanteInexistente();
}

void Prova::alterarLocal(){
	string l;
	cout << endl << "Novo local: ";
	cin >> l;
}

void Prova::alterarData(){

}

void Prova::alterarDuracao(){
	int dur;
	cout << endl << "Nova duracao: ";
	cin >> dur;
}

bool Prova::operator !=(const Prova &p){

	bool result = true;

	if (this->local == p.getLocal() || (this->getData().ano == p.getData().ano && this->getData().dia == p.getData().dia && this->getData().mes == p.getData().mes && this->getData().hora == p.getData().hora)){
		result = false;
	}

	/*if(this->getData().hora < p.getData().hora + p.getDuracao()){

		result = false;
	}*/

	return result;
}

string Prova::getDataFormatada() const {
		string dta = "";

		stringstream ss;

		ss << data.dia;
		ss << "-";
		ss << data.mes;
		ss << "-";
		ss << data.ano;

		ss >> dta;

		return dta;
}
