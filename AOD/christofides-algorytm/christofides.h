#include <string>
#include <vector>

using namespace std;

class Christofides
{
    struct Node {
        double x;
        double y;
    };

    string iFile;

    // List of odd nodes
    vector<int>odds;

    //Adjacency list
    vector<int> *adjList;

    void findOdds();

public:
    // Number of cities
    int n;

    //Shortest path length
    int pathLength;

    //euler circuit
    vector<int> circuit;

    vector<Node> cities;

    // n x n, pairwise distances between cities
    typedef double distance_t;
    distance_t **graph;
    static distance_t const DINF;

    vector<int>* adjlist;

    // Constructor
    Christofides(string in);

    // Destructor
    ~Christofides();

    distance_t get_distance(struct Node c1, struct Node c2);

    //Find perfect matching
    void perfectMatching();

    //Find Euler tour
    void euler_tour(int start, vector<int> &path);

    //Find Hamiltonian path
    void make_hamiltonian(vector<int> &path, int &pathCost);

    // Prim's algorithm
    void findMST();

    int getMinIndex(distance_t key[], bool mst[]);

    void printResult();
    void printPath();
    void printEuler();
    void printAdjList();
    void printCities();

    int get_size() { return n; };

    void fillMatrix();

    int findBestPath(int start);

};
