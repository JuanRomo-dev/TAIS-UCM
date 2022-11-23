
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

class UsuariosNoticia {
public:
    UsuariosNoticia(Grafo const& g) : visitados(g.V(), false) {

    }
private:
    vector<bool> visitados;
    int dfs() {

    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;          // N es el número de usuarios de la red y M es el número de grupos;

    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;

    int nUsuarios, aux, anterior;       // nUsuarios es el número de usuarios de un grupo, aux para leer cada miembro del grupo y en anterior se va guardando el usuario leído antes para poder unir aristas.
    Grafo g(N);
    for (int i = 0; i < M; i++) {       // Recorremos el número de grupos.
        cin >> nUsuarios;
        if (nUsuarios != 0) {
            cin >> anterior;            // Leemos el primer miembro del grupo
        }
        for (int j = 1; j < nUsuarios; j++) {
            cin >> aux;
            g.ponArista(anterior - 1, aux - 1);
            anterior = aux;
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    UsuariosNoticia uNoticia(g);

    // escribir la solución

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