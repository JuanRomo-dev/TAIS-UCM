/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1:   Juan Romo Iribarren TAIS89.
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <vector>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El coste del algoritmo en el caso peor es O(N log(N)), ya que este es el coste de la operación sort que utilizamos para ordenar las puntuaciones y donde N es el tamaño de las puntuaciones.

 Escribe también una demostración que justifique que tu solución encuentra
 siempre soluciones óptimas.

 He resuelto el problema mediante un algoritmo voraz, que encuentra la solución de manera muy directa, eligiendo en cada paso la mejor opción posible, con el objetivo de obtener una solución
 óptima de forma global al problema. En este caso, tenemos un partido i, en el cuál los broncos obtienen bi puntos y los rivales ri puntos. Se debe cumplit que bi > ri, sumando
 en cada paso la diferencia de puntos al resultado. Además, tenemos que ordenar los puntos de los rivales de menor a mayor: r1 < r2 < ... < ri, y los puntos de los broncos de mayor
 a menor: b1 > b2 > ... > bi. Por otra parte, si se encuentra en algún momento que bi < ri, quiere decir que los broncos han perdido ese partido, por lo que finalizaría el algoritmo, 
 pues al estar los valores ordenados, en el momento en el que se encuentre un partido perdido, los demás también van a ser perdidos, por lo que el resultado no crecería más. 

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

int exitoMaximo(vector<int>& pRivales, vector<int>& pBroncos) {
    int maximo = 0;                                             // Éxito máximo que se puede lograr al reorganizar las puntuaciones de forma óptima.

    sort(pRivales.begin(), pRivales.end(), less<int>());    // Ordenamos la puntuación de los rivales de menor a mayor.
    sort(pBroncos.begin(), pBroncos.end(), greater<int>()); // Ordenamos la puntuación de los broncos de menor a mayor.

    bool broncosPierden = false;                            // Variable booleana para saber si los broncos han perdido un partido, ya que al estar ordenadas las puntuaciones te ahorras seguir recorriendo.  
    int i = 0;
    while (i < pRivales.size() && !broncosPierden) {        // Mientras no haya un partido perdido o no lleguemos al límite del vector
        if (pBroncos[i] < pRivales[i]) {                    // Si los broncos pierden un partido lo marcamos.
            broncosPierden = true;
        }
        else {
            maximo += pBroncos[i] - pRivales[i];            // Vamos sumando las puntuaciones para obtener la puntuación máxima que se puede lograr.
        }

        i++;
    }

    return maximo;
}

bool resuelveCaso() {

    int N;
    cin >> N;  // número de partidos

    if (N == 0)
        return false;

    // leer el resto del caso y resolverlo
    vector<int> pRivales, pBroncos;                         // Vectores para guardar las puntuaciones de broncos y rivales.
    int aux;

    for (int i = 0; i < N; i++) {
        cin >> aux;
        pRivales.push_back(aux);
    }

    for (int j = 0; j < N; j++) {
        cin >> aux;
        pBroncos.push_back(aux);
    }

    cout << exitoMaximo(pRivales, pBroncos) << '\n';

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // system("PAUSE");
#endif
    return 0;
}
