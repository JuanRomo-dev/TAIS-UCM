/*
 * MUY IMPORTANTE: Solo se corregir�n los comentarios y el c�digo
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificaci�n fuera de esas etiquetas no ser� corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes hab�is hecho esta soluci�n:
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 El coste del algoritmo en el caso peor es O(N log(N)), ya que este es el coste de la operaci�n sort que utilizamos para ordenar las puntuaciones y donde N es el tama�o de las puntuaciones.

 Escribe tambi�n una demostraci�n que justifique que tu soluci�n encuentra
 siempre soluciones �ptimas.

 He resuelto el problema mediante un algoritmo voraz, que encuentra la soluci�n de manera muy directa, eligiendo en cada paso la mejor opci�n posible, con el objetivo de obtener una soluci�n
 �ptima de forma global al problema. En este caso, tenemos un partido i, en el cu�l los broncos obtienen bi puntos y los rivales ri puntos. Se debe cumplit que bi > ri, sumando
 en cada paso la diferencia de puntos al resultado. Adem�s, tenemos que ordenar los puntos de los rivales de menor a mayor: r1 < r2 < ... < ri, y los puntos de los broncos de mayor
 a menor: b1 > b2 > ... > bi. Por otra parte, si se encuentra en alg�n momento que bi < ri, quiere decir que los broncos han perdido ese partido, por lo que finalizar�a el algoritmo, 
 pues al estar los valores ordenados, en el momento en el que se encuentre un partido perdido, los dem�s tambi�n van a ser perdidos, por lo que el resultado no crecer�a m�s. 

 @ </answer> */

 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo (despu�s de la marca)
 //@ <answer>

int exitoMaximo(vector<int>& pRivales, vector<int>& pBroncos) {
    int maximo = 0;                                             // �xito m�ximo que se puede lograr al reorganizar las puntuaciones de forma �ptima.

    sort(pRivales.begin(), pRivales.end(), less<int>());    // Ordenamos la puntuaci�n de los rivales de menor a mayor.
    sort(pBroncos.begin(), pBroncos.end(), greater<int>()); // Ordenamos la puntuaci�n de los broncos de menor a mayor.

    bool broncosPierden = false;                            // Variable booleana para saber si los broncos han perdido un partido, ya que al estar ordenadas las puntuaciones te ahorras seguir recorriendo.  
    int i = 0;
    while (i < pRivales.size() && !broncosPierden) {        // Mientras no haya un partido perdido o no lleguemos al l�mite del vector
        if (pBroncos[i] < pRivales[i]) {                    // Si los broncos pierden un partido lo marcamos.
            broncosPierden = true;
        }
        else {
            maximo += pBroncos[i] - pRivales[i];            // Vamos sumando las puntuaciones para obtener la puntuaci�n m�xima que se puede lograr.
        }

        i++;
    }

    return maximo;
}

bool resuelveCaso() {

    int N;
    cin >> N;  // n�mero de partidos

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
//  Lo que se escriba debajo de esta l�nea ya no forma parte de la soluci�n.

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
