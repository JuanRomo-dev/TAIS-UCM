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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
    int valor, s;   // Valor que hay que conseguir sumar tirando dardos a una diana y el n�mero de sectores en los que est� dividida la diana.

    cin >> valor >> s;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> dianas(s + 1);
    for (int i = 1; i <= s; i++) {
        cin >> dianas[i];
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la soluci�n
    resolver(dianas, valor, s);

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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