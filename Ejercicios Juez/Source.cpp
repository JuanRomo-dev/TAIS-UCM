
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

 @ </answer> */

struct tarea {
    int inicio, fin, periodo;
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool operator<(tarea const& a, tarea const& b) {
    return a.inicio < b.inicio;
}

bool hayConflictos(priority_queue<tarea> cola, int t) {
    bool conflicto = false;
    int tiempo = 0;

    while (!conflicto && cola.empty() && cola.top().inicio < t) {
        tarea tar = cola.top();
        cola.pop();

        if (tar.inicio < tiempo) {
            conflicto = true;
        }
        tiempo = tar.fin;
        if (tar.periodo > 0) {
            cola.push({ tar.inicio + tar.periodo, tar.fin + tar.periodo, tar.periodo });
        }
    }
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int n, m, t;    // n es el número de tareas únicas, m es el número de tareas periódicas y t es el número de minutos en el que averiguar si hay conflictos.

    if (!std::cin)  // fin de la entrada
        return false;

    cin >> n >> m >> t;

    priority_queue<tarea> cola;
    int ini, f, rep;

    for (int i = 0; i < n; i++) {
        cin >> ini >> f;
        rep = 0;
        cola.push({ ini, f, rep });
    }

    for (int i = 0; i < m; i++) {
        cin >> ini, f, rep;
        cola.push({ ini, f, rep });
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    if (t != 0 && hayConflictos(cola, t)) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }

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