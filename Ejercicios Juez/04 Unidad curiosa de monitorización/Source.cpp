
/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Simularemos el paso del tiempo. Tendremos una cola de prioridad en la que están los usuarios registrados con prioridad según la periocidad que tengan. El que tenga el menor valor,
 es el que recibirá el siguiente envío. Estos valores los guardamos en tRegistro.

 El coste del algoritmo es O(N log(N) + k log(N))

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct tRegistro {
    int id;         // Identificador (Para cuándo se de un caso de empate en orden creciente)
    int periodo;    // Tiempo entre 2 envíos de información para un usuario.
    int momento;    // Cuándo le toca recibir el envío siguiente.
};

bool operator<(tRegistro const& a, tRegistro const& b) {
    return b.momento < a.momento || (a.momento == b.momento && b.id < a.id);
}

bool resuelveCaso() {
    int n;                  // Número de usuarios registrados.

    // leer los datos de la entrada
    cin >> n;               
    if (n == 0)
        return false;

    priority_queue<tRegistro> cola;
    int idaux, period;

    for (int i = 0; i < n; i++) {
        cin >> idaux >> period;
        cola.push({ idaux, period, period });
    }

    int envios;
    cin >> envios;          // Número de envíos a mostrar.

    // resolver el caso posiblemente llamando a otras funciones
    while (envios--) {              // El coste del bucle es O(k log(N)).
        auto e = cola.top();        // O(1).
        cola.pop();                 // O(log N).
        cout << e.id << "\n";           
        e.momento += e.periodo;
        cola.push(e);               // O(log N).
    }
    // escribir la solución
    cout << "---\n";

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
