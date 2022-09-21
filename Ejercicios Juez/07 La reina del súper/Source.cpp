/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Juan Romo Iribarren TAIS 89
  * Estudiante 2:
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Tenemos 2 valores, el número de cajas abiertas (N) y el número de clientes esperando (C). Luego según avance el bucle se irá leyendo el tiempo que tardará cada cliente
 en pasar por la caja. Si por ejemplo tenemos 2 clientes, uno tarda 5 y el otro 10, entonces la caja que tarda 5 se quedará vacía antes y será por la que pase Ismael.
 También tendremos la variable numCajasAtendiendo, que es el número de cajas que están ocupadas en ese momento. Por otro lado, la priority queue tiene el tipo caja, que es
 un struct que contiene el numero de la caja (caja 1, caja 2 etc) y el tiempo de espera para que esa caja se quede vacía. Al ir leyendo el tiempo de cada cliente, si el
 número de cajas que están atendiendo en ese momento es menor que el número de cajas abiertas, entonces tiene que pasar un cliente a una de las cajas abiertas, por lo que
 insertamos en la priority queue el numCajasAtendiendo como numCaja, ya que es la siguiente y el tiempo que tarda ese cliente en pasar por caja. Por otro lado, si resulta
 que no se cumple la condición anteriormente establecida, quiere decir que todas las cajas están ocupadas, por lo que la que tenga el tiempo de espera más bajo se extrae de
 la cola y se establece la cola según la prioridad de mínimos ordenando según la que menos tiempo va a tardar (como se puede ver en la función operator<).

 El coste de la función es O(N log(N)).

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct caja {
    int numCaja;            // Número de la caja para el caso de que los tiempos de espera sean iguales.
    int espera;             // Tiempo de espera para que una caja quede libre.
};

bool operator<(caja const& a, caja const& b) {
    if (a.espera == b.espera) return b.numCaja < a.numCaja;
    else {
        return b.espera < a.espera;
    }
}

bool resuelveCaso() {

    // leemos la entrada
    int N, C;               // Número de cajas abiertas (N) y número de clientes esperando (C).
    cin >> N >> C;
    if (N == 0 && C == 0)
        return false;

    // leer el resto del caso y resolverlo
    int tiempo, numCajasAtendiendo = 0;             // Tiempo que tardará cada cliente en ser atendido y número de cajas atendiendo en ese momento.
    priority_queue<caja> fila;
    for (int i = 0; i < C; i++) {                           // Coste: O(N log(N)), siendo N el número de clientes esperando.
        cin >> tiempo;
        if (numCajasAtendiendo < N) {
            fila.push({ numCajasAtendiendo, tiempo });      // O(log N).
            numCajasAtendiendo++;
        }
        else {
            caja c = fila.top();                            // O(1).   
            fila.pop();                                     // O(log N).
            fila.push({ c.numCaja, tiempo + c.espera });    // O(log N).

        }
    }

    if (numCajasAtendiendo < N) {                   // Caja en la que será atendido Ismael.
        cout << numCajasAtendiendo + 1 << '\n';
    }
    else {
        cout << fila.top().numCaja + 1 << '\n';
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

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
