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

 El coste es o(n), donde n es el n�mero de pel�culas que se van a proyectar.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

int resolver(vector<pair<int, int>> const& pelis, int N) {
    int maxPelis = 1;
    int aux = pelis[0].first;
    for (int i = 1; i < N; i++) {
        if (aux + 10 <= (pelis[i].first - pelis[i].second)) {       // Si la hora a la que acaba es menor o igual a la que empieza (hora acaba - duracion peli)
            aux = pelis[i].first;
            maxPelis++;     // Puede ir a verla.
        }
    }

    return maxPelis;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;      // N�mero de pel�culas que se van a proyectar.

    cin >> N;
    if (N == 0)
        return false;

    vector<pair<int, int>> pelis(N);     // Vector de pares que contiene la hora de comienzo de la peli (en mins) y su duraci�n (en mins).
    int h, min, duracion;   // Para leer la hora y el minuto de una peli y su duracion.
    char c;
    for (int i = 0; i < N; i++) {
        cin >> h >> c >> min >> duracion;
        int mins = (h * 60) + min + duracion;   // Le sumamos la duraci�n para saber a que hora acaba.
        pelis[i].first = mins;
        pelis[i].second = duracion;
    }

    sort(pelis.begin(), pelis.end());       // Ordenamos las pelis de menor a mayor por hora de comienzo.

    // resolver el caso posiblemente llamando a otras funciones
    int sol = resolver(pelis, N);

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