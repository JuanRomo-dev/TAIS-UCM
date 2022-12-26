/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El coste en el peor caso es O(N^2 + K * N^2), donde N es el tamaño de las dimensiones de la matriz y K es el numero de caras del dado.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int resolver(unordered_map<int, int> extremos, int N, int K, int S, int E) {
    // resolver el caso posiblemente llamando a otras funciones
    queue<int> cola;
    vector<int> distancia(N * N + 1);
        
    cola.push(1);
    distancia[1] = 0;

    while (!cola.empty()) {             // Realizamos una búsqueda en profundiad (BFS), probando con el dado según sus caras el camino más corto.
        int posicion = cola.front();
        cola.pop();

        for (int i = 1; i <= K && posicion + i <= N * N; i++) {     // Recorremos todas las caras del dado y las casillas.
            int p = posicion + i;
            if (extremos.count(p)) {
                p = extremos.at(p);
            }
            if (distancia[p] == 0) {
                distancia[p] = distancia[posicion] + 1;
                if (p == N * N) {
                    return distancia[p];
                }
                cola.push(p);
            }
        }
    }
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, K, S, E;         // N es la dimensión del tablero, K el número de caras del dado, S el número de serpientes y E el número de escaleras.

    cin >> N >> K >> S >> E;
    if (N == 0 && K == 0 && S == 0 && E == 0)
        return false;

    int nElems = S + E;
    unordered_map<int, int> extremos;
    int v, w;
    for (int i = 0; i < nElems; i++) {
        cin >> v >> w;
        extremos.insert({ v, w });
    }

    // escribir la solución
    cout << resolver(extremos, N, K, S, E) << '\n';

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
