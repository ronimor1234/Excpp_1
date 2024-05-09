//ID: 208018028, Mail: ronimordechai70@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stdexcept> // For std::invalid_argument

namespace ariel {
    class Graph {
    private:
        std::vector<std::vector<int>> adjMatrix;
        bool isUndirected; // New property to store if the graph is undirected

        // Private method to ensure the adjacency matrix is square
        static void validateMatrix(const std::vector<std::vector<int>>& matrix) ;
    
    public:
        //method to check if the adjacency matrix is symmetric
        static bool isSymmetric(const std::vector<std::vector<int>>& matrix) ;

    
        // Default constructor
        Graph(); 
        
        // Constructor with an initial adjacency matrix
        Graph(const std::vector<std::vector<int>>& matrix);

        // Method to load a new graph with validation
        void loadGraph(const std::vector<std::vector<int>>& newMatrix);

        // Method to determine if the graph is undirected
        bool isUndirectedGraph() const;

        // Print information about the graph
        void printGraph() const;

        // Get the adjacency matrix
        const std::vector<std::vector<int>>& getAdjMatrix() const;
    };
}

#endif // GRAPH_HPP

