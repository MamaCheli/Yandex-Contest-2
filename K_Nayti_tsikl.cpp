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

void dfs(int v, int &cycle, std::vector<Vertex> &graph, std::vector<int> &wayl) {
    if(cycle == 1) {
        return;
    } else {
        graph[v].color = 1;
        wayl.push_back(v);
        for(int i = 0; i < graph[v].parent.size(); i++) {
            if(graph[graph[v].parent[i]].color == 1) {
                cycle = 1;
                std::cout << "YES\n";
                int k = 0;
                while(wayl[k] != graph[v].parent[i]){
                    k++;
                }
                for(;k < wayl.size(); ++k) {
                    std::cout << wayl[k] << " ";
                }
                return;
            } else {
                if(graph[graph[v].parent[i]].color == 0) {
                    dfs(graph[v].parent[i], cycle, graph, wayl);
                }
            }
            if(cycle == 1) {
                return;
            }
        }
        graph[v].color = 2;
        wayl.pop_back();
    }
}

int main() {
    int n;
    int m;
    int cycle = 0;
    std::cin >> n >> m;
    std::vector<Vertex> graph(n + 1);
    for(int i = 0; i < m; ++i) {
        int x;
        int y;
        std::cin >> x >> y;
        graph[x].parent.push_back(y);
    }
    std::vector<int> wayl;
    for(int ind = 1; ind <= n; ind++) {
        dfs(ind, cycle, graph, wayl);
    }
    if(cycle == 0) {
        std::cout << "NO";
    }
}
