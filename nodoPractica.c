#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ESTRUCTURAS
struct tarea
{
    int tareaId;
    char *descripcion;
    int duracion;

} typedef Tarea;

struct nodo
{
    Tarea t;
    struct nodo *siguiente;
} typedef TNodo;

// FUNCIONES
TNodo *CrearListaVacia();
TNodo *CrearNodo(int tareaId, char *descripcion, int duracion);
void InsertarNodo(TNodo **start, TNodo *nodo);
void CargarTareas(TNodo **start);
void MostrarNodo(TNodo *nodo);
void MostrarLista(TNodo **start);
void TransferirTareas(TNodo **pendientes, TNodo **realizadas);
void BuscarTareas(TNodo *pendientes, TNodo *realizadas);

// MAIN
int main()
{
    // LISTAS 1 Y 2: TAREAS PENDIENTES y REALIZADAS
    TNodo *start1 = CrearListaVacia();
    TNodo *start2 = CrearListaVacia();
    CargarTareas(&start1);
    MostrarLista(&start1);

    TransferirTareas(&start1, &start2);

    printf("Lista de tareas pendientes actualizada:\n");
    MostrarLista(&start1);

    printf("Lista de tareas realizadas:\n");
    MostrarLista(&start2);

    BuscarTareas(start1,start2);

    return 0;
}

// DESARROLLO DE FUNCIONES
TNodo *CrearListaVacia()
{
    return NULL;
}

TNodo *CrearNodo(int tareaId, char *descripcion, int duracion)
{
    TNodo *nuevoNodo = (TNodo *)malloc(sizeof(TNodo));
    nuevoNodo->t.tareaId = tareaId;
    nuevoNodo->t.duracion = duracion;
    nuevoNodo->t.descripcion = (char *)malloc(strlen(descripcion) + 1);
    strcpy(nuevoNodo->t.descripcion, descripcion);
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void InsertarNodo(TNodo **start, TNodo *nodo)
{
    nodo->siguiente = *start;
    *start = nodo;
}

void MostrarNodo(TNodo *nodo)
{
    if (nodo != NULL)
    {
        printf("Tarea ID = %d\n", nodo->t.tareaId);
        printf("Descripcion = %s\n", nodo->t.descripcion);
        printf("Duracion = %d\n", nodo->t.duracion);
        printf("\n");
    }
}

void MostrarLista(TNodo **start)
{
    printf("\t-----Nodos-----\n");
    TNodo *aux = *start;
    while (aux) // es lo mismo que aux != NULL
    {
        MostrarNodo(aux);
        aux = aux->siguiente;
    }
}

void CargarTareas(TNodo **start)
{
    int tareaId = 1000;
    char descripcion[100];
    int duracion;
    char opcion;

    do
    {
        printf("\nIngrese la descripcion de la tarea: ");
        fflush(stdin);
        fgets(descripcion, sizeof(descripcion), stdin);
        descripcion[strcspn(descripcion, "\n")] = 0; // Elimina el salto de línea final

        printf("Ingrese la duracion de la tarea (10 a 100): ");
        scanf("%d", &duracion);

        // Validar duración
        while (duracion < 10 || duracion > 100)
        {
            printf("Duracion invalida. Ingrese nuevamente (10 a 100): ");
            scanf("%d", &duracion);
        }

        // Crear nodo y agregarlo a la lista
        TNodo *nuevaTarea = CrearNodo(tareaId, descripcion, duracion);
        InsertarNodo(start, nuevaTarea);

        tareaId++; // Incrementar ID

        printf("\n¿Desea ingresar otra tarea? (s/n): ");
        fflush(stdin);
        scanf("%c", &opcion); // Espacio para leer correctamente un caracter
    } while (opcion == 's' || opcion == 'S');
}

void TransferirTareas(TNodo **pendientes, TNodo **realizadas)
{

    TNodo *actual = *pendientes;
    TNodo *anterior = NULL;
    char opcion;

    while (actual != NULL)
    {
        printf("\n¿Realizó esta tarea?\n");
        MostrarNodo(actual);
        printf("(s/n): ");
        fflush(stdin);
        scanf("%c", &opcion);

        if (opcion == 's' || opcion == 'S')
        {
            TNodo *tareaRealizada = actual;

            // Eliminar de lista de pendientes
            if (anterior == NULL)
            {
                // El primer nodo fue realizado
                *pendientes = actual->siguiente;
            }
            else
            {
                anterior->siguiente = actual->siguiente;
            }

            // Insertar en lista de realizadas
            InsertarNodo(realizadas, tareaRealizada);

            // Avanzar
            actual = (anterior == NULL) ? *pendientes : anterior->siguiente;
        }
        else
        {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}




void BuscarTareas(TNodo *pendientes, TNodo *realizadas)
{
    int opcionBusqueda;
    printf("\nBuscar tarea por:\n");
    printf("1. ID\n");
    printf("2. Palabra clave\n");
    printf("Ingrese su opción: ");
    scanf("%d", &opcionBusqueda);

    if (opcionBusqueda == 1)
    {
        int id;
        printf("Ingrese el ID de la tarea a buscar: ");
        scanf("%d", &id);

        bool encontrada = false;

        // Buscar en pendientes
        TNodo *aux = pendientes;
        while (aux != NULL)
        {
            if (aux->t.tareaId == id)
            {
                printf("\nTarea encontrada en pendientes:\n");
                MostrarNodo(aux);
                encontrada = true;
                break;
            }
            aux = aux->siguiente;
        }

        // Buscar en realizadas
        aux = realizadas;
        while (!encontrada && aux != NULL)
        {
            if (aux->t.tareaId == id)
            {
                printf("\nTarea encontrada en realizadas:\n");
                MostrarNodo(aux);
                encontrada = true;
                break;
            }
            aux = aux->siguiente;
        }

        if (!encontrada)
        {
            printf("\nTarea no encontrada.\n");
        }
    }
    else if (opcionBusqueda == 2)
    {
        char palabraClave[50];
        printf("Ingrese palabra clave a buscar: ");
        fflush(stdin);
        fgets(palabraClave, sizeof(palabraClave), stdin);
        palabraClave[strcspn(palabraClave, "\n")] = 0; // Eliminar salto de línea

        bool encontrada = false;

        // Buscar en pendientes
        TNodo *aux = pendientes;
        while (aux != NULL)
        {
            if (strstr(aux->t.descripcion, palabraClave) != NULL)
            {
                if (!encontrada)
                    printf("\nTareas encontradas en pendientes:\n");
                
                MostrarNodo(aux);
                encontrada = true;
            }
            aux = aux->siguiente;
        }

        // Buscar en realizadas
        aux = realizadas;
        while (aux != NULL)
        {
            if (strstr(aux->t.descripcion, palabraClave) != NULL)
            {
                if (!encontrada)
                    printf("\nTareas encontradas en realizadas:\n");

                MostrarNodo(aux);
                encontrada = true;
            }
            aux = aux->siguiente;
        }

        if (!encontrada)
        {
            printf("\nNo se encontraron tareas con esa palabra clave.\n");
        }
    }
    else
    {
        printf("\nOpción inválida.\n");
    }
}

