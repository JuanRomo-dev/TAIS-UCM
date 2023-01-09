/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Demostramos formalmente que nuestra soluci�n es �ptima. En este caso para que una soluci�n sea �ptima, el n�mero de parches utilizados debe de ser el menor posible.

 Recorremos los agujeros de la manguera en orden seg�n la distancia a la que se encuentran del primero agujero. La soluci�n voraz seleccionar� si se coloca un
 parche �nicamente si con el anteriormente colocado no se alcanza al agujero actual, que necesitar� un nuevo parche para ser colocado.

 En cuanto al coste del algoritmo es O(n), donde n es el n�mero de agujeros de la manguera.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

int resolver(vector<int> const& agujeros, int L) {
    int nParches = 1;           // Se coloca un parche en el primer agujero siempre.
    bool parcheGrande = false;
    int distancia = agujeros[0];    // La distancia comienza siendo la del primero agujero

    for (int i = 0; i < agujeros.size(); i++) {
        if (distancia + L < agujeros[i]) {      // Si colocando el parche de longitud L desde el agujero anterior no se llega al siguiente, entonces se coloca uno nuevo.
            distancia = agujeros[i];
            nParches++;
        }
    }

    return nParches;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, L;       // N�mero de agujeros de la manguera y longitud de los parches.

    cin >> N >> L;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> agujeros(N);
    for (int i = 0; i < N; i++) {
        cin >> agujeros[i];
    }

    // resolver el caso posiblemente llamando a otras funciones
    int sol = resolver(agujeros, L);

    // escribir la soluci�n
    cout << sol << '\n';

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