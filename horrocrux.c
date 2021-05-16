#include "horrocrux.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COLUMNA_LIMITE 0
#define FILAS_DIARIO 2
#define COLUMNAS_DIARIO 4
#define CENTRAR_FILA_DIARIO 3
#define CENTRAR_COLUMNA_DIARIO 2
#define FILA_LIMITE 0
#define RUMBO_DERECHO 0
#define RUMBO_IZQUIERDO 4
#define COLUMNA_ENTRADA 2
#define COLUMNA_ENTRADA_SIGUIENTE 3;
#define FILA_ENTRADA_SIGUIENTE 6;
#define FILA_SALIDA 0
#define COLUMNA_SALIDA 2
#define SIGUIENTE_COLUMNA_SALIDA 3
#define FILA_RESTRINGIDA_GUARDAPELO 1
#define FILA_PROHIBIDA_GUARDAPELO 5
#define FILAS_GUARDAPELO 6
#define COLUMNAS_GUARDAPELO 6
#define FILA_ENTRADA 4
#define COL_BORDE_BASILISCO 1
#define COLUMNA_BORDE_BASILISCO 5
#define FILA_BORDE_BASILISCO 4
#define FIL_BORDE_BASILISCO 2
#define FILAS_DOLORES 3
#define COLUMNAS_DOLORES 3
#define COLUMNA_RESTRINGIDA_DIARIO 0
#define COL_RESTRINGIDA_DIARIO 6
#define FILA_UNO_RESTRINGIDA_DIARIO 2
#define FILA_DOS_RESTRINGIDA_DIARIO 3
#define FILA_TRES_RESTRINGIDA_DIARIO 4
#define COLUMNA_UNO_RESTRINGIDA_GUARDAPELO 2
#define COLUMNA_DOS_RESTRINGIDA_GUARDAPELO 3
#define COLUMNA_TRES_RESTRINGIDA_GUARDAPELO 4
#define FILA_BORDE_UNO_RESTRINGIDA_GUARDAPELO 0
#define FILA_BORDE_DOS_RESTRINGIDA_GUARDAPELO 6
#define COLUMNA_BORDE_UNO_RESTRINGIDA_GUARDAPELO 0
#define COLUMNA_BORDE_DOS_RESTRINGIDA_GUARDAPELO 6
#define TURNOS_PERDIDOS_POR_DUENDE 7
#define TURNOS_PERDIDOS_POR_DOLORES 10
#define JUGANDO 0
#define GANADO 1
#define PERDIDO -1
#define JUGADOR 'J'
#define VACIO '\0'
#define SALIDA 'S'
#define DERECHA 'd'
#define IZQUIERDA 'a'
#define DIRECCION_IZQUIERDA 'i'
#define DIRECCION_DERECHA 'd'
#define ABAJO 's'
#define ARRIBA 'w'
#define ANILLO 'A'
#define GUARDAPELOS 'L'
#define DIARIO 'D'
#define COPA 'C'
#define COLMILLO 'F'
#define ESPADA 'E'
#define CURA 'P'
#define BASILISCO 'B'
#define DUENDE 'G'
#define DOLORES 'U'
#define MAX_TURNOS_ENVENENADO 10
#define FILAS_DISPONIBLES_COPA 3
#define FILA_RESTRINGIDA_DUENDE 2
#define BORDE_DERECHO_DIARIO 4
#define BORDE_IZQUIERDO_DIARIO 2
#define COLUMNA_DEL_DIARIO 3
#define FILAS_NIVEL_UNO 5
#define COLUMNAS_NIVEL_UNO 5
#define FILAS_NIVEL_DOS 7
#define COLUMNAS_NIVEL_DOS 7
#define FILAS_NIVEL_TRES 5
#define COLUMNAS_NIVEL_TRES 5
#define FILAS_NIVEL_CUATRO 7
#define COLUMNAS_NIVEL_CUATRO 7
#define C_OBJETOS_NIVEL_UNO 3
#define C_OBJETOS_NIVEL_DOS 7
#define C_OBJETOS_NIVEL_TRES 0
#define C_OBJETOS_NIVEL_CUATRO 0
#define FILA_BASILISCO 3
#define COLUMNA_BASILISCO 5
#define FILA_DUENDE 2
#define COLUMNA_DUENDE 2
#define TAM_DOLORES 3
#define TURNOS_INICIALES 75
#define CURAS_NECESARIAS 1
#define COLMILLOS_NECESARIOS 2
#define COLMILLO_NECESARIO 1
#define ESPADAS_NECESARIAS 1
#define ITEMS_INICIALES 0
#define ENVENENADOS_INICIO 0
#define FILA_RESTRINGIDA


/* * Precondiciones: recibe dos elementos del tipo elemento_t.
   * Postcondiciones: Devuelve True en caso de que ambos elementos estén posicionados en la misma posición, False en caso contrario.*/
bool misma_posicion_aleatoria_objetos( elemento_t elemento, elemento_t otro_elemento){
    return( (elemento.posicion.fila== otro_elemento.posicion.fila) && (elemento.posicion.columna== otro_elemento.posicion.columna) );
}
/* * Precondiciones: recibe dos elementos uno del tipo coordenadas_t y otro del tipo elemento_t.
   * Postcondiciones: Devuelve True en caso de que ambos elementos estén posicionados en la misma posición, False en caso contrario.*/
bool misma_posicion(coordenadas_t coordenada, elemento_t elemento){
    return( (coordenada.fila == elemento.posicion.fila) && (coordenada.columna == elemento.posicion.columna));
}
/* * Precondiciones: Recibe un elemento del tipo elemento_t.
   * Postcondiciones: Devuelve un booleano verdadero si el elemento está en la zona restringida unicamente al diario, falso en caso contrario.*/
