#ifndef SRC_PROVA_H_
#define SRC_PROVA_H_

#include <vector>
#include "Equipa.h"
#include "Desporto.h"
#include "Utilities.h"
#include "Atleta.h"

class Equipa;
class Atleta;

class Prova{

	int id;
	static int newID;
	date data;
	string local;
	unsigned int duracao;   //"Cada prova terá um tempo de duracao."
	vector<Equipa*> vs;
	Modalidade* mod;
	Equipa* vencedor;
	bool realizada;

public:
	Prova(){}
	Prova(date d, string l, unsigned int dur, vector <Equipa*> v, Modalidade* modal);

	int getId()const;
	date getData() const;
	void setRealizada();
	string getDataFormatada() const;
	string getLocal() const;
	unsigned int getDuracao() const;
	vector<Equipa*> getAdversarios() const;
	Modalidade* getModalidade() const;
	void setModalidade(Modalidade* modal);
	Equipa* getVencedor() const;
	void setVencedor(Equipa* v);
	void setParticipantes (Atleta* a1, Atleta* a2);
	void alterarModalidade();
	void alterarLocal();
	void alterarData();
	void alterarDuracao();
	void alterarEquipa(bool equipaEsq);
	void alterarVencedor();

	Atleta* getParticipante(int i) const;

	bool operator !=(const Prova &p);
	bool operator ==(const Prova &p);
};

#endif /* SRC_PROVA_H_ */
