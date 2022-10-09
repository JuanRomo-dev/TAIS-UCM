/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"
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

void calculaHoras(PriorityQueue<int, less<int>> pilasA, PriorityQueue<int, less<int>> pilasB, int N) {
    int horasVuelo = 0, aux1, aux2;

    if (pilasA.top() < pilasB.top()) {
        aux1 = pilasA.top();
        horasVuelo += aux1;
        aux2 = pilasB.top();
        aux2 -= aux1;

        pilasB.pop();
        pilasB.push(aux2);
        pilasA.pop();
    }
    else if (pilasA.top() > pilasB.top()) {
        aux1 = pilasB.top();
        horasVuelo += aux1;
        aux2 = pilasA.top();
        aux2 -= aux1;

        pilasA.pop();
        pilasA.push(aux2);
        pilasB.pop();
    }
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, A, B;                        // N es el n�mero de drones que tenemos, A es el n�mero de pilas de 9 V y B es el n�mero de pilas de 1.5 V.

    cin >> N >> A >> B;
    if (!std::cin)  // fin de la entrada
        return false;

    PriorityQueue<int, less<int>> pilasA, pilasB;  // pilasA es una cola de prioridad de m�nimos de las pilas de tipo A, y pilasB es una cola de pilas de tipo B.

    int aux;                                       // Para ir leyendo el n�mero de horas de vuelo que permite cada pila.
    for (int i = 0; i < A; i++) {                  // Leemos el n�mero de horas de vuelo que permite cada pila tipo A, guardandolo en la cola.
        cin >> aux;
        pilasA.push(aux);
    }

    for (int j = 0; j < B; j++) {                   // Lo mismo para las pilas tipo B.
        cin >> aux;
        pilasB.push(aux);
    }

    // resolver el caso posiblemente llamando a otras funciones
    calculaHoras(pilasA, pilasB, N);
    // escribir la soluci�n

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