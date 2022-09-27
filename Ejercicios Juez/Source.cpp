
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */

struct tarea {
    int inicio, fin, periodo;
};

// ================================================================
// Escribe el c�digo completo de tu soluci�n aqu� debajo
// ================================================================
//@ <answer>

bool operator<(tarea const& a, tarea const& b) {
    return a.inicio < b.inicio;
}

bool hayConflictos(priority_queue<tarea> cola, int t) {                     // Función para ver si hay conflictos
    bool conflicto = false;
    int tiempo = 0;         // Aquí se guarda el valor final del tiempo de un intervalo.

    while (!conflicto && !cola.empty() && cola.top().inicio < t) {          // Mientras no haya conflictos, la cola no esté vacía y el tiempo inicial del intervalo no supere el tiempo en el que vamos a ver si hay conflictos.
        tarea tar = cola.top();     // Obtenemos el primer valor de la cola.
        cola.pop();

        if (tar.inicio < tiempo) {      // Si el inicio del intervalo es menor que el tiempo final del intervalo anterior, entonces hay conflicto. 
            conflicto = true;
        }
        tiempo = tar.fin;               // Guardamos el valor del tiempo final del intervalo.
        if (tar.periodo > 0) {          // Si el intervalo que vamos a mirar tiene repetición
            cola.push({ tar.inicio + tar.periodo, tar.fin + tar.periodo, tar.periodo });        // Actualizamos la tarea que se repite a su siguiente intervalo.
        }
    }

    return conflicto;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int n, m, t;    // n es el n�mero de tareas �nicas, m es el n�mero de tareas peri�dicas y t es el n�mero de minutos en el que averiguar si hay conflictos.

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
        cin >> ini >> f >> rep;
        cola.push({ ini, f, rep });
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la soluci�n
    if (t != 0 && hayConflictos(cola, t)) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }

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
