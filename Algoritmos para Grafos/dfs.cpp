#include <iostream>
#include <list>
#include <vector>

using namespace std;

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

        void dfs();

        void dfs_visit(Vertex v, vector<int> &cor, vector<int> &pi, 
                        vector<int> &d, vector<int> &f, int &tempo);
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

void DigraphAL::dfs(){
    vector<int> cor(num_vertex);            // Vetor que guarda as condições de visita de cada vértice
    vector<int> predecessor(num_vertex);    // Vetor que guarda os predecessores de cada vértice
    vector<int> descoberta(num_vertex);     // Armazena o tempo de descoberta
    vector<int> termino(num_vertex);        // Armazena o tempo de término

    for (int i = 0; i < num_vertex; i++){
        cor[i] = -1;
        predecessor[i] = -1;
    }

    int tempo = 0;

    for(int i = 0; i < num_vertex; i++){
        if(cor[i] == -1){
            dfs_visit(i, cor, predecessor, descoberta, termino, tempo);
        }
    }
}

void DigraphAL::dfs_visit(Vertex v, vector<int> &cor, vector<int> &pi, vector<int> &d, vector<int> &f, int &tempo){
    tempo = tempo + 1;
    d[v] = tempo;
    cor[v] = 0;

    for(Vertex u : adj[v]){
        if(cor[u] == -1){
            pi[u] = v;
            dfs_visit(u, cor, pi, d, f, tempo);
        }
    }

    cor[v] = 1;
    tempo = tempo + 1;
    f[v] = tempo;
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

    g.dfs();

    return 0;
}