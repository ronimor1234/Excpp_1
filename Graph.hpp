//ID: 208018028, Mail: ronimordechai70@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel {
    class Graph {
    private:
        std::vector<std::vector<int>> adjMatrix;
    public:
        Graph(); // Default constructor
        Graph(const std::vector<std::vector<int>>& matrix);

        // Load a new adjacency matrix into the graph
        void loadGraph(const std::vector<std::vector<int>>& newMatrix);

        // Print information about the graph
        void printGraph() const;

        const std::vector<std::vector<int>>& getAdjMatrix() const;
    };
}

#endif



