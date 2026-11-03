#include <stdio.h>
#include <string.h>
<<<<<<< HEAD

// ======= Configuracion: ======== //
=======
#include <stdlib.h>

// ======= Configuracion: ======== //

#define DIAS_SEMANA 7
#define TAM_FIJO 5

// =============== //
>>>>>>> 322effd30b5edc414640c77fe6cfd022e82f00b9

#define DIAS_SEMANA 7                                   /// Dias de la semana considerados para los calculos
#define TAM_FIJO 5                                      /// D E B U G 

// =============== //


<<<<<<< HEAD
int main()
{

    // ======= Configuracion: ======== //

    int tam_nombre;
    int tam_personas;
    int lim_MAX;
    int consumo_litros;

    // =============== //

    char nombre[tam_nombre][32];                        /// Nombre de los hogares
    int personas[tam_personas],                         /// Cantidad de personas por hogar
        limitediario[lim_MAX],                          /// Promedio litros a la semana por hogar
        consumolitros[TAM_FIJO][DIAS_SEMANA];           /// Consumo de litros por hogar por día

    // ======= T E S T ========== //

    /// escaneamos la matriz para obtener todos sus valores
    printf("PASO 1");
    for(int i=0; i<TAM_FIJO; i++)
    {
        printf("PASO 2");
        for(int j=0; j<DIAS_SEMANA; j++)
        {
            printf("escaneo consumo litroz [%d][%d]", i, j);
            scanf("%d", &consumolitros[i][j]);
        }
    }

    return 0;
}
=======
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
>>>>>>> 322effd30b5edc414640c77fe6cfd022e82f00b9
