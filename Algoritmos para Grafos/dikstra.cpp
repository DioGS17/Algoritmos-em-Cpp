#include <iostream>
#include <list>
#include <vector>
#include <limits>

using namespace std;

template<typename T>
class MinHeap{
private:
    T heap[1000];
    unsigned int tam_heap = 0;

public:
    T *get_heap(){ return heap; }
    unsigned int get_tam_heap(){ return tam_heap; }

    unsigned int left(int i){ return i*2; }
    unsigned int right(int i){ return i*2+1; }

    bool isEmpty(){
        if(tam_heap == 0){
            return true;
        }
        return false;
    }

    T minimal(){ return heap[0]; }

    void insert(T i){
        heap[tam_heap++] = i;
        build_min_heap();
    }

    void min_heapfy(int i){
        int menor;

        int l = left(i);
        int r = right(i); 

        if (l <= tam_heap && heap[l-1] < heap[i-1]){
            menor = l;
        }else{
            menor = i;
        }

        if (r <= tam_heap && heap[r-1] <  heap[menor-1]){
            menor = r;
        }

        if (menor != i){
            T temp = heap[i-1];
            heap[i-1] = heap[menor-1];
            heap[menor-1] = temp;
            min_heapfy(menor);
        }
    }

    void build_min_heap(){
        for (int i = tam_heap/2; i > 0; i--){
            min_heapfy(i);
        }
    }

    T extractMin(){
        T min = heap[0];
        heap[0] = heap[(tam_heap--)-1];
        min_heapfy(1);

        return min;
    }
};

typedef unsigned int Vertex;
typedef float Weight;

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

public:
    WeightedGraphAL(unsigned int num_vertice);

    ~WeightedGraphAL();

    int add_edge(Vertex u, Vertex v, Weight w);

    unsigned int get_num_vertex(){ return num_vertex; }

    unsigned int get_num_edges(){ return num_edges; }

    list<VertexWeightPair> get_adj(Vertex v){ return adj[v]; }

    void dijkstra(Vertex s, Vertex o);
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
    
    VertexWeightPair edge_u(v, w);
    adj[u].push_back(edge_u);
    VertexWeightPair edge_v(u, w);
    adj[v].push_back(edge_v);
    num_edges++;
    return 1;
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

void WeightedGraphAL::dijkstra(Vertex s, Vertex o){
    vector<Weight> distancias(num_vertex);
    vector<int> predecessor(num_vertex);
    MinHeap<Vertex> fila;

    for(unsigned int i = 0; i < num_vertex; i++){
        distancias[i] = numeric_limits<float>::infinity();
        predecessor[i] = -1;
    }
    distancias[s] = 0;
    fila.insert(s);

    while(!fila.isEmpty()){
        Vertex u = fila.extractMin();

        for (VertexWeightPair edge : adj[u]){
            if (distancias[edge.vertex] > distancias[u] + edge.weight){
                distancias[edge.vertex] = distancias[u] + edge.weight;
                predecessor[edge.vertex] = u;
                fila.insert(edge.vertex); 
            }
        }
    }

    cout << "Dikstra - Vertice de origem: "<< s << endl;
    for (int i = 1; i < num_vertex; i++){
        cout << "Distancia de " << s << " ate " << i << ": " << distancias[i] << endl;
    }

    cout << "\n";

    for (int i = 1; i < num_vertex; i++){
        cout << "Predecessor de " << i << ": " << predecessor[i] << endl;
    }

    list<Vertex> caminho;
    caminho.push_front(o);
    Vertex v = o;
    while(v != s){
        v = predecessor[v];
        caminho.push_front(v);
    }

    cout << "\nCaminho minimo do vertice " << s << " ate o " << o << ": ";
    for(auto i : caminho){
        cout << i << " ";
    }
    cout << endl;
}

void display_list(list<VertexWeightPair> lst){
    for(VertexWeightPair vw : lst){
        cout << "(" << vw.vertex << ", " << vw.weight << "), ";
    }
    cout << endl;
}

void display_graph(WeightedGraphAL &g){
    for (int i = 1; i < g.get_num_vertex(); i++){
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

    Vertex i, f;
    cin >> i >> f;

    cout << "\n";
    display_graph(g);

    cout <<"\n================\n"<<endl;

    g.dijkstra(i, f);

    return 0;
}