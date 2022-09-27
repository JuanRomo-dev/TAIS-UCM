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

 Para resolver el problema, tenemos un struct llamado tareas, con enteros tanto de cuando
 empieza el intervalo, como de cuando acaba, así como del periodo en el cuál se repite
 ese intervalo, además de un booleano el cuál indica si ese intervalo se repite o no.
 En la función que comprueba si hay conflictos o no entre los intervalos, se recorre 
 el priority_queue y para detectarlo, tenemos que ver si el tiempo del intervalo de ese momento
 es menor que el final del intervalo anterior, lo cual indicaria que hay conflicto.
 En la cola se guarda la tarea más prioritaria. En caso de que el intervalo actual
 tenga repetición, se incrementan los tiempos, actualizando la cola.

 El coste de la resolución es O(N*log(N)), donde N es el número de tareas de la cola, siendo N = Z + M,
 es decir, la suma de las tareas que se repiten y las que no se repiten.
 @ </answer> */

struct tarea {
    int inicio, fin, periodo;
    bool repeticion;
};

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool operator<(tarea const& a, tarea const& b) {
    return b.inicio < a.inicio;
}

bool hayConflictos(priority_queue<tarea> cola, int t) {
    bool conflicto = false;
    int tiempo = 0;

    while (!cola.empty() && !conflicto &&  cola.top().inicio < t) {     // Coste O(N*log(N)).
        auto tar = cola.top();
        cola.pop();
        conflicto = tar.inicio < tiempo;
        tiempo = tar.fin;
        if (tar.repeticion) {
            tar.inicio += tar.periodo;
            tar.fin += tar.periodo;
            cola.push(tar);
        }
    }

    return conflicto;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int n, m, t;    // n es el número de tareas únicas, m es el número de tareas periódicas y t es el número de minutos en el que averiguar si hay conflictos.

    cin >> n >> m >> t;

    if (!std::cin)  // fin de la entrada
        return false;

    priority_queue<tarea> cola;

    for (int i = 0; i < n; i++) {               // Coste O(M*log(N)).
        tarea tar;
        cin >> tar.inicio >> tar.fin;
        tar.periodo = 0;
        tar.repeticion = false;
        cola.push({ tar });
    }

    for (int i = 0; i < m; i++) {               // Coste O(Z*log(N)).
        tarea tar;
        cin >> tar.inicio >> tar.fin >> tar.periodo;
        tar.repeticion = true;
        cola.push({ tar });
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    if (hayConflictos(cola, t)) {
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
