//
//  Grafo.h
//
//  Implementación de grafos no dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
private:
   int _V;  // número de vértices
   int _A;  // número de aristas
   std::vector<Adys> _ady;  // vector de listas de adyacentes
public:
   
   /**
    * Crea un grafo con V vértices.
    */
   Grafo(int V) : _V(V), _A(0), _ady(_V) {}
   
   /**
    * Crea un grafo a partir de los datos en el flujo de entrada.
    */
   Grafo(std::istream & flujo) : _A(0) {
      flujo >> _V;
      _ady.resize(_V);
      int E, v, w;
      flujo >> E;
      while (E--) {
         flujo >> v >> w;
         ponArista(v, w);
      }
   }
   
   /**
    * Devuelve el número de vértices del grafo.
    */
   int V() const { return _V; }
   
   /**
    * Devuelve el número de aristas del grafo.
    */
   int A() const { return _A; }
   
   /**
    * Añade la arista v-w al grafo.
    * @throws domain_error si algún vértice no existe
    */
   void ponArista(int v, int w) {
      if (v < 0 || v >= _V || w < 0 || w >= _V)
         throw std::domain_error("Vertice inexistente");
      ++_A;
      _ady[v].push_back(w);
      _ady[w].push_back(v);
   }
  
   /**
    * Devuelve la lista de adyacencia de v.
    * @throws domain_error si v no existe
    */
   Adys const& ady(int v) const {
      if (v < 0 || v >= _V)
         throw std::domain_error("Vertice inexistente");
      return _ady[v];
   }
   
   /**
    * Muestra el grafo en el stream de salida o (para depurar)
    */
   void print(std::ostream & o = std::cout) const {
      o << _V << " vértices, " << _A << " aristas\n";
      for (int v = 0; v < _V; ++v) {
         o << v << ": ";
         for (int w : _ady[v]) {
            o << w << " ";
         }
         o << "\n";
      }
   }

   bool hayArista(int v, int w) const {
     bool existe = false;

     if (v < 0 || v >= _V)
        throw std::domain_error("Vertice inexistente");

     for(auto u: _ady[v]) {
         if (u == w) {
            existe = true;
         }
     }
   
     return existe;
    }

};

/**
 * Para mostrar grafos por la salida estándar
 */
inline std::ostream & operator<<(std::ostream & o, Grafo const& g){
   g.print(o);
   return o;
}


#endif /* GRAFO_H_ */

using namespace std;

int main() {
   Grafo g(6);
   g.ponArista(0, 1);
   g.ponArista(2, 3);
   g.ponArista(4, 3);
   g.ponArista(1, 5);


   

   if (g.hayArista(3,4))
      cout << "Hay arista entre el 3 y el 4.\n"; // debe mostrar este mensaje
   else
      cout << "No hay arista entre el 3 y el 4.\n";
   if (g.hayArista(0,5))
      cout << "Hay arista entre el 0 y el 5.\n";
   else
      cout << "No hay arista entre el 0 y el 5.\n"; // debe mostrar este mensaje


   return 0;

}//
//  Grafo.h
//
//  Implementación de grafos no dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
private:
   int _V;  // número de vértices
   int _A;  // número de aristas
   std::vector<Adys> _ady;  // vector de listas de adyacentes
public:
   
   /**
    * Crea un grafo con V vértices.
    */
   Grafo(int V) : _V(V), _A(0), _ady(_V) {}
   
   /**
    * Crea un grafo a partir de los datos en el flujo de entrada.
    */
   Grafo(std::istream & flujo) : _A(0) {
      flujo >> _V;
      _ady.resize(_V);
      int E, v, w;
      flujo >> E;
      while (E--) {
         flujo >> v >> w;
         ponArista(v, w);
      }
   }
   
   /**
    * Devuelve el número de vértices del grafo.
    */
   int V() const { return _V; }
   
   /**
    * Devuelve el número de aristas del grafo.
    */
   int A() const { return _A; }
   
   /**
    * Añade la arista v-w al grafo.
    * @throws domain_error si algún vértice no existe
    */
   void ponArista(int v, int w) {
      if (v < 0 || v >= _V || w < 0 || w >= _V)
         throw std::domain_error("Vertice inexistente");
      ++_A;
      _ady[v].push_back(w);
      _ady[w].push_back(v);
   }
  
   /**
    * Devuelve la lista de adyacencia de v.
    * @throws domain_error si v no existe
    */
   Adys const& ady(int v) const {
      if (v < 0 || v >= _V)
         throw std::domain_error("Vertice inexistente");
      return _ady[v];
   }
   
   /**
    * Muestra el grafo en el stream de salida o (para depurar)
    */
   void print(std::ostream & o = std::cout) const {
      o << _V << " vértices, " << _A << " aristas\n";
      for (int v = 0; v < _V; ++v) {
         o << v << ": ";
         for (int w : _ady[v]) {
            o << w << " ";
         }
         o << "\n";
      }
   }

   bool hayArista(int v, int w) const {
     bool existe = false;

     if (v < 0 || v >= _V)
        throw std::domain_error("Vertice inexistente");

     for(auto u: _ady[v]) {
         if (u == w) {
            existe = true;
         }
     }
   
     return existe;
    }

};

/**
 * Para mostrar grafos por la salida estándar
 */
inline std::ostream & operator<<(std::ostream & o, Grafo const& g){
   g.print(o);
   return o;
}


#endif /* GRAFO_H_ */

using namespace std;

int main() {
   Grafo g(6);
   g.ponArista(0, 1);
   g.ponArista(2, 3);
   g.ponArista(4, 3);
   g.ponArista(1, 5);


   

   if (g.hayArista(3,4))
      cout << "Hay arista entre el 3 y el 4.\n"; // debe mostrar este mensaje
   else
      cout << "No hay arista entre el 3 y el 4.\n";
   if (g.hayArista(0,5))
      cout << "Hay arista entre el 0 y el 5.\n";
   else
      cout << "No hay arista entre el 0 y el 5.\n"; // debe mostrar este mensaje


   return 0;

}
