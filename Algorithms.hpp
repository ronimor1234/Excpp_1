//ID: 208018028, Mail: ronimordechai70@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>

namespace ariel {
    class Algorithms {
    public:
        // Check if a graph is connected
        static bool isConnected(const Graph& g);

        // Find the shortest path between two nodes (start and end)
        static std::string shortestPath(const Graph& g, int start, int end);

        // Check if a graph contains a cycle
        static std::string isContainsCycle(const Graph& g);

        // Determine if a graph is bipartite
        static std::string isBipartite(const Graph& g);

        // Check if a graph contains a negative cycle
        static std::string negativeCycle(const Graph& g);
    };
}

#endif

