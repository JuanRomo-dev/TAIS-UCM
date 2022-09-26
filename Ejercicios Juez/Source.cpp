
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
        cin >> ini, f, rep;
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