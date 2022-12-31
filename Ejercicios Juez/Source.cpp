/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include <queue>
#include <vector>
#include "ConjuntosDisjuntos.h"
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 El problema a resolver consiste en que tenemos una serie de islas, en las cu�les tenemos una serie de puentes a construir con un cierto coste, y queremos saber si podemos
 conectar todas las islas de tal forma que el coste total de los puentes sea el m�nimo posible. Para ello, vamos a imaginar las islas y los puentes como un grafo valorado, en el
 cu�l, las islas ser�n los v�rtices, y los puentes las aristas, siendo el valor de estas el coste de construir cada puente. De esta manera, utilizaremos el algoritmo de Kruskal,
 que sirve para buscar arboles de recubrimiento m�nimo (ARM), es decir, un subgrafo que conecta todos los v�rtices del grafo original, tal que la suma de los costes de las aristas
 sea m�nima. En la clase ARM_Kruskal, tenemos un vector de aristas para indicar que aristas formar�n parte de este ARM, y un coste para ir calculando el m�nimo. Tambi�n haremos
 uso de los Conjuntos Disjuntos, ya que nos servir� para que no se formen ciclos y ver si 2 v�rtices est�n unidos. En el algoritmo en s�, tendremos una cola de prioridad
 de las aristas ordenadas por su coste para ir viendo cu�les nos convienen seguir. De esta forma iremos marcando que puentes colocar o no dependiendo de si las islas estaban
 ya unidas por otros v�rtices o no. En el momento en el que consigamos construir un ARM del tama�o de los v�rtices del grafo, ya sabremos que s� es posible unir todas las islas,
 devolviendo el coste total de unirlas por los puentes. En caso contrario, si hemos recorrido toda la pq, quiere decir que no se pueden unir todas las islas, por lo que 
 no tendremos puentes suficientes.

 El coste en el peor de los casos es O(A * log(A)), siendo A el n�mero de aristas del grafo, produci�ndose A vueltas al bucle de hasta A aristas.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class ARM_Kruskal {
private:
    vector<Arista<int>> _ARM;       // Vector de aristas para indicar como es el �rbol de recubrimiento m�nimo.
    ConjuntosDisjuntos cjtos;       // Conjuntos disjuntos
    int coste;                      // Coste de la suma de los valores de las aristas.

    void kruskal(GrafoValorado<int> const& islas) {         // Algoritmo de Kruskal para averiguar un �rbol de recubrimiento m�nimo en un grafo conexo.
        auto aristas = islas.aristas();     
        priority_queue<Arista<int>, vector<Arista<int>>, greater<Arista<int>>> pq(aristas.begin(), aristas.end());      // Cola de prioridad para procesar las aristas en orden.
        while (!pq.empty()) {
            auto a = pq.top();      // Obtenemos la arista.
            pq.pop();
            int v = a.uno(), w = a.otro(v);     // Obtenemos los v�rtices de la arista.
            if (!cjtos.unidos(v, w)) {      // Si no est�n los v�rtices (islas) unidos
                cjtos.unir(v, w);       // Los unimos por una arista (puente)
                _ARM.push_back(a);      // Marcamos la arista en el ARM.
                coste += a.valor();     // Aumentamos el coste que llevamos hasta el momento en el total.
                if (_ARM.size() == islas.V() - 1) {     // Si todas las islas son alcanzables con los puentes dados, interrumpimos la b�squeda, pues ya lo hemos encontrado.
                    break;
                }
            }
        }
    }

public:
    ARM_Kruskal(GrafoValorado<int> const& islas) : coste(0), cjtos(islas.V()) {
        kruskal(islas);
    }

    int costeARM() const {
        return coste;
    }

    bool suficientes() const {
        return cjtos.num_cjtos() == 1;
    }
 
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int I;  // N�mero de islas del archipi�lago.
    cin >> I;

    if (!std::cin)  // fin de la entrada
        return false;

    int P; // N�mero de puentes presupuestados.
    cin >> P;

    GrafoValorado<int> islas(I);    // Grafo valorado en el que los v�rtices son las islas, y las aristas valoradas los puentes entre las islas y su coste.
    int v, w, costePuente;          // v y w son las 2 islas que unen un puente, y costePuente es el coste de ese puente.
    for (int i = 0; i < P; i++) {
        cin >> v >> w >> costePuente;
        islas.ponArista({ v - 1, w - 1, costePuente });
    }
    
    ARM_Kruskal arm(islas);

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la soluci�n
    if (arm.suficientes()) {
        cout << arm.costeARM();
    }
    else {
        cout << "No hay puentes suficientes";
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