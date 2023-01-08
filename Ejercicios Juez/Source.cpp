/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
#include "IndexPQ.h"
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Coste: O(A * log(V))

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class Colegio {
public:
    Colegio(GrafoValorado<int> g) : dist(g.V(), INF), pq(g.V()), caminos(g.V()) {
        dist[0] = 0;
        caminos[0] = 1;
        pq.push(0, 0);
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v)) {
                relajar(a, v);
            }
        }
    }

    int distanciaMin() const {
        return caminos[caminos.size() - 1];
    }

private:
    const int INF = std::numeric_limits<int>::max();
    vector<int> dist;
    IndexPQ<int> pq;
    vector<int> caminos;

    void relajar(Arista<int> a, int v) {
        int w = a.otro(v);
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            caminos[w] = caminos[v];
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor()) {      // Si hemos encontrado otro camino de coste minimo.
            caminos[w] += caminos[v];
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, C;      // Numero de intersecciones y n�mero de calles.

    cin >> N >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> g(N);
    int v, w, longitud;
    for (int i = 0; i < C; i++) {
        cin >> v >> w >> longitud;
        g.ponArista({ v - 1, w - 1, longitud });
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la soluci�n
    Colegio cole(g);

    cout << cole.distanciaMin() << '\n';

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