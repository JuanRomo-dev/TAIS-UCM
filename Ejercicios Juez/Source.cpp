/*
 * MUY IMPORTANTE: Solo se corregir�n los comentarios y el c�digo
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificaci�n fuera de esas etiquetas no ser� corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes hab�is hecho esta soluci�n:
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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Para resolver el ejercicio vamos a utilizar un grafo dirigido valorado, en el cu�l las celdas del laberinto son los v�rtices y los pasadizos que atraviesa un rat�n son las aristas,
 siendo el valor de esta el tiempo que tarda un rat�n en atravesarla. Debemos de buscar los caminos de coste m�nimo desde un v�rtice origen (primeraCelda) a todos los dem�s del grafo,
 para lo cu�l utilizamos el algoritmo de Dijkstra. Para comprobar que podemos llegar a todos los v�rtices con el menor coste posible, colocamos las aristas al rev�s (de B a A). 

 El coste es O(N * log V + V), donde N es el n�mero de aristas del grafo y V es el n�mero de v�rtices del grafo.

 @ </answer> */

 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo (despu�s de la marca)
 //@ <answer>

template <typename tSalida>
class Ratones {
private:
	int tiempoCrono;											// Tiempo cuenta atr�s del cron�metro.
	int primeraCelda;											// V�rtice origen para buscar caminos de coste m�nimo.
	const tSalida limiteMAX = numeric_limits<tSalida>::max();	// Para establecer un l�mite.
	IndexPQ<tSalida> cola;										// Cola de prioridad
	vector<tSalida> camino;										// Vector para ir guardando el camino.

public:
	Ratones(int primer, int tiemp, DigrafoValorado<tSalida> const& grv) : primeraCelda(primer), tiempoCrono(tiemp), camino(grv.V(), limiteMAX), cola(grv.V()) {
		camino[primeraCelda] = 0;		// Inicializamos el primer valor del camino
		cola.push(primeraCelda, 0);		// Inicializamos la cola de prioridad.

		while (!cola.empty()) {				
			int vertice = cola.top().elem;		// Obtenemos el primer v�rtice del camino desde la cola de prioridad.
			cola.pop();
			for (auto a : grv.ady(vertice))		// Relajamos las aristas del grafo para ir encontrando los caminos m�nimos.
				relajar(a);
		}
	}

	int numAlcanzan() const {		// Empieza en -1 porque el primer rat�n que sale no se cuenta y es distinto de limiteMAX.
		int cont = -1;
		for (int i : camino) {
			if (i != limiteMAX) {		// Vemos el n�mero de ratones que alcanzan la salida.
				cont++;
			}
		}
		return cont;
	}

private:
	void relajar(AristaDirigida<tSalida> arista) {			// Funci�n para relajar la arista (para encontrar el camino m�nimo)
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
	int N, S, T, P;				// N es el n�mero de celdas del laberinto, S es el n�mero de la celda donde se encuentra la salida, T es el n�mero de segundos con el que incicia el cron�metro y P es el
								// n�mero de l�neas que describen cada una de ellas un pasadizo.
	cin >> N >> S >> T >> P;

	if (!cin) {
		return false;
	}

	// leer el resto del caso y resolverlo
	DigrafoValorado<int> digr(N);			// Utilizamos un digrafo valorado para representar caminos valorados seg�n el tiempo entre 2 celdas.
	for (int i = 0; i < P; i++) {			// Recorremos el n�mero de pasadizos.
		int A, B, tiempo;						// Leemos los datos de cada pasadizo: A es el primer n�mero de celda, B es el segundo n�mero de celda y tiempo es lo que tarda un rat�n en llegar de A a B.
		cin >> A >> B >> tiempo;
		digr.ponArista({ B - 1, A - 1, tiempo });		// Colocamos una arista entre las 2 celdas con el valor tiempo.
	}

	Ratones<int> ratones(S - 1, T, digr);
	cout << ratones.numAlcanzan() << '\n';

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