bool espacio_restringido_diario(elemento_t elemento){
    bool restringido= false;
    if(elemento.posicion.columna != COLUMNA_RESTRINGIDA_DIARIO || elemento.posicion.columna != COL_RESTRINGIDA_DIARIO ){
        if(elemento.posicion.fila == FILA_UNO_RESTRINGIDA_DIARIO || elemento.posicion.fila == FILA_DOS_RESTRINGIDA_DIARIO || elemento.posicion.fila == FILA_TRES_RESTRINGIDA_DIARIO)
            restringido= true;
    }return restringido;
}
/* * Precondiciones: Recibe un elemento del tipo elemento_t.
   * Postcondiciones: Devuelve un booleano verdadero si el elemento está en la zona está restringida, false en caso contrario. */
bool espacio_restringido_guardapelo(elemento_t elemento){
    bool restringido = false;
    if(elemento.posicion.fila == FILA_RESTRINGIDA_GUARDAPELO || elemento.posicion.fila== FILA_PROHIBIDA_GUARDAPELO){
        if(elemento.posicion.columna == COLUMNA_UNO_RESTRINGIDA_GUARDAPELO || elemento.posicion.columna == COLUMNA_DOS_RESTRINGIDA_GUARDAPELO || elemento.posicion.columna == COLUMNA_TRES_RESTRINGIDA_GUARDAPELO)
            restringido = true;
    }if(elemento.posicion.fila == FILA_BORDE_UNO_RESTRINGIDA_GUARDAPELO || elemento.posicion.fila == FILA_BORDE_DOS_RESTRINGIDA_GUARDAPELO || elemento.posicion.columna == COLUMNA_BORDE_UNO_RESTRINGIDA_GUARDAPELO || elemento.posicion.columna == COLUMNA_BORDE_DOS_RESTRINGIDA_GUARDAPELO)
        restringido = true;
    return restringido;
}
/* * Precondiciones: Recibe el juego en un estado valido.
   * Postcondiciones: Devuelve un booleano true si la posición pertenece al espacio recorrido por dolores, false en caso contrario*/
bool espacio_dolores(juego_t* juego){
    bool pertenece=false;
    if((*juego).niveles[3].guardian.posicion.fila == ((*juego).niveles[3].horrocrux.posicion.fila+1) || (*juego).niveles[3].guardian.posicion.fila == ((*juego).niveles[3].horrocrux.posicion.fila-1))
        if((*juego).niveles[3].guardian.posicion.columna == ((*juego).niveles[3].horrocrux.posicion.columna-1) || (*juego).niveles[3].guardian.posicion.columna == ((*juego).niveles[3].horrocrux.posicion.columna+1)
        || (*juego).niveles[3].guardian.posicion.columna == ((*juego).niveles[3].horrocrux.posicion.columna))
            pertenece = true;
    if((*juego).niveles[3].guardian.posicion.fila == (*juego).niveles[3].horrocrux.posicion.fila)
        if((*juego).niveles[3].guardian.posicion.columna == ((*juego).niveles[3].horrocrux.posicion.columna-1) || (*juego).niveles[3].guardian.posicion.columna == ((*juego).niveles[3].horrocrux.posicion.columna+1))
            pertenece = true;
    return pertenece;
}
/* * Precondiciones: Recibe un tipo de dato elemento_t.
   * Postcondiciones: Devuelve un booleano true si la posición analizada está en el espacio del diario, false en caso contrario*/
bool espacio_diario(elemento_t cosa){
    bool restringido= false;
    if(cosa.posicion.fila== FILA_DOS_RESTRINGIDA_DIARIO)
        if(cosa.posicion.columna== BORDE_IZQUIERDO_DIARIO || cosa.posicion.columna== COLUMNA_DEL_DIARIO || cosa.posicion.columna== BORDE_DERECHO_DIARIO)
            restringido= true;
    return restringido;
}
/* * Precondiciones: Recibe el juego en un estado valido.
   * Postcondiciones: Devuelve True si el jugador está posicionado en la salida, False en caso contrario.*/
bool en_salida(coordenadas_t jugador, coordenadas_t salida){
    return((jugador.fila== salida.fila) && (jugador.columna== salida.columna));
}
/* * Precondiciones: Recibe un tipo de dato elemento_t.
   * Postcondiciones: Devuelve un booleano true si la posición pertenece al espacio recorrido por dolores, false en caso contrario*/
bool espacio_duende(elemento_t copa){
    return(copa.posicion.fila==FILA_RESTRINGIDA_DUENDE);
}

/* *Precondiciones: Recibe el juego en un estado valido
   *Postcondiciones: Inicializa y carga todos los valores (sea estado, cantidad de objetos, etc) necesarios para jugar en el nivel uno*/
