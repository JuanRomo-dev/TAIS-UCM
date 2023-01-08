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
#include <queue>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El coste es O(K * (A * log(V) + (V + A))), donde k es el número de consultas, A * log(V) es el coste del algoritmo de Dijsktra y V + A el coste de BFS.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Camino {
public:
    Camino(GrafoValorado<int> const& g, int const& ini, int const& fin) : distBFS(g.V(), INF), dist(g.V(), { 0, INF }), pq(g.V()), hayCamino(false), caminoCoinciden(false) {
        bfs(g, ini);
        if (distBFS[fin] != INF) {      //Si se ha explorado el último vértice, entonces la distancia respecto al origen no es INF y por tanto existe un camino.
            dist[ini] = { 0, 0 };      // La distancia del origen respecto al origen es 0.
            pq.push(ini, {0, 0});    // Lo añadimos a la cola de prioridad.
            while (!pq.empty()) {       // Buscamos con el algoritmo de Dijskstra caminos de coste mínimo según el valor de las aristas.
                int v = pq.top().elem;  
                pq.pop();
                for (auto a : g.ady(v)) {   // Recorremos los adyacentes, relajando las arista.
                    relajar(a, v);
                }
            }

            hayCamino = true;       // Marcamos que existe camino.

            if (dist[fin].first == distBFS[fin]) {        // Si la distancia hasta la última intersección es la misma en ambos recorridos, lo marcamos.
                caminoCoinciden = true;
            }
        }
    }

    bool existeCamino() const {
        return hayCamino;
    }

    bool coincidenCaminos() const {
        return caminoCoinciden;
    }

    int distanciaMinima(int n) {
        return dist[n].second;
    }

private:
    const int INF = std::numeric_limits<int>::max();        // Para marcar que aún no ha sido explorado se indica que la distancia respecto al origen es infinita.
    IndexPQ<pair<int, int>> pq;
    vector<int> distBFS;        // Para el recorrido en anchura para buscar el camino mínimo de ini a fin.
    vector<pair<int,int>> dist;     // Para llevar la cuenta de cuántas intersecciones se están recorriendo en Dijkstra y luego así comparar con los recorridos por BFS y tambien el coste.
    bool hayCamino;         // Para marcar si existe camino o no entre el origen y el final.
    bool caminoCoinciden;   // Para marcar si además de haber camino, coinciden el camino más corto en intersecciones (BFS) con el de coste (Dijkstra).

    void bfs(GrafoValorado<int> const& g, int const& ini) {     // Recorrido en anchura para encontrar el camino más corto pasando por el menor número de calles posibles.
        distBFS[ini] = 0;
        queue<int> q;
        q.push(ini);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto a : g.ady(v)) {       // Recorremos los adyacentes a v, buscando el camino más corto.
                int w = a.otro(v);          // Obtenemos un adyacente
                if (distBFS[w] == INF) {    // Si no ha sido explorado
                    distBFS[w] = distBFS[v] + 1; // Marcamos que lo hemos explorado aumentando en 1 su distancia respecto al origen.
                    q.push(w);      // Lo guardamos en la cola para después explorar sus adyacentes.
                }
            }
        }
    }

    void relajar(Arista<int> a, int v) {
        int w = a.otro(v);
        if (dist[w].second > dist[v].second + a.valor()) {    // Si es un camino mínimo se marca.
            dist[w].second = dist[v].second + a.valor();
            dist[w].first = dist[w].first + 1;
            pq.update(w, dist[w]);
        }
        else if (dist[w].second == dist[v].second + a.valor() && dist[w].first > dist[v].first + 1) { // En caso de que el coste sea el mismo y el número de vertices es mayor
            dist[w].first = dist[v].first + 1;          // Aumenta el numero de vertices al camino con menor coste
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, C;      // Número de intersecciones y de calles.

    cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    int v, w, longitud;       // Intersecciones que unen una calle y longitud de la calle.
    GrafoValorado<int> g(N);
    for (int i = 0; i < C; i++) {
        cin >> v >> w >> longitud;
        g.ponArista({ v - 1, w - 1, longitud });
    }

    int k, ini, fin;      //Número de consultas a realizar, e intersecciones origen y destino.
    cin >> k;


    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    for (int i = 0; i < k; i++) {
        cin >> ini >> fin;
        Camino camino(g, ini - 1, fin - 1);
        if (!camino.existeCamino()) {
            cout << "SIN CAMINO" << '\n';
        }
        else {
            cout << camino.distanciaMinima(fin - 1) << " ";
            if (camino.coincidenCaminos()) {
                cout << "SI" << '\n';
            }
            else {
                cout << "NO" << '\n';
            }
        }
    }

    cout << "---" << '\n';

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
