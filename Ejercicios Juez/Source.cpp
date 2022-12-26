
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Debemos realizar una b�squeda en profundidad (dfs) para encontrar un v�rtice sumidero, es decir, que su grado de entrada sea V - 1 (que todos los dem�s v�rtices apunten
 hacia �l, y qye su grado de salida sea 0 (que el v�rtice no apunte a ning�n otro). Para hallar si es sumidero o no, en la clase Sumidero, al realizar la dfs, buscaremos
 v�rtices que tengan la lista de adyacentes vac�a, e iremos viendo si cada v�rtice tiene al original de adyacente, sumando el grado de entrada del v�rtice en vector
 llamado gradoV, donde cada posici�n del vector indica el v�rtice por el n�mero.

 Por otro lado, en cuanto al coste del algoritmo es O(V+A), donde V es el n�mero de v�rtices y A el n�mero de aristas.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class Sumidero {
public:
    Sumidero(Digrafo const& dig) : visit(dig.V(), false), gradoV(dig.V()) {
        sumidero = false;
        solucion = -1;
        for (int i = 0; i < dig.V(); i++) {                                     // Recorremos todos los v�rtices del grafo.
            if (!visit[i]) {                                                    // Si no ha sido visitado realizamos la b�squeda en profundidad.
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
    vector<bool> visit;         // Para marcar los v�rtices que ya han sido visitados.
    bool sumidero;              // Para marcar si el v�rtice es sumidero o no.
    vector<int> gradoV;         // Para guardar el valor del grado de entrada de cada v�rtice.
    int solucion;               // Para guardar la posible soluci�n del v�rtice.

    void dfs(Digrafo const& dig, int v) {
        visit[v] = true;            // Marcamos el v�rtice como visitado.
        if (dig.ady(v).size() == 0) {   // Si el grado de salida de v es 0, entonces es una posible soluci�n.
            solucion = v;
        }
        for (int w : dig.ady(v)) {  // Recorremos sus adyacentes.
            gradoV[w]++;            // Incrementamos el valor del grado de entrada.
            if (!visit[w]) {        // Si w no ha sido visitado realizamos la llamada recursiva para continuar la b�squeda en profundidad.
                dfs(dig, w);        
            }
        }
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int V, A;       // N�mero de v�rtices y aristas 

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

    // escribir la soluci�n
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