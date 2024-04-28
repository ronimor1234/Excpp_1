//ID: 208018028, Mail: ronimordechai70@gmail.com
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <vector> // for std::vector
#include <string> // for std::string
#include <queue> // for std::queue
#include <limits>
#include <functional>
#include <algorithm> // for std::reverse
#include <stdexcept> // for std::out_of_range
#include <sstream> // for std::ostringstream
#include <iostream> // for std::cout
#include <stack>

namespace ariel {

    // Ensure consistent unsigned type for indexing
    using IndexType = std::vector<int>::size_type;
 
    // Helper function for Depth-First Search (DFS)
    void DFS(const std::vector<std::vector<int>>& adj, std::size_t start, std::vector<bool>& visited) {
        std::stack<std::size_t> stack;
        stack.push(start);

        while (!stack.empty()) {
            std::size_t current = stack.top();
            stack.pop();

            if (visited[current]) continue;

            visited[current] = true;

            // Traverse all adjacent vertices
            for (std::size_t i = 0; i < adj.size(); ++i) {
                if (adj[current][i] != 0 && !visited[i]) { // Non-zero indicates an edge
                    stack.push(i);
                }
            }
        }
    }
    //return true if its scc else false.
    bool Algorithms::isConnected(const Graph& g) {
        const auto& adj = g.getAdjMatrix(); // Get the adjacency matrix from the graph
        std::size_t numVertices = adj.size();

        if (numVertices == 0) {
            return true; // An empty graph is trivially connected
        }

        // Check forward reachability
        std::vector<bool> visited(numVertices, false);
        DFS(adj, 0, visited);

        for (std::size_t i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                return false; // If any vertex wasn't visited, the graph isn't a single SCC
            }
        }

