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

 Para resolver el problema, he utlizado dos colas de prioridad, una para pilas de tipo A y otra para pilas de tipo B. En la función calculaHoras,
 para todos los drones vamos viendo que pila utilizar y calculamos el total de horas de vuelo realizadas. Para ello vamos viendo del primer
 elemento de cada cola cuál es el que tiene menos batería. Sumamos las horas de esa pila a las de vuelo y le quitamos las horas correspondientes
 a las pilas. Si alguna de esas pilas sigue teniendo batería las guardamos en un vector para volver a utlizarlas más adelante. Finalmente,
 las pilas que han quedado guardadas en los vectores, se vuelven a añadir a las colas.

 El coste del algoritmo es O(N log(A + B)), siendo N el número de drones que tenemos, A el número de pilas de 9 V y B el número de pilas de 1.5 V.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

void calculaHoras(PriorityQueue<int, greater<int>> pilasA, PriorityQueue<int, greater<int>> pilasB, int N) {
    while (!pilasA.empty() && !pilasB.empty()) {                // Mientras las colas sean vacías.
        int horasVuelo = 0;                                     // Para la solución
        int i = 0;
        vector<int> v1, v2;                                     // Vectores donde iremos guardando las pilas usadas que aún tengan carga.

        while (!pilasA.empty() && !pilasB.empty() && i < N) {   // Recorremos todos los drones.
            int aux1 = pilasA.top();        // Obtenemos los valores primeros de cada cola.
            int aux2 = pilasB.top();

            pilasA.pop();
            pilasB.pop();
            
            int min = std::min(aux1, aux2);                 // Vemos cuál de las pilas tiene menos carga.
            horasVuelo += min;                              // Sumamos las horas.
            aux1 -= min;                                    // Restamos las horas de vuelo a las pilas que se han gastado.
            aux2 -= min;
            if (aux1 != 0) {                                // Si todavía tiene carga la pila.
                v1.push_back(aux1);                         // La guardamos en el vector para utilizarla más adelante.
            }
            if (aux2 != 0) {
                v2.push_back(aux2);
            }
            i++;
        }
        
        for (int i = 0; i < v1.size(); i++) {               // Las pilas que todavía tienen carga que hemos utlizado se vuelven a guardar en la cola.
            pilasA.push(v1[i]);
        }
        for (int j = 0; j < v2.size(); j++) {
            pilasB.push(v2[j]);
        }

        cout << horasVuelo << " ";
    }
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, A, B;                        // N es el n�mero de drones que tenemos, A es el n�mero de pilas de 9 V y B es el n�mero de pilas de 1.5 V.

    cin >> N >> A >> B;
    if (!std::cin)  // fin de la entrada
        return false;

    PriorityQueue<int, greater<int>> pilasA, pilasB;  // pilasA es una cola de prioridad de m�nimos de las pilas de tipo A, y pilasB es una cola de pilas de tipo B.

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
    cout << '\n';

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
