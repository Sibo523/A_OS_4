
#include <iostream>
#include <random>
#include <unistd.h>
#include "Graph.hpp"

void generateRandomGraph(Graph &g, int numVertices, int numEdges, unsigned seed)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0, numVertices - 1);

    for (int i = 0; i < numEdges; ++i)
    {
        int u = dis(gen);
        int v = dis(gen);
        if (g.existsEdge(u, v) || g.existsEdge(v, u) || u == v)
        {
            i--;
            continue;
        }
        std::cout << u << " " << v << std::endl;
        g.addEdge(u, v);
    }

    std::cout << "Generated graph structure:" << std::endl;
    g.printGraph();
}

int main(int argc, char *argv[])
{
    int numVertices = 0, numEdges = 0;
    unsigned seed = 0;
    int opt;

    while ((opt = getopt(argc, argv, "v:e:s:")) != -1)
    {
        switch (opt)
        {
        case 'v':
            numVertices = std::stoi(optarg);
            break;
        case 'e':
            numEdges = std::stoi(optarg);
            break;
        case 's':
            seed = std::stoul(optarg);
            break;
        default:
            std::cerr << "Usage: " << argv[0] << " -v <vertices> -e <edges> -s <seed>" << std::endl;
            return 1;
        }
    }

    if (numVertices <= 0 || numEdges < numVertices)
    {
        std::cerr << "Invalid number of vertices or edges. Ensure vertices > 0 and edges >= vertices." << std::endl;
        return 1;
    }

    Graph g(numVertices);
    generateRandomGraph(g, numVertices, numEdges, seed);

    std::cout << "Generated random graph with " << numVertices << " vertices and " << numEdges << " edges." << std::endl;

    if (g.isEulerianCircuit())
    {
        std::cout << "The graph contains an Eulerian circuit." << std::endl;
        std::vector<int> circuit = g.findEulerianCircuit();
        std::cout << "Eulerian circuit: ";
        for (int v : circuit)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "The graph does not contain an Eulerian circuit." << std::endl;
    }

    return 0;
}
