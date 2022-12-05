/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <vector>
#include <deque>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Tareas {
public:
    Tareas(Digrafo const& dig) : visit(dig.V(), false), ant(dig.V()), apilado(dig.V(), false), hayCiclo(false), posibleOrdenar(false) {
        for (int i = 0; i < dig.V(); i++) {
            if (!visit[i]) {
                posibleOrdenar = dfs(dig, i);
            }
        }
    }
    bool esPosible() {
        return posibleOrdenar;
    }

    deque<int> const& ordenTareas() {
        return _orden;
    }

private:
    vector<bool> visit;
    vector<int> ant;
    vector<bool> apilado;
    deque<int> _orden;
    bool hayCiclo;
    bool posibleOrdenar;

    bool dfs(Digrafo const& dig, int v) {
        visit[v] = true;
        apilado[v] = true;
        for (int w : dig.ady(v)) {
            if (hayCiclo) {
                return false;
            }
            if (!visit[w]) {
                ant[w] = v;
                dfs(dig, w);
            }
            else if (apilado[w]) {
                hayCiclo = true; 
            }
        }
        apilado[v] = false;
        _orden.push_front(v);

        return true;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;          // Número de tareas a realizar.

    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    int M;          // Relaciones de dependencia 
    cin >> M;

    Digrafo dig(M);
    int v, w;
    for (int i = 0; i < M; i++) {
        cin >> v >> w;
        dig.ponArista(v, w);
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    Tareas t(dig);
    if (t.esPosible()) {
        deque<int> ordenT = t.ordenTareas();
        for (int i = 0; i < ordenT.size(); i++) {
            cout << ordenT[i] << " ";
        }
        cout << '\n';
    }
    else {
        cout << "Imposible";
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