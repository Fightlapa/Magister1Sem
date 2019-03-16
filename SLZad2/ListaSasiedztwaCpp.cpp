#include <string>
#include <list>
#include <algorithm>
#include <vector>
#include <sstream>
#include "ListaSasiedztwaCpp.h"


// Wyjątek pojawiający się przy próbie konwersji z błędnej reprezentacji tekstowej.
class ListaSasiedztwaCpp::G6Error : std::exception
{
public:
    G6Error(const char* msg) : std::exception(msg)
    {
    }
};
// Wyjątek pojawiający się przy próbie usunięcia z grafu ostatniego wierzchołka.
class ListaSasiedztwaCpp::NoVerticesError : std::exception
{
public:
    NoVerticesError(const char* msg) : std::exception(msg)
    {
    }
};
// Wyjątek pojawiający się przy próbie dodania 17 - tego wierzchołka.
class ListaSasiedztwaCpp::TooManyVerticesError : std::exception
{
public:
    TooManyVerticesError(const char* msg) : std::exception(msg)
    {
    }
};

// Tworzy graf o podanej reprezentacji tekstowej(domyślnie: 1 - wierzchołkowy graf pusty).
ListaSasiedztwaCpp::ListaSasiedztwaCpp(const char* text = "@")
{
    fromString(text);
}

// Zwraca liczbę wierzchołków grafu.
int ListaSasiedztwaCpp::order()
{
    return __order;
}

// Dodaje do grafu nowy izolowany wierzchołek.
void ListaSasiedztwaCpp::addVertex()
{
    if (__order == 16)
    {
        throw TooManyVerticesError("too many vertices");
    }
    std::vector<int> vertexList;
    AdjencyList.push_back(vertexList);

}


// Usuwa z grafu wskazany wierzchołek.
void ListaSasiedztwaCpp::deleteVertex(int u)
{
    if (__order == 1)
    {
        throw NoVerticesError("graph must have vertices");
    }
    for (std::vector<int> vertexAdjencyList : AdjencyList)
    {
        vertexAdjencyList.erase(remove(vertexAdjencyList.begin(), vertexAdjencyList.end(), u), vertexAdjencyList.end());
    }
    std::vector<std::vector<int>>::iterator it;
    it = AdjencyList.begin();
    advance(it, u);
    AdjencyList.erase(it);
}


// Zwraca informację o tym, czy podane wierzchołki sąsiadują z sobą.
bool ListaSasiedztwaCpp::isEdge(int u, int v)
{
    return std::find(AdjencyList.at(u).begin(), AdjencyList.at(u).end(), v) != AdjencyList.at(u).end();
}


// Dodaje podaną krawędź.
void ListaSasiedztwaCpp::addEdge(int u, int v)
{
    AdjencyList.at(u).push_back(v);
    AdjencyList.at(v).push_back(u);
}


// Usuwa podaną krawędź.
void ListaSasiedztwaCpp::deleteEdge(int u, int v)
{
    AdjencyList.at(u).erase(remove(AdjencyList.at(u).begin(), AdjencyList.at(u).end(), v), AdjencyList.at(u).end());
    AdjencyList.at(v).erase(remove(AdjencyList.at(v).begin(), AdjencyList.at(v).end(), u), AdjencyList.at(v).end());
}


// Przekształca reprezentację tekstową grafu w graf.
void ListaSasiedztwaCpp::fromString(const char* text)
{
    int k = 0;
    __order = text[0] - 63;
    if (__order < 1 || __order > 16)
    {
        std::stringstream ss;
        ss << "wrong character: " << std::to_string(__order + 63);
        const char* converted = ss.str().c_str();
        throw G6Error(converted);
    }

    for (int i = 0; i < __order; i++)
    {
        std::vector<int> newList;
        AdjencyList.push_back(newList);
    }

    for (int charIndex = 1; charIndex < __order; charIndex++) {
        int c = text[charIndex] - 63;

        for (int v = 0; v < __order; v++)
        {
            for (int u = 0; u < v; u++)
            {
                if (k == 0)
                    c = text[charIndex] - 63;
                if (c < 0 || c > 63)
                {
                    std::stringstream ss;
                    ss << "wrong character: " << std::to_string(c + 63);
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
const char* ListaSasiedztwaCpp::__str__()
{
    int k = 0;
    int c = 0;
    char* text = new char[1];
    char* char_type = new char[std::to_string(__order + 63).length()];
    strcpy(char_type, std::to_string(__order + 63).c_str());
    
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
                text = strcat(text, std::to_string(c + 63).c_str());
                k = 6;
                c = 0;
            }
            k -= 1;
        }
    }
    if (k != 5)
        text = strcat(text, std::to_string(c + 63).c_str());
    return text;
}


// Test równości dwóch reprezentacji grafów.
bool ListaSasiedztwaCpp::__eq__(ListaSasiedztwaCpp other)
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
bool ListaSasiedztwaCpp::__ne__(ListaSasiedztwaCpp other)
{
    return !__eq__(other);
}

