#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>

class Graph
{
private:
    int V;
    std::vector<std::unordered_map<int, int>> adj; // vertex -> (neighbor, count)

public:
    Graph(int vertices);
    void addEdge(int u, int v);
    bool existsEdge(int u, int v) const;
    bool isEulerianCircuit() const;
    bool isConnected() const;
    std::vector<int> findEulerianCircuit() const;
    void printGraph() const;
    int getEdgeCount(int u, int v) const;

private:
    void dfs(int v, std::vector<bool> &visited) const;
};

#endif // GRAPH_HPP
