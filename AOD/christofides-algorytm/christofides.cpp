#include "christofides.h"

#include <assert.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <string>
#include <stdio.h>
#include <vector>


Christofides::distance_t const Christofides::DINF = 1.0e+99;

//Constructor
Christofides::Christofides(string in) {
    iFile = in;

    ifstream inStream;
    inStream.open(iFile.c_str(), ios::in);

    if (!inStream) {
        cerr << "Can't open input file " << iFile << endl;
        exit(1);
    }

    //READ DATA
    double x, y;
    int count = 0;
    while (!inStream.eof()) {
        inStream >> x >> y;
        count++;
        struct Node newCity = { x,y };
        cities.push_back(newCity);
    }
    count--;
    cout << "węzły stworzone" << endl;
    inStream.close();

    std::srand(unsigned(std::time(0)));
    std::random_shuffle(cities.begin(), cities.end());

    n = count;
    graph = new distance_t*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new distance_t[n];
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    adjlist = new vector<int>[n];
}

Christofides::~Christofides() {
    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] adjlist;
}

Christofides::distance_t Christofides::get_distance(struct Christofides::Node c1, struct Christofides::Node c2) {
    double dx = c1.x - c2.x;
    double dy = c1.y - c2.y;
    double d = sqrt(dx*dx + dy * dy);
    return (distance_t)d;
}

void Christofides::fillMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = graph[j][i] = get_distance(cities[i], cities[j]);
        }
    }
}


void Christofides::findMinimumSpanningTree() {
    // Prim's algorithm
    distance_t *key = new distance_t[n];
    bool *included = new bool[n];
    int *parent = new int[n];

    for (int i = 0; i < n; i++) {

        // set each key to infinity
        key[i] = DINF;

        // node node yet included in MST
        included[i] = false;

    }

    // root of MST has distance of 0 and no parent
    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n - 1; i++) {

        // find closes vertex not already in tree
        int const k = getMinIndex(key, included);

        // set included to true for this vertex
        included[k] = true;

        // examine each unexamined vertex adjacent to most recently added
        for (int j = 0; j < n; j++) {

            // node exists, is unexamined, and graph[k][j] less than previous
            // key for u
            if (graph[k][j] && !included[j] && graph[k][j] < key[j]) {

                // update parent
                parent[j] = k;

                // update key
                key[j] = graph[k][j];

            }
        }

    }

    // construct a tree by forming adjacency matrices
    for (int i = 0; i < n; i++) {

        int j = parent[i];

        if (j != -1) {
            assert((j >= 0) && (j < n));
            adjlist[i].push_back(j);
            adjlist[j].push_back(i);

        }

    }

}


int Christofides::getMinIndex(distance_t key[], bool mst[]) {
    // find the index of the closest unexamined node

    // initialize min and min_index
    distance_t min = DINF;
    int min_index = -1;

    // iterate through each vertex
    for (int i = 0; i < n; i++) {

        // if vertex hasn't been visited and has a smaller key than min
        if (!mst[i] && key[i] < min) {

            // reassign min and min_index to the values from this node
            min = key[i];
            min_index = i;

        }

    }

    assert((min_index >= 0) && (min_index < n));
    return min_index;

}


void Christofides::findOdds() {
    // find all vertices of odd degree in the MST. Store them in an subgraph O

    for (int i = 0; i < n; i++) {

        // if degree of vertex i is odd
        if ((adjlist[i].size() % 2) != 0) {

            // push vertex to odds, which is a representation of subgraph O
            odds.push_back(i);

        }

    }

}


void Christofides::perfectMatching() {
    // find a perfect matching M in the subgraph O

    int closest;
    std::vector<int>::iterator tmp, first;

    // Find nodes with odd degrees in T to get subgraph O
    findOdds();

    // for each odd node
    while (!odds.empty()) {
        first = odds.begin();
        vector<int>::iterator it = odds.begin() + 1;
        vector<int>::iterator end = odds.end();
        distance_t length = DINF;
        for (; it != end; ++it) {
            // if this node is closer than the current closest, update closest and length
            if (graph[*first][*it] < length) {
                length = graph[*first][*it];
                closest = *it;
                tmp = it;
            }
        } // two nodes are matched, end of list reached
        adjlist[*first].push_back(closest);
        adjlist[closest].push_back(*first);
        odds.erase(tmp);
        odds.erase(first);
    }
}

void Christofides::euler_tour(int start, vector<int> &path) {
    assert((start >= 0) && (start < n));
    //Create copy of adj. list
    vector<int> *tempList = new vector<int>[n];
    for (int i = 0; i < n; i++) {
        tempList[i].resize(adjlist[i].size());
        tempList[i] = adjlist[i];
    }

    stack<int> stack;
    int pos = start;
    path.push_back(start);
    while (!stack.empty() || tempList[pos].size() > 0) {
        //Current node has no neighbors
        if (tempList[pos].empty()) {
            //add to circuit
            path.push_back(pos);
            //remove last vertex from stack and set it to current
            pos = stack.top();
            stack.pop();
        }
        //If current node has neighbors
        else {
            //Add vertex to stack
            stack.push(pos);
            //Take a neighbor
            int neighbor = tempList[pos].back();
            //Remove edge between neighbor and current vertex
            tempList[pos].pop_back();
            for (auto i = 0U; i < tempList[neighbor].size(); i++) {
                if (tempList[neighbor][i] == pos) {
                    tempList[neighbor].erase(tempList[neighbor].begin() + i);
                }
            }
            //Set neighbor as current vertex
            pos = neighbor;
        }
    }
    path.push_back(pos);
    delete[] tempList;
}

void Christofides::make_hamiltonian() {
    make_hamiltonian(circuit, pathLength);
}

void Christofides::make_hamiltonian(vector<int> &path, int &pathCost) {
    // From euler tour to Hamiltonian

    //remove visited nodes from Euler tour
    bool *visited = new bool[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    pathCost = 0;

    int root = path.front();
    vector<int>::iterator cur = path.begin();
    vector<int>::iterator iter = path.begin() + 1;
    visited[root] = 1;

    //iterate through circuit
    while (iter != path.end()) {
        if (!visited[*iter]) {
            pathCost += graph[*cur][*iter];
            cur = iter;
            visited[*cur] = 1;
            iter = cur + 1;
        }
        else {
            iter = path.erase(iter);
        }
    }
    //Add distance to root
    vector<int>::iterator begin = path.begin();
    pathCost += graph[*cur][*begin];
}

void Christofides::euler_tour(int start) {
    euler_tour(start, circuit);
}

int Christofides::findBestPath(int start) {
    vector<int> path;
    euler_tour(start, path);

    int length;
    make_hamiltonian(path, length);

    return length;
}

void Christofides::find_shortest_path()
{
    // Loop through each index and find shortest path, save starting index
    Christofides::distance_t best = Christofides::DINF;
    shortestPathStartNode = -1;
    for (long t = 0; t < n; t++) {
        Christofides::distance_t result = findBestPath(t);
        if (result < best) {
            shortestPathStartNode = t;
            best = result;
        }
    }
}

void Christofides::printPath() {
    cout << endl;
    for (vector<int>::iterator it = circuit.begin(); it != circuit.end() - 1; ++it) {
        cout << *it << " to " << *(it + 1) << " ";
        cout << graph[*it][*(it + 1)] << endl;
    }
    cout << *(circuit.end() - 1) << " to " << circuit.front();
    cout << "\nLength: " << pathLength << endl << endl;
};
