// Victorgonl - GrafoPonderado Ponderado - 20220205

#include <vector>
#include <utility>
#include <algorithm>

#ifndef GRAFOPONDERADO
#define GRAFOPONDERADO

typedef unsigned Vertice;
typedef std::pair<Vertice, Vertice> Aresta;
typedef unsigned Peso;

class GrafoPonderado{
	private:
		unsigned n_vertices;
		std::vector<Aresta> lista_arestas;
		std::vector<Peso> funcao_peso;
		void insertionSort_Peso();
	public:
		GrafoPonderado(unsigned);
		void inserirAresta(Aresta, Peso);
		Peso somaPesos();
		void debug();
	friend GrafoPonderado kruskal(const GrafoPonderado);
};

GrafoPonderado::GrafoPonderado(unsigned n){
	n_vertices = n;
}

void GrafoPonderado::inserirAresta(Aresta aresta, Peso peso){
	if(aresta.first >= n_vertices or aresta.second >= n_vertices){
		throw;
	}
	if(aresta.first > aresta.second){
		std::swap(aresta.first, aresta.second);
	}
	if(std::find(lista_arestas.begin(), lista_arestas.end(), aresta) == lista_arestas.end()){
		lista_arestas.push_back(aresta);
		funcao_peso.push_back(peso);
		insertionSort_Peso();
	}
}

void GrafoPonderado::insertionSort_Peso(){
	int j;
	Peso key_peso;
	Aresta key_aresta;
	for (unsigned i = 1; i < lista_arestas.size(); i++){
		key_aresta = lista_arestas.at(i);
		key_peso = funcao_peso.at(i);
		j = i - 1;
		while (j >= 0 and funcao_peso.at(j) > key_peso)
		{
			lista_arestas.at(j + 1) = lista_arestas.at(j);
			funcao_peso.at(j + 1) = funcao_peso.at(j);
			j = j - 1;
		}
		lista_arestas.at(j + 1) = key_aresta;
		funcao_peso.at(j + 1) = key_peso;
	}
}

Peso GrafoPonderado::somaPesos(){
	Peso soma = 0;
	for(unsigned i = 0; i < funcao_peso.size(); i++){
		soma += funcao_peso.at(i);
	}
	return soma;
}

/*
void GrafoPonderado::debug(){
	std::cout << std::endl;
	for(unsigned i = 0; i < lista_arestas.size(); i++){
		std::cout << lista_arestas.at(i).first + 1<< '-' << lista_arestas.at(i).second + 1 << ": " << funcao_peso.at(i) << '\n';
	}
	std::cout << std::endl;
}
*/

#endif