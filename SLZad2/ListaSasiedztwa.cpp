#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <sstream>
#include "ListaSasiedztwa.h"
using namespace std;

// Wyjątek pojawiający się przy próbie konwersji z błędnej reprezentacji tekstowej.
class ListaSasiedztwa::G6Error : exception
{
public:
    G6Error(const char* msg) : std::exception(msg)
    {
    }
};
// Wyjątek pojawiający się przy próbie usunięcia z grafu ostatniego wierzchołka.
class ListaSasiedztwa::NoVerticesError : exception
{
public:
    NoVerticesError(const char* msg) : std::exception(msg)
    {
    }
};
// Wyjątek pojawiający się przy próbie dodania 17 - tego wierzchołka.
class ListaSasiedztwa::TooManyVerticesError : exception
{
public:
    TooManyVerticesError(const char* msg) : std::exception(msg)
    {
    }
};

// Tworzy graf o podanej reprezentacji tekstowej(domyślnie: 1 - wierzchołkowy graf pusty).
ListaSasiedztwa::ListaSasiedztwa(string text = "@")
{
    fromString(text);
}

// Zwraca liczbę wierzchołków grafu.
int ListaSasiedztwa::order()
{
    return __order;
}

// Dodaje do grafu nowy izolowany wierzchołek.
void ListaSasiedztwa::addVertex()
{
    if (__order == 16)
    {
        throw TooManyVerticesError("too many vertices");
    }
    vector<int> vertexList;
    AdjencyList.push_back(vertexList);

}


// Usuwa z grafu wskazany wierzchołek.
void ListaSasiedztwa::deleteVertex(int u)
{
    if (__order == 1)
    {
        throw NoVerticesError("graph must have vertices");
    }
    for (vector<int> vertexAdjencyList : AdjencyList)
    {
        vertexAdjencyList.erase(remove(vertexAdjencyList.begin(), vertexAdjencyList.end(), u), vertexAdjencyList.end());
    }
    vector<vector<int>>::iterator it;
    it = AdjencyList.begin();
    advance(it, u);
    AdjencyList.erase(it);
}


// Zwraca informację o tym, czy podane wierzchołki sąsiadują z sobą.
bool ListaSasiedztwa::isEdge(int u, int v)
{
    return find(AdjencyList.at(u).begin(), AdjencyList.at(u).end(), v) != AdjencyList.at(u).end();
}


// Dodaje podaną krawędź.
void ListaSasiedztwa::addEdge(int u, int v)
{
    AdjencyList.at(u).push_back(v);
    AdjencyList.at(v).push_back(u);
}


// Usuwa podaną krawędź.
void ListaSasiedztwa::deleteEdge(int u, int v)
{
    AdjencyList.at(u).erase(remove(AdjencyList.at(u).begin(), AdjencyList.at(u).end(), v), AdjencyList.at(u).end());
    AdjencyList.at(v).erase(remove(AdjencyList.at(v).begin(), AdjencyList.at(v).end(), u), AdjencyList.at(v).end());
}


// Przekształca reprezentację tekstową grafu w graf.
void ListaSasiedztwa::fromString(string text)
{
    int k = 0;
    for (int charIndex = 0; charIndex < __order; charIndex++) {
        int c = text.at(charIndex) - 63;
        if (c < 1 || c > 16)
        {
            stringstream ss;
            ss << "wrong character: " << to_string(c + 63);
            const char* converted = ss.str().c_str();
            throw G6Error(converted);
        }

        __order = c;
        for (int i = 0; i < __order; i++)
        {
            vector<int> newList;
            AdjencyList.push_back(newList);
        }

        for (int v = 0; v < __order; v++)
        {
            for (int u = 0; u < v; u++)
            {
                if (k == 0)
                    c = text.at(charIndex) - 63;
                if (c < 0 || c > 63)
                {
                    stringstream ss;
                    ss << "wrong character: " << to_string(c + 63);
                    const char* converted = ss.str().c_str();
                    throw G6Error(converted);
                }
                k = 6;
                k -= 1;
                if ((c & (1 << k)) != 0)
                {
                    addEdge(u, v);
                }

            }
        }
    }

}


// Przekształca graf w reprezentację tekstową.
string ListaSasiedztwa::__str__()
{
    int k = 0;
    int c = 0;
    string text = to_string(__order + 63);
    for (int v = 0; v < __order; v++)
    {
        for (int u = 0; u < v; u++)
        {
            if (isEdge(u, v))
            {
                c |= (1 << k);
            }
            if (k == 0)
            {
                text += to_string(c + 63);
                k = 6;
                c = 0;
            }
            k -= 1;
        }
    }
    if (k != 5)
        text += to_string(c + 63);
    return text;
}


// Test równości dwóch reprezentacji grafów.
bool ListaSasiedztwa::__eq__(ListaSasiedztwa other)
{
    if (__order != other.__order)
        return false;
    for (int v = 0; v < __order; v++)
    {
        for (int u = 0; u < v; u++)
        {
            if (isEdge(u, v) != other.isEdge(u, v))
            {
                return false;
            }
        }
    }
    return true;
}


// Test różności dwóch reprezentacji grafów.
bool ListaSasiedztwa::__ne__(ListaSasiedztwa other)
{
    return !__eq__(other);
}

