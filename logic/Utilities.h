#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include <vector>
#include <string>
#include <iostream>

using namespace std;


/*
 	 *						*
 	 * 		UTILITARIOS		*
 	 *						*
*/

struct info{				// CC atleta
	string nome;
	string pais;
	unsigned int idade;
	unsigned int peso;
	unsigned int altura;
};


struct date{				// a usar em prova, campeonato
	unsigned int dia;
	unsigned int mes;
	unsigned int ano;
	float hora;
};





/*
 	 *			ALGORITMOS			*
 	 * 		PESQUISA e ORDENACAO	*
 	 *			VECTORES			*
*/

template <class Comparable>
int sequentialSearch(const vector<Comparable> &v, Comparable x)
{
    for (unsigned int i = 0; i < v.size(); i++)
        if(v[i] == x)
           return i;   // encontrou
    return -1;     // nao encontrou
}



template <class Comparable>
void insertionSort(vector<Comparable> &v)
{
    for (unsigned int p = 1; p < v.size(); p++)
    {
    	Comparable tmp = v[p];
    	int j;
    	for (j = p; j > 0 && tmp < v[j-1]; j--)
    		v[j] = v[j-1];
    	v[j] = tmp;
    }
}





/*
	 * 		TRATAMENTO			*
	 * 			de				*
	 * 		EXCEPCOES			*
*/

class ValorInvalido {
public:
	int v;
	ValorInvalido(int v) :v(v) {}
	int getValor(){return v;}
};

class ErroNoFicheiro{
public:
	string filename;
	ErroNoFicheiro(string fn): filename(fn){
		cout << "Erro no ficheiro: " << filename << endl;
	}
	string getFileName(){return filename;}
};

class AtletaInexistente {
public:
	int id;
	string nome;
	AtletaInexistente(int id) :id(id) {}
	AtletaInexistente(string nome): nome(nome){}
	int getID(){return id;}
	string getNome(){return nome;}
};

#endif /* SRC_UTILITIES_H_ */