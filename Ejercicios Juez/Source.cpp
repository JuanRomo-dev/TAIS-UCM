/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Digrafo.h"
#include <queue>
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Debemos buscar en profundidad para probar si es posible realizar todas las tareas, de tal forma que
 se respeten todas las dependencias, y aquellos v�rtices que no tengan aristas dirigidas se guardan en una cola.
 
 El coste del algoritmo es O(V+A), donde V es el n�mero de v�rtices del grafo y A el n�mero de aristas.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class Tareas {
public:
    Tareas(Digrafo const& dig) : visit(dig.V(), false), apilado(dig.V(), false), hayCiclo(false) {
        for (int i = 0; i < dig.V(); i++) {
            if (!visit[i]) {
                dfs(dig, i);
            }
        }
    }
    bool existeCiclo() const {
        return hayCiclo;
    }

    deque<int> const& ordenTareas() const {
        return _orden;
    }

private:
    vector<bool> visit;
    vector<bool> apilado;
    deque<int> _orden;
    bool hayCiclo;

    void dfs(Digrafo const& dig, int v) {
        visit[v] = true;
        apilado[v] = true;
        for (int w : dig.ady(v)) {
            if (hayCiclo) {
                return;
            }
            if (!visit[w]) {
                dfs(dig, w);
            }
            else if (apilado[w]) {
                hayCiclo = true; 
            }
        }
        apilado[v] = false;
        _orden.push_front(v);
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;          // N N�mero de tareas a realizar. M Relaciones de dependencia.

    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo dig(N);
    
    for (int i = 0; i < M; i++) {
        int v, w;
        cin >> v >> w;
        dig.ponArista(v-1, w-1);
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la soluci�n
    Tareas t(dig);
    if (!t.existeCiclo()) {
        for (int c : t.ordenTareas()) {
            cout << c + 1 << " ";
        }
    }
    else {
        cout << "Imposible";
    }
    cout << '\n';
        
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