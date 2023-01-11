/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

int resolver(vector<pair<int,int>> const& trabajo, int C, int F, bool& b) {
    int nTrabajos = 0;
    int ini = C;

    int i = 0;
    while (!b && ini < F) {     // Recorremos el intervalo del planeta.
        int aux = ini;
        while (i < trabajo.size() && trabajo[i].first <= ini) {
            if (trabajo[i].second > aux) {
                aux = trabajo[i].second;
            }
            i++;
        }
        if (aux > ini) {
            nTrabajos++;
            ini = aux;
        }
        else {
            b = true;
        }
    }

    return nTrabajos;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int C, F, N;        // Comienzo y final del intervalo en el que el planeta est� expuesto, n�mero de trabajos de investigaci�n propuestos.

    cin >> C >> F >> N;
    if (C == 0 && F == 0 && N == 0)
        return false;

    int ci, fi;     // Comienzo y final de los intervalos en que cada trabajo utilizar�a el telescopio.
    vector<pair<int, int>> trabajos(N); // Vector de pares que contiene en el primer valor el comienzo del intervalo de un trabajo y el segundo valor, el final.
    for (int i = 0; i < N; i++) {
        cin >> ci >> fi;
        trabajos[i].second = fi;
        trabajos[i].first = ci;     // Ordenamos por el comienzo de los intervalos.
    }
    sort(trabajos.begin(), trabajos.end());     // O(N log(N))

    bool b = false;
    // resolver el caso posiblemente llamando a otras funciones
    int sol = resolver(trabajos, C, F, b);

    // escribir la soluci�n
    if (!b) {
        cout << sol;
    }
    else {
        cout << "Imposible";
    }
    cout << '\n';

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