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
using namespace std;


/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

  Para resolver el problema, he creado una clase Atril, en la cu�l tenemos el n�mero de m�sicos que tocan un instrumento, el n�mero de partituras que se tienen para ese instrumento
  y el n�mero de m�sicos que van a estar tocando en ese atril. A continuaci�n, despu�s de haber le�do el n�mero de partituras que podemos comprar (P) y el n�mero de instrumentos distintos de la orquesta
  (N), creamos una cola de prioridad con los datos de cada atril, para as� poder acceder f�cilmente a cu�l es el atril m�s prioritario, es decir, el m�s compartido (el que m�s m�sicos utilizan).
  Despu�s se calcula el n�mero de partituras a repartir restando P - N, y se recorre en un bucle 1 a 1 estas partituras a repartir para cada instrumento, reordenando la cola seg�n su prioridad.
  Finalmente, mostramos cu�l es el atril que m�s m�sicos est�n utilizando al mismo tiempo.

  El coste de la soluci�n es O(N*log(N)), siendo N el n�mero de instrumentos de la orquesta.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo (despu�s de la marca)
 //@ <answer>

class Atril {
public:
    Atril(int musicos) : nMusicos(musicos), nTocando(musicos), nPartituras(1) {}      // nMusicos indica el n�mero de personas que tocan ese instrumento, nTocando el n�mero de m�sicos 
    // en el atril y nPartituras es el n�mero de partituras para ese instrumento.                                                     

    int getnTocando() const {       // Accesora para el numero de musicos tocando en el atril.
        return nTocando;
    }
    void darPartitura() {           // A�ade una partitura a este tipo de instrumento
        nPartituras++;
        nTocando = nMusicos / nPartituras + (nMusicos % nPartituras != 0); // Para calcular el n�mero de m�sicos por atril en ese instrumento.
    }
    bool operator<(Atril const& b) const {  // Para reordenar la cola seg�n el atril m�s compartido (con mayor n�mero de m�sicos).
        return b.nTocando > this->nTocando;
    }

private:
    int nMusicos;       // N�mero de m�sicos de un instrumento.
    int nPartituras;    // N�mero de partituras de un instrumento.
    int nTocando;       // N�mero de personas tocando en el atril.
};

bool resuelveCaso() {

    // leemos la entrada
    int P, N;
    cin >> P >> N;          // P n�mero de partituras que podremos comprar y N n�mero de instrumentos distintos de la orquesta.

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    priority_queue<Atril> cola;    // priority_queue donde guardamos los datos de cada atril seg�n su prioridad.
    int cantidadMusicos;
    for (int i = 0; i < N; i++) {   // Coste O(N*log(N))
        cin >> cantidadMusicos;
        cola.push(cantidadMusicos);       // cantidadMusicos es el n�mero de m�sicos que hay en la orquesta para ese instrumento.
    }                                              
    
    int nPartituras = P - N;            // Calculamos el n�mero de partituras que se deben repartir entre los atriles.
 
    while (nPartituras != 0) {          // Vamos repartiendo cada partitura una a una.
        Atril atr = cola.top();
        cola.pop();
        atr.darPartitura();             // A�adimos una partitura a ese instrumento.
        cola.push(atr);                 // Reordenamos la cola.
        nPartituras--;                  // Se reduce el n�mero de partituras que quedan por repartir.
    }

    cout << cola.top().getnTocando() << "\n";       // Mostramos cu�l es el atril m�s compartido.

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
