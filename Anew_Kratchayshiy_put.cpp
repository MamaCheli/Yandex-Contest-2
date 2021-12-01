#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>

const int64_t INF = 1000000000;

typedef uint64_t Vertex;
typedef int64_t DistT;

enum edge {
    NO_EDGE = 0,
    IS_EDGE = 1
};

class Graph {
protected:

    Vertex num_vertex_ = 0;

public:

    Vertex GetNumVertex() const {
        return num_vertex_;
    }

    virtual std::vector<Vertex> GetNeighbors(const Vertex& v) const = 0;

    virtual void AddEdge(const Vertex& a, const Vertex& b) = 0;
};

class GraphList : public Graph {

    std::unordered_map<Vertex, std::vector<Vertex>> list;

public:

    GraphList(const Vertex& num_vertex) {
        for (Vertex i = 0; i < num_vertex; i++) {
            std::vector<Vertex> tmp;
            list[i] = tmp;
        }
        num_vertex_ = num_vertex;
    }

    std::vector<Vertex> GetNeighbors(const Vertex& v) const override {
        return list.at(v);
    }

    void AddEdge(const Vertex& u, const Vertex& v) override {
        if (u == v) {
            return;
        }
        list[u].push_back(v);
        list[v].push_back(u);
    }
};


class GraphMatrix : public Graph {

    std::vector<std::vector<Vertex>> matrix;

public:
    GraphMatrix(const Vertex& num_vertex) {
        for (Vertex i = 0; i < num_vertex; i++) {
            std::vector<Vertex> tmp(num_vertex, 0);
            matrix.push_back(tmp);
        }
        num_vertex_ = num_vertex;
    }

    std::vector<Vertex> GetNeighbors(const Vertex& v) const override {
        std::vector<Vertex> neighbors;
        for (Vertex i = 0; i < GetNumVertex(); i++) {
            if (matrix[v][i] == 1) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    void AddEdge(const Vertex& u, const Vertex& v) override {
        if (u == v) {
            return;
        }
        matrix[u][v] = IS_EDGE;
        matrix[v][u] = IS_EDGE;
    }
};

void PrintDistAndPath(std::vector<DistT>& dist, std::vector<Vertex>& parent, const Vertex& source, const Vertex& destination) {
    if (dist[destination] == INF) {
        std::cout << -1;
        return;
    }
    std::cout << dist[destination] << "\n";

    std::vector<Vertex> path;
    Vertex v = destination;
    while(v != source) {
        path.push_back(v);
        v = parent[v];
    }
    path.push_back(source);

    for(Vertex i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] + 1 << " ";
    }
}

void BFS(const Graph& G, const Vertex& source, const Vertex& destination) {
    std::vector<DistT> dist(G.GetNumVertex(), INF);
    std::vector<Vertex> parent(G.GetNumVertex(), -1);
    std::queue<Vertex> q;
    q.push(source);
    dist[source] = 0;
    while (!q.empty()) {
        Vertex v = q.front();
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

    PrintDistAndPath(dist, parent, source, destination);
}

int main() {
    Vertex num_ver, num_edg;
    std::cin >> num_ver >> num_edg;
    Vertex start_ver, finish_ver;
    std::cin >> start_ver >> finish_ver;
    start_ver--;
    finish_ver--;

    GraphList G(num_ver);
    for (Vertex i = 0; i < num_edg; i++) {
        Vertex u, v;
        std::cin >> u >> v;
        u--;
        v--;
        G.AddEdge(u, v);
    }

    BFS(G, start_ver, finish_ver);
    return 0;
}
