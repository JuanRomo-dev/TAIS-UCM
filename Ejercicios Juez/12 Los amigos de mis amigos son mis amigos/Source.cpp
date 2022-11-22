
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

 Para resolver el problema, se representa mediante un grafo donde los vértices son las personas y las aristas representan si una persona y otra son amigos. Como se dice que si el 
 vértice a es amigo del vértice b y el vértice b es amigo del vértice c entonces a y c son amigos, debemos realizar un recorrido en profundidad sobre el grafo para explorar todos los 
 amigos de un vértice v. Así pues una grupo de amigos representa a una componente conexa (un subgrafo en el cuál todas sus vértices están conectadas formando un camino). Como
 tenemos que encontrar el grupo de amigos con el mayor tamaño (es decir, la máxima componente conexa en la cuál se recorren el mayor número de vértices en un grafo), por cada vértice,
 se irá calculando el tamaño de su grupo de amigos y guardaremos el de mayor tamaño.

 En cuanto al coste del algoritmo es (N+ M), donde N es el número de personas (vértices) y M el número de relaciones de amistad dadas (vértices).
 @ </answer> */

class Amigos {
private:
    vector<bool> visitado;              // Vector para marcar que vértices han sido visitados.
    int maximoGrupo;                    // Grupo de amigos de mayor tamaño.
    int dfs(Grafo const& g, int v) {    // Búsqueda en profundidad
        visitado[v] = true;             // Marcamos el vértice v como visitado.
        int tam = 1;                    // El tamaño del grupo comienza siendo 1.
        for (int w : g.ady(v)) {        // Recorremos los vértices adyacentes a v uno a uno.
            if (!visitado[w]) {         // Si el vértice adyacente w no ha sido visitado
                tam += dfs(g, w);       // Llamamos recursivamente sobre ese vértice w y lo sumamos al tamaño del grupo de amigos.
            }
        }
        return tam;
    }

public :
    Amigos(Grafo const& g) : visitado(g.V(), false), maximoGrupo(0) {       // Constructora de la clase. Inicializamos las posiciones del vector a false ya que aún ningún vértice ha sido visitado.
        for (int v = 0; v < g.V(); v++) {       // Recorremos los vértices del grafo.
            if (!visitado[v]) {         // Si el vértice aún no ha sido visitado
                int tamanyo = dfs(g, v);                    // Calculamos el tamaño del grupo de amigos con una búsqueda en profundidad (dfs).
                maximoGrupo = max(tamanyo, maximoGrupo);    // Comprobamos si es el grupo de máximo tamaño de los que hemos explorado.
            }
        }
    }

    int maxim() const {         // Devuelve el grupo de tamaño más grande.
        return maximoGrupo;
    }
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void resuelveCaso() {
    // leer los datos de la entrada
    int N, M;           // N número de personas que viven en la ciudad (en este casos son los vértices), M pares de personas que se conocen que son amigas (en este caso son las aristas.

    cin >> N >> M;

    Grafo g(N);         // Grafo para representar grupos de amigos, donde los vértices son las personas y las aristas representan si dos personas son amigos.
    int v, w;           // Vértices de pares de amigos

    for (int i = 0; i < M; i++) {       // Recorremos los pares de amigos para guardarlos en el grafo.
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }

    // resolver el caso posiblemente llamando a otras funciones
    Amigos amigos(g);
    // escribir la solución
    cout << amigos.maxim() << '\n';
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
