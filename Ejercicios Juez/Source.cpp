/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Juan Romo Iribarren TAIS89
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Para resolver el ejercicio vamos a utilizar un grafo dirigido valorado, en el cuál las celdas del laberinto son los vértices y los pasadizos que atraviesa un ratón son las aristas,
 siendo el valor de esta el tiempo que tarda un ratón en atravesarla. Debemos de buscar los caminos de coste mínimo desde un vértice origen (primeraCelda) a todos los demás del grafo,
 para lo cuál utilizamos el algoritmo de Dijkstra. Para comprobar que podemos llegar a todos los vértices con el menor coste posible, colocamos las aristas al revés (de B a A). 

 El coste es O(N * log V + V), donde N es el número de aristas del grafo y V es el número de vértices del grafo.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

template <typename tSalida>
class Ratones {
private:
	int tiempoCrono;											// Tiempo cuenta atrás del cronómetro.
	int primeraCelda;											// Vértice origen para buscar caminos de coste mínimo.
	const tSalida limiteMAX = numeric_limits<tSalida>::max();	// Para establecer un límite.
	IndexPQ<tSalida> cola;										// Cola de prioridad
	vector<tSalida> camino;										// Vector para ir guardando el camino.

public:
	Ratones(int primer, int tiemp, DigrafoValorado<tSalida> const& grv) : primeraCelda(primer), tiempoCrono(tiemp), camino(grv.V(), limiteMAX), cola(grv.V()) {
		camino[primeraCelda] = 0;		// Inicializamos el primer valor del camino
		cola.push(primeraCelda, 0);		// Inicializamos la cola de prioridad.

		while (!cola.empty()) {				
			int vertice = cola.top().elem;		// Obtenemos el primer vértice del camino desde la cola de prioridad.
			cola.pop();
			for (auto a : grv.ady(vertice))		// Relajamos las aristas del grafo para ir encontrando los caminos mínimos.
				relajar(a);
		}
	}

	int numAlcanzan() const {		// Empieza en -1 porque el primer ratón que sale no se cuenta y es distinto de limiteMAX.
		int cont = -1;
		for (int i : camino) {
			if (i != limiteMAX) {		// Vemos el número de ratones que alcanzan la salida.
				cont++;
			}
		}
		return cont;
	}

private:
	void relajar(AristaDirigida<tSalida> arista) {			// Función para relajar la arista (para encontrar el camino mínimo)
		int a1 = arista.desde();
		int a2 = arista.hasta();
		if ((camino[a2] > (camino[a1] + arista.valor())) && ((camino[a1] + arista.valor()) <= tiempoCrono)) {	
			camino[a2] = camino[a1] + arista.valor();
			cola.update(a2, camino[a2]);
		}
	}
};

bool resuelveCaso() {
	// leemos la entrada
	int N, S, T, P;				// N es el número de celdas del laberinto, S es el número de la celda donde se encuentra la salida, T es el número de segundos con el que incicia el cronómetro y P es el
								// número de líneas que describen cada una de ellas un pasadizo.
	cin >> N >> S >> T >> P;

	if (!cin) {
		return false;
	}

	// leer el resto del caso y resolverlo
	DigrafoValorado<int> digr(N);			// Utilizamos un digrafo valorado para representar caminos valorados según el tiempo entre 2 celdas.
	for (int i = 0; i < P; i++) {			// Recorremos el número de pasadizos.
		int A, B, tiempo;						// Leemos los datos de cada pasadizo: A es el primer número de celda, B es el segundo número de celda y tiempo es lo que tarda un ratón en llegar de A a B.
		cin >> A >> B >> tiempo;
		digr.ponArista({ B - 1, A - 1, tiempo });		// Colocamos una arista entre las 2 celdas con el valor tiempo.
	}

	Ratones<int> ratones(S - 1, T, digr);
	cout << ratones.numAlcanzan() << '\n';

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
