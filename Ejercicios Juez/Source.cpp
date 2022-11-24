/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Grafo.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

class Red {
public:
    Red(Grafo const& g) : visitados(g.V(), false), anterior(g.V()), distancia(g.V()), s(s) {
        bfs(g);
    }
    int getDistancias(int i) {
        return distancia[i];
    }

private:
    vector<bool> visitados;         // Vector para marcar que vértices han sido ya visitados. (¿Hay camino de s a v?)
    vector<int> anterior;           // Vector para marcar el vértice anterior. (Último vértice antes de llegar a v).
    vector<int> distancia;          // Distancia a la que se encuentra el vértice del origen. (Aristas en el camino s-v más corto).
    int s;                          // Vértice origen desde el que deseamos buscar caminos más cortos.
    void bfs(Grafo const& g) {
        queue<int> cola;            // Cola para guardar los vértices alcanzados de los que aún no se han explorado sus adyacentes.
        distancia[0] = 0;           // Como es el vértice origen la distancia es 0.
        visitados[s] = true;        // Marcamos el vértice origen como visitado.
        cola.push(s);               // Lo añadimos a la cola para comenzar a explorar sus adyacentes.
        while (!cola.empty()) {
            int v = cola.front();
            cola.pop();
            for (int w : g.ady(v)) {
                if (!visitados[w]) {
                    anterior[w] = v;
                    distancia[w] = distancia[v] + 1;
                    visitados[w] = true;
                    cola.push(w);
                }
            }
        }
    } 
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, C;           // N es el número de nodos de la red y C es el número de conexiones entre nodos de la red.

    cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    int v, w;       // v y w son los nodos a guardar en el grafo por cada línea.
    Grafo g(N);
    for (int i = 0; i < N; i++) {   // Construimos el grafo uniendo los pares de nodos.
        cin >> v >> w;
        g.ponArista(v, w);
    }

    int k;          // k es el número de consultas a realizar para ver cuántos nodos no son accesibles desde el nodo inicial.
    cin >> k;

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    Red red(g);
    int s, ttl;
    for (int i = 0; i < k; i++) {
        cin >> s >> ttl;
        cout << red.getDistancias(i) << '\n';
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