#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>

typedef uint64_t vertex;
typedef uint64_t dist_t;

class Graph {
protected:

    vertex num_vertex = 0;

public:

    std::vector<int> color;

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

struct Vertex {
    std::vector<vertex> parent;
    vertex color = 0;
};

void dfs(vertex v, int ind, std::vector<Vertex> &graph, std::vector<std::vector<vertex>> &way) {
    graph[v].color = 2;
    way[ind].push_back(v);
    for(int i = 0; i < graph[v].parent.size(); i++) {
        if(graph[graph[v].parent[i]].color == 0) {
          dfs(graph[v].parent[i], ind, graph, way);
      }
    }
}

int main() {
    vertex n;
    vertex m;
    vertex cycle = 0;
    std::cin >> n >> m;
    std::vector<Vertex> graph(n + 1);
    std::vector<std::vector<vertex>> way(0, std::vector<vertex>(0));
    std::vector<vertex> vec;
    for(int i = 0; i < m; i++) {
        vertex x;
        vertex y;
        std::cin >> x >> y;
        graph[x].parent.push_back(y);
        graph[y].parent.push_back(x);
    }

    int i = 0;
    for(int ind = 1; ind <= n; ind++) {
        if(graph[ind].color == 0) {
            way.push_back(vec);
            dfs(ind, i, graph, way);
            i++;
        }
    }

    std::cout << i << "\n";
    int k = i;
    for(i = 0; i < k; ++i) {
        std::cout << way[i].size() << "\n";
        for(int j = 0; j < way[i].size(); j++) {
            std::cout << way[i][j] << " ";
        }
        std::cout << "\n";
    }
}
