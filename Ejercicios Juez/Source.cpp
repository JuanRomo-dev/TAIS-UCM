
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

 Para resolver el problema, utilizamos dos colas de prioridad. Una para los p�jaros que est�n a la izquierda del que va primero, y la otra estar�
 ordenada de menor a mayor para que en el primer elemento siempre est� el primer p�jaro. A continuaci�n llamaremos a la funci�n edadPrimero, en la cu�l
 se a�adir� a la pareja a la bandada seg�n las edades de los p�jaros, pudiendo ser menor o mayor que el que iba primero.

 El coste del algoritmo es O((log N) * M) siendo N el n�mero de p�jaros que hay en total, y M la suma de los elementos en las colas izq y der.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

void edadPrimero(PriorityQueue<int, greater<int>>& pajarosLadoIzq, PriorityQueue<int>& pajarosLadoDer, int aux1, int aux2) {
    int primer = pajarosLadoDer.top();      // Cogemos el p�jaro que va primero.
    int aux;

    // Ahora dividimos en casos para ver a donde colocamos a cada uno de los miembros de la pareja, si a la derecha o a la izquierda.
    if (aux1 < primer && aux2 < primer) {
        pajarosLadoIzq.push(aux1);          // Como los 2 p�jaros de la pareja son mas j�venes que el primero, se colocan a la izquierda.
        pajarosLadoIzq.push(aux2);

        // Como ahora hay m�s a la izquierda que a la derecha, reordenamos, colocando a uno de la izquierda a la derecha.
        aux = pajarosLadoIzq.top();
        pajarosLadoIzq.pop();
        pajarosLadoDer.push(aux);
    }
    else if (aux1 > primer && aux2 > primer) {  // Los 2 p�jaros tienen m�s edad que el que est� al frente, as� que se coloca la pareja a la derecha.
        pajarosLadoDer.push(aux1);
        pajarosLadoDer.push(aux2);

        // Como ahora hay m�s p�jaros a la derecha que a la izquierda, reordenamos, coloando a uno de la derecha a la izquierda.
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
    int edadPrimer, nParejas;           // edadPrimer es la edad del primer p�jaro que echa a volar, y nParejas es el n�mero de parejas que se ir�n uniendo despu�s.

    cin >> edadPrimer >> nParejas;
    if (edadPrimer == 0 && nParejas == 0)   // Caso final.
        return false;

    int aux1, aux2;                         // Para leer cada uno de los miembros de la pareja.
    PriorityQueue<int, greater<int>>  pajarosLadoIzq;     // Cola de prioridad para los p�jaros a la izquierda del primero.
    PriorityQueue<int> pajarosLadoDer;     // Cola de prioridad para los p�jaros a la derecha del primero.
    pajarosLadoDer.push(edadPrimer);        // Guardamos al p�jaro que est� primero en la cola de la derecha, ya que como est� ordenada de menor a mayor, el primer elemento siempre ser� el primer p�jaro.
    for (int i = 0; i < nParejas; i++) {
        cin >> aux1 >> aux2;                // Leemos los miembros de la pareja.
        edadPrimero(pajarosLadoIzq, pajarosLadoDer, aux1, aux2);        // Funci�n para ver como colocar a los p�jaros.
        cout << pajarosLadoDer.top() << " ";
    }
    cout << '\n';

    // resolver el caso posiblemente llamando a otras funciones

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