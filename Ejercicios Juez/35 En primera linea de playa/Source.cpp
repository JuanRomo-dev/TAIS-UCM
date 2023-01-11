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

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int resolver(vector<pair<int, int>> const& edificios, int N) {
    int nPasadizos = 1;
    int aux = edificios[0].first;

    for (int i = 1; i < N; i++) {
        if (edificios[i].second >= aux) {
            nPasadizos++;
            aux = edificios[i].first;
        }
        
    }
    
    return nPasadizos;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;      // Número de edificios.

    cin >> N;
    if (N == 0)
        return false;

    int w, e;       // Extremos más occidental y más oriental de un edificio.
    vector<pair<int, int>> edificios(N);    // Vector para guardar los extremos de cada edificio.
    for (int i = 0; i < N; i++) {
        cin >> w >> e;
        edificios[i].first = e;     // Ordenamos por el final de cada edificio
        edificios[i].second = w;
    }
    
    sort(edificios.begin(), edificios.end());

    // resolver el caso posiblemente llamando a otras funciones
    int sol = resolver(edificios, N);

    // escribir la solución
    cout << sol << '\n';

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
