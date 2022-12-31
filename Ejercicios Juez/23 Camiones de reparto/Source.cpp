
/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include <vector>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 En este ejercicio, tenemos una serie de ciudades conectadas por calles, las cuáles poseen una anchura determinada. Tenemos camiones con una cierta
 anchura que queremos averiguar si sería posible atravesar el camino de una ciudad a otra. Para ello utilizamos la búsqueda en profundidad de un
 grafo valorado.
 
 El coste en el caso peor del algoritmo es O(k* (V+A)), donde k son las consultas a realizar, V son los vértices y A las aristas.    

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Reparto {     
private:
    vector<bool> visit;         // Vector para marcar los vértices que se han visitado en la dfs.
    bool puede;         // Para marcar si el camion puede pasar.

    void dfs(GrafoValorado<int> const& intersecciones, int i, int anchuraCamion) {
        visit[i] = true;
        for (auto a : intersecciones.ady(i)) {      // Recorremos las aristas adyacentes al vértice i
            if (a.valor() >= anchuraCamion) {        // Si el valor de la anchura del camion es menor que el de la arista (calle), puede pasar.
                int w = a.otro(i);      
                if (!visit[w]) {            // Si el vértice adyacente w no ha sido visitado, continuamos la dfs por él.
                    dfs(intersecciones, w, anchuraCamion);
                }
            }
        }
    }

public:
    Reparto(GrafoValorado<int> const& intersecciones, int const origen, int const destino, int anchuraCamion) : visit(intersecciones.V(), false), puede(false) {
        dfs(intersecciones, origen, anchuraCamion);
        if (visit[destino]) {       // Si desde el origen se puede llegar al destino.
            puede = true;
        }
    }

    bool puedeRecorrer() {
        return puede;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, E;          // V es el número de intersecciones (vértices), E es el número de calles entre intersecciones (aristas).

    cin >> V >> E;
    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> intersecciones(V);
    int v, w, anchura;   // Para leer las intersecciones que unen una calle y la anchura máxima que puede tener un camión transitando.
    for (int i = 0; i < E; i++) {
        cin >> v >> w >> anchura;
        intersecciones.ponArista({ v - 1, w - 1, anchura });
    }

    int k;      // Número de consultas a realizar
    cin >> k;
    int origen, destino, anchuraCamion;     // Origen y destino para ver si en ese camino puede pasar el camion por la variable anchuraCamion.
    for (int i = 0; i < k; i++) {       // Recorremos las consultas a realizar.
        cin >> origen >> destino >> anchuraCamion;
        Reparto r(intersecciones, origen - 1, destino - 1, anchuraCamion);
        if (r.puedeRecorrer()) {
            cout << "SI";
        }
        else {
            cout << "NO";
        }
        cout << '\n';
    }


    // resolver el caso posiblemente llamando a otras funciones

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
