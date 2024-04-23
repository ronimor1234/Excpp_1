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

    bool Algorithms::isConnected(const Graph& g) {
        const auto& adj = g.getAdjMatrix();
        IndexType numVertices = adj.size();

        if (numVertices == 0) {
            return true; // A graph with no vertices is trivially connected
        }

        std::vector<bool> visited(numVertices, false);
        std::queue<IndexType> q;
        q.push(0); // Start from the first vertex

        while (!q.empty()) {
            IndexType node = q.front();
            q.pop();

            if (visited[node]) {
                continue;
            }

            visited[node] = true;

            for (IndexType i = 0; i < adj[node].size(); ++i) {
                if (adj[node][i] && !visited[i]) {
                    q.push(i);
                }
            }
        }

        // Check if all vertices have been visited
        for (bool v : visited) {
            if (!v) {
                return false; // Not connected
            }
        }
        return true; // All vertices visited, graph is connected
    }

    // Function to find the shortest path between two vertices in an adjacency matrix
    std::string Algorithms::shortestPath(const Graph& g, int start, int end) {
        const auto& adj = g.getAdjMatrix();
        IndexType numVertices = adj.size();

        if (start < 0 || start >= static_cast<int>(numVertices) ||
            end < 0 || end >= static_cast<int>(numVertices)) {
            throw std::out_of_range("Invalid vertex index.");
        }

        // Initialization for BFS
        std::vector<int> prev(numVertices, -1); // Previous nodes for path reconstruction
        std::vector<bool> visited(numVertices, false); // To track visited nodes
        std::queue<IndexType> q;
        q.push(static_cast<IndexType>(start)); // Correctly cast to IndexType
        visited[static_cast<IndexType>(start)] = true; // Correctly cast to IndexType

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            if (node == static_cast<IndexType>(end)) {
                break;
            }

            // Explore neighbors
            for (IndexType i = 0; i < adj[node].size(); ++i) {
                if (adj[node][i] && !visited[i]) { // Only unvisited nodes
                    prev[i] = static_cast<int>(node); // Mark previous node
                    visited[i] = true; // Mark as visited
                    q.push(i); // Add to the queue for further exploration
                }
            }
        }

        if (prev[static_cast<IndexType>(end)] == -1) {
            return "No path found"; // No valid path exists
        }

        std::vector<IndexType> pathIndices;
        for (IndexType at = static_cast<IndexType>(end); at != static_cast<IndexType>(-1); at = static_cast<IndexType>(prev[at])) {
            pathIndices.push_back(at);
        }

        std::reverse(pathIndices.begin(), pathIndices.end()); // Reverse path to start-to-end

        std::ostringstream oss;
        for (IndexType i = 0; i < pathIndices.size(); ++i) {
            if (i > 0) {
                oss << "->"; // Path separator
            }
            oss << pathIndices[i]; // Node index in the path
        }

        return oss.str(); // Return the formatted path
    }
    // Helper function for DFS-based cycle detection
    bool isCycleDFS(const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::vector<bool>& recStack, std::vector<int>::size_type node) {
        if (recStack[node]) { // Check if node is in recursion stack
            return true; // Cycle detected
        }

        if (visited[node]) { // If already visited, no cycle from this node
            return false;
        }

        visited[node] = true; // Mark node as visited
        recStack[node] = true; // Add node to recursion stack

        // Check all adjacent nodes
        for (std::vector<int>::size_type i = 0; i < adj[node].size(); ++i) {
            if (adj[node][i] == 1) { // If there's an edge
                if (isCycleDFS(adj, visited, recStack, i)) { // Recursive check
                    return true;
                }
            }
        }

        recStack[node] = false; // Remove from recursion stack
        return false; // No cycle detected
    }

    bool Algorithms::isContainsCycle(const Graph& g) {
        const auto& adj = g.getAdjMatrix();
        std::vector<bool> visited(adj.size(), false); // Track visited nodes
        std::vector<bool> recStack(adj.size(), false); // Track recursion stack

        // Check for cycles starting from each node
        for (std::vector<int>::size_type start = 0; start < adj.size(); ++start) {
            if (!visited[start]) {
                if (isCycleDFS(adj, visited, recStack, start)) {
                    return true; // If any node leads to a cycle
                }
            }
        }

        return false; // No cycles found
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
                                return "Graph is not bipartite";
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
                group1 += std::to_string(i) + " ";
            } else if (colors[i] == 1) {
                group2 += std::to_string(i) + " ";
            }
        }

        result = "Graph is bipartite. Group 1: " + group1 + "Group 2: " + group2;
        return result;
    }

    std::string Algorithms::negativeCycle(const Graph& g) {
        const auto& adj = g.getAdjMatrix();
        IndexType numVertices = adj.size();

        std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
        distances[0] = 0; // Start from the first vertex

        // Bellman-Ford algorithm to detect negative cycles
        for (IndexType k = 0; k < numVertices - 1; ++k) {
            for (IndexType i = 0; i < numVertices; ++i) {
                for (IndexType j = 0; j < adj[i].size(); ++j) {
                    if (adj[i][j] && distances[i] != std::numeric_limits<int>::max() && distances[j] > distances[i] + adj[i][j]) {
                        distances[j] = distances[i] + adj[i][j];
                    }
                }
            }
        }

        // Checking for negative cycles
        for (IndexType i = 0; i < numVertices; ++i) {
            for (IndexType j = 0; j < adj[i].size(); ++j) {
                if (adj[i][j] && distances[i] != std::numeric_limits<int>::max() && distances[j] > distances[i] + adj[i][j]) {
                    return "Graph contains a negative cycle";
                }
            }
        }

        return "Graph does not contain a negative cycle"; // Ensure a return statement for all control paths
    }

} // namespace ariel
