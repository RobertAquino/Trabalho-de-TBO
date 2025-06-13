#include <iostream>
#include "Bibliotecas/arrayList.hpp"

int main()
{
    ArrayList<int> lista;

    lista.add(3);
    lista.add(6);
    lista.add(10);
    lista.add(3);
    lista.add(8);
    
    lista.print();   
    std::cout << lista[2] << std::endl;
    
    lista.removeAt(2);
    lista.removeAll(3);

    lista.print();

    for(int i = 0; i < lista.getSize(); i++)
    {
        std::cout << "Valor: " << lista[i] << std::endl;
    }
    return 0;
}