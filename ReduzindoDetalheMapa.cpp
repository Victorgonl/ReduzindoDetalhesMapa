// Victorgonl - Reduzindo Detalhes em um Mapa - 20220205

#include <iostream>
#include "GrafoPonderado.h"
#include "DisjointSet.h"
#include "kruskal.h"

int main(){
	unsigned n, m;
	std::cin >> n >> m;

	GrafoPonderado g(n);

	for(unsigned i = 0; i < m; i++){
		Vertice u, v;
		Peso p;
		std::cin >> u >> v >> p;
		u--; v--;
		g.inserirAresta(Aresta(u, v), p);
	}

	GrafoPonderado t = kruskal(g);

	std::cout << t.somaPesos();

	return 0;
}


