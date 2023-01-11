/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Recurrencia de cada una de las fases:
                        {   sePuede(i,0) = true
    sePuede(i,j) =      {   sePuede(0,j) = false
                        {   sePuede(i-1,j)                                                      si longitud[i-1] > j
                        {   sePuede(i-1,j) || sePuede(i-1,j-longitud[i-1])                      si longitud[i-1] <= j
                        {   maneras(i,0) = 1
    maneras(i,j) =      {   maneras(0,j) = 0
                        {   maneras(i-1,j)                                                      si longitud[i-1] > j
                        {   maneras(i-1,j) + maneras(i-1,j-longitud[i-1])                       si longitud[i-1] <= j
                        {   minCordeles(i,0) = 0
    minCordeles(i,j) =  {   minCordeles(0,j) = 0
                        {   minCordeles(i-1,j)                                                  si longitud[i-1] > j
                        {   min(minCordeles(i-1,j) + minCordeles(i-1,j-longitud[i-1]) + 1)      si longitud[i-1] <= j
                        {   coste(i,0) = 0
    costes(i,j) =       {   coste(0,j) = 0
                        {   coste(i-1,j)                                                        si longitud[i-1] > j
                        {   min(coste(i-1,j) + coste(i-1,j-longitud[i-1]) + coste[i-1])         si longitud[i-1] <= j

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

struct tCordel {    // Contiene la longitud y el coste de un cordel. 
    int longitud;
    int coste;
};

void resolver(vector<tCordel> const& cordeles, int L, int N) {
    // Primero debemos probar si se puede fabricar una cometa con la longitud deseada:

    Matriz<bool> sePuede(N + 1, L + 1, false); // Para resolver el problema din�micamente utilizaremos una matriz, en la cu�l guardaremos las soluciones a los subproblemas.
                                         // En este caso, se ir� diciendo si es posible construir una cometa con las logitudes menores a L (De L a L + 1).
    sePuede[0][0] = true;   // 0 cordeles forman un total de 0 en la longitud de la cometa.

    for (int i = 1; i <= N; i++) {      // Recorremos los cordeles.
        sePuede[i][0] = true;       // La longitud es 0.
        for (int j = 1; j <= L; j++) {  // Recorremos todas las posibles longitudes anteriores a L.
            if (cordeles[i - 1].longitud > j) {     // Si la longitud del cordel anterior es mayor a la total que estamos probando para la cometa.
                sePuede[i][j] = sePuede[i - 1][j];  // Entonces ya tenemos el subproblema resuelto.
            }
            else {  // Si no tenemos la "subsoluci�n" ( pues cordeles[i - 1].longitud <= j)
                sePuede[i][j] = sePuede[i - 1][j] || sePuede[i - 1][j - cordeles[i - 1].longitud];  // sePuede ser� true si la anterior longitud de cordeles era exactamente igual a la de j,
                        // o si, para la longitud j que llevamos, menos la longitud del cordel anterior, eso nos da lo que nos falta por completar de la longitud de la cometa,
            }           // por lo que consultamos si el subproblema para ese trozo que nos falta por completar lo tenemos.
        }
    }

    if (sePuede[N][L]) {        // Si se puede formar la cometa con los cordeles disponibles de longitud L.
        cout << "SI" << " ";

        // Ahora, sabiendo que se puede formar la cometa, debemos averiguar de cuantas formas posibles se puede realizar.
        Matriz<int> maneras(N + 1, L + 1, 0); // Para resolver din�micamente el problema de averiguar de cuantas maneras distintas pordemos formar la longitud L de la cometa usando los N
                    // cordeles de los que disponemos, utilizamos esta matriz, la cu�l guardar� por cada n�mero de cordeles utilizados, el n�mero de maneras distintas de obtener la longitud de 0 a L.
        
        maneras[0][0] = 1;  // Para formar 0 de longitud se requieren de 0 cordeles.

        for (int i = 1; i <= N; i++) {
            maneras[i][0] = 1;  // Una longitud de 0 solo hay 1 forma (conjunto vac�o). "Caso base".
            for (int j = 1; j <= L; j++) {
                if (cordeles[i - 1].longitud > j) {     // Si la longitud del cordel anterior es mayor que la longitud j. (Hay subsoluci�n).
                    maneras[i][j] = maneras[i - 1][j];  
                }
                else {      // Si no tenemos la subsoluci�n (pues cordeles[i - 1].longitud <= j)
                    maneras[i][j] = maneras[i - 1][j] + maneras[i - 1][j - cordeles[i - 1].longitud]; // Entonces, sumamos las maneras de obtener la longitud j, junto a las maneras de obtener 
                                // lo que nos falta para llegar a j desde el cordel anterior.
                }
            }
        }

        cout << maneras[N][L] << " ";      // Mostramos las maneras diferentes que hay de formar con N cordeles una cometa de longitud L.

        // Ahora buscamos cu�l es el m�nimo de cordeles necesario para formar la longitud L.
        Matriz<EntInf> minCordeles(N + 1, L + 1, Infinito);   // Para resolver din�micamente el problema de averiguar cu�l es el m�nimo de cordeles N que necesitamos para formar la cometa
                    // de longitud L, utilizamos esta matriz, la cu�l guardar� el m�nimo de cordeles necesarios para formar la longitud L.

        minCordeles[0][0] = 0;  

        for (int i = 1; i <= N; i++) {
            minCordeles[i][0] = 0;  // Para formar una cometa de longitud 0, no necesitamos cordeles.
            for (int j = 1; j <= L; j++) {
                if (cordeles[i - 1].longitud > j) {
                    minCordeles[i][j] = minCordeles[i - 1][j];
                }
                else {
                    minCordeles[i][j] = min(minCordeles[i - 1][j], minCordeles[i][j - cordeles[i - 1].longitud] + 1);   // Obtenemos el m�nimo.
                }
            }
        }

        cout << minCordeles[N][L] << " ";      // Mostramos cu�l es el m�nimo de cordeles necesarios para obtener una cometa de longitud L.

        // Finalmente calculamos cu�l ser�a el coste m�s bajo de obtener la longitud L, disponiendo de los cordeles N.
        Matriz<EntInf> costes(N + 1, L + 1, Infinito);
        
        costes[0][0] = 0;   

        for (int i = 1; i <= N; i++) {
            costes[i][0] = 0;
            for (int j = 1; j <= L; j++) {
                if (cordeles[i - 1].longitud > j) {
                    costes[i][j] = costes[i - 1][j];
                }
                else {
                    costes[i][j] = min(costes[i - 1][j], costes[i - 1][j - cordeles[i - 1].longitud] + cordeles[i - 1].coste);
                }
            }
        }

        cout << costes[N][L];   // Mostramos el coste m�nimo de obtener la cometa de longitud L usando N cordeles.
    }
    else {
        cout << "NO";
    }
    cout << '\n';
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, L;      // N�mero de cordeles y longitud de la cometa a formar.
    
    cin >> N >> L;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<tCordel> cordeles(N);        // Vector con la informaci�n  de todos los cordeles.

    int longi, cost;        // Para leer la longitud y el coste de un cordel.
    for (int i = 0; i < N; i++) {
        cin >> longi >> cost;
        cordeles[i] = { longi, cost };
    }

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la soluci�n
    resolver(cordeles, L, N);

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