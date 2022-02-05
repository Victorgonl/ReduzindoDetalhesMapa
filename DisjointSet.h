// Victorgonl - Disjoint-set - 20220205

#ifndef DISJOINTSET
#define DISJOINTSET

class DisjointSet{
	private:
		unsigned* sets;
		unsigned n_elements;
	public:
		DisjointSet(unsigned);
		~DisjointSet();
		void u(unsigned, unsigned);
		bool same_set(unsigned, unsigned);
		void debug();
};

DisjointSet::DisjointSet(unsigned n){
	n_elements = n;
	sets = new unsigned[n];
	for(unsigned i = 0; i < n_elements; i++){
		sets[i] = i;
	}
}

DisjointSet::~DisjointSet(){
	delete[] sets;
}

void DisjointSet::u(unsigned u, unsigned v){
	if(u >= n_elements or v >= n_elements){
		throw;
	}
	if(u > v){
		unsigned temp = u;
		u = v;
		v = temp;
	}
	unsigned root_u = sets[u], root_v = sets[v];
	unsigned i_u = 0, i_v = 0;
	while(root_u != sets[root_u]){
		root_u = sets[root_u];
		i_u++;
	}
	while(root_v != sets[root_v]){
		root_v = sets[root_v];
		i_v++;
	}
	if(root_u == root_v){
		return;
	}
	if(root_u == u and root_v == v){
		sets[v] = root_u;
	}else{
		if(i_u >= i_v){
			sets[root_v] = root_u;
		}
		else{
			sets[root_u] = root_v;
		}
	}
}

bool DisjointSet::same_set(unsigned u, unsigned v){
	if(u >= n_elements or v >= n_elements){
		throw;
	}
	unsigned root_u = sets[u], root_v = sets[v];
	unsigned i_u = 0, i_v = 0;
	while(root_u != sets[root_u]){
		root_u = sets[root_u];
		i_u++;
	}
	while(root_v != sets[root_v]){
		root_v = sets[root_v];
		i_v++;
	}
	if(root_u == root_v){
		return true;
	}
	return false;
}

/*
void DisjointSet::debug(){
	std::cout << std::endl;
	for(unsigned i = 0; i < n_elements; i++){
		unsigned root_i = sets[i];
		while(root_i != sets[root_i]){
			root_i = sets[root_i];
		}
		std::cout << "element: " << i + 1 << " father: " << sets[i] + 1 << " root: " << root_i + 1 << '\n'; 
	}
	std::cout << std::endl;
}
*/

#endif