void inicializar_nivel_uno(juego_t* juego){
    (*juego).niveles[0].numero = 1;
    (*juego).niveles[0].cantidad_objetos= C_OBJETOS_NIVEL_UNO;
    (*juego).niveles[0].salida.fila= FILA_SALIDA;
    (*juego).niveles[0].salida.columna= COLUMNA_SALIDA;
    (*juego).niveles[0].entrada.fila= FILA_ENTRADA;
    (*juego).niveles[0].entrada.columna= COLUMNA_ENTRADA;
    (*juego).niveles[0].filas = FILAS_NIVEL_UNO;
    (*juego).niveles[0].columnas = COLUMNAS_NIVEL_UNO;
    (*juego).niveles[0].tiene_guardian = false;
    (*juego).niveles[0].horrocrux.codigo= ANILLO;
    (*juego).niveles[0].horrocrux_destruido= false;
    (*juego).niveles[0].objetos[0].codigo= CURA;
    (*juego).niveles[0].objetos[1].codigo= CURA;
    (*juego).niveles[0].objetos[2].codigo= CURA;
    (*juego).nivel_actual = 1;
    (*juego).jugador.posicion.fila= (*juego).niveles[(*juego).nivel_actual-1].entrada.fila;
    (*juego).jugador.posicion.columna= (*juego).niveles[(*juego).nivel_actual-1].entrada.columna;

    do{
        (*juego).niveles[0].objetos[0].posicion= posicion_aleatoria((*juego).niveles[0].filas, (*juego).niveles[0].columnas);
    }while(misma_posicion((*juego).niveles[0].salida,(*juego).niveles[0].objetos[0]) || misma_posicion((*juego).niveles[0].entrada,(*juego).niveles[0].objetos[0]) );
    do{
        (*juego).niveles[0].horrocrux.posicion= posicion_aleatoria((*juego).niveles[0].filas, (*juego).niveles[0].columnas);
    }while(misma_posicion((*juego).niveles[0].salida,(*juego).niveles[0].horrocrux) || misma_posicion((*juego).niveles[0].entrada,(*juego).niveles[0].horrocrux) || misma_posicion_aleatoria_objetos((*juego).niveles[0].horrocrux,(*juego).niveles[0].objetos[0]));

    do{
        (*juego).niveles[0].objetos[1].posicion= posicion_aleatoria((*juego).niveles[0].filas, (*juego).niveles[0].columnas);
    }while(misma_posicion((*juego).niveles[0].salida,(*juego).niveles[0].objetos[1]) || misma_posicion((*juego).niveles[0].entrada,(*juego).niveles[0].objetos[1]) || misma_posicion_aleatoria_objetos((*juego).niveles[0].objetos[1],(*juego).niveles[0].horrocrux)
    || misma_posicion_aleatoria_objetos((*juego).niveles[0].objetos[1],(*juego).niveles[0].objetos[0]) );

    do{
        (*juego).niveles[0].objetos[2].posicion= posicion_aleatoria((*juego).niveles[0].filas, (*juego).niveles[0].columnas);
    }while(misma_posicion((*juego).niveles[0].salida,(*juego).niveles[0].objetos[2]) || misma_posicion((*juego).niveles[0].entrada,(*juego).niveles[0].objetos[2])
    || misma_posicion_aleatoria_objetos((*juego).niveles[0].objetos[2],(*juego).niveles[(*juego).nivel_actual-1].horrocrux)
    || misma_posicion_aleatoria_objetos((*juego).niveles[0].objetos[2],(*juego).niveles[(*juego).nivel_actual-1].objetos[0])
    || misma_posicion_aleatoria_objetos((*juego).niveles[0].objetos[2],(*juego).niveles[(*juego).nivel_actual-1].objetos[1]));

}
/* *Precondiciones: Recibe el juego en un estado valido
   *Postcondiciones: Inicializa y carga todos los valores (sea estado, cantidad de objetos, etc) necesarios para jugar en el nivel dos*/
