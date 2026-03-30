#ifndef __LISTA_SIMPLE_H__
#define __LISTA_SIMPLE_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct Nodo {
    void* dato;
    struct Nodo* siguiente;
} Nodo;

typedef struct {
    Nodo* head;
    Nodo* tail;
} Lista;

// Callbacks
typedef int (*CompararFunc)(void*, void*);
typedef void (*ImprimirFunc)(void*);

//Funciones para Nodo
Nodo* crearNodo(void *dato, size_t size);
void liberarNodo(Nodo *n);
bool modificarNodo(Nodo *n, void *dato,  size_t size);

// Crear / estado
Lista* crearLista();
bool esVacia(Lista* lista);

// Inserciones
void insertarInicio(Lista* l, void* dato, size_t size);
void insertarFinal(Lista* l, void* dato, size_t size);
void insertarPorPosicion(Lista* l, void* dato, size_t size, int p);

// Eliminaciones
void eliminarInicio(Lista *l);
void eliminarFinal(Lista *l);
void eliminarPorPosicion(Lista* l, int p);
void eliminarPorElemento(Lista* l, void* dato, CompararFunc cmp);
void eliminarElementosIguales(Lista *l, void *dato, CompararFunc cmp);

// Búsquedas
void* buscarPorPosicion(Lista* l, int pos);
int buscarPorElemento(Lista* l, void* dato, CompararFunc cmp);

// Navegación
void* primero(Lista* l);
void* ultimo(Lista* l);
void* siguiente(void* actual);

// Modificar
void modificar(Lista* l, int p, void* dato, size_t size);

// Utilidad
void imprimirLista(Lista* l, ImprimirFunc imprimir);
void vaciarLista(Lista* l);
void borrarLista(Lista* l);

#endif