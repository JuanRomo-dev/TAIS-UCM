/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include <queue>
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Este problema consiste en que tenemos una serie de localidades o ciudades, que necesitan tener acceso a un aeropuerto, ya sea en la propia localidad o por
 conexi�n mediante carretera. Entonces, dados el coste de construcci�n de un aeropuerto y una lista de posibles carreteras entre pares de localidades y sus
 correspondientes costes, tenemos que decidir cu�l es la forma m�s barata de garantizar que todas las localidades tienen acceso a un aeropuerto.
 Para ello vamos a utilizar un grafo valorado de tal forma que los v�rtices son las distintas localidades, y las aristas son las carreteras que las conectan, siendo
 el valor el coste de cada una de las carreteras. Vamos a emplear al algoritmo de Kruskal para averiguar si todas las localidades est�n unidas o no, aunque con un 
 matiz, no voy a utilizar el TAD del arbol de recubrimiento m�nimo (ARM), ya que no buscamos exactamente tener un s�lo arbol, si no averiguar a trav�s del TAD
 de conjuntos disjuntos, si tenemos 1 o m�s, ya que si hay 1 quiere decir que entonces todas las localidades est�n conectadas entre s�, necesitando s�lo un 
 aeropuerto. En el algoritmo de kruskal, iremos obteniendo cada arista a trav�s de una cola de prioridad con las aristas del grafo, calculando el coste total.
 Finalmente sumaremos al coste total de los aeropuertos el de las carreteras.
 
 En cuanto al de la soluci�n, en el peor de los casos es de O(A * log(A)), donde A es el n�mero de aristas.
@ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class Aeropuertos {
private:
    ConjuntosDisjuntos cjtos;           // Utilizaremos los conjuntos disjuntos para averiguar si todas las localidades est�n unidas. En caso de que no, el n�mero de conjuntos nos idicar� cu�ntos aeropuertos necesitamos (1 por conjunto).
    int coste;          // Para calcular el coste de construir las carreteras.

    void kruskal(GrafoValorado<int> const& localidades) {
        auto aristas = localidades.aristas();
        priority_queue<Arista<int>, vector<Arista<int>>, greater<Arista<int>>> pq(aristas.begin(), aristas.end());
        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno();
            int w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                coste += a.valor();
            }
        }

    }

public:
    Aeropuertos(GrafoValorado<int> const& localidades) : cjtos(localidades.V()), coste(0) {
        kruskal(localidades);
    }

    int costeCarreteras() {
        return coste; 
    }

    int aeropuertosNecesarios() {
        return cjtos.num_cjtos();
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M, A;      // N�mero de localidades, N�mero de caminos posibles que se pueden construir, coste de construir un aeropuerto.

    cin >> N >> M >> A;
    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> localidades(N);  // Grafo valorado en el que los v�rtices son las localidades y las aristas los caminos entre ellas, siendo el valor el coste de construir el camino.
    int X, Y, C;        // X, Y localidades a unir, C el coste del camino entre X e Y.
    for (int i = 0; i < M; i++) {
        cin >> X >> Y >> C;
        if(C < A)
            localidades.ponArista({ X - 1,Y - 1, C });
    }

    // resolver el caso posiblemente llamando a otras funciones
    Aeropuertos aeropuertos(localidades);

    // escribir la soluci�n
    int costeConstruccion = aeropuertos.aeropuertosNecesarios() * A;
    cout << aeropuertos.costeCarreteras() + costeConstruccion << " " << aeropuertos.aeropuertosNecesarios() << '\n';


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