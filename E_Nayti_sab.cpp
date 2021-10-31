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

const int INF = 1000000000;

bool check(int n, int m, int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int delta_x[] = {0, 0, -1, 1};
int delta_y[] = {-1, 1, 0, 0};

void SubWay (int n, int m, std::vector<std::vector<dist_t>> dist, std::queue<std::pair<int,int>> q) {
    while(!q.empty()) {
        std::pair<int,int> pn = q.front();
        q.pop();
        for(int i = 0; i < 4; i++) {
            int tx = pn.first + delta_x[i];
            int ty = pn.second + delta_y[i];
            if(check(n, m, tx, ty)) {
                if(dist[tx][ty] > dist[pn.first][pn.second] + 1) {
                    dist[tx][ty] = dist[pn.first][pn.second] + 1;
                    q.push({tx, ty});
                }
            }
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cout << dist[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<vertex>> crossroad(n);
    std::vector<std::vector<dist_t>> dist(n);
    std::queue<std::pair<int,int>> q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            dist[i].resize(m);
            crossroad[i].resize(m);
            dist[i][j] = INF;
            std::cin >> crossroad[i][j];
            if(crossroad[i][j] == 1) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    SubWay (n, m, dist, q);
    return 0;
}
