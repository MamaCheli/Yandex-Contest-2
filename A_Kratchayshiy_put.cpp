#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>

const int INF = 1000000000;

typedef uint64_t vertex;
typedef uint64_t dist_t;

class Graph {
protected:

    vertex num_vertex = 0;

public:

    vertex GetNumVertex() const {
        return num_vertex;
    }

    virtual std::vector<vertex> GetNeighbors(const vertex& v) const = 0;

    virtual void AddEdge(const vertex& a, const vertex& b) = 0;
};

class GraphList : public Graph {

    std::unordered_map<vertex, std::vector<vertex>> list;

public:

    GraphList(const vertex& quantity) {
        for (vertex i = 0; i < quantity; i++) {
            std::vector<vertex> tmp;
            list[i] = tmp;
        }
        num_vertex = quantity;
    }

    std::vector<vertex> GetNeighbors(const vertex& v) const override {
        return list.at(v);
    }

    void AddEdge(const vertex& u, const vertex& v) override {
        if (u == v) {
            return;
        }
        list[u].push_back(v);
        list[v].push_back(u);
    }
};

class GraphMatrix : public Graph {

    std::vector<std::vector<vertex>> matrix;

public:
    GraphMatrix(const vertex& quantity) {
        for (vertex i = 0; i < quantity; i++) {
            std::vector<vertex> tmp(quantity, 0);
            matrix.push_back(tmp);
        }
        num_vertex = quantity;
    }

    std::vector<vertex> GetNeighbors(const vertex& v) const override {
        std::vector<vertex> neighbors;
        for (vertex i = 0; i < GetNumVertex(); i++) {
            if (matrix[v][i] == 1) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    void AddEdge(const vertex& u, const vertex& v) override {
        if (u == v) {
            return;
        }
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }
};

void BFS(const Graph& G, const vertex& source, const vertex& destination) {
    std::vector<dist_t> dist(G.GetNumVertex(), INF);
    std::vector<vertex> parent(G.GetNumVertex(), -1);
    std::queue<vertex> q;
    q.push(source);
    dist[source] = 0;
    while (!q.empty()) {
        vertex v = q.front();
        q.pop();
        auto neighbors = G.GetNeighbors(v);
        for (auto &u: neighbors) {
            if (dist[u] > dist[v] + 1) {
                q.push(u);
                dist[u] = dist[v] + 1;
                parent[u] = v;
            }
        }
    }
    if (dist[destination] == INF) {
        std::cout << -1;
        return;
    }
    std::cout << dist[destination] << "\n";

    std::vector<int> path;
    vertex v = destination;
    while(v != source) {
        path.push_back(v);
        v = parent[v];
    }
    path.push_back(source);

    for(int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] + 1 << " ";
    }
}

int main() {
    vertex num_ver, num_edg;
    std::cin >> num_ver >> num_edg;
    vertex start_ver, finish_ver;
    std::cin >> start_ver >> finish_ver;
    start_ver--;
    finish_ver--;

    GraphList G(num_ver);
    for (uint64_t i = 0; i < num_edg; i++) {
        vertex u, v;
        std::cin >> u >> v;
        u--;
        v--;
        G.AddEdge(u, v);
    }

    BFS(G, start_ver, finish_ver);
    return 0;
}
