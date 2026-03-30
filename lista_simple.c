#include "lista_simple.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
        free(n);
    }
}

bool modificarNodo(Nodo *n, void *dato, size_t size) {
    if(n != NULL) {
        memcpy(n->dato, dato, size);
        return true;
    } 
    return false;
}

// Crear / estado
Lista* crearLista() {
    Lista *l = (Lista*)malloc(sizeof(Lista));
    if(l != NULL) {
        l->head = l->tail = NULL;
    }
    return l;
}

bool esVacia(Lista* l) {
    return l->head == NULL;
}

// Inserciones
void insertarInicio(Lista *l, void* dato, size_t size) {
    Nodo *nuevoNodo = crearNodo(dato, size);
    nuevoNodo->siguiente = l->head;
    l->head = nuevoNodo;
}

void insertarFinal(Lista* l, void* dato, size_t size) {
    Nodo *nuevoNodo = crearNodo(dato, size);
    if(esVacia(l)) {
        l->head = l->tail = nuevoNodo;
    } else {
        l->tail->siguiente = nuevoNodo;
        l->tail = nuevoNodo;
    }
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
            if(tmp->siguiente == NULL) {
                // p es mayor que el tamaño: insertar al final
                tmp->siguiente = nuevoNodo;
                l->tail = nuevoNodo;
                printf("Posicion fuera de rango, nodo añadido al final\n");
                return;
            }
            tmp = tmp->siguiente;
        }

        nuevoNodo->siguiente = tmp->siguiente;
        tmp->siguiente = nuevoNodo;

        if(nuevoNodo->siguiente == NULL) {
            l->tail = nuevoNodo;
            printf("El nodo se añadio al final de la lista\n");
        }
    }
}

// Eliminaciones
void eliminarInicio(Lista *l) {
    Nodo *tmp = l->head;
    l->head = l->head->siguiente;
    tmp->siguiente = NULL;
    liberarNodo(tmp);
}

void eliminarFinal(Lista *l) {
    Nodo *tmp = l->head;
    for( ;tmp->siguiente != l->tail; tmp = tmp->siguiente);

    l->tail = tmp;
    tmp = l->tail->siguiente;
    l->tail->siguiente = NULL;

    liberarNodo(tmp);
}

void eliminarPorPosicion(Lista* l, int p) {
    if(esVacia(l)) {
        printf("La lista esta vacia\n");
        return;
    } else if(p == 0) {
        eliminarInicio(l);
        return;
    }

    Nodo *tmp = l->head;
    Nodo *tmp2 = NULL;

    for(int i = 0; i < p && tmp != NULL; i++) {
    tmp2 = tmp;
    tmp = tmp->siguiente;
    }

    if(tmp == NULL) {
    printf("Posicion fuera de rango\n");
    return;
    }

    if(tmp == l->tail) {
        eliminarFinal(l);
        return;
    }

    tmp2->siguiente = tmp->siguiente;
    tmp->siguiente = NULL;
    liberarNodo(tmp);
}

void eliminarPorElemento(Lista* l, void* dato, CompararFunc cmp) {
    if(esVacia(l)) {
        printf("La lista esta vacia\n");
        return;
    } else {
        int p = buscarPorElemento(l, dato, cmp);
        if(p == -1) {
            printf("Elemento no encontrado\n");
            return;
        }
        eliminarPorPosicion(l, p);
    }
}

void eliminarElementosIguales(Lista *l, void *dato, CompararFunc cmp) {
    if(esVacia(l)) {
        printf("La lista esta vacia\n");
        return;
    }

    int p = buscarPorElemento(l, dato, cmp);

    while(p != -1) {
        eliminarPorPosicion(l, p);
        p = buscarPorElemento(l, dato, cmp);
    }
}

// Búsquedas
void* buscarPorPosicion(Lista* l, int p) {
    if(esVacia(l)) return NULL;
    
    Nodo* tmp = l->head;
    for(int i = 0; i < p && tmp != NULL; i++) {
        tmp = tmp->siguiente;
    }
    
    if(tmp == NULL) return NULL;
    
    return tmp->dato;
}

int buscarPorElemento(Lista* l, void* dato, CompararFunc cmp) {
    if(esVacia(l)) return -1;

    Nodo* tmp = l->head;
    int p = 0;

    while(tmp != NULL) {
        if(cmp(tmp->dato, dato) == 0) {
            return p;
        }
        tmp = tmp->siguiente;
        p++;
    }

    return -1;
}

// Navegación
void* primero(Lista* l) {
    if(esVacia(l)) return NULL;
    return l->head->dato;
}

void* ultimo(Lista* l) {
    if(esVacia(l)) return NULL;
    return l->tail->dato;
}

void* siguiente(void* actual) {
    if(actual == NULL || ((Nodo*)actual)->siguiente == NULL) return NULL;
    return ((Nodo*)actual)->siguiente->dato;
}

// Modificar
void modificar(Lista* l, int p, void* dato, size_t size) {
    if(esVacia(l)) {
        printf("La lista esta vacia\n");
        return;
    }

    Nodo* tmp = l->head;
    for(int i = 0; i < p && tmp != NULL; i++) {
        tmp = tmp->siguiente;
    }

    if(tmp == NULL) {
        printf("Posicion fuera de rango\n");
        return;
    }

    modificarNodo(tmp, dato, size);
}

// Utilidad
void imprimirLista(Lista* l, ImprimirFunc imprimir) {
    if(esVacia(l)) {
        printf("La lista esta vacia\n");
        return;
    }

    Nodo* tmp = l->head;
    while(tmp != NULL) {
        imprimir(tmp->dato);
        tmp = tmp->siguiente;
    }
}

void vaciarLista(Lista* l) {
    while(!esVacia(l)) {
        eliminarInicio(l);
    }
}

void borrarLista(Lista* l) {
    vaciarLista(l);
    free(l);
}