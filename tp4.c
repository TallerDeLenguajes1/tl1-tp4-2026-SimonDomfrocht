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

//PARTE DE NODOS
Nodo * crearNodo(Tarea Tareita){
    Nodo * nuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    nuevoNodo->T = Tareita;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

Nodo * quitarNodo(Nodo ** primero, int id){
    Nodo *nodoAux = (*primero);
    Nodo *nodoAnt = NULL;
    while (nodoAux != NULL && nodoAux->T.TareaID != id)
    {
        nodoAnt = nodoAux;
        nodoAux = nodoAux->Siguiente;
    }

    if (nodoAux != NULL){
        if (nodoAux == (*primero))
        {
            (*primero) = nodoAux->Siguiente;
        }else{
            nodoAnt->Siguiente = nodoAux->Siguiente;
        }
        nodoAux->Siguiente = NULL;
    }
    return(nodoAux);

}

void insertarNodo(Nodo ** primero, Nodo * nNodo){
    nNodo->Siguiente = *primero;
    *primero = nNodo;
}

//PARTE DE LISTAS
void mostrarLista(Nodo * lista){
    
    if (lista == NULL)
    {
        printf("Lista vacia\n"); //si es vacia
        return;
    }
    
    Nodo * aux = lista;
    while (aux != NULL)
    {
        printf("ID: %d | Duracion: %d min | Desc: %s\n",aux->T.TareaID,aux->T.Duracion,aux->T.Descripcion);
        aux = aux->Siguiente; //voy avanzando
    }
    
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

//PARTE DE CARGAR Y MARCAR TAREAS
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

void marcarTarea(Nodo ** realizadas, Nodo ** pendientes){

    if (*pendientes == NULL)
    {
        printf("No hay tareas pendientes\n"); //si es vacia
        return;
    }
    
    mostrarLista(*pendientes);

    int id;
    printf("\nSeleccione el id de la tarea que desea marcar como hecha: ");
    scanf("%d",&id);

    Nodo * nodoMovido = quitarNodo(pendientes, id);

    if (nodoMovido == NULL)
    {
        printf("\nNo se encontro ninguna tarea con ese ID");
        return;
    }

    insertarNodo(realizadas,nodoMovido);
    printf("\nTarea de ID %d realizada\n",id);
    
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
        printf("\nIngrese la opcion que quiere: \n");
        printf("1- Si quiere agregar tarea \n");
        printf("2- Si quiere marcar tarea como realizada \n");
        printf("3- Mostrar lista \n");
        printf("0- Salir\n");
        scanf("%d",&opcion);

        switch (opcion)
        {
            case 1:
                cargarTarea(&pendiente);
            break;
            case 2:
                marcarTarea(&realizada,&pendiente);
            break;
            case 3:
                printf("\nLista de tareas pendientes: \n");
                mostrarLista(pendiente);
                printf("\nLista de tareas realizadas: \n");
                mostrarLista(realizada);
            break;
        
        default:
            break;
        }
        
    } while (opcion != 0);
    
    liberarLista(pendiente);
    liberarLista(realizada);
    

    
}