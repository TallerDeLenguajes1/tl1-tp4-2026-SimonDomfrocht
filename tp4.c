#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int contador = 1000;

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

int main(){

    Nodo * start;
    Tarea * tareita;
    char buff[50];

    start = crearListaVacia();
    
    printf("\n---MENU---\n");
    int opcion;
    do
    {
        printf("Ingrese la opcion que quiere: \n");
        printf("1- Si quiere agregar tarea \n");
        printf("0- Si quiere finalizar la carga \n");
        scanf("%d",&opcion);

        if (opcion == 1)
        {
            tareita = (Tarea *) malloc(sizeof(Tarea));
            tareita->TareaID = contador++;
            tareita->Duracion = rand() % 91;

            printf("\nIngrese descripcion de la tarea: ");
            scanf("%s",buff);
            tareita->Descripcion = (char *) malloc((strlen(buff) + 1) * sizeof(char));
            strcpy(tareita->Descripcion, buff);

            Nodo * nuevoNodo = crearNodo(*tareita);
            insertarNodo(start,nuevoNodo);

        }
        
    } while (opcion != 0);
    
    

    
}