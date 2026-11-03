#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ======= Configuracion: ======== //

#define DIAS_SEMANA 7
#define TAM_FIJO 5

// =============== //

int main() {
    FILE *data_base;
    /*
        data_base = fopen("db", r); READ
        data_base = fopen("db", w); WRITTE
        data_base = fopen("db", a); APPEND
    */
    char nombre[][32];                  // Nombre de los hogares

    int personas[],                     // Cantidad de personas por hogar
        limitediario[],                 // Promedio litros a la semana por hogar
        consumoLitros[][DIAS_SEMANA];   // Consumo de litros por hogar por día

    int opciones;                       // Ingreso de una opcion
    
    do {

        printf("\t[PROYECTO] CUIDEMOS EL AGUA\n\n");
        printf("\t[1] Regitrar Datos\n\t[2] Modificar Dato\n\t[3] Detectar Excesos\n\t[4] Estadisticas\n\t[0] Salir\n");
        
        scanf("%d", &opciones);

        switch(opciones) {
            
            case 0: {
                return 0;
                break;
            }
            case 1: {
                // Registrar Datos 
                break;
            }
            case 2: {
                // Modificar Dato
                break;
            }
            case 3: {
                // Detectar excesos
                break;
            }
            case 4: {
                // Estadisticas
                break;
            }
            default: {
                printf("[ERROR] Debe ingresar una opcion valida.\n");
            }

        }

    } while (1);


    return 0;

}
void registrarDatos(char nombre[][32], int personas[], int consumoLitros[][DIAS_SEMANA])
{                     // aqui se debe arreglar
    int cant, litros; // cantidad y litros
    char nom;         // nombre
    printf("ingrese nombre del hogar\n");
    scanf("%d", &nom);
    printf("cantidad de ocupantes de la vivienda\n");
    do
    {
        scanf("%d", &cant);

        if (1 < cant && cant < 20)
        {
            printf("ERROR,datos duera de los parametros");
        }

    } while (1 < cant && cant < 20);

    printf("consumo de litros\n");
    do
    {
        scanf("%d", &litros);

        if (litros < 20)
        {
            printf("ERROR,datos duera de los parametros");
        }

    } while (litros < 5000);
}
