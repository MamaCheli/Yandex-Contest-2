#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>

typedef uint64_t vertex;
typedef uint64_t dist_t;

const int INF = 1000000000;

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

const int delta_x[] = {-2, -2, -1, 1, 2,  2,  1, -1};
const int delta_y[] = {-1,  1,  2, 2, 1, -1, -2, -2};

bool InsideGraph(vertex n, vertex x, vertex y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}



void HorsePath(vertex N, vertex start_x, vertex start_y, vertex finish_x, vertex finish_y) {
    std::vector<std::vector<dist_t>> dist(N);
    std::vector<std::vector<std::pair<vertex, vertex>>> pr(N);
    std::queue<std::pair<vertex, vertex> > q;
    for(int i = 0; i < N; i++) {
        dist[i].resize(N);
        pr[i].resize(N);
        for(int j = 0; j < N; j++) {
            dist[i][j] = INF;
            pr[i][j] = {-1, -1};
        }
    }
    dist[start_x][start_y] = 0;
    q.push({start_x, start_y});

    while(!q.empty()) {
        std::pair<vertex, vertex> pn = q.front();
        q.pop();
        for(int i = 0; i < 8; i++) {
            vertex Tx = pn.first + delta_x[i];
            vertex Ty = pn.second + delta_y[i];
            if(InsideGraph(N, Tx, Ty)) {
                if(dist[Tx][Ty] > dist[pn.first][pn.second] + 1) {
                    dist[Tx][Ty] = dist[pn.first][pn.second] + 1;
                    q.push({Tx, Ty});
                    pr[Tx][Ty] = {pn.first, pn.second};
                }
            }
        }
    }

    std::cout << dist[finish_x][finish_y] << std::endl;
    std::vector<std::pair<vertex, vertex>> path;
    while(start_x != finish_x || start_y != finish_y) {
        path.push_back({finish_x, finish_y});
        vertex x = pr[finish_x][finish_y].first;
        vertex y = pr[finish_x][finish_y].second;
        finish_x = x;
        finish_y = y;
    }
    path.push_back({start_x, start_y});

    for(int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i].first + 1 << " " << path[i].second + 1 << std::endl;
    }
}

int main() {
    vertex N;
    vertex start_x, start_y, finish_x, finish_y;
    std::cin >> N;
    std::cin >> start_x >> start_y >> finish_x >> finish_y;
    start_x--;
    start_y--;
    finish_x--;
    finish_y--;

    HorsePath(N, start_x, start_y, finish_x, finish_y);
    return 0;
}
