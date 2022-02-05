#include "GrafoPonderado.h"
#include "DisjointSet.h"

#ifndef KRUSKAL
#define KRUSKAL

GrafoPonderado kruskal(const GrafoPonderado g){
	GrafoPonderado t(g.n_vertices);
	DisjointSet dj(g.n_vertices);
	for(unsigned i = 0; i < g.lista_arestas.size(); i++){
		if(!dj.same_set(g.lista_arestas.at(i).first, g.lista_arestas.at(i).second)){
			t.inserirAresta(g.lista_arestas.at(i), g.funcao_peso.at(i));
			dj.u(g.lista_arestas.at(i).first, g.lista_arestas.at(i).second);
		}
	}
	return t;
}

#endif