#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    TNodo *start1 = CrearListaVacia();
    CargarTareas(&start1);

    return 0;
}

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
