//ID: 208018028, Mail: ronimordechai70@gmail.com
#include "Graph.hpp"
#include <iostream> // For std::cout

namespace ariel {

    // Default constructor for an empty graph
    Graph::Graph() : adjMatrix(0, std::vector<int>(0)), isUndirected(true) {}

    // Constructor with validation
    Graph::Graph(const std::vector<std::vector<int>>& matrix) {
        validateMatrix(matrix); // Validate that the matrix is square
        adjMatrix = matrix; // Assign the matrix to the graph
        isUndirected = isSymmetric(matrix); // Determine if the graph is undirected
    }

    // Validate if the matrix is square, throws an exception if not
    void Graph::validateMatrix(const std::vector<std::vector<int>>& matrix) const {
        size_t rowCount = matrix.size();
        for (const auto& row : matrix) {
            if (row.size() != rowCount) { // Ensure each row has the same length
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
    }

    // Check if the adjacency matrix is symmetric
    bool Graph::isSymmetric(const std::vector<std::vector<int>>& matrix) const {
        size_t size = matrix.size();
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                if (matrix[i][j] != matrix[j][i]) { // Not symmetric
                    return false;
                }
            }
        }
        return true; // Symmetric
    }

    // Load a new graph with validation and determine if it is undirected
    void Graph::loadGraph(const std::vector<std::vector<int>>& newMatrix) {
        validateMatrix(newMatrix); // Ensure the matrix is square
        adjMatrix = newMatrix; // If valid, assign the new matrix
        isUndirected = isSymmetric(newMatrix); // Determine if the graph is undirected
    }

    // Method to determine if the graph is undirected
    bool Graph::isUndirectedGraph() const {
        return isUndirected; // Return the status of the graph
    }

    // Corrected printGraph function for undirected graphs
    void Graph::printGraph() const {
        size_t vertices = adjMatrix.size();
        int edges = 0;

        if (isUndirected) {
            // Count only unique edges (upper triangle)
            for (size_t i = 0; i < vertices; i++) {
                for (size_t j = i + 1; j < vertices; j++) { // Only consider edges in the upper triangle
                    if (adjMatrix[i][j] > 0) { // If there's an edge
                        edges++;
                    }
                }
            }
        } else {
            // Count all edges for directed graphs
            for (const auto& row : adjMatrix) {
                for (int value : row) {
                    if (value > 0) { // Consider any positive value as an edge
                        edges++;
                    }
                }
            }
        }

        std::cout << "Graph with " << vertices << " vertices and " << edges << " edges." << std::endl;
    }

    // Implementation of getAdjMatrix with class scope
    const std::vector<std::vector<int>>& Graph::getAdjMatrix() const {
        return adjMatrix; // Return the adjacency matrix
    }

}