void inicializar_nivel_dos(juego_t* juego){
    (*juego).niveles[1].numero = 2;
    (*juego).niveles[1].cantidad_objetos = C_OBJETOS_NIVEL_DOS;
    (*juego).niveles[1].filas= FILAS_NIVEL_DOS;
    (*juego).niveles[1].columnas= COLUMNAS_NIVEL_DOS;
    (*juego).niveles[1].salida.fila= FILA_SALIDA;
    (*juego).niveles[1].salida.columna= SIGUIENTE_COLUMNA_SALIDA;
    (*juego).niveles[1].entrada.fila= FILA_ENTRADA_SIGUIENTE;
    (*juego).niveles[1].entrada.columna= COLUMNA_ENTRADA_SIGUIENTE;
    (*juego).niveles[1].tiene_guardian= true;
    (*juego).niveles[1].guardian.posicion.fila= FILA_BASILISCO;
    (*juego).niveles[1].guardian.posicion.columna= COLUMNA_BASILISCO;
    (*juego).niveles[1].horrocrux_destruido= false;
    (*juego).niveles[1].horrocrux.codigo= DIARIO;
    (*juego).niveles[1].objetos[0].codigo= COLMILLO;
    (*juego).niveles[1].objetos[1].codigo= COLMILLO;
    (*juego).niveles[1].objetos[2].codigo= COLMILLO;
    (*juego).niveles[1].objetos[3].codigo= COLMILLO;
    (*juego).niveles[1].objetos[4].codigo= COLMILLO;
    (*juego).niveles[1].objetos[5].codigo= COLMILLO;
    (*juego).niveles[1].objetos[6].codigo= ESPADA;
    (*juego).niveles[1].guardian.codigo= BASILISCO;
    (*juego).nivel_actual = 2;
    (*juego).jugador.posicion.fila= (*juego).niveles[(*juego).nivel_actual-1].entrada.fila;
    (*juego).jugador.posicion.columna= (*juego).niveles[(*juego).nivel_actual-1].entrada.columna;
    do{
        (*juego).niveles[1].objetos[0].posicion= posicion_aleatoria((*juego).niveles[1].filas, (*juego).niveles[1].columnas);

    }while(misma_posicion((*juego).niveles[1].salida,(*juego).niveles[1].objetos[0]) || misma_posicion((*juego).niveles[1].entrada,(*juego).niveles[1].objetos[0])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[0],(*juego).niveles[1].guardian) || espacio_restringido_diario((*juego).niveles[1].objetos[0]));
    do{
        (*juego).niveles[1].horrocrux.posicion= posicion_aleatoria(FILAS_DIARIO, COLUMNAS_DIARIO);
        (*juego).niveles[1].horrocrux.posicion.fila+= CENTRAR_FILA_DIARIO;
        (*juego).niveles[1].horrocrux.posicion.columna+= CENTRAR_COLUMNA_DIARIO;

    }while(misma_posicion((*juego).niveles[1].salida,(*juego).niveles[1].horrocrux) || misma_posicion((*juego).niveles[1].entrada,(*juego).niveles[1].horrocrux) || misma_posicion_aleatoria_objetos((*juego).niveles[1].horrocrux,(*juego).niveles[1].objetos[0])
     || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[1],(*juego).niveles[1].guardian));
    do{
        (*juego).niveles[1].objetos[1].posicion= posicion_aleatoria((*juego).niveles[1].filas, (*juego).niveles[1].columnas);
    }while(misma_posicion((*juego).niveles[1].salida,(*juego).niveles[1].objetos[1]) || misma_posicion((*juego).niveles[1].entrada,(*juego).niveles[1].objetos[1]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[1],(*juego).niveles[1].horrocrux)
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[1],(*juego).niveles[1].objetos[0]) ||  misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[0],(*juego).niveles[1].guardian) || espacio_restringido_diario((*juego).niveles[1].objetos[1]) );

    do{
        (*juego).niveles[1].objetos[2].posicion= posicion_aleatoria((*juego).niveles[1].filas, (*juego).niveles[1].columnas);
    }while(misma_posicion((*juego).niveles[1].salida,(*juego).niveles[1].objetos[2]) || misma_posicion((*juego).niveles[1].entrada,(*juego).niveles[1].objetos[2])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[2],(*juego).niveles[(*juego).nivel_actual-1].horrocrux) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[2],(*juego).niveles[(*juego).nivel_actual].objetos[0])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[2],(*juego).niveles[(*juego).nivel_actual-1].objetos[1]) ||  misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[2],(*juego).niveles[1].guardian) || espacio_restringido_diario((*juego).niveles[1].objetos[2]));

    do{
        (*juego).niveles[1].objetos[3].posicion= posicion_aleatoria((*juego).niveles[1].filas, (*juego).niveles[1].columnas);
    }while(misma_posicion((*juego).niveles[1].salida,(*juego).niveles[1].objetos[3]) || misma_posicion((*juego).niveles[1].entrada,(*juego).niveles[1].objetos[3])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[3],(*juego).niveles[1].horrocrux) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[3],(*juego).niveles[1].objetos[0])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[3],(*juego).niveles[1].objetos[1]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[3],(*juego).niveles[1].objetos[2]) || espacio_restringido_diario((*juego).niveles[1].objetos[3]));

    do{
        (*juego).niveles[1].objetos[4].posicion= posicion_aleatoria((*juego).niveles[1].filas, (*juego).niveles[1].columnas);

    }while(misma_posicion((*juego).niveles[1].salida,(*juego).niveles[1].objetos[4]) || misma_posicion((*juego).niveles[1].entrada,(*juego).niveles[1].objetos[4]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[4],(*juego).niveles[1].horrocrux)
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[4],(*juego).niveles[1].objetos[0]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[4],(*juego).niveles[1].objetos[1])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[4],(*juego).niveles[1].objetos[2]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[4],(*juego).niveles[1].objetos[3])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[4],(*juego).niveles[1].guardian)|| espacio_restringido_diario((*juego).niveles[1].objetos[4]));

    do{
        (*juego).niveles[1].objetos[5].posicion= posicion_aleatoria((*juego).niveles[1].filas, (*juego).niveles[1].columnas);

    }while(misma_posicion((*juego).niveles[1].salida,(*juego).niveles[1].objetos[5]) || misma_posicion((*juego).niveles[1].entrada,(*juego).niveles[1].objetos[5]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[5],(*juego).niveles[1].horrocrux)
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[5],(*juego).niveles[1].objetos[0]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[5],(*juego).niveles[1].objetos[1])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[5],(*juego).niveles[1].objetos[2]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[5],(*juego).niveles[1].objetos[3])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[5],(*juego).niveles[1].objetos[4]) ||  misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[5],(*juego).niveles[1].guardian) || espacio_restringido_diario((*juego).niveles[1].objetos[5]));

    do{
        (*juego).niveles[1].objetos[6].posicion= posicion_aleatoria((*juego).niveles[1].filas, (*juego).niveles[1].columnas);
    }while(misma_posicion((*juego).niveles[1].salida,(*juego).niveles[1].objetos[6]) || misma_posicion((*juego).niveles[1].entrada,(*juego).niveles[1].objetos[6]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[6],(*juego).niveles[1].horrocrux)
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[6],(*juego).niveles[1].objetos[0]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[6],(*juego).niveles[1].objetos[1])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[6],(*juego).niveles[1].objetos[2]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[6],(*juego).niveles[1].objetos[3])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[6],(*juego).niveles[1].objetos[4]) || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[6],(*juego).niveles[1].objetos[5])
    || misma_posicion_aleatoria_objetos((*juego).niveles[1].objetos[0],(*juego).niveles[1].guardian) || espacio_restringido_diario((*juego).niveles[1].objetos[6]));

}
/* *Precondiciones: Recibe el juego en un estado valido
   *Postcondiciones: Inicializa y carga todos los valores (sea estado, cantidad de objetos, etc) necesarios para jugar en el nivel tres*/
void inicializar_nivel_tres(juego_t* juego){
    (*juego).niveles[2].numero = 3;
    (*juego).niveles[2].filas= FILAS_NIVEL_TRES;
    (*juego).niveles[2].columnas= COLUMNAS_NIVEL_TRES;
    (*juego).niveles[2].cantidad_objetos = C_OBJETOS_NIVEL_TRES;
    (*juego).niveles[2].salida.fila= FILA_SALIDA;
    (*juego).niveles[2].salida.columna= COLUMNA_SALIDA;
    (*juego).niveles[2].entrada.fila= FILA_ENTRADA;
    (*juego).niveles[2].entrada.columna= COLUMNA_ENTRADA;
    (*juego).niveles[2].guardian.posicion.fila= FILA_DUENDE;
    (*juego).niveles[2].guardian.posicion.columna= COLUMNA_DUENDE;
    (*juego).niveles[2].horrocrux_destruido= false;
    (*juego).niveles[2].horrocrux.codigo= COPA;
    (*juego).niveles[2].tiene_guardian=true;
    (*juego).niveles[2].guardian.codigo= DUENDE;
    (*juego).niveles[2].direccion_duende= DIRECCION_DERECHA;
    (*juego).nivel_actual = 3;
    (*juego).jugador.posicion.fila= (*juego).niveles[(*juego).nivel_actual-1].entrada.fila;
    (*juego).jugador.posicion.columna= (*juego).niveles[(*juego).nivel_actual-1].entrada.columna;

    do{
        (*juego).niveles[2].horrocrux.posicion = posicion_aleatoria((*juego).niveles[2].filas ,(*juego).niveles[2].columnas );
    }while(espacio_duende((*juego).niveles[2].horrocrux) || misma_posicion((*juego).niveles[2].entrada, (*juego).niveles[2].horrocrux) || misma_posicion((*juego).niveles[2].salida, (*juego).niveles[2].horrocrux));

}
/* *Precondiciones: Recibe el juego en un estado valido
   *Postcondiciones: Inicializa y carga todos los valores (sea estado, cantidad de objetos, etc) necesarios para jugar en el nivel cuatro*/
