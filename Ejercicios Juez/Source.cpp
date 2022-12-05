/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Este problema consiste en que originalmente se da un n�mero, y decidiendo cada vez que bot�n pulsar alcanzar un n�mero dado en el menor n�mero de pulsaciones
 posibles. Es decir, debemos de buscar caminos m�nimos, por lo que realizaremos una b�squeda en anchura desde el n�mero origen probando cada vez una operaci�n dada.
 Cuando encontremos el n�mero destino tras pulsar una serie de botones se devolver� el n�mero de pulsaciones total de los botones.

 En cuanto al coste del algoritmo se encuentra en O(V + A), donde V en este caso son todos los posibles n�meros calculados entre el origen y el destino y las aristas
 son las operaciones realizadas.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

const int MAX_DIGITOS = 10000;  // M�ximo de d�gitos de la m�quina calculadora, ya que solo puede tener hasta 4 d�gitos.
const int INF = INT_MAX;        // Infinito (en realidad es el m�ximo valor que puede tener un int).

int adyacente(int v, int i) {   // Posibles botones que pulsar para ir calculando n�meros que nos puedan llevar al destino
    switch (i) {
    case 0: return (v + 1) % MAX_DIGITOS;           // Sumar 1. Como se puede desbordar del m�ximo de d�gitos de la m�quina se hace m�dulo 10.000.
    case 1: return (v * 2) % MAX_DIGITOS;           // Multiplicar 2. "                                                                             "
    case 2: return v / 3;                           // Dividir entre 3. En este caso no hace falta el m�dulo 10.000 pues nunca se va a desbordar. 
    }
}

int bfs(int const& origen, int const& destino) {    // B�squeda en anchura.
    if (origen == destino) {
        return 0;
    }
    vector<int> distancia(MAX_DIGITOS, INF);    // El vector distancia tendr� un espacio MAX_DIGITOS, ya que la distancia entre el origen y el destino podr�a ser m�ximo ese valor
                                                // y cada valor del vector ser� INF (infinito) para marcar como que a�n no ha sido visitado.
    distancia[origen] = 0;                      // La distancia del origen es 0.
    queue<int> q;
    q.push(origen);                             // A�adimos el origen a la cola;
    while (!q.empty()) {                        // Mientras haya n�meros por explorar en la cola de prioridad.
        int v = q.front();
        q.pop();
        for (int i = 0; i < 3; i++) {
            int w = adyacente(v, i);                    // Se calcula el siguiente n�mero adyacente por alguna de las operaciones seg�n el valor de la i.
            if (distancia[w] == INF) {                             // Si w no ha sido explorado a�n
                distancia[w] = distancia[v] + 1;        // Se marca como visitado aumentando la distancia respecto al origen.
                if (w == destino) {
                    return distancia[w];                // Si resulta que hemos alcanzado el destino, se devuelve la distancia a la que se encuentra del origen.
                }
                else {
                    q.push(w);                          // Si no se a�ade a la cola para buscar en anchura m�s adelante.
                }
            }
        }
    }

}

bool resuelveCaso() {
    // leer los datos de la entrada
    int origen, destino;                        // Origen es el n�mero que se da al principio en la m�quina y destino el que se debe lograr pulsando los botones

    cin >> origen >> destino;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    int nPulsaciones = bfs(origen, destino);

    // escribir la soluci�n
    cout << nPulsaciones << '\n';

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