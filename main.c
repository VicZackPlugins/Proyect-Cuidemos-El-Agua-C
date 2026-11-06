#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ======= CONFIGURACION: ======== //

#define DIAS_SEMANA 7
#define MAX_DATOS 10
#define HOGAR 3

FILE *vectores;     // Filas y Columna de datos de los vectores
FILE *matriz;       // Filas y Columna de datos de la matriz
FILE *temp;         // Archivo temporal para modificar datos
FILE *datos;        // Guardar el nro de filas de los arreglos

char nombre_vectores[] = "vectores.txt";
char nombre_matriz[] = "matriz.txt";
char nombre_temp[] = "temp.txt";
char nombre_datos[] = "nro_datos.txt";

// data_base = fopen("db.txt", r); READ
// data_base = fopen("db.txt", w); WRITTE
// data_base = fopen("db.txt", a); APPEND
// fclose(file)

// ========= FUNCIONES: ========== //

void limpiar_pantalla();
void mostrarMenu();
void iniciarArreglos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void cargarDatosArchivos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float consumoLitros[HOGAR][DIAS_SEMANA]);
void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[HOGAR]);

int obtener_datos();
void actualizar_cantidad_datos(int cantidad);

int main() {
    
    char nombre[MAX_DATOS][32];                  // Nombre de los hogares

    int personas[MAX_DATOS];                     // Cantidad de personas por hogar

    float limiteDiario[MAX_DATOS],               // Promedio litros a la semana por hogar
          consumoLitros[MAX_DATOS][DIAS_SEMANA]; // Consumo de litros por hogar por día

    // Iniciar arreglos con valores por defecto (0 o "")
    iniciarArreglos(nombre, personas, limiteDiario, consumoLitros);

    int opciones;                                // Ingreso de una opcion
    
    limpiar_pantalla();
    
    cargarDatosArchivos(nombre, personas, limiteDiario, consumoLitros);
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
                limpiar_pantalla();
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
    printf("   CUIDEMOS EL AGUA - ODS N 6\n");
    printf("==========================================\n");
    printf(" 1. ¿Que ODS aborda este programa? \n 2. Configurar elementos \n 3. Registrar datos \n 4. Modificar un dato\n");
    printf(" 5. [Operacion principal del proyecto] \n 6. Ver tabla de datos \n 7. Ver estadisticas \n 8. Guardar datos\n");
    printf(" 9. Ayuda y Acerca de \n 0. Salir \n");
    printf("==========================================\n");
    printf("Elija una opcion: ");
}

void iniciarArreglos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) {

    for (int i = 0; i < MAX_DATOS; i++) {
        strcpy(nombre[i], "");
        personas[i] = 0;
        limiteDiario[i] = 0;

        for (int v = 0; v < DIAS_SEMANA; v++) {
            consumoLitros[i][v] = 0;
        }
    }

}

void cargarDatosArchivos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) {
    
    char nombre_temp[32];
    int personas_temp;
    float limD_temp, conL_temp;

    vectores = fopen(nombre_vectores, "r");
    if (vectores == NULL) {
        printf("[AVISO] No hay datos guardados, se inicia vacio.\n");

        vectores = fopen(nombre_vectores, "w"); fclose(vectores);
        matriz = fopen(nombre_matriz, "w"); fclose(matriz);

        actualizar_cantidad_datos(-(obtener_datos()));

        return;
    }

    if (obtener_datos() == 0) { 
        printf("[AVISO] No hay datos guardados, se inicia vacio.\n");
        return;
    }
    
    matriz = fopen(nombre_matriz, "r");

    for (int i = 0; i < obtener_datos(); i++) {
        fscanf(vectores, "%s %d %f", nombre_temp, &personas_temp, &limD_temp);

        strcpy(nombre[i], nombre_temp);
        personas[i] = personas_temp;
        limiteDiario[i] = limD_temp;

        for (int v = 0; v < DIAS_SEMANA; v++) {
            fscanf(matriz, "%f", &conL_temp);

            consumoLitros[i][v] = conL_temp;
        }
    }

    fclose(vectores); fclose(matriz);

    printf("[AVISO] Datos cargados correctamente.\n");
    /*
    DEBUG

    for (int i = 0; i < obtener_datos(); i++) {
        printf("%s %d %f ", nombre[i], personas[i], limiteDiario[i]);
        
        for (int v = 0; v < DIAS_SEMANA; v++) {
            printf("%f ", consumoLitros[i][v]);
        }
        printf("\n");
    }
    */
}

// ========= J U A N J O S E ========= //

void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[HOGAR]) {
    printf("========= Configuracion =========");

    // scanf("%d");
    // switch




}


void RegistrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float consumoLitros[HOGAR][DIAS_SEMANA]) {

    for(int i=0; i<HOGAR; i++)
    {
        printf("============ Hogar %d ============\n", i+1);
        printf("\n");
        for(int j=0; j<DIAS_SEMANA; j++)
        {
            do
            {
                printf("CONSUMO DIA %d : ", j+1);
                scanf("%f", &consumoLitros[i][j]);
                printf("\n");
                if (consumoLitros[i][j]>5000 || consumoLitros[i][j]<0)
                {
                    printf("ERROR: valor fuera de rango, intentalo denuevo\n");
                }
            } while(consumoLitros[i][j]>5000 || consumoLitros[i][j]<0);         
        }
    }


    /// REGISTRO DE DATOS POR PASO
    // 1: NOMBRE DEL HOGAR
    // 2: CANTIDAD DE PERSONAS
    // 3: LIMITE DIARIO



    // bitacora git:

}

// ============ E L I A S ============ //

int obtener_datos() {

    int cantidad_datos = 0;
    
    datos = fopen(nombre_datos, "r");
    if (datos == NULL) {
        return 0;
    }

    fscanf(datos, "%d", &cantidad_datos);

    fclose (datos);

    return cantidad_datos;
}

void actualizar_cantidad_datos(int cantidad) {

    int cantidad_datos_actuales = obtener_datos();
    int nueva_cantidad = cantidad_datos_actuales + cantidad;

    datos=fopen(nombre_datos, "w");
    fprintf(datos, "%d", nueva_cantidad);

    fclose(datos);
}
