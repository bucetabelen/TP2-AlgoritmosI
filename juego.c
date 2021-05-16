#include "horrocrux.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define JUGANDO 0

int main(){

    char escenario[MAX_FILAS][MAX_COLUMNAS];
    juego_t juego;
    char movimiento;
    srand((unsigned int) time(NULL));
    printf("**Destruyendo Horrocruxes***\n");
    inicializar_juego(&juego);
    actualizar_escenario(juego, escenario);
    mostrar_escenario(escenario, (juego).niveles[(juego).nivel_actual-1].filas, (juego).niveles[(juego).nivel_actual-1].columnas);

    while(estado_juego(juego) == JUGANDO && juego.jugador.turnos_restantes>0) {
        printf("NIVEL %i\n", (juego).nivel_actual );
        printf("TURNOS DISPONIBLES %i. ¡USALOS BIEN!\n",(juego).jugador.turnos_restantes );
        printf("EL HORROCRUX QUE DEBES DESTRUIR ES %c\n", (juego).niveles[(juego).nivel_actual-1].horrocrux.codigo );
        do{
            printf("       ↑\n");
            printf("       w\n");
            printf("   <-a s d →\n");
            printf("       ↓    ");
            printf("\n");
            printf("Movimiento: \n");
            scanf(" %c", &movimiento);
        }while(!puede_moverse_jugador(movimiento, juego));
        mover_jugador(&juego, movimiento);
        mover_guardian(&juego);
        actualizar_escenario(juego, escenario);
        mostrar_escenario(escenario, (juego).niveles[(juego).nivel_actual-1].filas, (juego).niveles[(juego).nivel_actual-1].columnas);
    }

  return 0;
}
