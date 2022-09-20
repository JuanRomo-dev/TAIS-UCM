
/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Se cogen los 2 primeros valore de la cola, se suman, añadiendo la suma de vuelt aa la cola y se guarda el esfuerzo, hasta
 obtener la suma final.

 El coste es O(log(N) * (N*M)), siendo N el número de elementos de la cola y M el número de veces que cola tiene más de 1 elemento.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

long long int calcular(priority_queue<long long int, vector<long long int>, greater<long long int>>& cola) {
    long long int a, b, esfuerzo = 0;
    if (cola.size() > 0) {
        while (cola.size() > 1) {
            a = 0, b = 0;
            a += cola.top();    // O(1)         Cogemos el valor a.
            cola.pop();         // O(log N)     Lo quitamos de la cola.
            b += cola.top();    // O(1)         Cogemos el valor b.
            cola.pop();         // O(log N)     Lo quitamos de la cola

            a += b;             // Calculamos el esfuerzo de esta suma.
            esfuerzo += a;      // Lo añadimos al esfurzo total de la suma de la cola.
            cola.push(a);       // Guardamos la suma en la cola para que se acabe sumando también.
        }
    }

    return esfuerzo;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;

    cin >> N;
    if (N == 0)
        return false;

    priority_queue<long long int, vector<long long int>, greater<long long int>> cola;
    long long int aux;
    for (int i = 0; i < N; i++) {
        cin >> aux;
        cola.push(aux);     // O(log N)
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    cout << calcular(cola) << "\n";

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
