/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include <queue>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Este problema consiste en que tenemos una serie de localidades o ciudades, que necesitan tener acceso a un aeropuerto, ya sea en la propia localidad o por
 conexión mediante carretera. Entonces, dados el coste de construcción de un aeropuerto y una lista de posibles carreteras entre pares de localidades y sus
 correspondientes costes, tenemos que decidir cuál es la forma más barata de garantizar que todas las localidades tienen acceso a un aeropuerto.
 Para ello vamos a utilizar un grafo valorado de tal forma que los vértices son las distintas localidades, y las aristas son las carreteras que las conectan, siendo
 el valor el coste de cada una de las carreteras. Vamos a emplear al algoritmo de Kruskal para averiguar si todas las localidades están unidas o no, aunque con un 
 matiz, no voy a utilizar el TAD del arbol de recubrimiento mínimo (ARM), ya que no buscamos exactamente tener un sólo arbol, si no averiguar a través del TAD
 de conjuntos disjuntos, si tenemos 1 o más, ya que si hay 1 quiere decir que entonces todas las localidades están conectadas entre sí, necesitando sólo un 
 aeropuerto. En el algoritmo de kruskal, iremos obteniendo cada arista a través de una cola de prioridad con las aristas del grafo, calculando el coste total.
 Finalmente sumaremos al coste total de los aeropuertos el de las carreteras.
 
 En cuanto al de la solución, en el peor de los casos es de O(A * log(A)), donde A es el número de aristas.
@ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Aeropuertos {
private:
    ConjuntosDisjuntos cjtos;           // Utilizaremos los conjuntos disjuntos para averiguar si todas las localidades están unidas. En caso de que no, el número de conjuntos nos idicará cuántos aeropuertos necesitamos (1 por conjunto).
    int coste;          // Para calcular el coste de construir las carreteras.

    void kruskal(GrafoValorado<int> const& localidades) {
        auto aristas = localidades.aristas();
        priority_queue<Arista<int>, vector<Arista<int>>, greater<Arista<int>>> pq(aristas.begin(), aristas.end());
        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno();
            int w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                coste += a.valor();
            }
        }

    }

public:
    Aeropuertos(GrafoValorado<int> const& localidades) : cjtos(localidades.V()), coste(0) {
        kruskal(localidades);
    }

    int costeCarreteras() {
        return coste; 
    }

    int aeropuertosNecesarios() {
        return cjtos.num_cjtos();
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M, A;      // Número de localidades, Número de caminos posibles que se pueden construir, coste de construir un aeropuerto.

    cin >> N >> M >> A;
    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> localidades(N);  // Grafo valorado en el que los vértices son las localidades y las aristas los caminos entre ellas, siendo el valor el coste de construir el camino.
    int X, Y, C;        // X, Y localidades a unir, C el coste del camino entre X e Y.
    for (int i = 0; i < M; i++) {
        cin >> X >> Y >> C;
        if(C < A)
            localidades.ponArista({ X - 1,Y - 1, C });
    }

    // resolver el caso posiblemente llamando a otras funciones
    Aeropuertos aeropuertos(localidades);

    // escribir la solución
    int costeConstruccion = aeropuertos.aeropuertosNecesarios() * A;
    cout << aeropuertos.costeCarreteras() + costeConstruccion << " " << aeropuertos.aeropuertosNecesarios() << '\n';


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