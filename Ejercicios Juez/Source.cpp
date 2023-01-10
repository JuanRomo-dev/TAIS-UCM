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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Demostramos que la soluci�n del problema es �ptima. Las soluciones son permutaciones de los �ndices de las equipaciones
 (sol[i] = k significa que al jugador i, le asignamos la equipaci�n con talla equipaciones[k].

 Suponemos a las equipaciones ordenadas de forma que i <= j -> equipaciones[i] <= equipaciones[j].

 Recorremos las equipaciones de menor a mayor por talla, y a los jugadores de menor a mayor tambi�n por la talla que necesitan.
 La soluci�n voraz sol selecciona la talla que se ajusta al jugador, eligiendo primero la de su talla y si no pasando a la de la 
 talla siguiente (si hay alguna), si no se pasar� al siguiente jugador. Las equipaciones que se descartan son aquellas que no le valen
 a ning�n jugador de los que tenemos. Por tanto, el aspecto de la soluci�n voraz es una secuencia creciente de indices de equipaciones 
 (que les valen a los jugadores) y luego el resto son jugadores que no se les ha podido asignar una equipaci�n, por lo que habr� que 
 comprarles una nueva.

 Ejemplo
 E  12 12 12 12 12
 J  10 12 13 14

 La soluci�n voraz: 1 2 (son las equipaciones que se han podido asignar a los 2 primeros jugadores. 3 y 4 son las equipaciones que sobran
 (estos n�meros son �ndices).

 Sea O una soluci�n �ptima y sea i la primera posici�n donde O y sol difieren: O[i] != sol[i].
 Entonces la equipaci�n sol[i] ha sido asignada m�s adelante en O. Sea k la posici�n que cumple O[k] = sol[i].

 Esta es la situaci�n:
 E      E[0]   <=   E[1] <= ...
 sol    sol[0]      sol[1] ... | sol[i]
            =           =      |  !=
 O      O[0]        O[1]   ... | O[i] ... O[k] = sol[i]

 CASO 1: D[sol[i]] == E[i]   (se puede asignar una equipacion en la voraz)
    - Caso  1.1 Si no se pudiese asignar la equipaci�n en la �ptima al jugador i,
    D[O[i]] != E[i], podemos intercambiar i y k sin perder equipaciones asignadas,
    ya que la i va a convertirse en una equipaci�n asignada porque D[sol[i]] == E[i] (tampoco van
    a asignarse ambas porque es �ptima).
    - Caso 1.2 Si se puede asignar una equipaci�n en i en la �ptima, D[O[i]] == E[i], entonces,
    D[O[i]] == D[sol[i]] porque de las equipaciones que quedan por asignar D[sol[i]] es la primera
    que se puede asignar (y las equipaciones que edan por asignar son las mismas) por la estrategia voraz.
    Tanto si se puede asignar un equipaci�n al jugador k como si no, intercambiar la posici�n i con la k en O no
    reduce el n�mero de equipaciones asignadas: el jugador i sigue teniendo una equipaci�n asignada y el
    jugador k est� recibiendo tambi�n una equipaci�n.

 CASO 2: D[sol[i]] != E[i] (no se puede asignar la equipaci�n en la voraz)
 Si no se puede asignar la equipaci�n en la voraz, no puede existir ninguna equipaci�n no asignada que permita ganar
 en i y por tanto D[O[i]] != E[i] (porque las equipaciones no asignadas son las mismas) ya que en caso contrario la 
 soluci�n voraz la hubiese asignado.
 Tampoco se puede asignar una equipaci�n al jugador k porque E[i] != E[k] as� que simplemente
 intercambiamos 2 equipaciones no asignadas para que se parezca m�s a la voraz.

 El coste del algoritmo es O(n), donde n = N si N > M o n = M si N < M.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

int resolver(vector<int> const& jugadores, vector<int> const& equipaciones, int N, int M) {
    int nComprar = 0;       // N�mero de equipaciones que se necesitar�n comprar.
    int j = 0;          // Para llevar la cuenta de las equipaciones asignadas.
    int i = 0;      // Para llevar la cuenta de los jugadores que ya tienen equipaci�n.
    vector<int> sol(N, -1);     // Para asignar una equipacion a un jugador.

    while (i < N && j < M) {        // Mientras que haya jugadores pendientes de recibir una equipaci�n y haya equipaciones disponibles. 
        if (jugadores[i] == equipaciones[j] || jugadores[i] + 1 == equipaciones[j]) {       // Si la talla de un jugador coincide con la de una equipacion o es la siguiente talla, se le asigna.
            sol[i] = j;
            i++;
            j++;
        }
        else if (jugadores[i] < equipaciones[j]) {      // Si al jugador vemos que la talla es demasiado grande, le tendremos que comprar una nueva, probamos con el siguiente jugador.
            i++;
        }
        else {          // Pasamos a probar con la siguiente equipaci�n.
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
    int N, M;       // N�mero de jugadores y equipaciones con las que se cuentan.

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

    // escribir la soluci�n
    cout << sol << '\n';

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