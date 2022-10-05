/*
 * MUY IMPORTANTE: Solo se corregir�n los comentarios y el c�digo
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificaci�n fuera de esas etiquetas no ser� corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes hab�is hecho esta soluci�n:
  * Estudiante 1: Juan Romo Iribarren TAIS89
  * Estudiante 2:
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
#include <climits>
#include "Grafo.h" 
using namespace std;


/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 El coste de la soluci�n es O(N + M), siendo N el n�mero de personajes en Overcity que coincide con el n�mero de v�rtices del grafo
 y M el n�mero de pares de amigos que coincide con el n�mero de aristas.

 Los personajes est�n guardados en un grafo, donde cada v�rtice representa a cada uno de los personajes y cada arista representa
 la conexi�n entre 2 amigos, es decir, cada par de amigos.

 Luego tenemos un vector donde se guarda el valor i-esimo de oro que pide cada personaje para difundir el rumor.
 En la funci�n dfs, recorremos el grafo, teniendo un vector de booleanos para saber si hemos recorrido un v�rtice
 o no. Para recorrerlo, visitamos los adyacentes de los adyacentes, llamando a la funci�n de manera recursiva,
 guardando el valor m�s bajo de todos esos adyacentes.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo (despu�s de la marca)
 //@ <answer>

class completarMision {
public:
    completarMision(Grafo const& g, vector<int> const& vVal) : visit(g.V(), false) {
        for (int i = 0; i < g.V(); i++) {                                   // Recorremos el n�mero de v�rtices del grafo.
            if (!visit[i]) {
                res += dfs(g, i, vVal);
                minimo = INT_MAX;
            }
        }
    }

    int minim() const {
        return res; 
    }

private:
    vector<bool> visit;
    vector<int> vVal;
    int res = 0;
    int minimo = INT_MAX;

   
    int dfs(Grafo const& g, int a, vector<int> const& v) {
        visit[a] = true;
        if (minimo > v[a]) {
            minimo = v[a];
        }
        for (int cont : g.ady(a)) {
            if (minimo > v[cont]) {
                minimo = v[cont];
            }
            if (!visit[cont]) {
                dfs(g, cont, v);
            }
        }
        return minimo;
    }
};

bool resuelveCaso() {

    // leemos la entrada
    int N, M;           // N es el n�mero de personajes en Overcity y M es el n�mero de pares de amigos
    cin >> N >> M;

    if (!cin)
        return false;


    vector<int> vVal;   // Vector para guardar la cantidad de oro que quiere cada personaje i-esimo.
    int aux;

    vVal.push_back(0);
    // leer el resto del caso y resolverlo
    for (int i = 0; i < N; i++) {       // Guardamos los valores de cantidad de oro en el vector.
        cin >> aux;
        vVal.push_back(aux);
    }

    Grafo g(N + 1);         // Grafo de personajes para guardar los pares de amigos.


    for (int j = 0; j < M; j++) {       // Conectamos quienes son amigos en el grafo mediante los pares dados en la entrada.
        int am1, am2;
        cin >> am1 >> am2;              // Leemos el par de amigos dados
        g.ponArista(am1, am2);  // Conectamos los amigos en el grafo.
    }
    
    completarMision c(g, vVal);
    cout << c.minim() << '\n';

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

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
