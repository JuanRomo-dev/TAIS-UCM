/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include <queue>
#include <vector>
#include "ConjuntosDisjuntos.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema a resolver consiste en que tenemos una serie de islas, en las cuáles tenemos una serie de puentes a construir con un cierto coste, y queremos saber si podemos
 conectar todas las islas de tal forma que el coste total de los puentes sea el mínimo posible. Para ello, vamos a imaginar las islas y los puentes como un grafo valorado, en el
 cuál, las islas serán los vértices, y los puentes las aristas, siendo el valor de estas el coste de construir cada puente. De esta manera, utilizaremos el algoritmo de Kruskal,
 que sirve para buscar arboles de recubrimiento mínimo (ARM), es decir, un subgrafo que conecta todos los vértices del grafo original, tal que la suma de los costes de las aristas
 sea mínima. En la clase ARM_Kruskal, tenemos un vector de aristas para indicar que aristas formarán parte de este ARM, y un coste para ir calculando el mínimo. También haremos
 uso de los Conjuntos Disjuntos, ya que nos servirá para que no se formen ciclos y ver si 2 vértices están unidos. En el algoritmo en sí, tendremos una cola de prioridad
 de las aristas ordenadas por su coste para ir viendo cuáles nos convienen seguir. De esta forma iremos marcando que puentes colocar o no dependiendo de si las islas estaban
 ya unidas por otros vértices o no. En el momento en el que consigamos construir un ARM del tamaño de los vértices del grafo, ya sabremos que sí es posible unir todas las islas,
 devolviendo el coste total de unirlas por los puentes. En caso contrario, si hemos recorrido toda la pq, quiere decir que no se pueden unir todas las islas, por lo que 
 no tendremos puentes suficientes.

 El coste en el peor de los casos es O(A * log(A)), siendo A el número de aristas del grafo, produciéndose A vueltas al bucle de hasta A aristas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ARM_Kruskal {
private:
    vector<Arista<int>> _ARM;       // Vector de aristas para indicar como es el árbol de recubrimiento mínimo.
    ConjuntosDisjuntos cjtos;       // Conjuntos disjuntos
    int coste;                      // Coste de la suma de los valores de las aristas.

    void kruskal(GrafoValorado<int> const& islas) {         // Algoritmo de Kruskal para averiguar un árbol de recubrimiento mínimo en un grafo conexo.
        auto aristas = islas.aristas();     
        priority_queue<Arista<int>, vector<Arista<int>>, greater<Arista<int>>> pq(aristas.begin(), aristas.end());      // Cola de prioridad para procesar las aristas en orden.
        while (!pq.empty()) {
            auto a = pq.top();      // Obtenemos la arista.
            pq.pop();
            int v = a.uno(), w = a.otro(v);     // Obtenemos los vértices de la arista.
            if (!cjtos.unidos(v, w)) {      // Si no están los vértices (islas) unidos
                cjtos.unir(v, w);       // Los unimos por una arista (puente)
                _ARM.push_back(a);      // Marcamos la arista en el ARM.
                coste += a.valor();     // Aumentamos el coste que llevamos hasta el momento en el total.
                if (_ARM.size() == islas.V() - 1) {     // Si todas las islas son alcanzables con los puentes dados, interrumpimos la búsqueda, pues ya lo hemos encontrado.
                    break;
                }
            }
        }
    }

public:
    ARM_Kruskal(GrafoValorado<int> const& islas) : coste(0), cjtos(islas.V()) {
        kruskal(islas);
    }

    int costeARM() const {
        return coste;
    }

    bool suficientes() const {
        return cjtos.num_cjtos() == 1;
    }
 
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int I;  // Número de islas del archipiélago.
    cin >> I;

    if (!std::cin)  // fin de la entrada
        return false;

    int P; // Número de puentes presupuestados.
    cin >> P;

    GrafoValorado<int> islas(I);    // Grafo valorado en el que los vértices son las islas, y las aristas valoradas los puentes entre las islas y su coste.
    int v, w, costePuente;          // v y w son las 2 islas que unen un puente, y costePuente es el coste de ese puente.
    for (int i = 0; i < P; i++) {
        cin >> v >> w >> costePuente;
        islas.ponArista({ v - 1, w - 1, costePuente });
    }
    
    ARM_Kruskal arm(islas);

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    if (arm.suficientes()) {
        cout << arm.costeARM();
    }
    else {
        cout << "No hay puentes suficientes";
    }
    cout << '\n';

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
