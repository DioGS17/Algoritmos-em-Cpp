#include <iostream>
#include <list>
#include <vector>
#include <limits>

using namespace std;

template<typename T>
class Fila{
    private:
        list<T> fila;
    public:

        T first(){ return fila.front(); }

        bool isEmpty(){ return fila.empty(); }

        void enqueue(T elem){ fila.push_back(elem); }

        void dequeue(){ fila.pop_front(); }
};

typedef unsigned int Vertex;

class DigraphAL {
    private:
        unsigned int num_vertex = 0;
        unsigned int num_edges = 0;
        list<Vertex> *adj;

    public:
        DigraphAL(unsigned int num_vertices);

        ~DigraphAL();

        int add_edge(Vertex u, Vertex v);

        unsigned int get_num_vertex() { return num_vertex; }

        unsigned int get_num_edges() { return num_edges; }

        list<Vertex> get_adj(Vertex v) { return adj[v]; }

        void bfs(Vertex s);
};

DigraphAL::DigraphAL(unsigned int num_vertices) {
    num_vertex = num_vertices;
    adj = new list<Vertex>[num_vertex];
}

DigraphAL::~DigraphAL() {
    for (unsigned int i = 0; i < num_vertex; ++i) {
        adj[i].clear();
    }
    delete[] adj;
    num_edges = num_vertex = 0;
}

int DigraphAL::add_edge(Vertex u, Vertex v) {
    if(u == v){
        return 0;
    }
    for (Vertex i : adj[u]) {
        if (i == v) {
            return 0;
        }
    }

    adj[u].push_back(v);
    num_edges++;
    return 1;
}

void DigraphAL::bfs(Vertex s){
    vector<int> cor(num_vertex);
    vector<int> distancias(num_vertex);
    vector<int> predecessor(num_vertex);
    vector<Vertex> ordem;

    for(int i = 0; i < num_vertex; i++){
        cor[i] = -1;
        distancias[i] = numeric_limits<int>::infinity();
        predecessor[i] = -1;
    }
    cor[s] = 0;
    distancias[s] = 0;
    predecessor[s] = -1;

    Fila<Vertex> bfs_fila;
    bfs_fila.enqueue(s);

    while(!bfs_fila.isEmpty()){
        Vertex u = bfs_fila.first();
        ordem.push_back(u);
        bfs_fila.dequeue();

        for(Vertex v : adj[u]){
            if(cor[v] == -1){
                cor[v] == 0;
                distancias[v] = distancias[u] + 1;
                predecessor[v] = u;
                bfs_fila.enqueue(v);
            }
        }
        cor[u] = 1;
    }

    cout << "Ordem de visitados: ";
    for(auto i : ordem){
        cout << i << " ";
    }
    cout << endl;
}

void display_list(list<Vertex> lst) {
    for (Vertex vertex : lst) {
        cout << vertex << ", ";
    }
    cout << endl;
}

void display_digraph(DigraphAL &g) {
    for (int v = 0; v < g.get_num_vertex(); v++) {
        cout << v << ": ";
        list<Vertex> lst = g.get_adj(v);
        display_list(lst);
    }
}

void input_digraph(DigraphAL &g, unsigned int num_edges) {
    Vertex u, v;
    for (int i = 0; i < num_edges; ++i) {
       cin >> u >> v;
       g.add_edge(u, v);
    }
}

int main() {
    unsigned int num_edges, num_vertex;
    cin >> num_vertex >> num_edges;
    
    DigraphAL g{num_vertex};
    input_digraph(g, num_edges);

    cout << endl;

    g.bfs(0);

    return 0;
}