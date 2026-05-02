#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

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
    
    Nodo *nodoAux = *primero;
    Nodo *nodoAnt = NULL;

    while (nodoAux != NULL && nodoAux->T.TareaID != id)
    {
        nodoAnt = nodoAux;
        nodoAux = nodoAux->Siguiente; //avanzo
    }

    if (nodoAux != NULL){
        if (nodoAux == *primero)
        {
            *primero = nodoAux->Siguiente;
        }else{
            nodoAnt->Siguiente = nodoAux->Siguiente;
        }
        nodoAux->Siguiente = NULL;
    }
    return(nodoAux);

}

void insertarNodo(Nodo ** primero, Nodo * nNodo){
    nNodo->Siguiente = *primero; //hacer que siguiente apunte a donde apunta primero
    *primero = nNodo; //hacer que primero ahora apunte al nuevo nodo insertado
}

//PARTE DE LISTAS

bool esListaVacia(Nodo * lista){
    if (lista == NULL)
    {
        return true;
    }else{
        return false;
    }
}

void mostrarLista(Nodo * lista){
    
    if (esListaVacia(lista))
    {
        printf("Lista vacia\n"); //si es vacia
        return;
    }else{
        while (!esListaVacia(lista))
        {
            printf("ID: %d | Duracion: %d min | Desc: %s\n",lista->T.TareaID,lista->T.Duracion,lista->T.Descripcion);
            lista = lista->Siguiente; //voy avanzando
        }
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

    Nodo * nuevoNodo = crearNodo(tareita); //creas un nodo con la informacion cargada de tareita
    insertarNodo(pendientes,nuevoNodo); //luego lo insertas en la lista
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

//PARTE DE BUSCAR TAREA

Nodo * buscarTareaId(Nodo * primero, int id){
    Nodo * aux = primero;
    while (aux != NULL && aux->T.TareaID != id)
    {
        aux = aux->Siguiente;
    }
    return aux;
}

int buscarTareaPalabra(Nodo * primero, char * palabra, char * tipoLista){
    int encontradas = 0;
    Nodo * aux = primero;  

    while (aux != NULL)
    {
        if (strstr(aux->T.Descripcion, palabra) != NULL)
        {
            printf("ID: %d | Duracion: %d min | Desc: %s (Lista %s)\n",aux->T.TareaID, aux->T.Duracion, aux->T.Descripcion, tipoLista);
            encontradas++;
        }
        aux = aux->Siguiente;
    }

    return encontradas;
}

void buscarTareas(Nodo * pendientes, Nodo * realizadas){
    int tipo;
    printf("\n--- Buscar tarea ---\n");
    printf("1- Por ID\n");
    printf("2- Por palabra clave\n");
    printf("Opcion: ");
    scanf("%d", &tipo);

    if (tipo == 1)
    {
        int id;
        printf("Ingrese el ID a buscar: ");
        scanf("%d", &id);

        Nodo * encontrado = buscarTareaId(pendientes, id);
        if (encontrado != NULL){
            printf("\nID: %d | Duracion: %d min | Desc: %s (Lista pendiente)\n",encontrado->T.TareaID, encontrado->T.Duracion, encontrado->T.Descripcion);
            return;
        }

        encontrado = buscarTareaId(realizadas, id);
        if (encontrado != NULL){
            printf("\nID: %d | Duracion: %d min | Desc: %s (Lista realizada)\n",encontrado->T.TareaID, encontrado->T.Duracion, encontrado->T.Descripcion);
            return;
        }

        printf("\nNo se encontro ninguna tarea con ID %d.\n", id);
    }
    else if (tipo == 2)
    {
        char palabra[100];
        printf("Ingrese palabra clave: ");
        scanf("%s", palabra);

        printf("\n--- Resultados ---\n");
        int total = 0;
        total += buscarTareaPalabra(pendientes, palabra, "pendiente");
        total += buscarTareaPalabra(realizadas, palabra, "realizada");

        if (total == 0){
            printf("No se encontraron tareas con la palabra %s.\n", palabra);
        } else {
            printf("\nTotal encontradas: %d\n", total);
        }
    }
    else
    {
        printf("Opcion invalida.\n");
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
        printf("\nIngrese la opcion que quiere: \n");
        printf("1- Si quiere agregar tarea \n");
        printf("2- Si quiere marcar tarea como realizada \n");
        printf("3- Mostrar lista \n");
        printf("4- Si quiere buscar tarea \n");
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
            case 4:
                buscarTareas(pendiente,realizada);
            break;
        
        default:
            break;
        }
        
    } while (opcion != 0);
    
    liberarLista(pendiente);
    liberarLista(realizada);
    

    
}