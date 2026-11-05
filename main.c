#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ======= CONFIGURACION: ======== //

#define DIAS_SEMANA 7
#define MAX_DATOS 10

FILE *data_base;    // Filas y Columna de datos
FILE *temp_db;      // Archivo temporal para modificar datos
FILE *datos;        // Guardar el nro de filas de los arreglos

char nombre_db[8] = "db.txt";
char nombre_temp[8] = "temp.txt";
char nombre_datos[8] = "datos.txt";

// data_base = fopen("db.txt", r); READ
// data_base = fopen("db.txt", w); WRITTE
// data_base = fopen("db.txt", a); APPEND
// fclose(file)

// ========= FUNCIONES: ========== //

void limpiar_pantalla();
void mostrarMenu();
void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], int consumoLitros[MAX_DATOS][DIAS_SEMANA]);

int main() {
    
    char nombre[MAX_DATOS][32];                  // Nombre de los hogares

    int personas[MAX_DATOS];                     // Cantidad de personas por hogar

    float limiteDiario[MAX_DATOS],               // Promedio litros a la semana por hogar
          consumoLitros[MAX_DATOS][DIAS_SEMANA]; // Consumo de litros por hogar por día

    int opciones;                                // Ingreso de una opcion
    
    limpiar_pantalla();
    do {
        
        mostrarMenu();
        
        int s_op;                               // Variable para el scanf de opciones

        while ((s_op = scanf("%d", &opciones)) != 1) {
            
            limpiar_pantalla();
            printf("[ERROR] Debe ingresar una opcion valida.\n");

            while (getchar() != '\n');
            
            mostrarMenu();
        }

        switch(opciones) {
            
            case 0: {
                // Cerrar Programa
                return 0;
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
                for(int i=0; i<MAX_DATOS; i++)
                {
                    printf("FOR 2 (COLUMNA)\n");
                    for(int j=0; j<DIAS_SEMANA; j++)
                    {
                        printf("Escaneo consumo litros [%.2f][%.2f]\n", i, j);
                        scanf("%f", &consumoLitros[i][j]);
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

// ========== V I C E N T E ========== //

void limpiar_pantalla() 
{
    system("cls");
}

void mostrarMenu() 
{
    printf("\n==========================================\n");
    printf("   [PROYECTO] CUIDEMOS EL AGUA - ODS Nro 6\n");
    printf("==========================================\n");
    printf(" 1. ¿Que ODS aborda este programa? \n 2. Configurar elementos \n 3. Registrar datos \n 4. Modificar un dato\n");
    printf(" 5. [Operacion principal del proyecto] \n 6. Ver tabla de datos \n 7. Ver estadisticas \n 8. Guardar datos\n");
    printf(" 9. Ayuda y Acerca de \n 0. Salir \n");
    printf("==========================================\n");
    printf("Elija una opcion: ");
}

// ========= J U A N J O S E ========= //

void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], int consumoLitros[MAX_DATOS][DIAS_SEMANA]) 
{
    for(int i=0; i<DIAS_SEMANA; i++)
    {
        for(int j=0; j<MAX_DATOS; j++)
        {
            
        }
    }

    // INICIAR ESPACIO PARA AGREGAR DATOS AL db.txt
    // USAR fopen("db.txt", a) y fprintf()
    // PONER IF VERIFICANDO SI fopen("db.txt", a) ES NULL O NO
    // FINALMENTE USAR fclose(data_base);

}

// ============ E L I A S ============ //