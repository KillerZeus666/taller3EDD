#ifndef ArbolAVL_h
#define ArbolAVL_h

#include "Nodo.h"
#include <iostream>
#include <queue>
#include <vector>

template<class T>
class ArbolAVL {
protected:
    Nodo<T>* raiz;

    // Funciones auxiliares para mantener el balance del árbol
    int obtenerBalance(Nodo<T>* nodo);
    Nodo<T>* rotarDerecha(Nodo<T>* y);
    Nodo<T>* rotarIzquierda(Nodo<T>* x);
    Nodo<T>* rotarIzquierdaDerecha(Nodo<T>* nodo);
    Nodo<T>* rotarDerechaIzquierda(Nodo<T>* nodo);

    // Inserción y eliminación de nodos en el árbol
    Nodo<T>* insertar(Nodo<T>* nodo, T& val);
    Nodo<T>* eliminar(Nodo<T>* nodo, T& val);

    // Encontrar el nodo con el valor mínimo
    Nodo<T>* encontrarMinimo(Nodo<T>* nodo);

public:
    // Constructor y destructor
    ArbolAVL();
    ~ArbolAVL();

    // Verificación si el árbol está vacío
    bool esVacio();

    // Obtener el valor de la raíz
    T& datoRaiz();

    // Obtener el tamaño del árbol (número de nodos)
    int tamano();
    int tamano(Nodo<T>* nodoActual);

    // Obtener la altura del árbol
    int altura();
    int altura(Nodo<T>* nodoActual);

    // Funciones de búsqueda e inserción
    bool insertar(T& val);
    bool eliminar(T& val);
    bool buscar(T& val);

    // Obtener el nivel de un valor específico en el árbol
    int obtenerNivel(T valor);
    int obtenerNivel(Nodo<T>* nodo, T valor, int nivel);

    // Recorridos del árbol
    void inOrden(Nodo<T>* nodo, std::vector<T>& elementos);
    std::vector<T> inOrden();

    void preOrden();
    void preOrden(Nodo<T>* nodoActual);

    void posOrden();
    void posOrden(Nodo<T>* nodoActual);

    void nivelOrden();
};

#include "ArbolAVL.hxx"

#endif