void inicializar_nivel_cuatro(juego_t* juego){
    (*juego).niveles[3].numero = 4;
    coordenadas_t una_posicion_aleatoria_dolores;
    (*juego).niveles[3].cantidad_objetos = C_OBJETOS_NIVEL_CUATRO;
    (*juego).niveles[3].entrada.fila= FILA_ENTRADA_SIGUIENTE;
    (*juego).niveles[3].entrada.columna= COLUMNA_ENTRADA_SIGUIENTE;
    (*juego).niveles[3].salida.fila= FILA_SALIDA;
    (*juego).niveles[3].salida.columna= SIGUIENTE_COLUMNA_SALIDA;
    (*juego).niveles[3].horrocrux_destruido= false;
    (*juego).niveles[3].horrocrux.codigo= GUARDAPELOS;
    (*juego).niveles[3].tiene_guardian=true;
    (*juego).niveles[3].guardian.codigo= DOLORES;
    (*juego).niveles[3].filas= FILAS_NIVEL_CUATRO;
    (*juego).niveles[3].columnas= COLUMNAS_NIVEL_CUATRO;
    (*juego).nivel_actual = 4;
    (*juego).jugador.posicion.fila= (*juego).niveles[(*juego).nivel_actual-1].entrada.fila;
    (*juego).jugador.posicion.columna= (*juego).niveles[(*juego).nivel_actual-1].entrada.columna;
    do{
        (*juego).niveles[3].horrocrux.posicion= posicion_aleatoria((*juego).niveles[3].filas, (*juego).niveles[3].columnas);
    }while(espacio_restringido_guardapelo((*juego).niveles[3].horrocrux));

    do{
        una_posicion_aleatoria_dolores= posicion_aleatoria(TAM_DOLORES, TAM_DOLORES);
    }while(una_posicion_aleatoria_dolores.fila==1 && una_posicion_aleatoria_dolores.columna==1);
    (*juego).niveles[3].guardian.posicion.fila = (*juego).niveles[3].horrocrux.posicion.fila + una_posicion_aleatoria_dolores.fila -1;
    (*juego).niveles[3].guardian.posicion.columna= (*juego).niveles[3].horrocrux.posicion.columna + una_posicion_aleatoria_dolores.columna -1;

}

void inicializar_juego(juego_t *juego){
    inicializar_nivel_uno(juego);
    inicializar_nivel_dos(juego);
    inicializar_nivel_tres(juego);
    inicializar_nivel_cuatro(juego);
    (*juego).nivel_actual = 1;
    (*juego).jugador.posicion.fila= (*juego).niveles[(*juego).nivel_actual-1].entrada.fila;
    (*juego).jugador.posicion.columna= (*juego).niveles[(*juego).nivel_actual-1].entrada.columna;
    (*juego).jugador.cantidad_items = ITEMS_INICIALES;
    (*juego).jugador.turnos_restantes= TURNOS_INICIALES;
    (*juego).jugador.turnos_envenenado= ENVENENADOS_INICIO;
    (*juego).jugador.envenenado=false;
    (*juego).estado = JUGANDO;

}

void actualizar_escenario(juego_t juego, char escenario[MAX_FILAS][MAX_COLUMNAS]){
    unsigned int filas = (juego).niveles[((juego).nivel_actual)-1].filas;
    unsigned int columnas = (juego).niveles[((juego).nivel_actual)-1].columnas;
    int i;

    for( i=0; i < filas; i++){
        for(int j=0; j < columnas; j++){
            escenario[i][j]= VACIO;
        }
    }
    for(int cant_objetos=0; cant_objetos<(juego).niveles[(juego).nivel_actual-1].cantidad_objetos; cant_objetos++){
        escenario[(juego).niveles[(juego).nivel_actual-1].objetos[cant_objetos].posicion.fila][(juego).niveles[(juego).nivel_actual-1].objetos[cant_objetos].posicion.columna] = (juego).niveles[(juego).nivel_actual-1].objetos[cant_objetos].codigo;
    }
    escenario[(juego).jugador.posicion.fila ][(juego).jugador.posicion.columna] = JUGADOR;
    if((juego).niveles[(juego).nivel_actual-1].tiene_guardian && !misma_posicion((juego).jugador.posicion, (juego).niveles[(juego).nivel_actual-1].guardian)){
        if((juego).nivel_actual==2 && (juego).niveles[(juego).nivel_actual-1].basilisco_destruido == false){
            escenario[(juego).niveles[(juego).nivel_actual-1].guardian.posicion.fila ][(juego).niveles[(juego).nivel_actual-1].guardian.posicion.columna] = (juego).niveles[(juego).nivel_actual-1].guardian.codigo;
        }
        else if ((juego).nivel_actual !=2)
            escenario[(juego).niveles[(juego).nivel_actual-1].guardian.posicion.fila ][(juego).niveles[(juego).nivel_actual-1].guardian.posicion.columna] = (juego).niveles[(juego).nivel_actual-1].guardian.codigo;

    }if(!en_salida((juego).jugador.posicion,(juego).niveles[(juego).nivel_actual-1].salida))
        escenario[(juego).niveles[(juego).nivel_actual-1].salida.fila][(juego).niveles[(juego).nivel_actual-1].salida.columna] = SALIDA;
    if((juego).niveles[(juego).nivel_actual-1].horrocrux_destruido == false && !misma_posicion((juego).jugador.posicion, (juego).niveles[(juego).nivel_actual-1].horrocrux))
        escenario[(juego).niveles[(juego).nivel_actual-1].horrocrux.posicion.fila][(juego).niveles[(juego).nivel_actual-1].horrocrux.posicion.columna] = (juego).niveles[(juego).nivel_actual-1].horrocrux.codigo;
}

void mostrar_escenario(char escenario[MAX_FILAS][MAX_COLUMNAS], unsigned int filas, unsigned int columnas){
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("[%c]" , escenario[i][j] );
        }
        printf("\n");
    }
    printf("\n\n");

}

/* * Precondiciones: Recibe el juego en un estado valido.-
   * Postcondiciones: Devuelve True si el jugador dispone de turnos, False en caso contrario.*/
