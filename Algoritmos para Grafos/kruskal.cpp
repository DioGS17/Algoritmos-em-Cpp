#include <iostream>
#include <list>
#include <vector>

using namespace std;

class UnionFind{
private:
    vector<int> parent, rank;

public:
    vector<int> get_parent(){ return parent; }
    vector<int> get_rank(){ return rank; }

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootX] = rootY;
                rank[rootY]++;
            }
        }
    }
};

typedef unsigned int Vertex;
typedef float Weight;

class Aresta{
public:
    Vertex origem, destino;
    Weight peso;
    Aresta(Vertex o, Vertex d, Weight p){
        origem = o;
        destino = d;
        peso = p;
    }
};

class VertexWeightPair{
public:
    Vertex vertex;
    Weight weight;
    VertexWeightPair(Vertex _vertex, Weight _weight){
        vertex = _vertex;
        weight= _weight;
    };
};

class WeightedGraphAL{
private:
    unsigned int num_vertex = 0, num_edges = 0;
    list<VertexWeightPair> *adj;
    vector<Aresta> arestas;

public:
    WeightedGraphAL(unsigned int num_vertice);

    ~WeightedGraphAL();

    int add_edge(Vertex u, Vertex v, Weight w);

    unsigned int get_num_vertex(){ return num_vertex; }

    unsigned int get_num_edges(){ return num_edges; }

    list<VertexWeightPair> get_adj(Vertex v){ return adj[v]; }

    Weight kruskal();
};

WeightedGraphAL::WeightedGraphAL(unsigned int num_vertice){
    num_vertex = num_vertice;
    adj = new list<VertexWeightPair>[num_vertex];
}

WeightedGraphAL::~WeightedGraphAL(){
    for (unsigned int i = 0; i < num_vertex; i++){
        adj[i].clear();
    }

    delete[] adj;
    num_edges = num_vertex = 0;
}

int WeightedGraphAL::add_edge(Vertex u, Vertex v, Weight w){
    for(VertexWeightPair i : adj[u]){
        if(i.vertex == v){
            return 0;
        }
    }

    Aresta a(u, v, w);
    arestas.push_back(a);
    VertexWeightPair edge_u(v, w);
    adj[u].push_back(edge_u);
    VertexWeightPair edge_v(u, w);
    adj[v].push_back(edge_v);
    num_edges++;
    return 1;
}

Weight WeightedGraphAL::kruskal(){
    vector<Aresta> a = arestas;

    for(int i = 0; i < num_edges; i++){
        for(int j = i+1; j < num_edges; j++){
            if(a[i].peso > a[j].peso){
                Aresta aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
        }
    }

    UnionFind uf(num_vertex);
    Weight soma_pesos = 0;

    for (auto i : a){
        int u = i.origem;
        int v = i.destino;
        float peso = i.peso;

        if(uf.find(u) != uf.find(v)){
            uf.unite(u,v);
            soma_pesos += peso;
        }
    }

    cout << "Soma dos pesos: " << soma_pesos << endl;
    return soma_pesos;
}

void input_graph(WeightedGraphAL &g, unsigned int num_arestas){
    Vertex u, v;
    Weight w;

    for (int i = 0; i < num_arestas; ++i){
        cin >> u >> v >> w;
        int teste_de_repeticao = g.add_edge(u, v, w);
        if(teste_de_repeticao == 0){
            --i;
        }
    }
    
}

void display_list(list<VertexWeightPair> lst){
    for(VertexWeightPair vw : lst){
        cout << "(" << vw.vertex << ", " << vw.weight << "), ";
    }
    cout << endl;
}

void display_graph(WeightedGraphAL &g){
    for (int i = 0; i < g.get_num_vertex(); i++){
        cout << i << ": ";
        list<VertexWeightPair> lst = g.get_adj(i);
        display_list(lst);
    }
    
}

int main(){
    unsigned int num_vertex, num_edges;
    cin >> num_vertex >> num_edges;
    WeightedGraphAL g{num_vertex};
    input_graph(g, num_edges);

    cout << endl;

    g.kruskal();

    return 0;
}