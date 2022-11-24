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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

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
    vector<bool> visitados;         // Vector para marcar que v�rtices han sido ya visitados. (�Hay camino de s a v?)
    vector<int> anterior;           // Vector para marcar el v�rtice anterior. (�ltimo v�rtice antes de llegar a v).
    vector<int> distancia;          // Distancia a la que se encuentra el v�rtice del origen. (Aristas en el camino s-v m�s corto).
    int s;                          // V�rtice origen desde el que deseamos buscar caminos m�s cortos.
    void bfs(Grafo const& g) {
        queue<int> cola;            // Cola para guardar los v�rtices alcanzados de los que a�n no se han explorado sus adyacentes.
        distancia[0] = 0;           // Como es el v�rtice origen la distancia es 0.
        visitados[s] = true;        // Marcamos el v�rtice origen como visitado.
        cola.push(s);               // Lo a�adimos a la cola para comenzar a explorar sus adyacentes.
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
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, C;           // N es el n�mero de nodos de la red y C es el n�mero de conexiones entre nodos de la red.

    cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    int v, w;       // v y w son los nodos a guardar en el grafo por cada l�nea.
    Grafo g(N);
    for (int i = 0; i < N; i++) {   // Construimos el grafo uniendo los pares de nodos.
        cin >> v >> w;
        g.ponArista(v, w);
    }

    int k;          // k es el n�mero de consultas a realizar para ver cu�ntos nodos no son accesibles desde el nodo inicial.
    cin >> k;

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la soluci�n
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