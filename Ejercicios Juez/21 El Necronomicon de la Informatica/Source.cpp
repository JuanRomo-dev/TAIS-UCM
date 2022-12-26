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

 Para resoslver el problema, se realiza una búsqueda en profundidad, en la cuál se verá si un programa puede terminar. Si nunca se llega a visitar el último nodo,
 quiere decir que la instrucción no se ha ejecutado, por lo que NUNCA terminaría el programa. En el caso de detectarse un ciclo, a través del vector apilado, el
 programa terminará a veces ya que se trataría de una instrucción de salto condicional, que dependiendo de si se realiza el salto o no, se produciría el ciclo o no, 
 por lo que el programa terminaría A VECES. En cualquier otro caso, todas las instrucciones se han ejecutado correctamente, al haber sido visitados todos los nodos del
 grafo dirigido, por lo que el programa terminaría SIEMPRE.

 En cuanto al coste en el peor caso es O(L), donde L es el número de instrucciones, en el cuál el número de aristas podría llegar a ser 2L si todas las instrucciones
 son de salto condicional, pero en complejidad 2L = L.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class programa {
public:
    programa(Digrafo const& dig) : visit(dig.V(), false), apilado(dig.V(), false), hayCiclo(false), tipoPrograma(0) {
        dfs(dig, 0);
        if (visit[dig.V() - 1]) {   // Si hemos llegado a la última instrucción, quiere decir que el programa podría llegar a finalizar.
            if (hayCiclo) {         // Dependiendo de si hay ciclo o no, el programa es de un tipo u otro.
                tipoPrograma = 1;
            }
            else {
                tipoPrograma = 2;
            }
        }
    }

    int tipo() {
        return tipoPrograma;
    }

private:
    vector<bool> visit;             // Para marcar los vértices ya visitados.
    vector<bool> apilado;           // Para detectar ciclos.
    int tipoPrograma;               // 0 si el programa nunca acaba, 1 si a veces y 2 si siempre.
    bool hayCiclo;                  // Guarda si hay un ciclo o no.

    void dfs(Digrafo const& dig, int v) {       // Búsqueda en profundidad.
        visit[v] = true;            // Marcamos el vértice v como visitado      
        apilado[v] = true;          // Apilamos v
        for (int w : dig.ady(v)) {  // Recorremos los adyacentes a v.
            if (!visit[w]) {        // Si w no ha sido visitado continuamos la búsqueda en profundidad
                dfs(dig, w);
            }
            else if (apilado[w]) {  // Si ya estaba w apilado, entonces se produce un ciclo.
                hayCiclo = true;
            }
        }
        apilado[v] = false;         // Desapilamos v.
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int L;                  // Número de instrucciones.

    cin >> L;
    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo necronomicon(L + 1);            // Grafo dirigido para representar las relaciones entre instrucciones
    char c;
    int salto;
    for (int i = 0; i < L; i++) {       
        cin >> c;
        if (c == 'A') {                 // Si la instrucción es aritmética, avanza a la siguiente instrucción.
            necronomicon.ponArista(i, i + 1);
        }
        else if (c == 'J') {            // Si la instrucción es un salto, avanza a la instrucción "salto".
            cin >> salto;
            necronomicon.ponArista(i, salto);
        }
        else if (c == 'C') {            // Si la instrucción es un salto condicional, puede avanzar a la siguiente instrucción, o saltar a la instrucción salto.
            cin >> salto;
            necronomicon.ponArista(i, i + 1);
            necronomicon.ponArista(i, salto);
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    programa p(necronomicon);

    // escribir la solución
    if (p.tipo() == 0) {
        cout << "NUNCA";
    }
    else if (p.tipo() == 1) {
        cout << "A VECES";
    }
    else {
        cout << "SIEMPRE";
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
