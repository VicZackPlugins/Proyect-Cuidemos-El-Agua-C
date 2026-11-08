#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ======= CONFIGURACION: ======== //

#define DIAS_SEMANA 7
#define MAX_DATOS 10

FILE *datos;        // Datos guardados
FILE *temp;         // Archivo temporal para modificar datos

char nombre_datos[] = "datos.txt";
char nombre_temp[] = "temp.txt";

// data_base = fopen("db.txt", r); READ
// data_base = fopen("db.txt", w); WRITTE
// data_base = fopen("db.txt", a); APPEND
// fclose(file)

// ========= FUNCIONES: ========== //

void limpiar_pantalla();
void mostrarMenu();
void iniciarArreglos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void cargarDatosArchivos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
int Buscar_Hogar(char nombre_hogar[32]);

int obtener_datos();
void actualizar_cantidad_datos(int cantidad);

int main() {
    
    char nombre[MAX_DATOS][32];                  // Nombre de los hogares

    int personas[MAX_DATOS],                     // Cantidad de personas por hogar
        hogares_cant[MAX_DATOS];                 // Cantidad de hogares a evaluar

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

                ConfigurarElementos(nombre, personas, limiteDiario, consumoLitros);

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

}

// ========= J U A N J O S E ========= //

/*          >> Configurar Elementos
            >> Buscar_Hogar
            >> 
*/ 

int Buscar_Hogar(char nombre_hogar[32])
{
    datos = fopen(nombre_datos, "r"); // abrimos el archivo con los datos en forma "read"

    int cantidad_datos = obtener_datos(); /// llamamos a la funcion obtener datos para
    // obtener la cantidad de los datos disponibles
    /// Creamos archivos temporales que nos serviran para 
    /// identificar el hogar que estamos buscando segun
    /// sus valores

    char nombre_temp[32];
    int personas_temp;
    float Consumo_Litros_Temp;

    for (int i=0; i< (cantidad_datos+1); i++) 

    //// Sumamos +1 a cantidad de datos para
    //// poder leer las lineas necesarias, ya que si no lo hacemos, se leera una linea menos 
    //// de la que nos interesa

    {
        if(i==0)
        {
            continue; /// ignoramos la primera linea
        }

        fscanf(datos, "%s %d %f", nombre_temp, personas_temp, Consumo_Litros_Temp);

        /// leemos los datos con los valores de las variables temporales para verificar
        /// si los elementos almacenados coinciden, es decir, que existan dentro de los
        /// datos almacenados con los mismos nombres de las variables temporales

        if(nombre_hogar == nombre_temp) 

        /// si el nombre del hogar coincide con el temporal
        /// significa que existe

        {
            fclose(datos); 

            //// cerramos el archivo en el que se almacenan los datos
            /// para evitar errores

            return 1;
        }
    }

    fclose(datos);
    return 0;

    //// cerramos el archivo en el que se almacenan los datos
    /// para evitar errores
    
}

void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) 
{
    //// inicializamos los elementos para que tengan un valor 
    
    int cantidad_datos = 0;

    printf("========= Configuracion =========\n");

    printf("Ingresa que dato quieres configurar\n");

    printf("Nombre del hogar\n >> "); //// Nombre del hogar a evaluar
    scanf("%s", nombre[cantidad_datos]);

    printf("Cantidad Personas\n >> "); //// cantidad de personas en un hogar
    scanf("%d", personas[cantidad_datos]);

    printf("Limite diario maximo\n >> "); //// Limite diario maximo para este hogar
    scanf("%f", limiteDiario[cantidad_datos]);

    for(int i=0; i<DIAS_SEMANA; i++) {
        consumoLitros[cantidad_datos][i]=0;
    } 
}

void Registrar_Datos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    char input_usuario[32];
    int index_hogar;

    do {

        scanf("%s", input_usuario);

        index_hogar = Buscar_Hogar(input_usuario);

        if (index_hogar  == 0) {
            printf("El elemento no existe. Ingrese otro porfavor\n>> ");
        }

    } while (index_hogar == 0);

    // SCANF PIDIENDO EL DIA DE LA SEMANA
    int input_dia;
    scanf("%d", input_dia);
    // APLICAR VERIFICACIONES ENTRE 1 a 7

    // SCANF PIDIENDO EL VALOR DE ESE DIA
    int input_valor;
    scanf("%d", input_valor);
    // APLICAR VERIFICACIONES HASTA 5000

    consumoLitros[index_hogar][input_dia - 1] = input_valor;
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