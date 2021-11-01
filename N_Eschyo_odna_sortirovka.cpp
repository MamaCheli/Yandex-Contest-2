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
    std::vector<vertex> neighbor;
    vertex color = 0;
};

bool Hinge(vertex v, std::vector<Vertex>& graph, std::vector <vertex>& ans) {
    graph[v].color = 1;

    for (int i = 0; i < graph[v].neighbor.size(); i++) {
        int j = graph[v].neighbor[i];

        if(graph[j].color == 0) {
            if (Hinge(j, graph, ans)) {
                return true;
            }
        } else if (graph[j].color == 1) {
            return true;
        }
    }
    ans.push_back(v);
    graph[v].color = 2;
    return false;
}

void Sort(int ind, std::vector<Vertex> &graph, std::vector <vertex> &ans) {
    for (int i = 0; i < ind; i++) {
        graph[i].color = 0;
    }
    ans.clear();
    for (int i = 0; i < ind; ++i) {
        if(graph[i].color ==0) {
            if (Hinge(i, graph, ans)) {
                std::cout << "-1\n";
                exit(0);
            }
        }
    }
    for(int i = 0; i < ans.size() / 2; ++i) {
        std::swap(ans[i], ans[ans.size() - 1 - i]);
    }
}

int main() {
    vertex n = 0;
    vertex m = 0;
    std::cin >> n >> m;
    std::vector <vertex> ans;
    std::vector<Vertex> graph(n);

    vertex x = 0;
    vertex y = 0;
    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y;
        x--;
        y--;
        bool ok = false;
        if (!ok) {
            graph[x].neighbor.push_back(y);
        }
    }
    Sort(n, graph, ans);
    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] + 1 << " ";
    }
}
