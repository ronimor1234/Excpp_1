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
            return "-1 (No path found)"; // No valid path exists
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

    // DFS-based cycle detection for undirected and directed graphs
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

    // Function to check if the graph contains a cycle and print it if found
    bool Algorithms::isContainsCycle(const Graph& g) {
        const auto& adj = g.getAdjMatrix(); // Get adjacency matrix
        std::vector<bool> visited(adj.size(), false); // Track visited nodes
        std::vector<bool> recStack(adj.size(), false); // Recursion stack for cycle detection
        std::vector<int> path; // Track current recursion path
        std::string cycleStr; // Store the cycle description
        bool isUndirected = g.isUndirectedGraph(); // Determine if the graph is undirected

        // Check for cycles starting from each node
        for (std::vector<int>::size_type start = 0; start < adj.size(); ++start) {
            if (!visited[start]) { // If not visited, start DFS
                if (isCycleDFS(adj, visited, recStack, path, start, std::numeric_limits<std::vector<int>::size_type>::max(), cycleStr, isUndirected)) {
                    std::cout << cycleStr << ". so it is:"; // Print the detected cycle
                    return true; // Cycle detected
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
                                return "0 (Graph is not bipartite)";
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