bool tiene_turnos(juego_t* juego){
  unsigned int turnos_restantes= (*juego).jugador.turnos_restantes;
  return(turnos_restantes>0);
}
/* * Precondiciones: Recibe un caracter.
   * Postcondiciones: Devuelve True si el caracter ingresado fue valido, False en caso contrario*/
bool comando_valido(char comando){
  return((comando== ARRIBA || comando== ABAJO || comando== DERECHA || comando== IZQUIERDA));
}
/* * Precondiciones: Recibe una direccion de movimiento junto con el juego.-
   * Postcondiciones: Devuelve True si el movimiento pertenece a los limites del escenario, False en caso contrario*/

bool movimiento_pertenece_escenario(juego_t juego, char movimiento){
    unsigned int ult_columna= ( ((juego).niveles[((juego).nivel_actual)-1].columnas)-1);
    unsigned int ult_fila=  ( ((juego).niveles[((juego).nivel_actual)-1].filas)-1);
    bool pertenece = true;
    if (movimiento == ARRIBA){
        if((juego).jugador.posicion.columna == COLUMNA_LIMITE && (juego).jugador.posicion.fila == FILA_LIMITE)
            pertenece = false;
        else if ((juego).jugador.posicion.fila == FILA_LIMITE)
            pertenece = false;
        else if ((juego).jugador.posicion.columna== ult_columna && (juego).jugador.posicion.fila == FILA_LIMITE)
            pertenece = false;
    }
    else if((juego).jugador.posicion.columna== COLUMNA_LIMITE && movimiento == IZQUIERDA )
        pertenece=false;
    else if ((juego).jugador.posicion.columna== ult_columna && movimiento == DERECHA)
        pertenece=false;
    else if((juego).jugador.posicion.fila==ult_fila && movimiento == ABAJO)
        pertenece=false;
    return (pertenece);

}
/* * Precondiciones: Recibe un caracter de movimiento y un juego.-
   * Postcondiciones: Devuelve True si el la direccion de movimiento es valida y el movimiento pertenece a los limites del escenario, false en caso contrario*/

bool puede_moverse_jugador(char movimiento, juego_t juego){
    return(movimiento_pertenece_escenario(juego, movimiento) && comando_valido(movimiento));
}
/* * Precondiciones: Recibe el juego en un estado valido.
   *Postcondiciones: En el caso de encontrar un objeto, lo guarda en la mochila del jugador y elimina el caracter del vector objetos*/
void recoger_item(juego_t* juego){
    bool encontro= false;
    char item;
    int cant_objetos = 0;
    int pos;
    while(cant_objetos < (*juego).niveles[(*juego).nivel_actual-1].cantidad_objetos && (!encontro)){
        if(misma_posicion((*juego).jugador.posicion, (*juego).niveles[(*juego).nivel_actual-1].objetos[cant_objetos])){
            encontro = true;
            item = (*juego).niveles[(*juego).nivel_actual-1].objetos[cant_objetos].codigo;
            (*juego).jugador.items[(*juego).jugador.cantidad_items].codigo = item;
            (*juego).jugador.cantidad_items++;
            pos = cant_objetos;

        }
    cant_objetos++;
    }
    if (encontro){
        for ( int i = pos ; i < ((*juego).niveles[(*juego).nivel_actual-1].cantidad_objetos-1) ; i ++ ){
            (*juego).niveles[(*juego).nivel_actual-1].objetos[i]= (*juego).niveles[(*juego).nivel_actual-1].objetos[i+1];
        }
        (*juego).niveles[(*juego).nivel_actual-1].cantidad_objetos--;
    }


}
//devuelve 0 si no lo encuentra  y la pos de donde lo encuentra si lo encuentra
/* * Precondiciones: Recibe el juego, el item a buscar en la mochila y la cantidad necesaria de esos items
   * Postcondiciones: Devuelve True si en la mochila del jugador se encontró la cantidad necesaria de items, False en caso contrario*/

bool tiene_item(juego_t* juego, char item, int suficientes){
    bool tiene = false;
    int i = 0;
    int contador = 0;
    while ( ( i < (*juego).jugador.cantidad_items)  && (!tiene) ) {
        if ( (*juego).jugador.items[i].codigo== item ) {
            contador++;
            if(contador== suficientes){
                tiene = true ;
            }
        }
        i ++;
    }
    return (tiene);

}

/* * Precondiciones: Recibe el juego y el item que se quiere usar.
   * Postcondiciones: Elimina de la mochila del jugador el item que se usó y actualiza la cantidad de items que le quedan en la mochila*/

void usar_item(juego_t* juego, char item){
    bool encontrado= false;
    int i=0;
    int pos;
    while ( ( i < (*juego).jugador.cantidad_items) && (!encontrado) ){
        if ( (*juego).jugador.items[i].codigo == item ){
            pos = i;
            encontrado = true;
        }
        i++;
    }
    for ( i = pos ; i < ((*juego).jugador.cantidad_items-1) ; i ++ ){
        (*juego).jugador.items[i]= (*juego).jugador.items[i+1];
    }
    (*juego).jugador.cantidad_items--;

}

/* *Precondiciones: Recibe el juego en un estado valido.
   * Postcondiciones: Actualiza la posicion del duende según la dirección en la que se encuentra.*/
