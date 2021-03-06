// AODProj.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <climits>
#include "christofides.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        exit(-1);
    }

    // Read file names from input
    string input;
    input = argv[1];

    // Create new tsp object
    Christofides tsp(input);
    cout << "tsp created" << endl;

    // Fill N x N matrix with distances between nodes
    cout << "Fillmatrix started" << endl;
    tsp.fillMatrix();
    cout << "Filled Matrix" << endl;

    // Find a MST T in graph G
    tsp.findMinimumSpanningTree();
    cout << "MST created" << endl;

    // Find a minimum weighted matching M for odd vertices in T
    tsp.perfectMatching();
    cout << "Matching completed" << endl;

    // Loop through each index and find shortest path, save starting index
    tsp.find_shortest_path();
    cout << "BestPath completed " << tsp.shortestPathStartNode << endl;

    //Create path for best tour
    tsp.euler_tour();
    tsp.make_hamiltonian();

    cout << "Final length: " << tsp.pathLength << endl;


    tsp.printPath();
    getchar();
}
