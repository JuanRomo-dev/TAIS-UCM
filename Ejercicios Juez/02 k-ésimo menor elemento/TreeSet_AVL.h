#pragma once
//
//  TreeSet_AVL.h
//
//  Implementaci�n de conjuntos mediante �rboles de b�squeda AVL
//
//  Facultad de Inform�tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef TREESET_AVL_H_
#define TREESET_AVL_H_

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <utility>


template <class T, class Comparator = std::less<T>>
class Set {
protected:

    /*
     Nodo que almacena internamente el elemento (de tipo T),
     punteros al hijo izquierdo y derecho, que pueden ser
     nullptr si el hijo es vac�o, y la altura.
     */
    struct TreeNode;
    using Link = TreeNode*;
    struct TreeNode {
        T elem;
        Link iz, dr;
        int altura;
        int tam_i;                                                  // A�adimos el atributo pedido, tam_i.
        TreeNode(T const& e, Link i = nullptr, Link d = nullptr,
            int alt = 1, int tamI = 1) : elem(e), iz(i), dr(d), altura(alt), tam_i(tamI) {}
    };

    // puntero a la ra�z de la estructura jer�rquica de nodos
    Link raiz;

    // n�mero de elementos (cardinal del conjunto)
    int nelems;

    // objeto funci�n que compara elementos (orden total estricto)
    Comparator menor;

public:

    // constructor (conjunto vac�o)
    Set(Comparator c = Comparator()) : raiz(nullptr), nelems(0), menor(c) {}

    // constructor por copia
    Set(Set const& other) {
        copia(other);
    }

    // operador de asignaci�n
    Set& operator=(Set const& that) {
        if (this != &that) {
            libera(raiz);
            copia(that);
        }
        return *this;
    }

    ~Set() {
        libera(raiz);
    };

    bool insert(T const& e) {
        return inserta(e, raiz);
    }

    bool empty() const {
        return raiz == nullptr;
    }

    int size() const {
        return nelems;
    }

    bool contains(T const& e) const {
        return pertenece(e, raiz);
    }

    bool erase(T const& e) {
        return borra(e, raiz);
    }

    Link existe(T const& k, Link nod) const {
        if (nod == nullptr)  {              // Caso base: si la ra�z es null, entonces no existe el elemento.
            return nullptr;
        }
        else if (k < nod->tam_i) {          // Si la k es menor que el tam_i de la ra�z buscamos el elemento por la izquierda con recursi�n.
            return existe(k, nod->iz);
        }
        else if (nod->tam_i < k) {          // Si la k es mayor que el tam_i de la ra�z buscamos el elemento por la derecha con recursi�n.
            // Como pasamos al hijo derecho, debemos restar la k por el tam_i de la ra�z, para que al bajar al hijo derecho sepa por donde tiene que ir.
            return existe(k - nod->tam_i, nod->dr);
        }
        else {
            return nod;                     // La �ltima opci�n ser�a que k = nod->tam_i, por lo que quiere decir que hemos encontrado la posici�n.
        }
    }

    T const& kesimo(T const& k) const {              // Funci�n que devuelve el k-�simo menor elemento del conjunto.
        Link nodo = existe(k, raiz);                // Vemos si existe el nodo o no.
        if (nodo != nullptr) {                  // Si existe se devuelve el elemento.
            return nodo->elem;
        }
        else {
            throw std::domain_error("Error");   // Si no existe, se lanza una excepci�n.
        }

    }

protected:

    void copia(Set const& other) {
        raiz = copia(other.raiz);
        nelems = other.nelems;
        menor = other.menor;
    }

    static Link copia(Link a) {
        if (a == nullptr) return nullptr;
        else return new TreeNode(a->elem, copia(a->iz), copia(a->dr), a->altura);
    }

    static void libera(Link a) {
        if (a != nullptr) {
            libera(a->iz);
            libera(a->dr);
            delete a;
        }
    }

    bool pertenece(T const& e, Link a) const {
        if (a == nullptr) {
            return false;
        }
        else if (menor(e, a->elem)) {
            return pertenece(e, a->iz);
        }
        else if (menor(a->elem, e)) {
            return pertenece(e, a->dr);
        }
        else { // e == a->elem
            return true;
        }
    }

    bool inserta(T const& e, Link& a) {
        bool crece;
        if (a == nullptr) { // se inserta el nuevo elemento e
            a = new TreeNode(e);
            ++nelems;
            crece = true;
        }
        else if (menor(e, a->elem)) {
            crece = inserta(e, a->iz);
            if (crece) {
                a->tam_i++;             // Aumentamos el valor de tam_i para mantener la coherencia, ya que este atributo contiene el n�mero de nodos del
                                        // hijo izquierdo m�s 1, y aqu� al insertar un elemento en la izquierda debemos aumentar tam_i.
                reequilibraDer(a);
            }                           
        }
        else if (menor(a->elem, e)) {
            crece = inserta(e, a->dr);
            if (crece) reequilibraIzq(a);
        }
        else // el elemento e ya est� en el �rbol
            crece = false;
        return crece;
    }