void mover_duende(juego_t* juego){
    if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == RUMBO_DERECHO)
        (*juego).niveles[(*juego).nivel_actual-1].direccion_duende= DIRECCION_DERECHA;

    if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == RUMBO_IZQUIERDO)
        (*juego).niveles[(*juego).nivel_actual-1].direccion_duende= DIRECCION_IZQUIERDA;

    if((*juego).niveles[(*juego).nivel_actual-1].direccion_duende== DIRECCION_DERECHA ){
        (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna++;
    }
    if((*juego).niveles[(*juego).nivel_actual-1].direccion_duende== DIRECCION_IZQUIERDA){
        (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna--;
    }

}
/* * Precondiciones: Recibe el juego en un estado valido.
   * Postcondiciones: Actualiza la posición de dolores según su recorrido en sentido horario.*/

void mover_dolores(juego_t* juego){
    if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila == (*juego).niveles[(*juego).nivel_actual-1].horrocrux.posicion.fila-1){
        if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == (*juego).niveles[(*juego).nivel_actual-1].horrocrux.posicion.columna-1)
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna++;
        else if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == (*juego).niveles[(*juego).nivel_actual-1].horrocrux.posicion.columna+1){
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila = (*juego).niveles[(*juego).nivel_actual-1].horrocrux.posicion.fila;
        }else
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna++;
    }
    else if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila == (*juego).niveles[(*juego).nivel_actual-1].horrocrux.posicion.fila){
        if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == (*juego).niveles[(*juego).nivel_actual-1].horrocrux.posicion.columna+1)
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila++;
        else if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == (*juego).niveles[(*juego).nivel_actual-1].horrocrux.posicion.columna-1)
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila--;
    }
    else{
        if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == (*juego).niveles[(*juego).nivel_actual-1].horrocrux.posicion.columna+1)
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna--;
        else if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == (*juego).niveles[(*juego).nivel_actual-1].horrocrux.posicion.columna)
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna--;
        else
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila--;
    }
}
/* * Precondiciones: Recibe el juego en un estado valido.
   * Postcondiciones: Actualiza la posición del basilisco según su recorrido en sentido horario*/
void mover_basilisco(juego_t* juego){
    if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == COLUMNA_BORDE_BASILISCO){
        if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila != FILA_BORDE_BASILISCO ){
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila++;
        }else
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna--;
        }else if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna == COL_BORDE_BASILISCO ){
            if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila!= FIL_BORDE_BASILISCO)
                (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila--;

            else
                (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna++;

        }
        else if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila == FIL_BORDE_BASILISCO){
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna++;
        }else if((*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.fila == FILA_BORDE_BASILISCO){
            (*juego).niveles[(*juego).nivel_actual-1].guardian.posicion.columna--;

        }
}
/* * Precondiciones: Recibe el juego en un estado valido y los turnos a perder en caso de chocar al guardian.
   * Postcondiciones: En caso de estar en la misma posición del duende, resta los turnos que pierde el jugador, actualiza cúantos turnos le quedan. En caso de no quedarle más turnos, actualiza el estado del juego*/
void chocar_guardian(juego_t* juego, unsigned int turnos_perdidos){
    if(misma_posicion((*juego).jugador.posicion, (*juego).niveles[(*juego).nivel_actual-1].guardian)){
        if((*juego).jugador.turnos_restantes> turnos_perdidos){
            (*juego).jugador.turnos_restantes-= turnos_perdidos;
        }else{
            (*juego).jugador.turnos_restantes=0;
            (*juego).estado=PERDIDO;
        }
    }
}

/* * Precondiciones: Recibe el juego en un estado valido.
   * Postcondiciones: En caso de estar en la misma posición que el basilisco, lo mata si tiene la espada para hacerlo. En caso contrario, se actualiza el juego a perdido ya que muere el jugador. */
void matar_basilisco(juego_t* juego){
    if(misma_posicion((*juego).jugador.posicion,(*juego).niveles[(*juego).nivel_actual-1].guardian)){
        if(tiene_item(juego, ESPADA,1)){
            (*juego).niveles[(*juego).nivel_actual-1].basilisco_destruido = true;

        }else{
            (*juego).estado = PERDIDO;
            printf("TE HA MATADO EL BASILISCO\n");
        }
    }
}
/* * Precondiciones: Recibe el juego en un estado valido.
   * Postcondiciones: Según el nivel que corresponda, llama a la función que actualiza la posición del guardián correspondiente al nivel.*/
void mover_guardian(juego_t* juego){
    if((*juego).nivel_actual == 2 && (*juego).niveles[(*juego).nivel_actual].basilisco_destruido == false){
        mover_basilisco(juego);
        matar_basilisco(juego);
    }if((*juego).nivel_actual == 3){
        mover_duende(juego);
        chocar_guardian(juego, TURNOS_PERDIDOS_POR_DUENDE);
    }if((*juego).nivel_actual == 4){
        mover_dolores(juego);
        chocar_guardian(juego, TURNOS_PERDIDOS_POR_DOLORES);
    }
}

/* * Precondiciones: Recibe el estado del juego valido.
   * Postcondiciones: Actualiza estado de envenenamiento del jugador, el del horrocrux. En el caso de tener en la mochila alguna cura, el jugador se cura. Caso contrario, queda envenenado.*/
void destruir_anillo(juego_t* juego){
    (*juego).jugador.envenenado=true;
    (*juego).niveles[(*juego).nivel_actual-1].horrocrux_destruido=true;

    if(tiene_item(juego, CURA, CURAS_NECESARIAS)){
        usar_item(juego, CURA);
        (*juego).jugador.envenenado=false;
        (*juego).jugador.turnos_envenenado=0;
    }
}
/* * Precondiciones: Recibe el estado del juego valido.
   * Postcondiciones: Destruye el diario si tiene los elementos para hacerlo y actualiza el estado del horrocrux*/
void destruir_diario(juego_t* juego){
    if(tiene_item(juego, COLMILLO, COLMILLO_NECESARIO)){
        usar_item(juego, COLMILLO);
        (*juego).niveles[(*juego).nivel_actual-1].horrocrux_destruido=true;

    }
}
/* * Precondiciones:  Recibe el estado del juego valido.
   * Postcondiciones: Destruye la copa en caso de tener los elementos para hacerlo y actualiza el estado del horrocrux.*/
void destruir_copa(juego_t* juego){
    if(tiene_item(juego, ESPADA, ESPADAS_NECESARIAS)){
        (*juego).niveles[(*juego).nivel_actual-1].horrocrux_destruido=true;

    }
    else if (tiene_item(juego,COLMILLO, COLMILLOS_NECESARIOS)){
        usar_item(juego,COLMILLO);
        usar_item(juego, COLMILLO);
        (*juego).niveles[(*juego).nivel_actual-1].horrocrux_destruido=true;

    }
}
/* * Precondiciones:  Recibe el estado del juego valido.
   * Postcondiciones: Destruye el guardapelo en caso de tener los elementos para hacerlo y actualiza el estado del horrocrux; */
