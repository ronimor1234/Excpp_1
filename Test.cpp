//ID: 208018028, Mail: ronimordechai70@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    //symatrical matrix so it is undirected graph.
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    //symatrical matrix so its undirected graph.
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    // My test to this function
    // unsymatrical matrix so its directed graph with negative edges.
    vector<vector<int>> graph3 = {
        {0, -1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, -1, 0, -1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    //unsymatrical matrix so its directed graph with negative edges.
    vector<vector<int>> graph4 = {
        {0, -1, 1, 0, -3},
        {1, 0, 1, 0, 0},
        {1, -1, 0, -1, 0},
        {0, 0, 1, 0, 0},
        {-2, 0, 0, 0, -10}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    //unsymatrical matrix so its directed graph with negative edges.
    // not scc graph.
    vector<vector<int>> graph5 = {
        {0, -1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, -1, 0, -1, 0},
        {0, 0, 1, 0, 0},
        {-2, 0, 0, 0, -11}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    //unsymatrical matrix so its directed graph with negative edges.
    // not scc graph.
    vector<vector<int>> graph6 = {
        {0, -1, 1, 0, -4},
        {1, 0, 1, 0, 0},
        {1, -1, 0, -1, 0},
        {0, 0, 0, 0, 0},
        {-2, 0, 0, 0, -11}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    // graph with 3 vertices but no edges so its need to be false.
    vector<vector<int>> graph7 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    // empty graph so its need to be true.
    std::vector<std::vector<int>> emptyGraph;
    g.loadGraph(emptyGraph);
    CHECK(ariel::Algorithms::isConnected(g) == true); // trivially connected
    
    // single vertex so its need to be true.
    vector<vector<int>> graph8 = {
        {0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    // single vertex with self loop.
    vector<vector<int>> graph9 = {
        {-6}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph10 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph10);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph11 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph11);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");

    // My test to this function
    // Test case with negative edges, but no negative cycles.
    std::vector<std::vector<int>> graph12 = {
        {0, 1, 0},
        {1, 0, -1},
        {0, 1, 0}};
    g.loadGraph(graph12);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    // Test case with negative edges forming a different path.
    std::vector<std::vector<int>> graph13 = {
        {0, 2, -1},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph13);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");

    // Test case with negative edges forming a complex path.
    std::vector<std::vector<int>> graph14 = {
        {0, 1, -2},
        {1, 0, 0},
        {-1, 2, 0}};
    g.loadGraph(graph14);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Graph contains a negative cycle so there is no shortest path");

    // Test case with negative edges and a negative cycle (so there is no shortest path)
    std::vector<std::vector<int>> graph15 = {
        {0, -1, 0},
        {0, 0, -1},
        {-1, 0, 0}};
    g.loadGraph(graph15);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Graph contains a negative cycle so there is no shortest path"); 

    // Test case with multiple paths with negative edges
    std::vector<std::vector<int>> graph16 = {
        {0, -2, 3},
        {1, 0, -1},
        {0, 2, 0}};
    g.loadGraph(graph16);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "Graph contains a negative cycle so there is no shortest path"); 
}

TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph17 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph17);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph18 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph18);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");

    // My test to this function
    // Graph with a simple cycle
    std::vector<std::vector<int>> graph19 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph19);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0"); 

    // Graph with a larger cycle.
    std::vector<std::vector<int>> graph20 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g.loadGraph(graph20);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->3->4->0");

    // Graph with multiple cycles.
    std::vector<std::vector<int>> graph21 = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 0},
        {0, 1, 0, 0}};
    g.loadGraph(graph21);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0"); 

    // Graph with negative edges but no cycles.
    std::vector<std::vector<int>> graph22 = {
        {0, -1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, -1},
        {0, 0, 0, 0}};
    g.loadGraph(graph22);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0"); 

    // Graph with a negative edge and cycle that equals to 0.
    std::vector<std::vector<int>> graph23 = {
        {0, 0, 0, 0},
        {1, 0, -1, 0},
        {0, 1, 0, 1},
        {-11, 0, 1, 0}};
    g.loadGraph(graph23);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 2->3->2"); // Cycle with negative edge

    // Graph with mixed positive and negative edges in unsymatrical matrix.
    // Graph with negative and positive cycles, so it will print the negative becouse it is check it first.
    std::vector<std::vector<int>> graph24 = {
        {0, 1, -3, 0},
        {1, 0, -2, 0},
        {-3, -2, 0, 1},
        {-11, 0, 1, 0}};
    g.loadGraph(graph24);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a negative cycle: 2->0->2"); 

    // Graph with all negative edges in unsymatrical matrix, so there is a negative cycle and it will print him.
    std::vector<std::vector<int>> graph25 = {
        {0, -1, -3, 0},
        {-1, 0, -2, 0},
        {-3, -2, 0, -1},
        {-10, 0, -1, 0}};
    g.loadGraph(graph25);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a negative cycle: 2->3->2");
}

TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph26 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph26);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, B={1}");

    vector<vector<int>> graph27 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph27);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph28 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 6},
        {0, 0, 0, 6, 0}};
    g.loadGraph(graph28);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    // My test to this function
    // Non-bipartite graph with odd-length cycle
    std::vector<std::vector<int>> graph29 = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 0},
        {0, 1, 0, 0}};
    g.loadGraph(graph29);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    // Test 3: Larger bipartite graph
    std::vector<std::vector<int>> graph30 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}};
    g.loadGraph(graph30);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, B={1,3}");

    // Graph with no edges (trivially bipartite)
    std::vector<std::vector<int>> graph31 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph31);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,1,2}, B={}"); 

    // Graph with negative weights (not affect bipartite property)
    std::vector<std::vector<int>> graph32 = {
        {0, -1, 0},
        {-1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph32);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, B={1}"); 
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph33 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 6}};
    CHECK_THROWS(g.loadGraph(graph33));

    // My test to this function.
    // Non-square matrix (invalid graph).
    vector<vector<int>> graph34 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph34)); // Ensure exception for non-square matrix

    // Matrix with inconsistent data (invalid graph)
    vector<vector<int>> graph35 = {
        {0, 1, 2},
        {1, 0, 3, 0}, // Extra element
        {2, 3, 0}}; // Correct length but inconsistent with the second row
    CHECK_THROWS(g.loadGraph(graph35)); // Ensure exception for inconsistent data
}

TEST_CASE("Test negativeCycle")
{
    ariel::Graph g;
    // My test to this function.
    // Directed graph with a negative cycle.
    vector<vector<int>> graph36 = {
        {0, -1, 0},
        {0, 0, -2},
        {-1, 0, 0}};
    g.loadGraph(graph36);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph contains a negative cycle: 1->0->2->1"); // Detect negative cycle

    // Directed graph without negative cycle.
    vector<vector<int>> graph37 = {
        {0, 1, 0},
        {0, 0, 2},
        {0, 0, 0}};
    g.loadGraph(graph37);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle"); // No negative cycle

    // Undirected graph with a negative cycle.
    vector<vector<int>> graph38 = {
        {0, -1, -1},
        {-1, 0, 1},
        {-1, 1, 0}};
    g.loadGraph(graph38);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph contains a negative cycle: 1->0->1"); // Detect negative cycle

    // Undirected graph without negative cycle.
    vector<vector<int>> graph39 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph39);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle"); // No negative cycle

    // Undirected graph with negative cycle.
    vector<vector<int>> graph40 = {
        {0, 1, -2, 0, 0, -1}, 
        {1, 0, -1, 0, 0, 2}, 
        {-2, -1, 0, 4, 0, -3}, 
        {0, 0, 4, 0, 6, 1}, 
        {0, 0, 0, 6, 0, 8}, 
        {1, -6, -6, 8, 11, 0}};
    g.loadGraph(graph40);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph contains a negative cycle: 2->5->2");
}