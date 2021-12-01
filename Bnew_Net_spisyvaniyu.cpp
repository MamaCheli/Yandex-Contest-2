#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

typedef uint64_t Vertex;
typedef int64_t DistT;

enum edge {
    NO_EDGE = 0,
    IS_EDGE = 1
};

enum color {
    BLACK = -1,
    GREY = 0,
    WHITE = 1
};

struct Graph {
    Vertex num_vertex_ = 0;

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
        num_vertex_ = num_vertex;
        for (Vertex i = 0; i < num_vertex_; i++) {
            std::vector<Vertex> tmp;
            list[i] = tmp;
        }
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

    bool IsBipartite(const Graph&);
};

class GraphMatrix : public Graph {

    std::vector<std::vector<Vertex>> matrix;

public:
    GraphMatrix(const Vertex& quantity) {
        for (Vertex i = 0; i < quantity; i++) {
            std::vector<Vertex> tmp(quantity, NO_EDGE);
            matrix.push_back(tmp);
        }
        num_vertex_ = quantity;
    }

    std::vector<Vertex> GetNeighbors(const Vertex& v) const override {
        std::vector<Vertex> neighbors;
        for (Vertex i = 0; i < GetNumVertex(); i++) {
            if (matrix[v][i] == IS_EDGE) {
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

void DFS(const Graph& G, std::vector<Vertex>& color, const Vertex& v, int part_col, bool& bipart) {
    color[v] = part_col;
    auto neighbors = G.GetNeighbors(v);
    for (auto &u: neighbors) {
        if(color[u] == color[v]) {
            bipart = false;
            return;
        }
        if(color[u] == BLACK) {
            DFS(G, color, u, part_col ^ 1, bipart);
        }
    }
}

bool IsBipartite(const Graph& G) {
    bool bipart = true;
    std::vector<Vertex> color(G.num_vertex_, BLACK);
    for(Vertex i = 0; i < G.num_vertex_; i++) {
        if(color[i] == BLACK) {
            DFS(G, color, i, GREY, bipart);
            if(!bipart) {
                return bipart;
            }
        }
    }
    return bipart;
}

int main() {
    Vertex num_ver, num_edg;
    std::cin >> num_ver >> num_edg;

    GraphList G(num_ver);
    for (Vertex i = 0; i < num_edg; i++) {
        Vertex u, v;
        std::cin >> u >> v;
        u--;
        v--;
        G.AddEdge(u, v);
    }

    if (IsBipartite(G)) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
    return 0;
}
