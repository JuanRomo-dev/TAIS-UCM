/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Demostramos que la solución del problema es óptima. Las soluciones son permutaciones de los índices de los equipos de defensa (V[i] = k signfica que a la ciudad i
 enviamos el equipo de defensa de tamaño D[k]).

 Suponemos a los enemigos ordenados de forma que i <= j => E[i] <= E[j]

 Recorremos los enemigos de menor a mayor y la solución voraz V selecciona la defensa más pequeña de las que quedan que le permite ganar (si hay alguna). Las derrotas
 da igual como se asignen. Por tanto, el aspecto de la solución voraz es una secuencia creciente de índices de defensas (que permiten ganar) y luego el resto son
 derrotas que en realidad da igual cómo se asignen.

 Ejemplo:
 E 4 7 9 11 13
 D 3 4 6 8 15

 La solución voraz: 1 3 4 (son victorias) y luego 0 2 son derrotas. (Son índices).

 Sea O una solución óptima y sea i la primera posición donde 0 y V difieren: O[i] != V[i].
 Entonces la defensa V[i] ha sido asignada más adelante en O. Sea k la posición que cumple que O[k] = V[i].

 Esta es la situación:
 E  E[0] <= E[1] <= ...
 V  v[0]    V[1]    ... | V[i]
       =       =    ... | !=
 O  O[0]    O[1]    ... | O[i] ... O[k] = V[i]

 CASO 1: D[V[i]] >= E[i]    (Hay victoria en la voraz)
    CASO 1.1 Si hubiese derrota en la óptima en la ciudad i, D[O[i]] < E[i], podemos intercambiar i y k sin perder victorias, ya que la i va a convertirse en victoria
    porque D[V[i]] >= E[i] (tampoco va a ganar ambas porque es óptima).
    CASO 1.2 Si hay victoria en i en la óptima, D[0[i]] >= E[i], entonces D[0[i]] >= D[V[i]] porque de las defensas que quedan por asignar D[V[i]] es la menor que
    permite ganar (y las defensas que quedan por asignar son las mismas) por la estrategia voraz. Tanto si hay victoria en la ciudad k como si no, intercambiar la
    posición i con la k en 0 no reduce el número de victorias: en la ciudad i seguimos ganando y a la ciudad k estamos enviando al menos el mismo número de defensas.

CASO 2: D[V[i]] < E[i] (hay derrota en la voraz)
    Si hay derrota en la voraz no puede existir ninguna defensa no asignada que permita ganar en i y por tanto D[O[i]] < E[i] (porque las defensas no asignadas son las 
    mismas) ya que en caso contrario la solución voraz la hubiese asignado.
    Tampoco hay victoria en k porque E[i] <= E[k] así que simplemente intercambiamos dos derrotas para que se parezca más a la voraz.

    En cuanto al coste del algoritmo es O(N), donde N es el número de ciudades invadidas a atacar.
    
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int resolver(vector<int> const& enemigos, vector<int> const& defensas, int N) {
    int maxCiudades = 0;        // Para llevar la cuenta de las ciudades reconquistadas.
    int j = 0;          // Hasta que una ciudad de enemigos no haya sido derrotada no se pasa a la siguiente

    for (int i = 0; i < N; i++) {
        if (enemigos[j] <= defensas[i]) {   // Si el número de efectivos de nuestras defensas son superiores o iguales a las fuerzas enemigas
            maxCiudades++;  // Reconquistamos una ciudad.
            j++;        // Pasamos a la siguiente ciudad
        }
    }

    return maxCiudades;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;      // Número de ciudades invadidas y equipos de defensa.

    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> enemigos(N);
    vector<int> defensas(N);

    for (int i = 0; i < N; i++) {
        cin >> enemigos[i];
    }
    
    sort(enemigos.begin(), enemigos.end());     // Ordenamos los enemigos de menor a mayor.

    for (int i = 0; i < N; i++) {
        cin >> defensas[i];
    }

    sort(defensas.begin(), defensas.end());     // Ordenamos las defensas de menor a mayor para colocar primero las de menor número de efectivos que permitan ganar. 

    // resolver el caso posiblemente llamando a otras funciones
    int sol = resolver(enemigos, defensas, N);

    // escribir la solución
    cout << sol << '\n';    
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