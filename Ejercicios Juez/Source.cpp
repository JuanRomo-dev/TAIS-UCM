/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Este problema consiste en que originalmente se da un número, y decidiendo cada vez que botón pulsar alcanzar un número dado en el menor número de pulsaciones
 posibles. Es decir, debemos de buscar caminos mínimos, por lo que realizaremos una búsqueda en anchura desde el número origen probando cada vez una operación dada.
 Cuando encontremos el número destino tras pulsar una serie de botones se devolverá el número de pulsaciones total de los botones.

 En cuanto al coste del algoritmo se encuentra en O(V + A), donde V en este caso son todos los posibles números calculados entre el origen y el destino y las aristas
 son las operaciones realizadas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int MAX_DIGITOS = 10000;  // Máximo de dígitos de la máquina calculadora, ya que solo puede tener hasta 4 dígitos.
const int INF = INT_MAX;        // Infinito (en realidad es el máximo valor que puede tener un int).

int adyacente(int v, int i) {   // Posibles botones que pulsar para ir calculando números que nos puedan llevar al destino
    switch (i) {
    case 0: return (v + 1) % MAX_DIGITOS;           // Sumar 1. Como se puede desbordar del máximo de dígitos de la máquina se hace módulo 10.000.
    case 1: return (v * 2) % MAX_DIGITOS;           // Multiplicar 2. "                                                                             "
    case 2: return v / 3;                           // Dividir entre 3. En este caso no hace falta el módulo 10.000 pues nunca se va a desbordar. 
    }
}

int bfs(int const& origen, int const& destino) {    // Búsqueda en anchura.
    if (origen == destino) {
        return 0;
    }
    vector<int> distancia(MAX_DIGITOS, INF);    // El vector distancia tendrá un espacio MAX_DIGITOS, ya que la distancia entre el origen y el destino podría ser máximo ese valor
                                                // y cada valor del vector será INF (infinito) para marcar como que aún no ha sido visitado.
    distancia[origen] = 0;                      // La distancia del origen es 0.
    queue<int> q;
    q.push(origen);                             // Añadimos el origen a la cola;
    while (!q.empty()) {                        // Mientras haya números por explorar en la cola de prioridad.
        int v = q.front();
        q.pop();
        for (int i = 0; i < 3; i++) {
            int w = adyacente(v, i);                    // Se calcula el siguiente número adyacente por alguna de las operaciones según el valor de la i.
            if (distancia[w] == INF) {                             // Si w no ha sido explorado aún
                distancia[w] = distancia[v] + 1;        // Se marca como visitado aumentando la distancia respecto al origen.
                if (w == destino) {
                    return distancia[w];                // Si resulta que hemos alcanzado el destino, se devuelve la distancia a la que se encuentra del origen.
                }
                else {
                    q.push(w);                          // Si no se añade a la cola para buscar en anchura más adelante.
                }
            }
        }
    }

}

bool resuelveCaso() {
    // leer los datos de la entrada
    int origen, destino;                        // Origen es el número que se da al principio en la máquina y destino el que se debe lograr pulsando los botones

    cin >> origen >> destino;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    int nPulsaciones = bfs(origen, destino);

    // escribir la solución
    cout << nPulsaciones << '\n';

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