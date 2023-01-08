/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
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

class Navegar {
public:
    Navegar(DigrafoValorado<int> const& grafo, vector<int> const& tiemposCarga) : dist(grafo.V(), INF), pq(grafo.V()) {
        dist[0] = tiemposCarga[0];
        pq.push(0, 0);
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : grafo.ady(v)) {
                relajar(a, tiemposCarga);
            }
        }
    }

    bool hayCamino() const {
        return dist[dist.size() - 1] != INF;
    }

    int tiempoNavegacion() {
        return dist[dist.size() - 1];
    }

private:
    const int INF = std::numeric_limits<int>::max();
    vector<int> dist;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a, vector<int> tiemposCarga) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor() + tiemposCarga[w]) {
            dist[w] = dist[v] + a.valor() + tiemposCarga[w];
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;      // Número de páginas manejadas.

    cin >> N;
    if (N == 0)
        return false;

    vector<int> tiemposCarga(N);
    for (int i = 0; i < N; i++) {
        cin >> tiemposCarga[i];
    }

    int M;      // Número de enlaces entre páginas que se han identificado.
    cin >> M;

    DigrafoValorado<int> grafo(N);
    int u, v, tiempo;       // Página en la que se encuentra, página a la que se va y tiempo que pasa desde que carga la página hasta que se encuentra el enlace.

    for (int i = 0; i < M; i++) {
        cin >> u >> v >> tiempo;
        grafo.ponArista({ u - 1, v - 1, tiempo });
    }

    Navegar nav(grafo, tiemposCarga);

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    if (nav.hayCamino()) {
        cout << nav.tiempoNavegacion();
    }
    else {
        cout << "IMPOSIBLE";
    }
    cout << '\n';

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