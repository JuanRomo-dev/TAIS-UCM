/*
 * MUY IMPORTANTE: Solo se corregir�n los comentarios y el c�digo
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificaci�n fuera de esas etiquetas no ser� corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes hab�is hecho esta soluci�n:
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Tenemos 2 valores, el n�mero de cajas abiertas (N) y el n�mero de clientes esperando (C). Luego seg�n avance el bucle se ir� leyendo el tiempo que tardar� cada cliente
 en pasar por la caja. Si por ejemplo tenemos 2 clientes, uno tarda 5 y el otro 10, entonces la caja que tarda 5 se quedar� vac�a antes y ser� por la que pase Ismael.
 Tambi�n tendremos la variable numCajasAtendiendo, que es el n�mero de cajas que est�n ocupadas en ese momento. Por otro lado, la priority queue tiene el tipo caja, que es
 un struct que contiene el numero de la caja (caja 1, caja 2 etc) y el tiempo de espera para que esa caja se quede vac�a. Al ir leyendo el tiempo de cada cliente, si el
 n�mero de cajas que est�n atendiendo en ese momento es menor que el n�mero de cajas abiertas, entonces tiene que pasar un cliente a una de las cajas abiertas, por lo que
 insertamos en la priority queue el numCajasAtendiendo como numCaja, ya que es la siguiente y el tiempo que tarda ese cliente en pasar por caja. Por otro lado, si resulta
 que no se cumple la condici�n anteriormente establecida, quiere decir que todas las cajas est�n ocupadas, por lo que la que tenga el tiempo de espera m�s bajo se extrae de
 la cola y se establece la cola seg�n la prioridad de m�nimos ordenando seg�n la que menos tiempo va a tardar (como se puede ver en la funci�n operator<).

 El coste de la funci�n es O(N log(N)).

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo (despu�s de la marca)
 //@ <answer>

struct caja {
    int numCaja;            // N�mero de la caja para el caso de que los tiempos de espera sean iguales.
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
    int N, C;               // N�mero de cajas abiertas (N) y n�mero de clientes esperando (C).
    cin >> N >> C;
    if (N == 0 && C == 0)
        return false;

    // leer el resto del caso y resolverlo
    int tiempo, numCajasAtendiendo = 0;             // Tiempo que tardar� cada cliente en ser atendido y n�mero de cajas atendiendo en ese momento.
    priority_queue<caja> fila;
    for (int i = 0; i < C; i++) {                           // Coste: O(N log(N)), siendo N el n�mero de clientes esperando.
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

    if (numCajasAtendiendo < N) {                   // Caja en la que ser� atendido Ismael.
        cout << numCajasAtendiendo + 1 << '\n';
    }
    else {
        cout << fila.top().numCaja + 1 << '\n';
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

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
