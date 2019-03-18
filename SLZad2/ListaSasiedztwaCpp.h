#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <sstream>
class ListaSasiedztwaCpp
{
public:
    // Wyjątek pojawiający się przy próbie konwersji z błędnej reprezentacji tekstowej.
    class G6Error;
    // Wyjątek pojawiający się przy próbie usunięcia z grafu ostatniego wierzchołka.
    class NoVerticesError;
    // Wyjątek pojawiający się przy próbie dodania 17 - tego wierzchołka.
    class TooManyVerticesError;
    size_t __order;
    std::vector<std::vector<int>> AdjencyList;

    // Tworzy graf o podanej reprezentacji tekstowej(domyślnie: 1 - wierzchołkowy graf pusty).
    ListaSasiedztwaCpp(const char* text = "@");

    // Zwraca liczbę wierzchołków grafu.
    int order();

    // Dodaje do grafu nowy izolowany wierzchołek.
    void addVertex();


    // Usuwa z grafu wskazany wierzchołek.
    void deleteVertex(int);


    // Zwraca informację o tym, czy podane wierzchołki sąsiadują z sobą.
    bool isEdge(int, int);


    // Dodaje podaną krawędź.
    void addEdge(int, int);


    // Usuwa podaną krawędź.
    void deleteEdge(int, int);

    // Przekształca reprezentację tekstową grafu w graf.
    void fromString(const char* string);


    // Przekształca graf w reprezentację tekstową.
    const char* __str__();



    // Test równości dwóch reprezentacji grafów.
    bool __eq__(ListaSasiedztwaCpp);


    // Test różności dwóch reprezentacji grafów.
    bool __ne__(ListaSasiedztwaCpp);


};

