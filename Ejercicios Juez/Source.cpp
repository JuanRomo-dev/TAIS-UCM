
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Para resolver este problema, debemos recorrer un bitmap en forma de matriz i, j, en el cu�l queremos buscar el n�mero de manchas que contiene, es decir, hay una mancha si hay uno
 o m�s p�xels unidos en vertical u horizontal. Para ello, vamos a ir recorriendo los p�xels y en el momento en el que encontremos uno negro (#), realizamos una b�squeda en profundidad
 (dfs) sobre ese p�xel, en la cu�l, recursivamente calcularemos el tama�o de la mancha. Finalmente guardaremos el tama�o de la mancha con mayor n�mero de p�xels encontrada.

 En cuanto al coste del algoritmo es O(F * C), siendo F el n�mero de filas del bitmap y C el n�mero de columnas.
 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class BitMap {
public:
    BitMap(vector<string> const& mapa) : F(mapa.size()), C(mapa[0].size()), nManchas(0), tamMax(0), visitados(F, vector<bool>(C, false)) {      // Constructora de la clase.
        for (int i = 0; i < F; i++) {       // Recorremos filas y columnas para buscar una nueva mancha.
            for (int j = 0; j < C; j++) {
                if (!visitados[i][j] && mapa[i][j] == '#') {        // Si el bit se trata de uno no visitado y negro se calcula el tama�o de su mancha.
                    nManchas++;
                    int tamMancha = dfs(mapa, i, j);
                    tamMax = max(tamMax, tamMancha);                // Guardamos el tama�o m�ximo de una mancha del bitmap.
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
    int F, C, nManchas, tamMax;             // F n�mero de filas, C n�mero de columnas, nManchas es el n�mero de manchas en el bitmap y tamMax es el tama�o de la mancha m�s grande.
    vector<vector<bool>> visitados;         // Vector para marcar que p�xel ha sido visitado.
    const vector<pair<int, int>> posiciones = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };     // Vector que contiene las direcciones para recorrer en la b�squeda en profundidad.

    bool posicionCorrecta(int i, int j) const {     // Para comprobar si la posici�n se encuentra en los l�mites del bitmap.
        return 0 <= i && i < F && 0 <= j && j < C;
    }

    int dfs(vector<string> const& mapa, int i, int j) {            // B�squeda en profundidad para averiguar el tama�o de una mancha.
        visitados[i][j] = true;             // Marcamos el bit
        int tam = 1;
        for (auto p : posiciones) {         // Recorremos las posiciones para ver los alrededores del bit (en vertical y horizontal).
            int ni = i + p.first;
            int nj = j + p.second;
            if (posicionCorrecta(ni, nj) && mapa[ni][nj] == '#' && !visitados[ni][nj]) {    // Si el p�xel es negro en una posici�n correcta y adem�s no ha sido visitado, realizamos la llamada recursiva.
                tam += dfs(mapa, ni, nj);
            }
        }
        return tam;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int F, C;       // F es el n�mero de filas y C es el n�mero de columnas del bitmap.

    cin >> F >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<string> mapa(F);         // En cada posici�n del vector se guarda una fila para construir el bitmap en forma de matriz.
    for (string& fila : mapa) {
        cin >> fila;
    }

    // resolver el caso posiblemente llamando a otras funciones
    BitMap bitmap(mapa);

    // escribir la soluci�n
    cout << bitmap.numeroManchas() << " " << bitmap.maxTam() << '\n';

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