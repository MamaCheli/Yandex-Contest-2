#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

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
    }
};

void BFS (std::string start_str, std::string finish_str) {
    std::unordered_map<std::string, int> dist;
    std::unordered_map<std::string, std::string> parents;
    std::queue<std::string> q;

    dist[start_str] = 0;
    q.push(start_str);
    while(!q.empty()) {
        std::string tmp = q.front();
        q.pop();
        std::string next = tmp;
        for(int i = 0; i < 3; i++) {
            std::swap(next[i], next[i + 1]);
        }

        if(!dist.count(next) || dist[next] > dist[tmp] + 1) {
            dist[next] = dist[tmp] + 1;
            parents[next] = tmp;
            q.push(next);
        }

        next = tmp;

        for(int i = 3; i > 0; i--) {
            std::swap(next[i], next[i - 1]);
        }

        if(!dist.count(next) || dist[next] > dist[tmp] + 1) {
            dist[next] = dist[tmp] + 1;
            parents[next] = tmp;
            q.push(next);
        }

        next = tmp;
        if(next[0] - '0' < 9) {
            next[0]++;
            if(!dist.count(next) || dist[next] > dist[tmp] + 1) {
                dist[next] = dist[tmp] + 1;
                parents[next] = tmp;
                q.push(next);
            }
        }
        next = tmp;
        if(next[3] - '0' > 1) {
            next[3]--;
            if(!dist.count(next) || dist[next] > dist[tmp] + 1) {
                dist[next] = dist[tmp] + 1;
                parents[next] = tmp;
                q.push(next);
            }
        }
    }

    std::vector<std::string> ans;
    while (start_str != finish_str) {
        ans.push_back(finish_str);
        finish_str = parents[finish_str];
    }
    ans.push_back(start_str);
    std::cout << ans.size() << std::endl;
    for(int i = ans.size() - 1; i >= 0; i--) {
        std::cout << ans[i] << std::endl;
    }
}

int main() {
    std::string start_str, finish_str;
    std::cin >> start_str >> finish_str;
    BFS(start_str, finish_str);
    return 0;
}
