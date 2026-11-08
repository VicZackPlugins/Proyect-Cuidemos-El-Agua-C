#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// ======= CONFIGURACION: ======== //

#define DIAS_SEMANA 7
#define MAX_DATOS 10

FILE *datos;        // Datos guardados

char nombre_datos[] = "datos.txt";

// datos = fopen("db.txt", r); READ
// datos = fopen("db.txt", w); WRITTE
// datos = fopen("db.txt", a); APPEND
// fclose(file)

int cantidadDatos = 0;

// ========= FUNCIONES: ========== //

void limpiar_pantalla();
void mostrarMenu();
void iniciarArreglos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void cargarDatosArchivos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS]);

int obtener_datos();
void aumentar_cantidad_datos();

int main() {
    
    char nombre[MAX_DATOS][32];                  // Nombre de los MAX_DATOSes

    int personas[MAX_DATOS];                     // Cantidad de personas por MAX_DATOS                     

    float limiteDiario[MAX_DATOS],               // Promedio litros a la semana por MAX_DATOS
          consumoLitros[MAX_DATOS][DIAS_SEMANA]; // Consumo de litros por MAX_DATOS por día

    // Iniciar arreglos con valores por defecto (0 o "")
    iniciarArreglos(nombre, personas, limiteDiario, consumoLitros);
    cantidadDatos = obtener_datos();

    int opciones;                                // Ingreso de una opcion
    
    limpiar_pantalla();
    
    cargarDatosArchivos(nombre, personas, limiteDiario, consumoLitros);
    do {
        
        mostrarMenu();
        
        int s_op;                                // Variable para el scanf de opciones

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

                aumentar_cantidad_datos();

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

    datos = fopen(nombre_datos, "r");
    if (datos == NULL) {
        printf("[AVISO] No hay datos guardados, se inicia vacio.\n");

        fopen(nombre_datos, "w");
        if (datos != NULL) fclose(datos);

        return;
    }

    char buffer[128];

    int linea = 1, index = 0;

    while(fgets(buffer, sizeof(buffer), datos) != NULL) {
        if (linea == 1) {
            sscanf(buffer, "%d", &cantidadDatos);
            linea++;
            continue;
        }

        if (linea <= (cantidadDatos + 1)) {
            sscanf(buffer, "%s %d %f", nombre[index], &personas[index], &limiteDiario[index]);
            index++;
            linea++;

            if (index >= cantidadDatos) index = 0;

            continue;
        }

        if (linea > (cantidadDatos + 1)) {
            for (int i = 0; i < DIAS_SEMANA; i++) {
                sscanf(buffer, "%f", &consumoLitros[index][i]);
            }
            
            index++;
            linea++;
        }
    }

    fclose(datos);

    printf("[AVISO] Datos cargados correctamente.\n");

}

// CREAR FUNCION GUARDAR DATOS

// ========= J U A N J O S E ========= //

void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS]) {
    printf("========= Configuracion =========");

    // scanf("%d");
    // switch

}


void RegistrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) {

    for(int i=0; i<MAX_DATOS; i++)
    {
        printf("============ MAX_DATOS %d ============\n", i+1);
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
    // 1: NOMBRE DEL MAX_DATOS
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

void aumentar_cantidad_datos() {

    cantidadDatos += 1;
}


