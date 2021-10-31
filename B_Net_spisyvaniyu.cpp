#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

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

void DFS(const Graph& G, std::vector<vertex>& color, const vertex& v, int cl) {
    color[v] = cl;
    auto neighbors = G.GetNeighbors(v);
    for (auto &u: neighbors) {
        if(color[u] == color[v]) {
            std::cout << "NO";
            exit(0);
        }
        if(color[u] == -1) {
            DFS(G, color, u, cl ^ 1);
        }
    }
}

int main() {
    vertex num_ver, num_edg;
    std::cin >> num_ver >> num_edg;

    GraphList G(num_ver);
    for (uint64_t i = 0; i < num_edg; i++) {
        vertex u, v;
        std::cin >> u >> v;
        u--;
        v--;
        G.AddEdge(u, v);
    }

    std::vector<vertex> color(num_ver, -1);
    for(vertex i = 0; i < num_ver; i++) {
        if(color[i] == -1) {
            DFS(G, color, i, 0);
        }
    }
    std::cout << "YES";
    return 0;
}
