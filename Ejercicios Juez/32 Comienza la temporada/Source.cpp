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

 Demostramos que la solución del problema es óptima. Las soluciones son permutaciones de los índices de las equipaciones
 (sol[i] = k significa que al jugador i, le asignamos la equipación con talla equipaciones[k].

 Suponemos a las equipaciones ordenadas de forma que i <= j -> equipaciones[i] <= equipaciones[j].

 Recorremos las equipaciones de menor a mayor por talla, y a los jugadores de menor a mayor también por la talla que necesitan.
 La solución voraz sol selecciona la talla que se ajusta al jugador, eligiendo primero la de su talla y si no pasando a la de la 
 talla siguiente (si hay alguna), si no se pasará al siguiente jugador. Las equipaciones que se descartan son aquellas que no le valen
 a ningún jugador de los que tenemos. Por tanto, el aspecto de la solución voraz es una secuencia creciente de indices de equipaciones 
 (que les valen a los jugadores) y luego el resto son jugadores que no se les ha podido asignar una equipación, por lo que habrá que 
 comprarles una nueva.

 Ejemplo
 E  12 12 12 12 12
 J  10 12 13 14

 La solución voraz: 1 2 (son las equipaciones que se han podido asignar a los 2 primeros jugadores. 3 y 4 son las equipaciones que sobran
 (estos números son índices).

 Sea O una solución óptima y sea i la primera posición donde O y sol difieren: O[i] != sol[i].
 Entonces la equipación sol[i] ha sido asignada más adelante en O. Sea k la posición que cumple O[k] = sol[i].

 Esta es la situación:
 E      E[0]   <=   E[1] <= ...
 sol    sol[0]      sol[1] ... | sol[i]
            =           =      |  !=
 O      O[0]        O[1]   ... | O[i] ... O[k] = sol[i]

 CASO 1: D[sol[i]] == E[i]   (se puede asignar una equipacion en la voraz)
    - Caso  1.1 Si no se pudiese asignar la equipación en la óptima al jugador i,
    D[O[i]] != E[i], podemos intercambiar i y k sin perder equipaciones asignadas,
    ya que la i va a convertirse en una equipación asignada porque D[sol[i]] == E[i] (tampoco van
    a asignarse ambas porque es óptima).
    - Caso 1.2 Si se puede asignar una equipación en i en la óptima, D[O[i]] == E[i], entonces,
    D[O[i]] == D[sol[i]] porque de las equipaciones que quedan por asignar D[sol[i]] es la primera
    que se puede asignar (y las equipaciones que edan por asignar son las mismas) por la estrategia voraz.
    Tanto si se puede asignar un equipación al jugador k como si no, intercambiar la posición i con la k en O no
    reduce el número de equipaciones asignadas: el jugador i sigue teniendo una equipación asignada y el
    jugador k está recibiendo también una equipación.

 CASO 2: D[sol[i]] != E[i] (no se puede asignar la equipación en la voraz)
 Si no se puede asignar la equipación en la voraz, no puede existir ninguna equipación no asignada que permita ganar
 en i y por tanto D[O[i]] != E[i] (porque las equipaciones no asignadas son las mismas) ya que en caso contrario la 
 solución voraz la hubiese asignado.
 Tampoco se puede asignar una equipación al jugador k porque E[i] != E[k] así que simplemente
 intercambiamos 2 equipaciones no asignadas para que se parezca más a la voraz.

 El coste del algoritmo es O(n), donde n = N si N > M o n = M si N < M.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int resolver(vector<int> const& jugadores, vector<int> const& equipaciones, int N, int M) {
    int nComprar = 0;       // Número de equipaciones que se necesitarán comprar.
    int j = 0;          // Para llevar la cuenta de las equipaciones asignadas.
    int i = 0;      // Para llevar la cuenta de los jugadores que ya tienen equipación.
    vector<int> sol(N, -1);     // Para asignar una equipacion a un jugador.

    while (i < N && j < M) {        // Mientras que haya jugadores pendientes de recibir una equipación y haya equipaciones disponibles. 
        if (jugadores[i] == equipaciones[j] || jugadores[i] + 1 == equipaciones[j]) {       // Si la talla de un jugador coincide con la de una equipacion o es la siguiente talla, se le asigna.
            sol[i] = j;
            i++;
            j++;
        }
        else if (jugadores[i] < equipaciones[j]) {      // Si al jugador vemos que la talla es demasiado grande, le tendremos que comprar una nueva, probamos con el siguiente jugador.
            i++;
        }
        else {          // Pasamos a probar con la siguiente equipación.
            j++;
        }
    }

    for (int i = 0; i < sol.size(); i++) {              
        if (sol[i] == -1) {
            nComprar++;
        }
    }

    return nComprar;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;       // Número de jugadores y equipaciones con las que se cuentan.

    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> jugadores(N);
    vector<int> equipaciones(M);

    for (int i = 0; i < N; i++) {
        cin >> jugadores[i];
    }  

    sort(jugadores.begin(), jugadores.end());       // Ordenamos los jugadores por su talla de menor a mayor

    for (int i = 0; i < M; i++) {
        cin >> equipaciones[i];
    }

    sort(equipaciones.begin(), equipaciones.end());     // Ordenamos las equipaciones por su talla de menor a mayor

    // resolver el caso posiblemente llamando a otras funciones
    int sol = resolver(jugadores, equipaciones, N, M);

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
