#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ======= Configuracion: ======== //

#define DIAS_SEMANA 7
#define TAM_FIJO 5

// =============== //

int main() {

    char nombre[][32];                  // Nombre de los hogares

    int personas[],                     // Cantidad de personas por hogar
        limitediario[],                 // Promedio litros a la semana por hogar
        consumoLitros[][DIAS_SEMANA];   // Consumo de litros por hogar por día

    int opciones;                       // Ingreso de una opcion
    
    do {

        printf("[1] Regitrar Datos\n[2] Modificar Dato\n[3] Detectar Excesos\n[4] Estadisticas");
        
        scanf("%d", &opciones);

        swith(opciones) {
            
            case 0: {
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
                printf("[ERROR] Debe usar una opcion valida.");
            }

        }

    } while (1);


    return 0;

}
void registrarDatos(char nombre[][32], int personas[], int csumoLitros[][DIAS_SEMANA]) { //aqui se debe arreglar
    int cant, litros;//cantidad y litros
    char nom;//nombre
    printf("ingrese nombre del hogar\n");
     scanf("%d",&nom);
    printf("cantidad de ocupantes de la vivienda\n");
     scanf("%d",&cant);
     printf("consumo de litros\n");
     scanf("%d",&litros);
}