void destruir_guardapelo(juego_t* juego){
    if(tiene_item(juego,ESPADA,1)){
        (*juego).niveles[(*juego).nivel_actual-1].horrocrux_destruido=true;

    }else if (tiene_item(juego,COLMILLO,COLMILLO_NECESARIO)){
        usar_item(juego,COLMILLO);
        (*juego).niveles[(*juego).nivel_actual-1].horrocrux_destruido=true;

    }
}
/* * Precondiciones:  Recibe el estado del juego valido.
   * Postcondiciones: Pasa al siguiente nivel si está en condiciones de hacerlo. Actualiza el nivel_actual y la posición del jugador*/
void pasar_nivel(juego_t* juego){
    if(((*juego).niveles[(*juego).nivel_actual-1].horrocrux_destruido) && en_salida((*juego).jugador.posicion,(*juego).niveles[(*juego).nivel_actual-1].salida)){
        if((*juego).nivel_actual == 4){
            if(en_salida((*juego).jugador.posicion,(*juego).niveles[(*juego).nivel_actual-1].salida) && (*juego).niveles[(*juego).nivel_actual-1].horrocrux_destruido== true){
                printf("YEAH! has ganado!\n");
                (*juego).estado = GANADO;
            }
        }
        else{
            (*juego).nivel_actual++;
            (*juego).jugador.posicion = (*juego).niveles[(*juego).nivel_actual-1].entrada;
        }
    }
}
/* *Precondiciones: recibe el juego en un estado valido.
    *Postcondiciones: Actualiza todos los valores, mochila de items, turnos restantes, etc, que son modificados producto del movimiento producido por el jugador*/
void accion_de_moverse(juego_t* juego){
    (*juego).jugador.turnos_restantes--;
    recoger_item(juego);
    if((*juego).niveles[(*juego).nivel_actual-1].tiene_guardian == true){
        if((*juego).niveles[(*juego).nivel_actual-1].guardian.codigo== BASILISCO && (*juego).niveles[(*juego).nivel_actual-1].basilisco_destruido==false){
            matar_basilisco(juego);
        }if((*juego).niveles[(*juego).nivel_actual-1].guardian.codigo== DUENDE){
            chocar_guardian(juego, TURNOS_PERDIDOS_POR_DUENDE);
        }if((*juego).niveles[(*juego).nivel_actual-1].guardian.codigo== DOLORES)
            chocar_guardian(juego, TURNOS_PERDIDOS_POR_DOLORES);

    }if(misma_posicion((*juego).jugador.posicion,(*juego).niveles[(*juego).nivel_actual-1].horrocrux) && (*juego).niveles[(*juego).nivel_actual-1].horrocrux_destruido== false){
        if((*juego).nivel_actual==1)
            destruir_anillo(juego);
        if((*juego).nivel_actual==2)
            destruir_diario(juego);
        if((*juego).nivel_actual==3)
            destruir_copa(juego);
        if((*juego).nivel_actual== 4)
            destruir_guardapelo(juego);
    }
    pasar_nivel(juego);

}
/* * Precondiciones:  Recibe el estado del juego valido y una direccion hacia la derecha de movimiento.
   * Postcondiciones: Actualiza la posicion del jugador, asi como todos los valores que son modificados producto del movimiento del jugador */
void moverse_derecha(juego_t* juego, char direccion){
    (*juego).jugador.posicion.columna++;
    accion_de_moverse(juego);
}
/* * Precondiciones:  Recibe el estado del juego valido y una direccion hacia arriba de movimiento.
   * Postcondiciones: Actualiza la posicion del jugador, */
void moverse_arriba(juego_t* juego, char direccion){
    (*juego).jugador.posicion.fila--;
    accion_de_moverse(juego);
}
/* * Precondiciones:  Recibe el estado del juego valido y una direccion hacia abajo de movimiento.
   * Postcondiciones: Actualiza la posicion del jugador, asi como todos los valores que son modificados producto del movimiento del jugador */
void moverse_abajo(juego_t* juego, char direccion){
    (*juego).jugador.posicion.fila++;
    accion_de_moverse(juego);
}
/* * Precondiciones:  Recibe el estado del juego valido y una direccion hacia la izquierda de movimiento.
   * Postcondiciones: Actualiza la posicion del jugador, asi como todos los valores que son modificados producto del movimiento del jugador */
void moverse_izquierda(juego_t* juego, char direccion){
    (*juego).jugador.posicion.columna--;
    accion_de_moverse(juego);

}
void mover_jugador(juego_t* juego, char direccion) {
    if((*juego).jugador.envenenado){
        if((*juego).jugador.turnos_envenenado < MAX_TURNOS_ENVENENADO){
            if(tiene_item(juego, CURA, CURAS_NECESARIAS)){
                usar_item(juego,CURA);
                (*juego).jugador.envenenado=false;
                (*juego).jugador.turnos_envenenado=0;
            }else{
                (*juego).jugador.turnos_envenenado++;

            }
        }
        else{
            printf("UPS! MORISTE ENVENENADO\n");
            (*juego).estado = PERDIDO;}

    }
    if (tiene_turnos(juego)){
        if(direccion == DERECHA)
            moverse_derecha(juego, direccion);
        else if(direccion ==ARRIBA)
            moverse_arriba(juego, direccion);
        else if(direccion == ABAJO)
            moverse_abajo(juego, direccion);
        else if(direccion == IZQUIERDA)
            moverse_izquierda(juego, direccion);
    }else{
        printf("UPS!TE HAS QUEDADO SIN TURNOS PARA JUGAR!\n");
        (*juego).estado = PERDIDO;
    }


}

int estado_juego(juego_t juego){
    return((juego).estado);
}

coordenadas_t posicion_aleatoria(unsigned int filas, unsigned int columnas){
  unsigned int fila = (unsigned int)rand()%(filas-1);
  unsigned int col = (unsigned int)rand()%(columnas-1);
  coordenadas_t coordenada;
  coordenada.fila = fila;
  coordenada.columna = col;
  return coordenada;
}
