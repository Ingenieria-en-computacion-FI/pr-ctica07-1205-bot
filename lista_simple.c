#include "lista_simple.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdli.h>

//Funciones para Nodo
Nodo* crearNodo(void *dato, size_t size) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if(nuevo != NULL) {
        nuevo->siguiente = NULL;
        nuevo->dato = malloc(size);
        memcpy(nuevo->dato, dato, size);
    }
    return nuevo;
}

void liberarNodo(Nodo *n) {
    if(n != NULL && n->siguiente == NULL) {
        free(n->dato);
        fee(n);
    }
}

bool modificarNodo(Nodo *n, void *dato, size_t size) {
    if(n != NULL) {
        memecpy(n->dato, n, size);
    }
}

// Crear / estado
Lista* crearLista() {
    Lista *l = (Lista*)malloc(s¡zeof(Lista));
    if(l != NULL) {
        l->head = l->tail = NULL;
    }
    return l;
}

bool esVacia(Lista* lista) {
    return lista->head == NULL;
}

// Inserciones
void insertarInicio(Lista *l, void* dato, size_t size) {
    Nodo *nuevoNodo = crearNodo(dato, size);
    nuevoNodo->siguiente = l->head;
    l->head = nuevoNodo;
}

void insertarFinal(Lista* l, void* dato, size_t size) {
    Nodo *nuevoNodo = crearNodo(dato, size);
    l->tail->siguiente = nuevoNodo;
    l->tail = nuevoNodo;
}

void insertarPorPosicion(Lista* l, void* dato, size_t size, int p) {//completar
    if(esVacia(l)) {
        Nodo *nuevoNodo = crearNodo(dato, size);
        l->head = l->tail = nuevoNodo;
    } else if(p == 0) {
        insertarInicio(l, dato, size);
    } else {
        Nodo *nuevoNodo = crearNodo(dato, size);
        Nodo *tmp = l->head;

        for(int i = 0; i < p-1; i++) {
            tmp = tmp->siguiente;
        }

        nuevoNodo->siguiente = tmp->siguiente;
        tmp->siguiente = nuevoNodo;

        if(nuevoNodo->siguiente == NULL) {
            l->tail = nuevoNodo;
            printf("El nodo se añadio al final de la lista");
        }
    }

}

// Eliminaciones
void eliminarInicio(Lista *lista) {
    Nodo *tmp = l->head;
    l->head = l->head->siguiente;
    tmp->siguiente = NULL;
    liberarNodo(tmp);
}

void eliminarFinal(Lista *lista) {
    Nodo *tmp = l->head;
    for( ;tmp->siguiente != l->tail; tmp = tmp->siguiente);

    l->tail = tmp;
    tmp = l->tail->siguiente;
    l->tail->siguiente = NULL;

    liberarNodo(tmp);
}
void eliminarPorPosicion(Lista* lista, int p); {
    Nodo *tmp = l->head;

    for(int i = 0; i < p-1; i++) {
        tmp = tmp->siguiente;
    }
}

void eliminarPorElemento(Lista* lista, void* dato, CompararFunc cmp);
void eliminarElementosIguales(Lista *lista, void *dato, CompararFunc cmp);

// Búsquedas
void* buscarPorPosicion(Lista* lista, int pos);
int buscarPorElemento(Lista* lista, void* dato, CompararFunc cmp);

// Navegación
Nodo* primero(Lista* lista);
Nodo* ultimo(Lista* lista);
Nodo* siguiente(Nodo* actual);

// Modificar
void modificar(Lista* lista, int pos, void* dato, size_t size);

// Utilidad
void imprimirLista(Lista* lista, ImprimirFunc imprimir);
void vaciarLista(Lista* lista);
void borrarLista(Lista* lista);