        // Reverse the graph to check backward reachability
        std::vector<std::vector<int>> reversedAdj(numVertices, std::vector<int>(numVertices, 0));
        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                if (adj[i][j] != 0) {
                    reversedAdj[j][i] = adj[i][j]; // Reverse the edge
                }
            }
        }

        // Check backward reachability
        visited.assign(numVertices, false); // Reset the visited array
        DFS(reversedAdj, 0, visited); // DFS on the reversed graph

        for (std::size_t i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                return false; // If any vertex wasn't visited, the graph isn't a single SCC
            }
        }

        return true; // All vertices were visited in both forward and backward reachability
    }
    std::string Algorithms::shortestPath(const Graph& g, int start, int end) {
        const auto& adj = g.getAdjMatrix(); // Get adjacency matrix
        auto numVertices = adj.size(); // Get the number of vertices

        // Validate indices for `start` and `end`
        if (start < 0 || start >= static_cast<int>(numVertices) ||
            end < 0 || end >= static_cast<int>(numVertices)) {
            throw std::out_of_range("Invalid vertex index.");
        }

        using IndexType = std::vector<int>::size_type; // Proper unsigned type
        std::vector<int> prev(numVertices, -1); // Previous nodes for path reconstruction
        std::vector<double> distances(numVertices, std::numeric_limits<double>::max()); // Correct initialization
        distances[static_cast<IndexType>(start)] = 0; // Start with the source vertex

        // Bellman-Ford edge relaxation
        for (IndexType k = 0; k < numVertices - 1; ++k) {
            for (IndexType i = 0; i < numVertices; ++i) { // Loop through all vertices
                for (IndexType j = 0; j < numVertices; ++j) { // Loop through all edges
                    if (adj[i][j] != 0 && distances[i] < std::numeric_limits<double>::max()) { // Valid edge check
                        double newDist = distances[i] + adj[i][j]; // Calculate new distance
                        if (newDist < distances[j]) { // Edge relaxation logic
                            distances[j] = newDist;
                            prev[static_cast<IndexType>(j)] = static_cast<int>(i); // Correct predecessor update
                        }
                    }
                }
            }
        }

        // Check for negative cycles
        for (IndexType i = 0; i < numVertices; ++i) {
            for (IndexType j = 0; j < numVertices; ++j) {
                if (adj[i][j] != 0 && distances[i] < std::numeric_limits<double>::max()) {
                    double newDist = distances[i] + adj[i][j];
                    if (newDist < distances[j]) { // Proper cycle detection logic
                        return "Graph contains a negative cycle so there is no shortest path"; // General negative cycle indication
                    }
                }
            }
        }

        // Check if there's a valid path
        if (prev[static_cast<IndexType>(end)] == -1) {
            return "-1"; // No valid path
        }

        // Reconstruct the path
        std::vector<IndexType> pathIndices;
        for (IndexType at = static_cast<IndexType>(end); at != std::numeric_limits<IndexType>::max(); at = static_cast<IndexType>(prev[at])) {
            pathIndices.push_back(at); // Collect the path
        }

        std::reverse(pathIndices.begin(), pathIndices.end()); // Reverse for correct path order

        // Convert to human-readable path
        std::ostringstream oss;
        for (IndexType i = 0; i < pathIndices.size(); ++i) {
            if (i > 0) {
                oss << "->";
            }
            oss << pathIndices[i];
        }

        return oss.str(); // Return the reconstructed path
    }

    // // DFS-based cycle detection for undirected and directed graphs

    bool isCycleDFS(const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::vector<bool>& recStack, std::vector<int>& path, std::vector<int>::size_type node, std::vector<int>::size_type parent, std::string& cycleStr, bool isUndirected) {
        if (recStack[node] && (!isUndirected || node != parent)) { // Check recursion stack for cycle
            // Find the cycle path
            auto it = std::find(path.begin(), path.end(), node);
            cycleStr = "The cycle is: ";
            while (it != path.end()) {
                cycleStr += std::to_string(*it) + "->"; // Append cycle nodes
                ++it;
            }
            cycleStr += std::to_string(*path.begin()); // Complete the loop
            return true; // Cycle detected
        }

        if (visited[node]) { // Already visited, no cycle
            return false;
        }

        // Mark as visited and add to recursion stack
        visited[node] = true;
        recStack[node] = true;
        path.push_back(node);

        // Traverse adjacent nodes
        for (std::vector<int>::size_type i = 0; i < adj[node].size(); ++i) {
            if (adj[node][i] > 0 && (isUndirected ? i != parent : true)) { // Valid edge
                if (isCycleDFS(adj, visited, recStack, path, i, node, cycleStr, isUndirected)) {
                    return true; // Cycle detected
                }
            }
        }

        recStack[node] = false; // Remove from recursion stack
        path.pop_back(); // Pop from the path
        return false; // No cycle detected
    }
    std::string Algorithms::isContainsCycle(const Graph& g) {
        const auto& adj = g.getAdjMatrix();
        std::vector<bool> visited(adj.size(), false);
        std::vector<bool> recStack(adj.size(), false);
        std::vector<int> path; // Track current recursion path
        std::string cycleStr; // String to store the detected cycle
        bool isUndirected = g.isUndirectedGraph(); // Determine if the graph is undirected

        for (std::vector<int>::size_type start = 0; start < adj.size(); ++start) {
            if (!visited[start]) { // If not visited, start DFS
                if (isCycleDFS(adj, visited, recStack, path, start, std::numeric_limits<std::vector<int>::size_type>::max(), cycleStr, isUndirected)) {
                    return cycleStr; // Return the cycle description
                }
            }
        }

        return "0"; // No cycles found
    }
    
    std::string Algorithms::isBipartite(const Graph& g) {
        const auto& adj = g.getAdjMatrix();
        IndexType numVertices = adj.size();

        std::vector<int> colors(numVertices, -1); // -1: uncolored, 0: one color, 1: another color

        std::queue<IndexType> q;

        for (IndexType i = 0; i < numVertices; ++i) {
            if (colors[i] == -1) {
                q.push(i);
                colors[i] = 0;

                while (!q.empty()) {
                    IndexType node = q.front();
                    q.pop();

                    for (IndexType j = 0; j < adj[node].size(); ++j) {
                        if (adj[node][j]) { // There's an edge
                            if (colors[j] == -1) { // Uncolored
                                colors[j] = 1 - colors[node]; // Flip color
                                q.push(j);
                            } else if (colors[j] == colors[node]) { // Same color as parent
                                return "0";
                            }
                        }
                    }
                }
            }
        }

        std::string result;
        std::string group1, group2;

        for (IndexType i = 0; i < numVertices; ++i) {
            if (colors[i] == 0) {
                group1 += std::to_string(i) + ",";
            } else if (colors[i] == 1) {
                group2 += std::to_string(i) + ",";
            }
        }

        // Remove the trailing commas
        if (!group1.empty() && group1.back() == ',') {
            group1.pop_back();
        }
        if (!group2.empty() && group2.back() == ',') {
            group2.pop_back();
        }

        result = "The graph is bipartite: A={" + group1 + "}, B={" + group2 + "}";
        return result;
    }

    std::string Algorithms::negativeCycle(const Graph& g) {
        const auto & adj = g.getAdjMatrix(); // Get adjacency matrix
        size_t numVertices = adj.size(); // Get the number of vertices

        // Initialize distances, setting the starting vertex distance to 0
        std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
        distances[0] = 0; // Start from the first vertex (or a designated source)

        // Relax edges V-1 times
        for (size_t k = 0; k < numVertices - 1; ++k) {
            for (size_t i = 0; i < numVertices; ++i) {
                for (size_t j = 0; j < numVertices; ++j) {
                    if (adj[i][j] != 0 && distances[i] != std::numeric_limits<int>::max() &&
                        distances[j] > distances[i] + adj[i][j]) {
                        distances[j] = distances[i] + adj[i][j]; // Relax edge
                    }
                }
            }
        }

        // Check for negative cycles with one more iteration
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if (adj[i][j] != 0 && distances[i] != std::numeric_limits<int>::max() &&
                    distances[j] > distances[i] + adj[i][j]) {
                    return "Graph contains a negative cycle"; // If further relaxation is possible, there's a negative cycle
                }
            }
        }

        return "Graph does not contain a negative cycle"; // No negative cycle found
    }
    

} // namespace ariel
