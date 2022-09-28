/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Juan Romo Iribarren
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

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

  Para resolver el problema, he creado una clase Atril, en la cuál tenemos el número de músicos que tocan un instrumento, el número de partituras que se tienen para ese instrumento
  y el número de músicos que van a estar tocando en ese atril. A continuación, después de haber leído el número de partituras que podemos comprar (P) y el número de instrumentos distintos de la orquesta
  (N), creamos una cola de prioridad con los datos de cada atril, para así poder acceder fácilmente a cuál es el atril más prioritario, es decir, el más compartido (el que más músicos utilizan).
  Después se calcula el número de partituras a repartir restando P - N, y se recorre en un bucle 1 a 1 estas partituras a repartir para cada instrumento, reordenando la cola según su prioridad.
  Finalmente, mostramos cuál es el atril que más músicos están utilizando al mismo tiempo.

  El coste de la solución es O(N*log(N)), siendo N el número de instrumentos de la orquesta.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

class Atril {
public:
    Atril(int musicos) : nMusicos(musicos), nTocando(musicos), nPartituras(1) {}      // nMusicos indica el número de personas que tocan ese instrumento, nTocando el número de músicos 
    // en el atril y nPartituras es el número de partituras para ese instrumento.                                                     

    int getnTocando() const {       // Accesora para el numero de musicos tocando en el atril.
        return nTocando;
    }
    void darPartitura() {           // Añade una partitura a este tipo de instrumento
        nPartituras++;
        nTocando = nMusicos / nPartituras + (nMusicos % nPartituras != 0); // Para calcular el número de músicos por atril en ese instrumento.
    }
    bool operator<(Atril const& b) const {  // Para reordenar la cola según el atril más compartido (con mayor número de músicos).
        return b.nTocando > this->nTocando;
    }

private:
    int nMusicos;       // Número de músicos de un instrumento.
    int nPartituras;    // Número de partituras de un instrumento.
    int nTocando;       // Número de personas tocando en el atril.
};

bool resuelveCaso() {

    // leemos la entrada
    int P, N;
    cin >> P >> N;          // P número de partituras que podremos comprar y N número de instrumentos distintos de la orquesta.

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    priority_queue<Atril> cola;    // priority_queue donde guardamos los datos de cada atril según su prioridad.
    int cantidadMusicos;
    for (int i = 0; i < N; i++) {   // Coste O(N*log(N))
        cin >> cantidadMusicos;
        cola.push(cantidadMusicos);       // cantidadMusicos es el número de músicos que hay en la orquesta para ese instrumento.
    }                                              
    
    int nPartituras = P - N;            // Calculamos el número de partituras que se deben repartir entre los atriles.
 
    while (nPartituras != 0) {          // Vamos repartiendo cada partitura una a una.
        Atril atr = cola.top();
        cola.pop();
        atr.darPartitura();             // Añadimos una partitura a ese instrumento.
        cola.push(atr);                 // Reordenamos la cola.
        nPartituras--;                  // Se reduce el número de partituras que quedan por repartir.
    }

    cout << cola.top().getnTocando() << "\n";       // Mostramos cuál es el atril más compartido.

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

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
