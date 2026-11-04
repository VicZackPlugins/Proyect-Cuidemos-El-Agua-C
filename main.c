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
void limpiar_pantalla();
void mostrarMenu();
void registrarDatos(char nombre[TAM_FIJO][32], int personas[TAM_FIJO], int consumoLitros[TAM_FIJO][DIAS_SEMANA]);

int main() {
    
    char nombre[TAM_FIJO][32];                  // Nombre de los hogares

    int personas[TAM_FIJO],                     // Cantidad de personas por hogar
        limiteDiario[TAM_FIJO],                 // Promedio litros a la semana por hogar
        consumoLitros[TAM_FIJO][DIAS_SEMANA];   // Consumo de litros por hogar por día

    int opciones;                               // Ingreso de una opcion
    
    limpiar_pantalla();
    do {
        
        mostrarMenu();
        
        scanf("%d", &opciones);

        switch(opciones) {
            
            case 0: {
                // Cerrar Programa
                return 0;
                
                break;
            }
            case 1: {
                // ¿Que ODS aborda este programa?
                limpiar_pantalla();
                
                break;
            }
            case 2: {
                // Configurar elementos
                limpiar_pantalla();

                break;
            }
            case 3: {
                // Registrar datos
                limpiar_pantalla();

                break;
            }
            case 4: {
                // Modificar un dato
                limpiar_pantalla();

                break;
            }
            case 5: {
                // [Operación principal del proyecto]
                limpiar_pantalla();

                break;
            }
            case 6: {
                // Ver tabla de datos
                limpiar_pantalla();

                break;
            }
            case 7: {
                // Ver estadísticas
                limpiar_pantalla();

                break;
            }
            case 8: {
                // Guardar datos
                limpiar_pantalla();

                break;
            }
            case 9: {
                // Ayuda y Acerca de
                limpiar_pantalla();

                break;
            }
            case 10: {
                // ========== T E S T ========== //
                limpiar_pantalla();

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
                limpiar_pantalla();
                printf("[ERROR] Debe ingresar una opcion valida.\n");
            }

        }

    } while (1);


    return 0;

}

void limpiar_pantalla() 
{
    system("cls");
}

void mostrarMenu() 
{
    printf("\n==========================================\n");
    printf("   [PROYECTO] CUIDEMOS EL AGUA\n");
    printf("==========================================\n");
    printf(" 1. ¿Que ODS aborda este programa? \n 2. Configurar elementos \n 3. Registrar datos \n 4. Modificar un dato\n");
    printf(" 5. [Operacion principal del proyecto] \n 6. Ver tabla de datos \n 7. Ver estadisticas \n 8. Guardar datos\n");
    printf(" 9. Ayuda y Acerca de \n 0. Salir \n");
    printf("==========================================\n");
    printf("Elija una opcion: ");
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