    int altura(Link a) {
        if (a == nullptr) return 0;
        else return a->altura;
    }

    void rotaDer(Link& r2) {
        Link r1 = r2->iz;
        r2->iz = r1->dr;
        r2->tam_i -= r1->tam_i;         // Como hemos rotado a la derecha el r1, r1 deja de ser el hijo izquierdo de r2, y r2 pasa a ser el hijo derecho de r1, entonces todo
                                        //  lo que ten�a de hijo izquierdo r1, deja de formar parte del tam_i de r2, por lo que lo restamos.        
        r1->dr = r2;
        r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
        r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
        r2 = r1;
    }

    void rotaIzq(Link& r1) {
        Link r2 = r1->dr;
        r1->dr = r2->iz;
        r2->tam_i += r1->tam_i;          // Ahora es al contrario, como hemos rotado r2 a la izquierda cuando r1 era la ra�z, siendo r2 el hijo derecho de r1, ahora r2 pasa a ser la ra�z
                                        // y r1 pasa a ser hijo izquierdo de r2, por lo que el tam_i de r1 debe sumarse al tam_i de r2.
        r2->iz = r1;
        r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
        r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
        r1 = r2;
    }

    void rotaIzqDer(Link& r3) {
        rotaIzq(r3->iz);
        rotaDer(r3);
    }   

    void rotaDerIzq(Link& r1) {
        rotaDer(r1->dr);
        rotaIzq(r1);
    }

    void reequilibraIzq(Link& a) {
        if (altura(a->dr) - altura(a->iz) > 1) {
            if (altura(a->dr->iz) > altura(a->dr->dr))
                rotaDerIzq(a);
            else rotaIzq(a);
        }
        else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
    }

    void reequilibraDer(Link& a) {
        if (altura(a->iz) - altura(a->dr) > 1) {
            if (altura(a->iz->dr) > altura(a->iz->iz))
                rotaIzqDer(a);
            else rotaDer(a);
        }
        else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
    }

    // devuelve y borra el m�nimo del �rbol con ra�z en a
    T borraMin(Link& a) {
        if (a->iz == nullptr) {
            T min = a->elem;
            a = a->dr;
            --nelems;
            return min;
        }
        else {
            T min = borraMin(a->iz);
            reequilibraIzq(a);
            return min;
        }
    }

    bool borra(T const& e, Link& a) {
        bool decrece = false;
        if (a != nullptr) {
            if (menor(e, a->elem)) {
                decrece = borra(e, a->iz);
                a->tam_i--;                     // Reducimos el tama�o al borrar.
                if (decrece) reequilibraIzq(a);
            }
            else if (menor(a->elem, e)) {
                decrece = borra(e, a->dr);
                if (decrece) reequilibraDer(a);
            }
            else { // e == a->elem
                if (a->iz == nullptr || a->dr == nullptr) {
                    Link aux = a;
                    a = (a->iz == nullptr) ? a->dr : a->iz;
                    --nelems;
                    delete aux;
                }
                else { // tiene dos hijos
                    T min = borraMin(a->dr);
                    a->elem = min;
                    reequilibraDer(a);
                }
                decrece = true;
            }
        }
        return decrece;
    }

public:
    // iteradores que recorren los elementos del conjunto de menor a mayor
    class const_iterator {
    public:
        T const& operator*() const {
            if (act == nullptr)
                throw std::out_of_range("No hay elemento a consultar");
            return act->elem;
        }

        T const* operator->() const {
            return &operator*();
        }

        const_iterator& operator++() {  // ++ prefijo
            next();
            return *this;
        }

        bool operator==(const_iterator const& that) const {
            return act == that.act;
        }

        bool operator!=(const_iterator const& that) const {
            return !(this->operator==(that));
        }

    protected:
        friend class Set;
        Link act;
        std::stack<Link> ancestros;  // antecesores no visitados

        // construye el iterador al primero
        const_iterator(Link raiz) { act = first(raiz); }

        // construye el iterador al �ltimo
        const_iterator() : act(nullptr) {}

        Link first(Link ptr) {
            if (ptr == nullptr) {
                return nullptr;
            }
            else { // buscamos el nodo m�s a la izquierda
                while (ptr->iz != nullptr) {
                    ancestros.push(ptr);
                    ptr = ptr->iz;
                }
                return ptr;
            }
        }

        void next() {
            if (act == nullptr) {
                throw std::out_of_range("El iterador no puede avanzar");
            }
            else if (act->dr != nullptr) { // primero del hijo derecho
                act = first(act->dr);
            }
            else if (ancestros.empty()) { // hemos llegado al final
                act = nullptr;
            }
            else { // podemos retroceder
                act = ancestros.top();
                ancestros.pop();
            }
        }
    };

    const_iterator begin() const {
        return const_iterator(raiz);
    }

    const_iterator end() const {
        return const_iterator();
    }
};


#endif