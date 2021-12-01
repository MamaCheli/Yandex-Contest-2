#include <iostream>
#include <vector>
#include <queue>

enum edge {
    NO_EDGE = 0,
    IS_EDGE = 1
};

const int64_t INF = 1e9;

typedef uint64_t Vertex;
typedef int64_t dist_t;

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

    std::vector<std::vector<Vertex>> list;

public:

    GraphList(const Vertex& num_vertex) {
        num_vertex_ = num_vertex;
        list.resize(num_vertex_);
    }

    std::vector<Vertex> GetNeighbors(const Vertex& v) const override {
        return list.at(v);
    }

    void AddEdge(const Vertex& u, const Vertex& v) override {
        if (u == v) {
            return;
        }
        list[u].push_back(v);
    }
};

class GraphMatrix : public Graph {

    std::vector<std::vector<Vertex>> matrix;

public:
    GraphMatrix(const Vertex& num_vertex) {
        for (Vertex i = 0; i < num_vertex; i++) {
            std::vector<Vertex> tmp(num_vertex, NO_EDGE);
            matrix.push_back(tmp);
        }
        num_vertex_ = num_vertex;
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
        matrix[u][v] = 1;
    }
};

std::vector<Vertex> DigitGetNeighbors(Vertex v) {
    std::vector<Vertex> answer;
    if (v / 1000 < 9) {
        answer.push_back(v + 1000);

    }
    if (v % 10 != 1) {
        answer.push_back(v - 1);
    }
    answer.push_back((v % 10) * 1000 + (v / 1000) * 100 + (v / 100 % 10) * 10 + (v / 10) % 10);
    answer.push_back((v % 10) * 10 + (v / 1000) + (v / 100 % 10) * 1000 + (v / 10 % 10) * 100);

    return answer;
}

std::vector<Vertex> DigitShortPath(const Graph& G, Vertex source, Vertex destination) {
    std::vector<dist_t> dist(G.GetNumVertex(), INF);
    std::vector<Vertex> parent(G.GetNumVertex());
    std::queue<Vertex> q;
    q.push(source);
    dist[source] = 0;

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        auto neighbors = DigitGetNeighbors(v);
        for (auto& u: neighbors) {
            if (dist[u] > dist[v] + 1) {
                q.push(u);
                dist[u] = dist[v] + 1;
                parent[u] = v;
            }
        }
    }

    std::vector<Vertex> answer;
    if (dist[destination] == INF) {
        return answer;
    }
    for (Vertex v = destination; v != source; v = parent[v]) {
        answer.push_back(v);
    }
    answer.push_back(source);
    for (Vertex i = 0; i < answer.size() / 2; i++) {
        std::swap(answer[i], answer[answer.size() - 1 - i]);
    }

    return answer;
}

int main() {
    Vertex start, finish;
    std::cin >> start >> finish;
    GraphList g(10000);

    std::vector<Vertex> ans = DigitShortPath(g, start, finish);
    std::cout << ans.size() << std::endl;
    for (auto& dig: ans) {
        std::cout << dig << std::endl;
    }
    return 0;
}
