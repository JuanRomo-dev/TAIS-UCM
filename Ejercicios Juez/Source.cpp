/*@ <answer>
 *
 * Nombre y Apellidos: Juan Romo Iribarren
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 Tenemos una cola de prioridad, de tipo tPaciente en el que se guarda el nombre del paciente, la gravedad indicando su estado de salud y la espera que le faltar�a
 para ser atendido en ese momento, donde los elementos est�n ordenados de mayor a menor seg�n la gravedad. Vamos a ir leyendo cada evento para saber que hacer en
 cada momento. Si el evento es I, entonces un paciente pasa a la cola, mientras que si el evento es A, el m�dico atiende al siguiente en la cola.

 El coste del algoritmo en el caso peor es O(N*M log(N)), siendo N el n�mero de eventos y M el n�mero de pacientes atendidos.
 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

struct tPaciente {
    string nombre;
    int gravedad;
    int espera;
};

bool operator<(tPaciente const& a, tPaciente const& b) {
    return(a.gravedad < b.gravedad || (a.gravedad == b.gravedad && a.espera > b.espera));
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int n;              // N�mero de eventos.

    cin >> n;
    if (n == 0)
        return false;

    char evento;      // Nombre del evento (I si es un nuevo paciente, A se atiende al siguiente paciente).
    string nombre;    // Nombre del paciente.
    priority_queue<tPaciente> cola;
    int gravedad;

    for (int i = 0; i < n; ++i) {
        cin >> evento;
        if (evento == 'I') {
            cin >> nombre >> gravedad;
            cola.push({ nombre, gravedad, i });
        }
        else if(cola.size() > 0) {                   // Si quedan pacientes esperando
            tPaciente atendido = cola.top();         // O(1).
            cola.pop();                              // O(log N).
            cout << atendido.nombre << "\n";
        }
    }
    // resolver el caso posiblemente llamando a otras funciones
    cout << "---\n";
    // escribir la soluci�n

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
