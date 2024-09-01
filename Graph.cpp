
#include "Graph.hpp"
#include <iostream>
#include <stack>

Graph::Graph(int vertices) : V(vertices), adj(vertices) {}

void Graph::addEdge(int u, int v)
{
    adj[u][v]++;
    if (u != v)
    {
        adj[v][u]++;
    }
}

bool Graph::existsEdge(int u, int v) const
{
    if (u < 0 || u >= V || v < 0 || v >= V)
    {
        return false; // Invalid vertex
    }
    return adj[u].find(v) != adj[u].end();
}

int Graph::getEdgeCount(int u, int v) const
{
    if (!existsEdge(u, v))
    {
        return 0;
    }
    return adj[u].at(v);
}

bool Graph::isEulerianCircuit() const
{
    for (const auto &edges : adj)
    {
        int degree = 0;
        for (const auto &[_, count] : edges)
        {
            degree += count;
        }
        if (degree % 2 != 0)
        {
            return false;
        }
    }
    return isConnected();
}

void Graph::dfs(int v, std::vector<bool> &visited) const
{
    visited[v] = true;
    for (const auto &[neighbor, _] : adj[v])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, visited);
        }
    }
}

bool Graph::isConnected() const
{
    std::vector<bool> visited(V, false);
    int i;
    for (i = 0; i < V; i++)
    {
        if (!adj[i].empty())
        {
            break;
        }
    }
    if (i == V)
        return true;
    dfs(i, visited);
    for (i = 0; i < V; i++)
    {
        if (!visited[i] && !adj[i].empty())
        {
            return false;
        }
    }
    return true;
}

std::vector<int> Graph::findEulerianCircuit() const
{
    if (!isEulerianCircuit())
    {
        return {};
    }

    std::vector<std::unordered_map<int, int>> adj_copy = adj;
    std::vector<int> circuit;
    std::stack<int> stack;
    int current = 0;

    stack.push(current);
    while (!stack.empty())
    {
        if (!adj_copy[current].empty())
        {
            stack.push(current);
            int next = adj_copy[current].begin()->first;
            if (--adj_copy[current][next] == 0)
            {
                adj_copy[current].erase(next);
            }
            if (current != next)
            {
                if (--adj_copy[next][current] == 0)
                {
                    adj_copy[next].erase(current);
                }
            }
            current = next;
        }
        else
        {
            circuit.push_back(current);
            current = stack.top();
            stack.pop();
        }
    }

    return circuit;
}

void Graph::printGraph() const
{
    for (int i = 0; i < V; i++)
    {
        std::cout << i << ": ";
        for (const auto &[neighbor, count] : adj[i])
        {
            for (int j = 0; j < count; j++)
            {
                std::cout << neighbor << " ";
            }
        }
        std::cout << std::endl;
    }
}
