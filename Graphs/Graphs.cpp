#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

class Graph {
    int V; // Número de vértices
    vector<vector<pair<int, int>>> adj; // Lista de adyacencia

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    void dijkstra(int src);
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w); // Si el grafo es no dirigido
}

void Graph::dijkstra(int src) {
    // Cola de prioridad para seleccionar el vértice con la distancia mínima
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(V, INT_MAX); // Vector de distancias inicializado a infinito

    pq.emplace(0, src);
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            // Si se encuentra una distancia más corta a v a través de u
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    // Imprimir las distancias desde el nodo fuente
    cout << "Distancias desde el nodo fuente " << src << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "Nodo " << i << " : " << dist[i] << "\n";
    }
}

int main() {
    int V = 5;
    Graph g(V);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 0, 7);
    g.addEdge(4, 2, 3);

    g.dijkstra(0);

    return 0;
}