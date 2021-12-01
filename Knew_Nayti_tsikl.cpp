#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <queue>

enum edge {
    NO_EDGE = 0,
    IS_EDGE = 1
};

enum color {
    BLACK = 0,
    GREY = 1,
    WHITE = 2
};

typedef uint64_t VertexT;
typedef int64_t DistT;

class Graph {
    VertexT num_vertex_ = 0;

    struct vertex {
        std::vector<VertexT> parent;
        VertexT color = BLACK;
    };
    std::vector<vertex> List;

public:

    Graph(VertexT num_vertex) {
        num_vertex_ = num_vertex;
        List.resize(num_vertex_ + 1);
    }

    VertexT GetNumVertex() const {
        return num_vertex_;
    }

    std::vector<VertexT> GetNeighbors(const VertexT& v);

    void AddEdge(const VertexT& a, const VertexT& b) {
        List[a].parent.push_back(b);
    }

    void DFS(VertexT v, bool &cycle, std::vector<VertexT> &path) {
        if(cycle) {
            return;
        }
        else {
            List[v].color = GREY;
            path.push_back(v);
            for(VertexT i = 0; i < List[v].parent.size(); i++) {
                if(List[List[v].parent[i]].color == GREY) {
                    cycle = true;
                    std::cout << "YES\n";
                    VertexT k = 0;
                    while(path[k] != List[v].parent[i]){
                        k++;
                    }
                    for(;k < path.size(); k++) {
                        std::cout << path[k] << " ";
                    }
                    return;
                }
                else {
                    if(List[List[v].parent[i]].color == BLACK) {
                        DFS(List[v].parent[i], cycle, path);
                    }
                }

                if(cycle) {
                    return;
                }
            }
            List[v].color = WHITE;
            path.pop_back();
        }
    }
};

int main() {
    VertexT num_ver;
    VertexT num_edge;
    std::cin >> num_ver >> num_edge;

    Graph g(num_ver);
    for(VertexT i = 0; i < num_edge; i++) {
        VertexT first;
        VertexT second;
        std::cin >> first >> second;
        g.AddEdge(first, second);
    }

    bool cycle = false;
    std::vector<VertexT> path;
    for(VertexT i = 1; i <= num_ver; i++) {
        g.DFS(i, cycle, path);
    }

    if(!cycle) {
        std::cout << "NO";
    }
    return 0;
}
