# EXCPP_1: Graph Algorithms Project

Welcome to EXCPP_1, a project focused on implementing various algorithms on graphs. The graphs are represented as square adjacency matrices, and any non-square matrix is considered invalid. This README serves as a comprehensive guide to the project, explaining its structure, components, key algorithms, and usage instructions.

## Table of Contents
- [Project Overview](#project-overview)
- [Installation](#installation)
- [Usage](#usage)
- [Core Components](#core-components)
- [Algorithms in Detail](#algorithms-in-detail)
- [Demo and Testing](#demo-and-testing)
- [License](#license)

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

```bash
# Clone the repository (replace with your repository URL!!!)
git clone <repository-url>
cd EXCPP_1

# Compile the project
make all

## usegs
