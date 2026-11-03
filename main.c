#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ======= CONFIGURACION: ======== //

#define DIAS_SEMANA 7
#define TAM_FIJO 5

FILE *data_base;
FILE *temp_db;

// data_base = fopen("db.txt", r); READ
// data_base = fopen("db.txt", w); WRITTE
// data_base = fopen("db.txt", a); APPEND

int filas_arreglo = 0;                          // Nro. de filas de los arreglos

// ========= FUNCIONES: ========== //
void registrarDatos(char nombre[TAM_FIJO][32], int personas[TAM_FIJO], int consumoLitros[TAM_FIJO][DIAS_SEMANA]);

int main() {
    
    char nombre[TAM_FIJO][32];                  // Nombre de los hogares

    int personas[TAM_FIJO],                     // Cantidad de personas por hogar
        limiteDiario[TAM_FIJO],                 // Promedio litros a la semana por hogar
        consumoLitros[TAM_FIJO][DIAS_SEMANA];   // Consumo de litros por hogar por día

    int opciones;                               // Ingreso de una opcion
    
    system("cls");                              // Limpiar pantalla
    do {
    
        printf("\n[PROYECTO] CUIDEMOS EL AGUA\n\n");
        printf("\t[1] Regitrar Datos\n\t[2] Modificar Dato\n\t[3] Detectar Excesos\n\t[4] Estadisticas\n\t[0] Salir\n\n>> ");
        
        scanf("%d", &opciones);

        switch(opciones) {
            
            case 0: {
                // ====== Cerrar Programa ====== //
                return 0;
                
                break;
            }
            case 1: {
                // ====== Registrar Datos ====== //
                system("cls");
                
                break;
            }
            case 2: {
                // ======= Modificar Dato ====== //
                system("cls");

                break;
            }
            case 3: {
                // ====== Detectar excesos ===== //
                system("cls");

                break;
            }
            case 4: {
                // ======== Estadisticas ======= //
                system("cls");

                break;
            }
            case 5: {
                // ========== T E S T ========== //
                system("cls");

                printf("FOR 1 (FILA)\n");
                for(int i=0; i<TAM_FIJO; i++)
                {
                    printf("FOR 2 (COLUMNA)\n");
                    for(int j=0; j<DIAS_SEMANA; j++)
                    {
                        printf("Escaneo consumo litros [%d][%d]\n", i, j);
                        scanf("%d", &consumoLitros[i][j]);
                    }
                }

                break;
            }
            default: {
                system("cls");
                printf("[ERROR] Debe ingresar una opcion valida.\n");
            }

        }

    } while (1);


    return 0;

}

void registrarDatos(char nombre[TAM_FIJO][32], int personas[TAM_FIJO], int consumoLitros[TAM_FIJO][DIAS_SEMANA]) 
{
    
    int cant,                               // Cantidad de personas
        litros;                             // Consumo de litros

    char nom[32];                           // Nombre del hogar

    printf("Ingrese el nombre del hogar:\n>> ");
    scanf("%s", nom);

    printf("Cantidad de ocupantes de la vivienda:\n>> ");
    do
    {
        scanf("%d", &cant);

        if (cant < 1 || cant > 20) // && Cambiado por || // (1 > cant && cant < 20) Cambiado por (cant < 1 || cant > 20)
        {
            printf("[ERROR] Datos fuera de los parametros.\n");
        }

    } while (cant < 1 || cant > 20); // && Cambiado por || // (1 > cant && cant < 20) Cambiado por (cant < 1 || cant > 20)

    printf("Consumo de litros del hogar:\n>> ");
    do
    {
        scanf("%d", &litros);

        if (litros > 5000) // 20 Cambiado por 5000 // (litros < 20) Cambiado por (litros > 5000)
        {
            printf("[ERROR] Datos fuera de los parametros.\n");
        }

    } while (litros > 5000); // (litros < 20) Cambiado por (litros > 5000)

    // INICIAR ESPACIO PARA AGREGAR DATOS AL db.txt
    // USAR fopen("db.txt", a) y fprintf()
    // PONER IF VERIFICANDO SI fopen("db.txt", a) ES NULL O NO
    // FINALMENTE USAR fclose(data_base);

}