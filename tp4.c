#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int contador = 1000; //el tp me pide inicializar el contador para id en 1000 y lo hago como variable global

typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo * crearListaVacia(){
    return NULL;
}

Nodo * crearNodo(Tarea Tareita){
    Nodo * nuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    nuevoNodo->T = Tareita;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

void insertarNodo(Nodo ** primero, Nodo * nNodo){
    nNodo->Siguiente = *primero;
    *primero = nNodo;
}

void mostrarLista(Nodo * lista){
    
    if (lista == NULL)
    {
        printf("Lista vacia\n");
        return;
    }
    
    Nodo * aux = lista;
    while (aux != NULL)
    {
        printf("ID: %d | Duracion: %d min | Desc: %s\n",aux->T.TareaID,aux->T.Duracion,aux->T.Descripcion);
        aux = aux->Siguiente; //voy avanzando
    }
    
}

void cargarTarea(Nodo ** pendientes){

    Tarea tareita;
    char buff[100];

    tareita.TareaID = contador++;
    tareita.Duracion = rand() % 91 + 10;
    
    printf("\nIngrese descripcion de la tarea: ");
    scanf("%s",buff);
    tareita.Descripcion = (char *) malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(tareita.Descripcion, buff);

    Nodo * nuevoNodo = crearNodo(tareita);
    insertarNodo(pendientes,nuevoNodo);
    printf("Tarea cargada con ID %d. \n\n",tareita.TareaID);
}

void liberarLista(Nodo * lista){
    Nodo * actual = lista;
    while(actual != NULL){
        Nodo * siguiente = actual->Siguiente;
        free(actual->T.Descripcion);
        free(actual);
        actual = siguiente;

    }
}

int main(){

    Nodo * pendiente;
    Nodo * realizada;
    Tarea * tareita;
    char buff[50];
    srand(time(NULL));

    pendiente = crearListaVacia();
    realizada = crearListaVacia();
    
    printf("\n---MENU---\n");
    int opcion;
    do
    {
        printf("Ingrese la opcion que quiere: \n");
        printf("1- Si quiere agregar tarea \n");
        printf("3- Mostrar lista \n");
        printf("0- Salir\n");
        scanf("%d",&opcion);

        switch (opcion)
        {
            case 1:
                cargarTarea(&pendiente);
            break;
            case 2:
            break;
            case 3:
                printf("\nLista de tareas pendientes: \n");
                mostrarLista(pendiente);
            break;
        
        default:
            break;
        }
        
    } while (opcion != 0);
    
    liberarLista(pendiente);
    liberarLista(realizada);
    

    
}