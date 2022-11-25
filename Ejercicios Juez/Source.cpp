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

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Este problema consiste en que tenemos una red de computadoras, la cu�l he representado mediante un grafo, donde los v�rtices son cada computadora o nodo de la red y las aristas representan las 
 conexiones entre esas computadoras. Tenemos un valor Time To Live (TTL), en el cu�l dado un nodo origen s, se emite un mensaje y el valor TTL indica hasta a cu�nta distancia de s puede ser emitido
 el mensaje. Tenemos que calcular cu�ntos nodos son inalcanzables dependiendo de la consulta que nos pidan (seg�n el valor TTL y s). Para ello he realizado un recorrido en anchura (bf), en el cu�l,
 se buscan caminos m�nimos seg�n TTL. En la clase red, realizaremos el bfs dado un grafo y un valor ttl, el cu�l ir� contando el n�mero de v�rtices alcanzables desde s dado ttl. Restaremos ese
 valor al n�mero de v�rtices del grafo y con ello tendremos el n�mero de v�rtices que son inalcanzables.

 En cuanto al coste del algoritmo, es O(V + A), donde V es el n�mero de v�rtices del grafo y A es el n�mero de aristas.

 @ </answer> */

class Red {
public:
    Red(Grafo const& g, int origen, int ttl) : visitados(g.V(), false), numVisitados(0), anterior(g.V()), distancia(g.V()), s(origen) {     // Constructora de la clase
        bfs(g, ttl);        // Realizamos una b�squeda en anchura (bfs), en la cu�l buscaremos caminos m�nimos dado el valor ttl.
        cout << g.V() - numVisitados << '\n';       // Restamos el n�mero de v�rtices del grafo con el n�mero de v�rtices visitados a distancia ttl del v�rtice origen s.
    }

private:
    vector<bool> visitados;         // Vector para marcar que v�rtices han sido ya visitados. (�Hay camino de s a v?)
    vector<int> anterior;           // Vector para marcar el v�rtice anterior. (�ltimo v�rtice antes de llegar a v).
    vector<int> distancia;          // Distancia a la que se encuentra el v�rtice del origen. (Aristas en el camino s-v m�s corto).
    int s, numVisitados;            // s es el v�rtice origen desde el que deseamos buscar caminos m�s cortos y numVisitados es un contador de nodos alcanzados desde el v�rtice origen a una distancia ttl.
    void bfs(Grafo const& g, int ttl) {     // B�squeda en anchura.
        queue<int> cola;            // Cola para guardar los v�rtices alcanzados de los que a�n no se han explorado sus adyacentes.
        distancia[0] = 0;           // Como es el v�rtice origen la distancia es 0.
        visitados[s] = true;        // Marcamos el v�rtice origen como visitado.
        numVisitados++;             // Como ya hemos visitado el v�rtice origen aumentamos el contador.
        cola.push(s);               // Lo a�adimos a la cola para comenzar a explorar sus adyacentes.
        while (!cola.empty()) {     // Mientras haya v�rtices sin explorar.
            int v = cola.front();   // Seleccionamos el v�rtice que toca seg�n la cola de prioridad.
            cola.pop();             // Lo eliminamos de la cola
            for (int w : g.ady(v)) {    // Recorremos sus adyacentes
                if (!visitados[w] && distancia[v] + 1 <= ttl) {     // Si el adyacente no ha sido visitado y est� a una distancia menor o igual al valor ttl
                    anterior[w] = v;                        // Marcamos que su v�rtice anterior es v
                    distancia[w] = distancia[v] + 1;        // Marcamos la distancia a la que se encuentra del nodo origen s.
                    visitados[w] = true;                    // Marcamos el v�rtice como visitado
                    numVisitados++;                         // Aumentamos en uno el contador de visitados
                    cola.push(w);                           // Lo a�adimos a la cola para poder explorar despu�s sus adyacentes.
                }
            }
        }
    } 
};

 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, C;           // N es el n�mero de nodos de la red y C es el n�mero de conexiones entre nodos de la red.

    cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    int v, w;       // v y w son los nodos a guardar en el grafo por cada l�nea.
    Grafo g(N);
    for (int i = 0; i < C; i++) {      // Construimos el grafo uniendo los pares de nodos.
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }

    int k;          // k es el n�mero de consultas a realizar para ver cu�ntos nodos no son accesibles desde el nodo inicial.
    cin >> k;

    // resolver el caso posiblemente llamando a otras funciones
    // escribir la soluci�n
    int s, ttl;     // s es el nodo origen desde el cu�l se empieza a emitir el mensaje y ttl es el campo Time To Live que 
                    // contiene el n�mero de nodos que pueden retransmitir el mensaje, reenvi�ndolo hacia su destino a trav�s de todos los nodos adyacentes, antes de que sea descartado.

    for (int i = 0; i < k; i++) {
        cin >> s >> ttl;                // Leemos los valores s y ttl para cada consulta
        Red red(g, s - 1, ttl);
    }
    cout << "---" << '\n';

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