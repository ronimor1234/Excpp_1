# EXCPP_1: Graph Algorithms Project

Welcome to EXCPP_1, a project focused on implementing various algorithms on graphs. The graphs are represented as square adjacency matrices, and any non-square matrix is considered invalid. This README serves as a comprehensive guide to the project, explaining its structure, components, key algorithms, and usage instructions.

## Table of Contents
- [Project Overview](#project-overview)
- [Installation](#installation)
- [Usage](#usage)
- [Core Components](#core-components)
- [Algorithms in Detail](#algorithms-in-detail)
- [Summery](#summery)

## Project Overview
EXCPP_1 is designed to work with graphs represented by square adjacency matrices. The project has multiple components, including code files, a demo, and test cases. The two main files are `Graph.cpp` and `Algorithms.cpp`.

- **Graph.cpp**: Represents the structure of the graph, providing functions like `validateMatrix`, `isSymmetric`, `loadGraph`, `isUndirectedGraph`, and `printGraph`. A key design choice is that symmetrical matrices represent undirected graphs, while unsymmetrical matrices represent directed graphs.
- **Algorithms.cpp**: Contains algorithms for working with graphs, including functions to check if a graph is connected, find the shortest path, detect cycles, check if a graph is bipartite, and identify negative cycles.

Additional files:
- `Demo.cpp`: Demonstrates various functionalities and outputs for the project.
- `Test.cpp`, `TestCounter.cpp`: Contains test cases for validating the algorithms.
- `Makefile`: Facilitates the building and compilation of the project.
- `doctest.h`: A header-only testing framework.

## Installation
To set up the project, you need a C++ compiler and build tools. The `Makefile` can be used to compile the project.

## Usage
After compiling the project by make all, you can run the demo to see the implemented algorithms in action. The demo shows different use cases and outputs for the graph algorithms.
bash

# Run the demo
./demo

The test cases in Test.cpp and TestCounter.cpp validate the project's behavior against edge cases and other scenarios. To run the tests, use:

# Run the test
./test

## Core Components
1. Graph.cpp

This file defines the structure of the graph and provides functions like validateMatrix(), isSymmetric(), loadGraph(), isUndirectedGraph(), and printGraph().

2. Algorithms.cpp

This file contains various algorithms for operations on graphs, including checking connectivity, finding the shortest path, detecting cycles, checking if a graph is bipartite, and identifying negative cycles.

## Algorithms in Detail

    *isConnected(): Uses Depth-First Search (DFS) to check if the graph is strongly connected, return true/false.

    shortestPath: Uses Bellman-Ford to find the shortest path, considering negative weights, return the path from the start v to the end v, if there is a negative cycle return "Graph contains a negative cycle so there is no shortest path" like we learned in algo 1, and if there is no path return "-1".
    
    *isCycleDFS():(help bool function to isContainsCycle()) 
    A DFS-based approach to detect cycles in the graph.The function get :the adjacency matrix, vectors to track visited nodes, recursion stack, current path, current node, parent node, a string to store cycle details, and a boolean indicating whether the graph is undirected. And return true and keep the cycle if there is,with this parameters else retutn false.
    *isContainsCycle(): This function checks if a graph contains any cycles by using isCycleDFS. It returns a description of the cycle if found, or "0" if no cycles are detected. 
    **Note: this functions works only to positive edges. if there is negative cycle it return 0, becouse there is a diffrente function for this.

    *isBipartite(): The function checks if the graph can be divided into two sets without internal connections. If so, it returns a message confirming the graph's bipartite nature with details on the sets. If not, it returns "0", indicating that the graph is not bipartite.

    *negativeCycle(): Uses Bellman-Ford to detect negative cycles by checking for additional relaxation after V-1 iterations. if something has change in the V'times iteration it return: "Graph contains a negative cycle" else return: "Graph does not contain a negative cycle".
    **note: i decided not to print the cycle


## Summary

This project focuses on implementing algorithms on graphs represented by square adjacency matrices. It includes functions to check connectivity, find shortest paths, detect cycles, and more. The demo and test cases validate the project's functionality. If you'd like to contribute, ensure you follow the project's coding guidelines and best practices.






 


