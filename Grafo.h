#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>

class Grafo{
	private:
		std::vector<unsigned>* lista_adjacencia;
		unsigned n_vertices;
	public:
		Grafo(unsigned);
		~Grafo();
		void inserirAresta(unsigned, unsigned);
		void converterMatriz(bool**);
		void verificarDominantes();
		bool* dfs(unsigned, int = -1);
		void debug();
};

// construtor que recebe um número de vertices e inicializa cada vértice com index de 0 à n
Grafo::Grafo(unsigned n){
	n_vertices = n;
	lista_adjacencia = new std::vector<unsigned>[n_vertices];
	for(unsigned i = 0; i < n_vertices; i++){
		lista_adjacencia[i].push_back(i);
	}
}

Grafo::~Grafo(){
	delete[] lista_adjacencia;
}

// insere um vérice v adjacente na lista de adjacência do vértice u
void Grafo::inserirAresta(unsigned u, unsigned v){
	if(u >= n_vertices){
		throw;
	}
	if(std::find(lista_adjacencia[u].begin(), lista_adjacencia[u].end(), v) == lista_adjacencia[u].end()){
		lista_adjacencia[u].push_back(v);
	}
}

// recebe uma matriz de adjacência como parâmetro e converte para a lista de adjacência da classe
void Grafo::converterMatriz(bool** matriz_adjacencia){ // 
	for(unsigned i = 0; i < n_vertices; i++){
		for(unsigned j = 0; j < n_vertices; j++){
			if(matriz_adjacencia[i][j])
				inserirAresta(i, j);
		}
	}
}

// depth-first search retornando os vérices visitados com a possibilidade de marcar um vértice para não ser explorado
bool* Grafo::dfs(unsigned inicio, int bloqueado){
	// criar lista de visitados e marcar todos os vértices como não visitados
	bool* visitado = new bool[n_vertices];
	for(unsigned i = 0; i < n_vertices; i++){
		visitado[i] = false;
	}
	// primeiro vértice a ser explorado
	unsigned v = inicio;
	std::stack<unsigned> pilha;
	pilha.push(v);
	// caso um vértice seja marcado como bloqueado, ele não poderá ser explorado
	if(bloqueado >= 0){
		visitado[bloqueado] = true;
	}
	// depth-first search salvando os vérices visitados
	while(pilha.size() > 0){
		v = pilha.top();
		pilha.pop();
		if(!visitado[v]){
			visitado[v] = true;
			for(unsigned i = 1; i < lista_adjacencia[v].size(); i++){
				if(!visitado[lista_adjacencia[v].at(i)]){
					pilha.push(lista_adjacencia[v].at(i));
				}
			}
		}
	}
	// vértice bloqueado é marcado como não vizitado para indicar que não foi explorado
	if(bloqueado >= 0){
		visitado[bloqueado] = false;
	}

	return visitado;
}

// verifica e imprime em sua linha de index, se existir, seus vértices dominados
void Grafo::verificarDominantes(){
	// calcula lista de todos os vértices alcançados a partir da origem 0
	const unsigned origem = 0;
	bool* origem_alcanca = dfs(origem);
	bool* alcanca = nullptr;
	bool* origem_alcanca_com_bloqueio = nullptr;
	// para cada vértice, calcula seus dominados se existirem
	for(unsigned i = 0; i < n_vertices; i++){
		// vértices válidos são apenas os que a origem alcança
		if(origem_alcanca[i]){
			alcanca = dfs(i);
			origem_alcanca_com_bloqueio = dfs(origem, i);
			// verifica possíveis dominados
			std::vector<unsigned> resultado;
			for(unsigned j = 0; j < n_vertices; j++){
				// vétices dominados são aqueles que a origem alcança, seu dominante alcança
				// e a origem não alcança caso o dominante não possa ser visitado
				if(origem_alcanca[j] and alcanca[j] and !origem_alcanca_com_bloqueio[j]){
					resultado.push_back(j);
				}
			}
			for(unsigned j = 0; j < resultado.size(); j++){
				if(j == 0){
					std::cout << resultado.at(j);
				}
				else{
					std::cout << ' ' << resultado.at(j);
				}
			}
		}
		else{
			std::cout <<  '-';
		}
		if(i != n_vertices - 1){
			std::cout << std::endl;
		}
	}
	delete[] origem_alcanca;
	delete[] alcanca;
	delete[] origem_alcanca_com_bloqueio;
}

void Grafo::debug(){
	std::cout << std::endl;
	for(unsigned i = 0; i < n_vertices; i++){
		std::cout << lista_adjacencia[i].at(0) << ':';
		for(unsigned j = 1; j < lista_adjacencia[i].size(); j++){
			std::cout << ' ' << lista_adjacencia[i].at(j);
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
}