
/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 El coste sería logarítimo O(log n), ya que en ningún momento recorremos todos los nodos en el caso peor.
 La explicación de las funciones está en TreeSet_AVL.h.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int n;
    
    cin >> n;
    if (n == 0) {
        return false;
    }
    Set<int> conjunto;
    for (int i = 0; i < n; i++) {
        int aux;
        cin >> aux;
        conjunto.insert(aux);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int pos;
        cin >> pos;
        try {
            int a = conjunto.kesimo(pos);
            cout << a << "\n";
        }
        catch (exception){
            cout << "??\n";
        }
    }

    cout << "---\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}