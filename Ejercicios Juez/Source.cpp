/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void resolver(vector<int> const& dianas, int valor, int s) {
    Matriz<EntInf> dardos(s + 1, valor + 1, Infinito);

    for (int i = 0; i <= s; ++i) {
        dardos[i][0] = 0;
    }

    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= valor; ++j) {
            if (dianas[i] > j) {
                dardos[i][j] = dardos[i - 1][j];
            }
            else {
                dardos[i][j] = min(dardos[i - 1][j], dardos[i][j - dianas[i]] + 1);
            }
        }
    }

    auto sol = dardos[s][valor];
    if (sol == Infinito) {
        cout << "Imposible\n";
    }
    else {
        cout << sol << ':';
        int i = s; int j = valor;
        while (j > 0) {
            if (dianas[i] <= j && dardos[i][j] == dardos[i][j - dianas[i]] + 1) {
                cout << ' ' << dianas[i];
                j -= dianas[i];
            }
            else {
                --i;
            }
        }
        cout << '\n';
    }

}

bool resuelveCaso() {
    // leer los datos de la entrada
    int valor, s;   // Valor que hay que conseguir sumar tirando dardos a una diana y el número de sectores en los que está dividida la diana.

    cin >> valor >> s;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> dianas(s + 1);
    for (int i = 1; i <= s; i++) {
        cin >> dianas[i];
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    resolver(dianas, valor, s);

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