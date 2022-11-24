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

 En este ejercicio, teníamos que mirar por cada usuario i-ésimo dados (1, 2, 3...), si el difunde una noticia, contar cuántos usuarios van a llegar a conocerla.
 La manera de conocer una noticia es estando en el mismo grupo que el usuario que difunde la noticia. Por tanto vamos a utilizar la clase Grafo.h para representar estas
 conexiones entre grupos. Los vértices del grafo serán los usuarios, mientras que las aristas representan si un grafo y otro están en el mismo grupo. De todas formas, no
 es totalmente necesario que 2 vértices estén directamente unidas por una arista, pues si se puede trazar un camino del vértice origen a otro lejano, atravesando otros vértices
 y aristas quiere decir que también forma parte de ese grupo. Por tanto, iremos comprobando en la clase UsuariosNoticia para cada usuario i-ésimo cuantos usuarios conocen la noticia.
 Recorremos los vértices del grafo y por cada vértice, se realiza una búsqueda en profundidad, en la cuál guardaremos en el vector nUsuarios el usuario i-ésimo que estamos 
 consultando en ese momento y miraremos los adyecentes a ese vértice, para así contar el tamaño de usuarios que han llegado a conocer la noticia. Guardaremos el tamaño por cada 
 usuario en el vector amigos.

 En cuanto al coste del algortimo es O(V + A), donde V es el número de vértices y A es el número de aristas.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class UsuariosNoticia {
public:
    UsuariosNoticia(Grafo const& g) : visitados(g.V(), false), nUsuarios(g.V()) {       // Constructora de la clase.
        int i = 0;                          // i lleva la cuenta del usuario que está difundiendo la noticia en ese momento.
        for (int v = 0; v < g.V(); v++) {   // Recorremos los vértices del grafo 
            if (!visitados[v]) {            // Si ese vértice aún no ha sido visitado
                int tam = dfs(g, v, i);     // Calculamos con la búsqueda en profundidad cuántos usuarios acabarán conociendo la noticia si la difunde el usuario i.
                amigos.push_back(tam);      // Guardamos en el vector de amigos el número de usuarios que acabarán conociendo la noticia.
                i++;                        // Pasamos al siguiente usuario.
            }
        }
    }
    int getAmigos(int v) {                  // Para acceder al número de usuarios conocedores de la noticia que tiene el vértice v que difunde la noticia recibido por parámetro.
        return amigos[nUsuarios[v]];
    }

private:
    vector<bool> visitados;             // Vector para marcar los vértices ya explorados en dfs.
    vector<int> nUsuarios;              // Vector que contiene el número de usuarios i-ésimo (cada uno dinfunde la noticia).
    vector<int> amigos;                 // Vector donde se guardan los tamaños del grupo de cada usuario

    int dfs(Grafo const& g, int v, int i) {     // Búsqueda en profundidad.
        visitados[v] = true;            // Marcamos el vértice v como visitado.
        nUsuarios[v] = i;               // Guardamos el usuario que difunde la noticia en el vector nUsuarios.
        int tam = 1;
        for (int w : g.ady(v)) {        // Miramos los adyacentes de v
            if (!visitados[w]) {        // Si el vértice adyacente a v, w no ha sido visitado
                tam += dfs(g, w, i);    // Seguimos buscando recursivamente en w con dfs, guardando el tamaño de todos los conectados al v original.
            }
        }
        return tam;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;          // N es el n�mero de usuarios de la red y M es el n�mero de grupos;

    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;

    int nUsuarios, aux, anterior;       // nUsuarios es el n�mero de usuarios de un grupo, aux para leer cada miembro del grupo y en anterior se va guardando el usuario le�do antes para poder unir aristas.
    Grafo g(N);
    for (int i = 0; i < M; i++) {       // Recorremos el n�mero de grupos.
        cin >> nUsuarios;
        if (nUsuarios != 0) {
            cin >> anterior;            // Leemos el primer miembro del grupo
        }
        for (int j = 1; j < nUsuarios; j++) {   // Vamos leyendo los miembros restantes del grupo
            cin >> aux;
            g.ponArista(anterior - 1, aux - 1); // Ponemos una arista entre cada miembro consecutivo.
            anterior = aux;
        }
    }
    // No es necesario colocar aristas entre cada uno de los miembros de un grupo con el resto, pues si vamos colocando aristas entre
    // cada miembro consecutivo, los anteriores nodos ya están unidos a través de un camino.

    // resolver el caso posiblemente llamando a otras funciones
    UsuariosNoticia uNoticia(g);

    // escribir la soluci�n
    for (int i = 0; i < N; i++) {
        cout << uNoticia.getAmigos(i) << " ";
    }
    cout << '\n';

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