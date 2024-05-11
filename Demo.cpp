//ID: 208018028, Mail: ronimordechai70@gmail.com
/*
 * Demo program for Exercise 1.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
using ariel::Algorithms;

auto main() -> int
{
    ariel::Graph g;
    // 3x3 matrix that represents a connected graph.
    // this matrix is symmetrical so its will be undirected graph.
    std::cout << "Test to graph1:" << endl;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph1); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 3 vertices and 2 edges."
    std::cout << "isConnected: ";
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    std::cout << "shortestPath: ";
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: 0->1->2.
    std::cout << "isContainsCycle: ";
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0" (false).
    std::cout << "isBipartite: ";
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2}, B={1}."
    std::cout << "\n";

    // 5x5 matrix that represents a non-connected graph with a cycle.
    // this matrix is symmetrical so its will be undirected graph.
    std::cout << "Test to graph2:" << endl;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    g.loadGraph(graph2); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 4 edges."
    std::cout << "isConnected: ";
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    std::cout << "shortestPath: ";
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "-1" (there is no path between 0 and 4).
    std::cout << "isContainsCycle: ";
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->2->0".
    std::cout << "isBipartite: ";
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" (false).
    std::cout << "\n";

    // 5x5 matrix that reprsents a connected weighted graph.
    // this matrix is symmetrical so its will be undirected graph.
    std::cout << "Test to graph3:" << endl;
    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 6},
        {0, 0, 0, 6, 0}};
    g.loadGraph(graph3); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 5 edges."
    std::cout << "isConnected: ";
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    std::cout << "shortestPath: ";
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: 0->2->3->4.
    std::cout << "isContainsCycle: ";
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->2->0."
    std::cout << "isBipartite: ";
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" (The graph is not bipartite-there is odd cycle)
    std::cout << "\n";

    // 5x4 matrix that reprsents invalid graph.
    // this matrix is symmetric so its will be undirected graph.
    std::cout << "Test to graph4:" << endl;
    vector<vector<int>> graph4 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 6}};
    try
    {
        g.loadGraph(graph4); // Load the graph to the object.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
    }
    std::cout << "\n";

    //My demo test:

    // 5x5 matrix that reprsents a connected with negative weighted graph.
    // this matrix is symmetric so its will be undirected graph.
    std::cout << "Test to graph5:" << endl;
    vector<vector<int>> graph5 = {
        {0, 1, 2, 0, 0},
        {1, 0, 1, 0, 0},
        {2, -1, 0, 4, 0},
        {0, 0, 4, 0, 6},
        {0, 0, 0, 6, 0}};
    g.loadGraph(graph5); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 5 edges."
    std::cout << "isConnected: ";
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    std::cout << "shortestPath: ";
    cout << Algorithms::shortestPath(g, 0, 3) << endl; // Should print: 0->1->3
    std::cout << "isContainsCycle: ";
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->0." (it is a edge with both direction)
    std::cout << "isBipartite: ";
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" there is odd cycle so the graph is not bipartite.
    std::cout << "negativeCycle: ";
    cout << Algorithms::negativeCycle(g) << endl;       // Should print: "Graph does not contain a negative cycle"
    std::cout << "\n";

    // 4x4 matrix that reprsents a unsymmetry matrix so its directed graph. 
    std::cout << "Test to graph6:" << endl;
    vector<vector<int>> graph6 = {
        {0, 1, 0, 11},
        {1, 0, 1, 2},
        {0, 2, 0, 0},
        {0, 1, 0, 0}};
    g.loadGraph(graph6); // Load the graph to the object.
    g.printGraph();                                    // Should print: "Graph with 4 vertices and 7 edges."
    std::cout << "isConnected: ";
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    std::cout << "shortestPath: ";
    cout << Algorithms::shortestPath(g, 0, 3) << endl;  // Should print: 0->1->3
    std::cout << "isContainsCycle: ";
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "the cycle is: 0->1->0"
    std::cout << "isBipartite: ";
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" there is odd cycle so the graph is not bipartite.
    std::cout << "negativeCycle: ";
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "Graph does not contain a negative cycle"
    std::cout << "\n";

    // 5x5 matrix that reprsents a connected with negative weighted graph.
    // this graph contain negative cycle. 
    std::cout << "Test to graph7:" << endl;
    vector<vector<int>> graph7 = {
        {0, 1, -2, 0, 0},
        {1, 0, -1, 0, 0},
        {-2, -1, 0, 4, 0},
        {0, 0, 4, 0, 6},
        {0, 0, 0, 6, 0}};
    g.loadGraph(graph7); // Load the graph to the object.
    g.printGraph();                                    // Should print: "Graph with 5 vertices and 5 edges."
    std::cout << "isConnected: ";
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    std::cout << "shortestPath: ";
    cout << Algorithms::shortestPath(g, 0, 3) << endl;  // Should print: "Graph contains a negative cycle so there is no shortest path"
    std::cout << "isContainsCycle: ";
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "Graph contains a negative cycle: 2->0->2"
    std::cout << "isBipartite: ";
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" there is odd cycle so the graph is not bipartite.
    std::cout << "negativeCycle: ";
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "Graph contains a negative cycle: 2->0->2"
    std::cout << "\n";

    // 5x5 matrix that reprsents a directed graph with negative weighted.
    // this graph does not contain negative cycle. 
    std::cout << "Test to graph8:" << endl;
    vector<vector<int>> graph8 = {
        {0, 0, 2, 0, 1},
        {-1, 0, 1, 0, 0},
        {2, 1, 0, 4, 0},
        {0, 0, 4, 0, 6},
        {1, 0, 0, 6, 0}};
    g.loadGraph(graph8); // Load the graph to the object.
    g.printGraph();                                    // Should print: "Graph with 5 vertices and 11 edges." (it is 11 edges because its undirected graph, so every edge with two directions its count like 2)
    std::cout << "isConnected: ";
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    std::cout << "shortestPath: ";
    cout << Algorithms::shortestPath(g, 0, 3) << endl;  // Should print: 0->2->3
    std::cout << "isContainsCycle: ";
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "the cycle is: 0->2->0"
    std::cout << "isBipartite: ";
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0"
    std::cout << "negativeCycle: ";
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "Graph does not contain a negative cycle"
    std::cout << "\n";

    // 5x5 matrix that reprsents a connected with negative weighted graph.
    // this graph contain negative cycle. 
    std::cout << "Test to graph9:" << endl;
    vector<vector<int>> graph9 = {
       {0, -1, 1, 0, -3},
        {1, 0, 1, 0, 0},
        {1, -1, 0, -1, 0},
        {0, 0, 1, 0, 0},
        {-2, 0, 0, 0, -10}};
    g.loadGraph(graph9); // Load the graph to the object.
    g.printGraph();                                    // Should print: "Graph with 5 vertices and 11 edges."
    std::cout << "isConnected: ";
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    std::cout << "shortestPath: ";
    cout << Algorithms::shortestPath(g, 0, 3) << endl;  // Should print: "Graph contains a negative cycle so there is no shortest path"
    std::cout << "isContainsCycle: ";
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "Graph contains a negative cycle: 4->4" (because there is a negative edge for himself so it is like a negative cycle)
    std::cout << "isBipartite: ";
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0"
    std::cout << "negativeCycle: ";
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "Graph contains a negative cycle: 4->4"
    std::cout << "\n";

    // 3x3 matrix that reprsents a connected with negative weighted graph.
    // this graph contain cycle that equals to 0 (it is not consider negative). 
    std::cout << "Test to graph10:" << endl;
    vector<vector<int>> graph10 = {
        {0, -2, 3},
        {1, 0, -1},
        {3, 5, 0}};
    g.loadGraph(graph10); // Load the graph to the object.
    g.printGraph();                                    // Should print: "Graph with 3 vertices and 6 edges."
    std::cout << "isConnected: ";
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    std::cout << "isContainsCycle: ";
    cout << Algorithms::isContainsCycle(g) << endl;     // Should print:"The cycle is: 0->2->0"
    std::cout << "isBipartite: ";
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "Graph does not contain a negative cycle"
}
