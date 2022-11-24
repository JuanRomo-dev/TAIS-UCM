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

class UsuariosNoticia {
public:
    UsuariosNoticia(Grafo const& g) : visitados(g.V(), false), nUsuarios(g.V()) {       // Constructora de la clase.
        int i = 0;                          // 
        for (int v = 0; v < g.V(); v++) {   // Recorremos los vértices del grafo 
            if (!visitados[v]) {
                int tam = dfs(g, v, i);
                amigos.push_back(tam);
                i++;
            }
        }   
    }
    int getAmigos(int v) {
        return amigos[nUsuarios[v]];
    }

private:
    vector<bool> visitados;
    vector<int> nUsuarios;
    vector<int> amigos;

    int dfs(Grafo const& g, int v, int i) {
        visitados[v] = true;
        nUsuarios[v] = i;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!visitados[w]) {
                tam += dfs(g, w, i);
            }
        }
        return tam;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;          // N es el n�mero de usuarios de la red y M es el n�mero de grupos;

    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;

    int nUsuarios, aux, anterior;       // nUsuarios es el n�mero de usuarios de un grupo, aux para leer cada miembro del grupo y en anterior se va guardando el usuario le�do antes para poder unir aristas.
    Grafo g(N);
    for (int i = 0; i < M; i++) {       // Recorremos el n�mero de grupos.
        cin >> nUsuarios;
        if (nUsuarios != 0) {
            cin >> anterior;            // Leemos el primer miembro del grupo
        }
        for (int j = 1; j < nUsuarios; j++) {   // Vamos leyendo los miembros restantes del grupo
            cin >> aux;
            g.ponArista(anterior - 1, aux - 1); // Ponemos una arista entre cada miembro consecutivo.
            anterior = aux;
        }
    }
    // No es necesario colocar aristas entre cada uno de los miembros de un grupo con el resto, pues si vamos colocando aristas entre
    // cada miembro consecutivo, los anteriores nodos ya están unidos a través de un camino.

    // resolver el caso posiblemente llamando a otras funciones
    UsuariosNoticia uNoticia(g);

    // escribir la soluci�n
    for (int i = 0; i < N; i++) {
        cout << uNoticia.getAmigos(i) << " ";
    }
    cout << '\n';

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