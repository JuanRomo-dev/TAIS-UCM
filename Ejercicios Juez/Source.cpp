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

 Para resoslver el problema, se realiza una b�squeda en profundidad, en la cu�l se ver� si un programa puede terminar. Si nunca se llega a visitar el �ltimo nodo,
 quiere decir que la instrucci�n no se ha ejecutado, por lo que NUNCA terminar�a el programa. En el caso de detectarse un ciclo, a trav�s del vector apilado, el
 programa terminar� a veces ya que se tratar�a de una instrucci�n de salto condicional, que dependiendo de si se realiza el salto o no, se producir�a el ciclo o no, 
 por lo que el programa terminar�a A VECES. En cualquier otro caso, todas las instrucciones se han ejecutado correctamente, al haber sido visitados todos los nodos del
 grafo dirigido, por lo que el programa terminar�a SIEMPRE.

 En cuanto al coste en el peor caso es O(L), donde L es el n�mero de instrucciones, en el cu�l el n�mero de aristas podr�a llegar a ser 2L si todas las instrucciones
 son de salto condicional, pero en complejidad 2L = L.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class programa {
public:
    programa(Digrafo const& dig) : visit(dig.V(), false), apilado(dig.V(), false), hayCiclo(false), tipoPrograma(0) {
        dfs(dig, 0);
        if (visit[dig.V() - 1]) {   // Si hemos llegado a la �ltima instrucci�n, quiere decir que el programa podr�a llegar a finalizar.
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
    vector<bool> visit;             // Para marcar los v�rtices ya visitados.
    vector<bool> apilado;           // Para detectar ciclos.
    int tipoPrograma;               // 0 si el programa nunca acaba, 1 si a veces y 2 si siempre.
    bool hayCiclo;                  // Guarda si hay un ciclo o no.

    void dfs(Digrafo const& dig, int v) {       // B�squeda en profundidad.
        visit[v] = true;            // Marcamos el v�rtice v como visitado      
        apilado[v] = true;          // Apilamos v
        for (int w : dig.ady(v)) {  // Recorremos los adyacentes a v.
            if (!visit[w]) {        // Si w no ha sido visitado continuamos la b�squeda en profundidad
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
    int L;                  // N�mero de instrucciones.

    cin >> L;
    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo necronomicon(L + 1);            // Grafo dirigido para representar las relaciones entre instrucciones
    char c;
    int salto;
    for (int i = 0; i < L; i++) {       
        cin >> c;
        if (c == 'A') {                 // Si la instrucci�n es aritm�tica, avanza a la siguiente instrucci�n.
            necronomicon.ponArista(i, i + 1);
        }
        else if (c == 'J') {            // Si la instrucci�n es un salto, avanza a la instrucci�n "salto".
            cin >> salto;
            necronomicon.ponArista(i, salto);
        }
        else if (c == 'C') {            // Si la instrucci�n es un salto condicional, puede avanzar a la siguiente instrucci�n, o saltar a la instrucci�n salto.
            cin >> salto;
            necronomicon.ponArista(i, i + 1);
            necronomicon.ponArista(i, salto);
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    programa p(necronomicon);

    // escribir la soluci�n
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