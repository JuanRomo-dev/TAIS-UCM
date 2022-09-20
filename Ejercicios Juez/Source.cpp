
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Simularemos el paso del tiempo. Tendremos una cola de prioridad en la que est�n los usuarios registrados con prioridad seg�n la periocidad que tengan. El que tenga el menor valor,
 es el que recibir� el siguiente env�o. Estos valores los guardamos en tRegistro.

 El coste del algoritmo es O(N log(N) + k log(N))

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

struct tRegistro {
    int id;         // Identificador (Para cu�ndo se de un caso de empate en orden creciente)
    int periodo;    // Tiempo entre 2 env�os de informaci�n para un usuario.
    int momento;    // Cu�ndo le toca recibir el env�o siguiente.
};

bool operator<(tRegistro const& a, tRegistro const& b) {
    return b.momento < a.momento || (a.momento == b.momento && b.id < a.id);
}

bool resuelveCaso() {
    int n;                  // N�mero de usuarios registrados.

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
    cin >> envios;          // N�mero de env�os a mostrar.

    // resolver el caso posiblemente llamando a otras funciones
    while (envios--) {              // El coste del bucle es O(k log(N)).
        auto e = cola.top();        // O(1).
        cola.pop();                 // O(log N).
        cout << e.id << "\n";           
        e.momento += e.periodo;
        cola.push(e);               // O(log N).
    }
    // escribir la soluci�n
    cout << "---\n";

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
