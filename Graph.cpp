//ID: 208018028, Mail: ronimordechai70@gmail.com
#include "Graph.hpp"
#include <iostream> // For printGraph output

namespace ariel {
    Graph::Graph() : adjMatrix(0, std::vector<int>(0)) {} // Default constructor
    Graph::Graph(const std::vector<std::vector<int>>& matrix) : adjMatrix(matrix) {}

    void Graph::loadGraph(const std::vector<std::vector<int>>& newMatrix) {
        adjMatrix = newMatrix;
    }

    void Graph::printGraph() const {
        size_t vertices = adjMatrix.size();
        int edges = 0;
        for (const auto& row : adjMatrix) {
            for (int value : row) {
                if (value > 0) {
                    edges++;
                }
            }
        }
        std::cout << "Graph with " << vertices << " vertices and " << edges << " edges.\n";
    }

    const std::vector<std::vector<int>>& Graph::getAdjMatrix() const {
        return adjMatrix;
    }
}
