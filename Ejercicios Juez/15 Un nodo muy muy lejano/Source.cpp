/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "Grafo.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Este problema consiste en que tenemos una red de computadoras, la cuál he representado mediante un grafo, donde los vértices son cada computadora o nodo de la red y las aristas representan las 
 conexiones entre esas computadoras. Tenemos un valor Time To Live (TTL), en el cuál dado un nodo origen s, se emite un mensaje y el valor TTL indica hasta a cuánta distancia de s puede ser emitido
 el mensaje. Tenemos que calcular cuántos nodos son inalcanzables dependiendo de la consulta que nos pidan (según el valor TTL y s). Para ello he realizado un recorrido en anchura (bf), en el cuál,
 se buscan caminos mínimos según TTL. En la clase red, realizaremos el bfs dado un grafo y un valor ttl, el cuál irá contando el número de vértices alcanzables desde s dado ttl. Restaremos ese
 valor al número de vértices del grafo y con ello tendremos el número de vértices que son inalcanzables.

 En cuanto al coste del algoritmo, es O(V + A), donde V es el número de vértices del grafo y A es el número de aristas.

 @ </answer> */

class Red {
public:
    Red(Grafo const& g, int origen, int ttl) : visitados(g.V(), false), numVisitados(0), anterior(g.V()), distancia(g.V()), s(origen) {     // Constructora de la clase
        bfs(g, ttl);        // Realizamos una búsqueda en anchura (bfs), en la cuál buscaremos caminos mínimos dado el valor ttl.
        cout << g.V() - numVisitados << '\n';       // Restamos el número de vértices del grafo con el número de vértices visitados a distancia ttl del vértice origen s.
    }

private:
    vector<bool> visitados;         // Vector para marcar que vértices han sido ya visitados. (¿Hay camino de s a v?)
    vector<int> anterior;           // Vector para marcar el vértice anterior. (Último vértice antes de llegar a v).
    vector<int> distancia;          // Distancia a la que se encuentra el vértice del origen. (Aristas en el camino s-v más corto).
    int s, numVisitados;            // s es el vértice origen desde el que deseamos buscar caminos más cortos y numVisitados es un contador de nodos alcanzados desde el vértice origen a una distancia ttl.
    void bfs(Grafo const& g, int ttl) {     // Búsqueda en anchura.
        queue<int> cola;            // Cola para guardar los vértices alcanzados de los que aún no se han explorado sus adyacentes.
        distancia[0] = 0;           // Como es el vértice origen la distancia es 0.
        visitados[s] = true;        // Marcamos el vértice origen como visitado.
        numVisitados++;             // Como ya hemos visitado el vértice origen aumentamos el contador.
        cola.push(s);               // Lo añadimos a la cola para comenzar a explorar sus adyacentes.
        while (!cola.empty()) {     // Mientras haya vértices sin explorar.
            int v = cola.front();   // Seleccionamos el vértice que toca según la cola de prioridad.
            cola.pop();             // Lo eliminamos de la cola
            for (int w : g.ady(v)) {    // Recorremos sus adyacentes
                if (!visitados[w] && distancia[v] + 1 <= ttl) {     // Si el adyacente no ha sido visitado y está a una distancia menor o igual al valor ttl
                    anterior[w] = v;                        // Marcamos que su vértice anterior es v
                    distancia[w] = distancia[v] + 1;        // Marcamos la distancia a la que se encuentra del nodo origen s.
                    visitados[w] = true;                    // Marcamos el vértice como visitado
                    numVisitados++;                         // Aumentamos en uno el contador de visitados
                    cola.push(w);                           // Lo añadimos a la cola para poder explorar después sus adyacentes.
                }
            }
        }
    } 
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, C;           // N es el número de nodos de la red y C es el número de conexiones entre nodos de la red.

    cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    int v, w;       // v y w son los nodos a guardar en el grafo por cada línea.
    Grafo g(N);
    for (int i = 0; i < C; i++) {      // Construimos el grafo uniendo los pares de nodos.
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }

    int k;          // k es el número de consultas a realizar para ver cuántos nodos no son accesibles desde el nodo inicial.
    cin >> k;

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la solución
    int s, ttl;     // s es el nodo origen desde el cuál se empieza a emitir el mensaje y ttl es el campo Time To Live que 
                    // contiene el número de nodos que pueden retransmitir el mensaje, reenviándolo hacia su destino a través de todos los nodos adyacentes, antes de que sea descartado.

    for (int i = 0; i < k; i++) {
        cin >> s >> ttl;                // Leemos los valores s y ttl para cada consulta
        Red red(g, s - 1, ttl);
    }
    cout << "---" << '\n';

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
