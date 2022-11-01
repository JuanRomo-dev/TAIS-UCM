/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"
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

class ArbolLibre {
private:
    vector<bool> visit;     // Para ver si el visit[v] (el vértice v) ha sido visitado o no desde el origen (es decir, si hay camino).
    int s, tam, V, A;                 // s es el Vértice origen y tam para contar los vértices conectados, V es el número de vértices y A el número de aristas.

    void dfs(Grafo const& g, int v) {       // Función para realizar el recorrido en profundidad.
        visit[v] = true;                    // Marcamos el vértice v como visitado.
        tam++;
        for (int w : g.ady(v)) {            // Recorremos los vértices adyacentes a v.
            if (!visit[w]) {                // Si el vértice no ha sido visitado, llamamos recursivamente a la función sobre ese vértice.
                dfs(g, w);
            }
        }
    }

public:
    ArbolLibre(Grafo const& g, int s) : visit(g.V(), false), s(s), tam(0), V(g.V()), A(g.A()) {     // Constructora de la clase.
        dfs(g, s);
    }

    bool esArbolLibre() const {
        return (V-1 == A) && (tam == V);    // Si los vértices visitados coinciden con el número de vértices del grafo entonces es un arbol libre.
    }

};

bool resuelveCaso() {
    // leer los datos de la entrada
    int _V;

    cin >> _V;
    if (!std::cin)  // fin de la entrada
        return false;

    int _A, u, w;
    cin >> _A;
    Grafo g(_V);

    for (int i = 0; i < _A; i++) {
        cin >> u >> w;
        if (u != w) {
            g.ponArista(u, w);
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    ArbolLibre arl(g, 0);

    // escribir la solución
    bool esArbolLibre = true;
    for (int i = 0; i < g.V(); i++) {
        if (!arl.esArbolLibre()) {
            esArbolLibre = false;
        }
    }

    if (esArbolLibre) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }

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
