// RunnableCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../SLZad2/ListaSasiedztwaCpp.h"
#include <iostream>


int main()
{
    //ListaSasiedztwaCpp check = ListaSasiedztwaCpp("I??????_?");
    ListaSasiedztwaCpp check = ListaSasiedztwaCpp("I????????");
    check.addVertex();
    check.deleteVertex(check.order() - 1);
    //ListaSasiedztwaCpp().deleteVertex(0);
    const char* wynik = check.__str__();
    std::cout << *wynik;
    std::cout << check.order();
    return 0;
}

