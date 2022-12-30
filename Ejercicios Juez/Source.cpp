/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "ConjuntosDisjuntos.h"
#include <string>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El coste de la función en el caso peor es O(F*C), donde F es el número de filas y C el número de columnas

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const vector<std::pair<int, int>> direcciones = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

bool resuelveCaso() {
    // leer los datos de la entrada

    int F, C;       // Número de filas y de columnas.

    cin >> F >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    ConjuntosDisjuntos conjuntos(F*C);
    vector<vector<string>> mapa(F, vector<string>(C));         // Vector tipo matriz para marcar las zonas del mapa con manchas (#).

    int maximo = 0;
    bool mancha = false;
    cin.ignore();
    for (int i = 0; i < F; i++) {
        string aux;
        getline(cin, aux, '\n');
        for (int j = 0; j < C; j++) {
            if (aux.at(j) == '#') {
                mapa[i][j] = '#';
                mancha = true;      // Hemos encontrado una mancha
                int pos = (i * C + j);          // Obtenemos la posición de i, j.
                for (auto d : direcciones) {    // Recorremos las celdas adyacentes a la celda [i][j] para ver si está unida a alguna mancha.
                    int fila = i + d.first;
                    int col = j + d.second;
                    int pos2 = fila * C + col;      // Obtenemos la posición de la adyacente.
                    if (fila >= 0 && fila < F && col >= 0 && col < C && mapa[fila][col] == "#" && !conjuntos.unidos(pos, pos2)) {   // Comprobamos que se encuentren dentro del rango, que sea una mancha y que no estén unidas las posiciones.
                        conjuntos.unir(pos, pos2);      // Unimos las celdas ya que están en la misma mancha.
                        maximo = max(maximo, conjuntos.cardinal(pos) -1);
                    }
                }
            }
            else {
                mapa[i][j] = "";
            }
        }
    }

    if (maximo == 0 && mancha) {    // Si se ha encontrado una mancha de sólo una celda.
        maximo = 1;
    }
    cout << maximo  << " "; 

        int N;      // Número de imágenes adicionales tomadas.
        cin >> N;
        if (maximo == 0 && N > 0) maximo = 1;
        for (int i = 0; i < N; i++) {
            int f, c;       // fila y columna donde aparece la nueva celda manchada.
            cin >> f >> c;
            f--;
            c--;
            mapa[f][c] = "#";       // Marcamos la celda.
            int pos = f * C + c;        // Obtenemos la posición
            for (auto d : direcciones) {    // Recorremos las celdas adyacentes a la celda [f][c] para ver si está unida a alguna mancha.
                int fila = f + d.first;
                int col = c + d.second;
                int pos2 = fila * C + col;      // Obtenemos la posición de la adyacente.
                if (fila >= 0 && fila < F && col >= 0 && col < C && mapa[fila][col] == "#" && !conjuntos.unidos(pos, pos2)) {   // Comprobamos que se encuentren dentro del rango, que sea una mancha y que no estén unidas las posiciones.
                    conjuntos.unir(pos, pos2);      // Unimos las celdas ya que están en la misma mancha.
                    maximo = max(maximo, conjuntos.cardinal(pos));
                }
            }
            cout << maximo << " ";
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