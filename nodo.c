#include <stdio.h>
#include <stdlib.h>

/*typedef struct player
{
    char *nombre;
    int vidas;
}Player;*/

typedef struct Tnodo
{
    // Player player
    int dato;
    struct Tnodo *siguiente;

} Tnodo;

Tnodo *CrearListaVacia();
Tnodo *CrearNodo(int valor);
void InsertarNodo(Tnodo **start, Tnodo *nodo);
void MostrarLista(Tnodo **start);
Tnodo *BuscarDato(Tnodo **start, int valor);
void MostrarNodo(Tnodo *nodo);
Tnodo *QuitarNodo(Tnodo **start, int valor);
void EliminarNodo(Tnodo *nodo);

int main()
{
    Tnodo *start = CrearListaVacia();
    // Tnodo *nuevoNodo1 = CrearNodo(10);
    // Tnodo *nuevoNodo2 = CrearNodo(20);
    // Tnodo *nuevoNodo3 = CrearNodo(30);
    InsertarNodo(&start, CrearNodo(10));
    InsertarNodo(&start, CrearNodo(20));
    InsertarNodo(&start, CrearNodo(30));
    MostrarLista(&start);
    // Tnodo *nodoBuscado = BuscarDato(&start, 30);
    MostrarNodo(BuscarDato(&start, 30));
    // Tnodo *nodoQuitado = QuitarNodo(&start, 20);
    EliminarNodo(QuitarNodo(&start, 20));
    printf("Despues de quitar el Nodo\n");
    MostrarLista(&start);

    return 0;
}

Tnodo *CrearListaVacia()
{
    return NULL;
}

Tnodo *CrearNodo(int valor)
{
    Tnodo *nuevoNodo = (Tnodo *)malloc(sizeof(Tnodo));
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void InsertarNodo(Tnodo **start, Tnodo *nodo)
{
    nodo->siguiente = *start;
    *start = nodo;
}

void MostrarLista(Tnodo **start)
{
    Tnodo *Aux = *start;

    while (Aux)
    {
        MostrarNodo(Aux);
        Aux = Aux->siguiente;
    }
}

Tnodo *BuscarDato(Tnodo **start, int valor)
{
    Tnodo *Aux = *start;

    while (Aux != NULL && Aux->dato != valor)
    {
        Aux = Aux->siguiente;
    }

    return Aux;
}

void MostrarNodo(Tnodo *nodo)
{
    if (nodo != NULL)
    {
        printf("Nodo = %d\n", nodo->dato);
    }
}

Tnodo *QuitarNodo(Tnodo **start, int valor)
{
    Tnodo **aux = start;
    while (*aux != NULL && (*aux)->dato != valor)
    {
        aux = &(*aux)->siguiente;
    }

    if (*aux)
    {
        Tnodo *temp = *aux;
        *aux = (*aux)->siguiente;
        temp->siguiente = NULL;
        return temp;
    }

    return NULL;
}

void EliminarNodo(Tnodo *nodo)
{
    free(nodo);
}
