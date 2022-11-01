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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class ArbolLibre {
private:
    vector<bool> visit;     // Para ver si el visit[v] (el v�rtice v) ha sido visitado o no desde el origen (es decir, si hay camino).
    int s, tam, V, A;                 // s es el V�rtice origen y tam para contar los v�rtices conectados, V es el n�mero de v�rtices y A el n�mero de aristas.

    void dfs(Grafo const& g, int v) {       // Funci�n para realizar el recorrido en profundidad.
        visit[v] = true;                    // Marcamos el v�rtice v como visitado.
        tam++;
        for (int w : g.ady(v)) {            // Recorremos los v�rtices adyacentes a v.
            if (!visit[w]) {                // Si el v�rtice no ha sido visitado, llamamos recursivamente a la funci�n sobre ese v�rtice.
                dfs(g, w);
            }
        }
    }

public:
    ArbolLibre(Grafo const& g, int s) : visit(g.V(), false), s(s), tam(0), V(g.V()), A(g.A()) {     // Constructora de la clase.
        dfs(g, s);
    }

    bool esArbolLibre() const {
        return (V-1 == A) && (tam == V);    // Si los v�rtices visitados coinciden con el n�mero de v�rtices del grafo entonces es un arbol libre.
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

    // escribir la soluci�n
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