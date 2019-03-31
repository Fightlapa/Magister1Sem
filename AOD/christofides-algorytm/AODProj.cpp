// AODProj.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <climits>
#include "christofides.h"
//#include "twoOpt.h"

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
    int tsp_size = tsp.get_size();

    // Fill N x N matrix with distances between nodes
    cout << "Fillmatrix started" << endl;
    tsp.fillMatrix();
    cout << "Filled Matrix" << endl;

    // Find a MST T in graph G
    tsp.findMST();
    cout << "MST created" << endl;

    // Find a minimum weighted matching M for odd vertices in T
    tsp.perfectMatching();
    cout << "Matching completed" << endl;

    // Loop through each index and find shortest path
    Christofides::distance_t best = Christofides::DINF;
    int bestIndex = -1;
    for (long t = 0; t < tsp_size; t++) {
        Christofides::distance_t result = tsp.findBestPath(t);
        if (result < best) {
            bestIndex = t;
            best = result;
        }
    }
    cout << "BestPath completed " << bestIndex << endl;

    //Create path for best tour
    tsp.euler_tour(bestIndex, tsp.circuit);
    tsp.make_hamiltonian(tsp.circuit, tsp.pathLength);

    cout << "Final length: " << tsp.pathLength << endl;


    tsp.printPath();
    getchar();
}
