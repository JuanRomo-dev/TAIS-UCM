
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

 Para resolver el problema, se representa mediante un grafo donde los v�rtices son las personas y las aristas representan si una persona y otra son amigos. Como se dice que si el 
 v�rtice a es amigo del v�rtice b y el v�rtice b es amigo del v�rtice c entonces a y c son amigos, debemos realizar un recorrido en profundidad sobre el grafo para explorar todos los 
 amigos de un v�rtice v. As� pues una grupo de amigos representa a una componente conexa (un subgrafo en el cu�l todas sus v�rtices est�n conectadas formando un camino). Como
 tenemos que encontrar el grupo de amigos con el mayor tama�o (es decir, la m�xima componente conexa en la cu�l se recorren el mayor n�mero de v�rtices en un grafo), por cada v�rtice,
 se ir� calculando el tama�o de su grupo de amigos y guardaremos el de mayor tama�o.

 En cuanto al coste del algoritmo es (N+ M), donde N es el n�mero de personas (v�rtices) y M el n�mero de relaciones de amistad dadas (v�rtices).
 @ </answer> */

class Amigos {
private:
    vector<bool> visitado;              // Vector para marcar que v�rtices han sido visitados.
    int maximoGrupo;                    // Grupo de amigos de mayor tama�o.
    int dfs(Grafo const& g, int v) {    // B�squeda en profundidad
        visitado[v] = true;             // Marcamos el v�rtice v como visitado.
        int tam = 1;                    // El tama�o del grupo comienza siendo 1.
        for (int w : g.ady(v)) {        // Recorremos los v�rtices adyacentes a v uno a uno.
            if (!visitado[w]) {         // Si el v�rtice adyacente w no ha sido visitado
                tam += dfs(g, w);       // Llamamos recursivamente sobre ese v�rtice w y lo sumamos al tama�o del grupo de amigos.
            }
        }
        return tam;
    }

public :
    Amigos(Grafo const& g) : visitado(g.V(), false), maximoGrupo(0) {       // Constructora de la clase. Inicializamos las posiciones del vector a false ya que a�n ning�n v�rtice ha sido visitado.
        for (int v = 0; v < g.V(); v++) {       // Recorremos los v�rtices del grafo.
            if (!visitado[v]) {         // Si el v�rtice a�n no ha sido visitado
                int tamanyo = dfs(g, v);                    // Calculamos el tama�o del grupo de amigos con una b�squeda en profundidad (dfs).
                maximoGrupo = max(tamanyo, maximoGrupo);    // Comprobamos si es el grupo de m�ximo tama�o de los que hemos explorado.
            }
        }
    }

    int maxim() const {         // Devuelve el grupo de tama�o m�s grande.
        return maximoGrupo;
    }
};

 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

void resuelveCaso() {
    // leer los datos de la entrada
    int N, M;           // N n�mero de personas que viven en la ciudad (en este casos son los v�rtices), M pares de personas que se conocen que son amigas (en este caso son las aristas.

    cin >> N >> M;

    Grafo g(N);         // Grafo para representar grupos de amigos, donde los v�rtices son las personas y las aristas representan si dos personas son amigos.
    int v, w;           // V�rtices de pares de amigos

    for (int i = 0; i < M; i++) {       // Recorremos los pares de amigos para guardarlos en el grafo.
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }

    // resolver el caso posiblemente llamando a otras funciones
    Amigos amigos(g);
    // escribir la soluci�n
    cout << amigos.maxim() << '\n';
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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