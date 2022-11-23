
/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Para resolver este problema, debemos recorrer un bitmap en forma de matriz i, j, en el cuál queremos buscar el número de manchas que contiene, es decir, hay una mancha si hay uno
 o más píxels unidos en vertical u horizontal. Para ello, vamos a ir recorriendo los píxels y en el momento en el que encontremos uno negro (#), realizamos una búsqueda en profundidad
 (dfs) sobre ese píxel, en la cuál, recursivamente calcularemos el tamaño de la mancha. Finalmente guardaremos el tamaño de la mancha con mayor número de píxels encontrada.

 En cuanto al coste del algoritmo es O(F * C), siendo F el número de filas del bitmap y C el número de columnas.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class BitMap {
public:
    BitMap(vector<string> const& mapa) : F(mapa.size()), C(mapa[0].size()), nManchas(0), tamMax(0), visitados(F, vector<bool>(C, false)) {      // Constructora de la clase.
        for (int i = 0; i < F; i++) {       // Recorremos filas y columnas para buscar una nueva mancha.
            for (int j = 0; j < C; j++) {
                if (!visitados[i][j] && mapa[i][j] == '#') {        // Si el bit se trata de uno no visitado y negro se calcula el tamaño de su mancha.
                    nManchas++;
                    int tamMancha = dfs(mapa, i, j);
                    tamMax = max(tamMax, tamMancha);                // Guardamos el tamaño máximo de una mancha del bitmap.
                }
            }
        }
    }
    int numeroManchas() const {
        return nManchas;
    }
    int maxTam() const {
        return tamMax;
    }

private:
    int F, C, nManchas, tamMax;             // F número de filas, C número de columnas, nManchas es el número de manchas en el bitmap y tamMax es el tamaño de la mancha más grande.
    vector<vector<bool>> visitados;         // Vector para marcar que píxel ha sido visitado.
    const vector<pair<int, int>> posiciones = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };     // Vector que contiene las direcciones para recorrer en la búsqueda en profundidad.

    bool posicionCorrecta(int i, int j) const {     // Para comprobar si la posición se encuentra en los límites del bitmap.
        return 0 <= i && i < F && 0 <= j && j < C;
    }

    int dfs(vector<string> const& mapa, int i, int j) {            // Búsqueda en profundidad para averiguar el tamaño de una mancha.
        visitados[i][j] = true;             // Marcamos el bit
        int tam = 1;
        for (auto p : posiciones) {         // Recorremos las posiciones para ver los alrededores del bit (en vertical y horizontal).
            int ni = i + p.first;
            int nj = j + p.second;
            if (posicionCorrecta(ni, nj) && mapa[ni][nj] == '#' && !visitados[ni][nj]) {    // Si el píxel es negro en una posición correcta y además no ha sido visitado, realizamos la llamada recursiva.
                tam += dfs(mapa, ni, nj);
            }
        }
        return tam;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int F, C;       // F es el número de filas y C es el número de columnas del bitmap.

    cin >> F >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<string> mapa(F);         // En cada posición del vector se guarda una fila para construir el bitmap en forma de matriz.
    for (string& fila : mapa) {
        cin >> fila;
    }

    // resolver el caso posiblemente llamando a otras funciones
    BitMap bitmap(mapa);

    // escribir la solución
    cout << bitmap.numeroManchas() << " " << bitmap.maxTam() << '\n';

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