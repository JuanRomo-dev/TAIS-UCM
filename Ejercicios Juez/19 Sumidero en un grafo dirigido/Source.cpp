
/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Digrafo.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Debemos realizar una búsqueda en profundidad (dfs) para encontrar un vértice sumidero, es decir, que su grado de entrada sea V - 1 (que todos los demás vértices apunten
 hacia él, y qye su grado de salida sea 0 (que el vértice no apunte a ningún otro). Para hallar si es sumidero o no, en la clase Sumidero, al realizar la dfs, buscaremos
 vértices que tengan la lista de adyacentes vacía, e iremos viendo si cada vértice tiene al original de adyacente, sumando el grado de entrada del vértice en vector
 llamado gradoV, donde cada posición del vector indica el vértice por el número.

 Por otro lado, en cuanto al coste del algoritmo es O(V+A), donde V es el número de vértices y A el número de aristas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Sumidero {
public:
    Sumidero(Digrafo const& dig) : visit(dig.V(), false), gradoV(dig.V()) {
        sumidero = false;
        solucion = -1;
        for (int i = 0; i < dig.V(); i++) {                                     // Recorremos todos los vértices del grafo.
            if (!visit[i]) {                                                    // Si no ha sido visitado realizamos la búsqueda en profundidad.
                dfs(dig, i);
            }
        }
        if (solucion != -1 && gradoV[solucion] == dig.V() - 1) {                // Si el grado de entrada de la arista es V - 1 entonces es solucion.
            sumidero = true;
        }
    }

    bool tieneSumidero() {
        return sumidero;
    }

    int sol() {
        return solucion;
    }

private:
    vector<bool> visit;         // Para marcar los vértices que ya han sido visitados.
    bool sumidero;              // Para marcar si el vértice es sumidero o no.
    vector<int> gradoV;         // Para guardar el valor del grado de entrada de cada vértice.
    int solucion;               // Para guardar la posible solución del vértice.

    void dfs(Digrafo const& dig, int v) {
        visit[v] = true;            // Marcamos el vértice como visitado.
        if (dig.ady(v).size() == 0) {   // Si el grado de salida de v es 0, entonces es una posible solución.
            solucion = v;
        }
        for (int w : dig.ady(v)) {  // Recorremos sus adyacentes.
            gradoV[w]++;            // Incrementamos el valor del grado de entrada.
            if (!visit[w]) {        // Si w no ha sido visitado realizamos la llamada recursiva para continuar la búsqueda en profundidad.
                dfs(dig, w);        
            }
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A;       // Número de vértices y aristas 

    cin >> V >> A;
    if (!std::cin)  // fin de la entrada
        return false;

    int v, w;       // aristas
    Digrafo dig(V);
    for (int i = 0; i < A; i++) {
        cin >> v >> w;
        dig.ponArista(v, w);
    }

    // resolver el caso posiblemente llamando a otras funciones
    Sumidero s(dig);

    // escribir la solución
    if (s.tieneSumidero()) {
        cout << "SI " << s.sol();
    }
    else {
        cout << "NO";
    }
    cout << '\n';

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
