// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez TAIS89


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree.h"
using namespace std;

bool resolver(BinTree<int> arbin, int& altura, int& maximo, int& minimo) {                                  // El coste en el caso peor de la función es logarítmico O(log n), siendo n el número de nodos.
    if (arbin.empty()) {            // Caso base. Si el árbol es vácío, entonces está equilibrado y es AVL.
        altura = 0;
        minimo = 99999999;
        maximo = 0;
        return true;
    }
    else {                          // Casos recursivos. Comprobamos si el árbol general está equilibrado, es decir, si la diferencia absoluta entre la rama izquierda y la rama derecha es como mucho 1. 
                                    // Además, los nodos a la izquierda deben ser menores a la raíz y los nodos a la derecha deben ser mayores a la raíz.
        int hijoDer, hijIzq, maxIzq, maxDer, minIzq, minDer;

        bool eqIzq = resolver(arbin.left(), hijIzq, maxIzq, minIzq);
        bool eqDer = resolver(arbin.right(), hijoDer, maxDer, minDer);

        if (abs(hijIzq - hijoDer) <= 1 && eqIzq && eqDer && arbin.root() > maxIzq && arbin.root() < minDer) {
            maximo = max(arbin.root(), maxDer);
            minimo = min(arbin.root(), minIzq);
            altura = max(hijIzq, hijoDer) + 1;
            return true;
        }
        else {
            return false;
        }
    }
    
}

bool esAVL(BinTree<int> arbin) {
    int altura, maximo, minimo;
    return resolver(arbin, altura, maximo, minimo);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    BinTree<int> arbin = read_tree<int>(cin);

    if (esAVL(arbin)) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
