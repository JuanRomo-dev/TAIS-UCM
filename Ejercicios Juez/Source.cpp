
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

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Para resolver el problema, utilizamos dos colas de prioridad. Una para los pájaros que están a la izquierda del que va primero, y la otra estará
 ordenada de menor a mayor para que en el primer elemento siempre esté el primer pájaro. A continuación llamaremos a la función edadPrimero, en la cuál
 se añadirá a la pareja a la bandada según las edades de los pájaros, pudiendo ser menor o mayor que el que iba primero.

 El coste del algoritmo es O((log N) * M) siendo N el número de pájaros que hay en total, y M la suma de los elementos en las colas izq y der.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void edadPrimero(PriorityQueue<int, greater<int>>& pajarosLadoIzq, PriorityQueue<int>& pajarosLadoDer, int aux1, int aux2) {
    int primer = pajarosLadoDer.top();      // Cogemos el pájaro que va primero.
    int aux;

    // Ahora dividimos en casos para ver a donde colocamos a cada uno de los miembros de la pareja, si a la derecha o a la izquierda.
    if (aux1 < primer && aux2 < primer) {
        pajarosLadoIzq.push(aux1);          // Como los 2 pájaros de la pareja son mas jóvenes que el primero, se colocan a la izquierda.
        pajarosLadoIzq.push(aux2);

        // Como ahora hay más a la izquierda que a la derecha, reordenamos, colocando a uno de la izquierda a la derecha.
        aux = pajarosLadoIzq.top();
        pajarosLadoIzq.pop();
        pajarosLadoDer.push(aux);
    }
    else if (aux1 > primer && aux2 > primer) {  // Los 2 pájaros tienen más edad que el que está al frente, así que se coloca la pareja a la derecha.
        pajarosLadoDer.push(aux1);
        pajarosLadoDer.push(aux2);

        // Como ahora hay más pájaros a la derecha que a la izquierda, reordenamos, coloando a uno de la derecha a la izquierda.
        aux = pajarosLadoDer.top();
        pajarosLadoDer.pop();
        pajarosLadoIzq.push(aux);
    }
    else if (aux1 < primer && aux2 > primer) {  // El primer miembro de la pareja es de menor edad que el primero, y el segundo miembro es mayor.
        pajarosLadoDer.push(aux2);
        pajarosLadoIzq.push(aux1);
    }
    else if (aux1 > primer && aux2 < primer) {   // El primer miembro de la pareja es mayor que el primero, y el segundo miembro es menor.
        pajarosLadoDer.push(aux1);
        pajarosLadoIzq.push(aux2);
    }
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int edadPrimer, nParejas;           // edadPrimer es la edad del primer pájaro que echa a volar, y nParejas es el número de parejas que se irán uniendo después.

    cin >> edadPrimer >> nParejas;
    if (edadPrimer == 0 && nParejas == 0)   // Caso final.
        return false;

    int aux1, aux2;                         // Para leer cada uno de los miembros de la pareja.
    PriorityQueue<int, greater<int>>  pajarosLadoIzq;     // Cola de prioridad para los pájaros a la izquierda del primero.
    PriorityQueue<int> pajarosLadoDer;     // Cola de prioridad para los pájaros a la derecha del primero.
    pajarosLadoDer.push(edadPrimer);        // Guardamos al pájaro que está primero en la cola de la derecha, ya que como está ordenada de menor a mayor, el primer elemento siempre será el primer pájaro.
    for (int i = 0; i < nParejas; i++) {
        cin >> aux1 >> aux2;                // Leemos los miembros de la pareja.
        edadPrimero(pajarosLadoIzq, pajarosLadoDer, aux1, aux2);        // Función para ver como colocar a los pájaros.
        cout << pajarosLadoDer.top() << " ";
    }
    cout << '\n';

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