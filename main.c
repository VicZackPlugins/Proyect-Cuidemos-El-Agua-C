#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
====== PROGRESO ACTUAL =======

    === JUAN JOSEXO === :

        QUE ESTA HECHO:

            >> Configurar Elementos         -- se supone que isto, faltan arreglos
            >> Buscar_Hogar                 -- se supone que isto, faltan arreglos

        QUE FALTA POR HACER:

    === VISHO === :

        QUE ESTA HECHO:

            >>
            >> 

        QUE FALTA POR HACER:

            >>
            >> 


    === ELIAS === : 

        QUE ESTA HECHO:

            >> 
            >>

        QUE FALTA POR HACER:

            >>
            >> 

*/




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
void guardarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
int Buscar_Hogar(char nombre_hogar[32]);

int obtener_datos();
int aumentar_cantidad_datos();
void ods_info();

int main() {
    
    char nombre[MAX_DATOS][32];                  // Nombre de los hogares

    int personas[MAX_DATOS];                     // Cantidad de personas por hogar

    float limiteDiario[MAX_DATOS],               // Promedio litros a la semana por hogar
          consumoLitros[MAX_DATOS][DIAS_SEMANA]; // Consumo de litros por hogar por día

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

                cantidadDatos = 3;
                
                for (int i = 0; i < cantidadDatos; i++) {
                    strcpy(nombre[i], "NOMBRE");
                    personas[i] = 20;
                    limiteDiario[i] = 5.5;

                    for (int v = 0; v < DIAS_SEMANA; v++) {
                        consumoLitros[i][v] = 0.5;
                    }
                }

                guardarDatos(nombre, personas, limiteDiario, consumoLitros);

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

void guardarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) {

    datos = fopen(nombre_datos, "w");

    fprintf(datos, "%d\n", cantidadDatos);

    for(int i = 0; i < cantidadDatos; i++) {
        fprintf(datos, "%s %d %f\n", nombre[i], personas[i], limiteDiario[i]);
    }

    for(int i = 0; i < cantidadDatos; i++){
        
        for(int v = 0; v < DIAS_SEMANA; v++) {
            if (v < DIAS_SEMANA - 1) {

                fprintf(datos, "%f ", consumoLitros[i][v]);

            } else if (i != cantidadDatos - 1 && v == DIAS_SEMANA - 1) {

                fprintf(datos, "%f\n", consumoLitros[i][v]);

            } else if (i == cantidadDatos - 1 && v == DIAS_SEMANA - 1) {
                
                fprintf(datos, "%f", consumoLitros[i][v]); 
            
            }
        }

    }

    fclose(datos);

}

// ========= J U A N J O S E ========= //

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

    for (int i=-1; i< (cantidad_datos); i++) 

    //// Sumamos +1 a cantidad de datos para
    //// poder leer las lineas necesarias, ya que si no lo hacemos, se leera una linea menos 
    //// de la que nos interesa

    {
        if(i==-1)
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

            return i;
        }
    }

    fclose(datos);
    return -1;

    //// cerramos el archivo en el que se almacenan los datos
    /// para evitar errores
    
}

void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) 
{
    //// inicializamos los elementos para que tengan un valor 

    char temp_nombre_hogar[32];


    printf("========= Configuracion =========\n");

    printf("Ingresa que dato quieres configurar\n");
    int resultado_busqueda;
    do
    {
        printf("Nombre del hogar\n >> "); //// Nombre del hogar a evaluar
        scanf("%s", temp_nombre_hogar); //// escaneamos la temporal para comparar caracteres
        resultado_busqueda = Buscar_Hogar(temp_nombre_hogar);   /// si el resultado de busqueda no coincide con el nombre de un hogar existente
                                                                /// volvemos a preguntar
        if (resultado_busqueda != -1)
        {
            printf("TU WEA NO EXISTE");
        }

    }while(resultado_busqueda != -1);   /// repetir mientras no hayan resultados coincidente

    int cantidad_datos = aumentar_cantidad_datos();     /// inicializamos la cantidad de datos como local para poder utilizarla

    strcpy(nombre[cantidad_datos-1], temp_nombre_hogarl);   //// pasamos el valor de la funcion original a cantidad de datos

    printf("Cantidad Personas\n >> "); //// cantidad de personas en un hogar
    scanf("%d", personas[cantidad_datos]);

    printf("Limite diario maximo\n >> "); //// Limite diario maximo para este hogar
    scanf("%f", limiteDiario[cantidad_datos]);

    /// los valores ingresados se traspasan a cantidad de datos para ser almacenados

    for(int i=0; i<DIAS_SEMANA; i++) {
        consumoLitros[cantidad_datos][i]=0;
    } 
}

void Registrar_Datos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    char input_usuario[32];

    /// establecemos la cantidad de uso diario para un hogar especifico

    /// primero buscar que el hogar exista...

    char temp_nombre_hogar[32];

    int resultado_busqueda;
    do
    {
        printf("Nombre del hogar\n >> "); //// Nombre del hogar para editar
        scanf("%s", temp_nombre_hogar); //// ingresamos el nombre del hogar (TIENE que existir, si no, se repite la pregunta)
        resultado_busqueda = Buscar_Hogar(temp_nombre_hogar);   /// si el resultado de busqueda no coincide con el nombre de un hogar existente
                                                                /// volvemos a preguntar
        if (resultado_busqueda != -1)
        {
            printf("TU WEA NO EXISTE");
        }

    }while(resultado_busqueda != -1);

    
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

int aumentar_cantidad_datos() {
    return cantidadDatos += 1;
}
void aumentar_cantidad_datos() {
    cantidadDatos += 1;
}
<<<<<<< HEAD
=======
void ods_info(){
printf("=====ODS 6: Agua Limpia y Saneamiento=====\n");
printf("\n");
printf("Mas de medio millon de personas no acceso a agua potable segura\n");
printf("a su ves el problema del saneamiento en las casas como retretes en\n");
printf("malas condiciones a su vez con las aguas residuales  que generamos son\n");
printf("el causante de degradar el ecosistema y el mayor problema un grave deficit\n"); 
printf("de financiamiento y gestion ineficiente de las cuencas y redes hidricas\n");
printf("con brechas muy marcadas entre las zonas urbanas y rurales\n");
printf("\n");
printf("Ayuda a garantizar la disponibilidad y la gestion sostenible del agua y los servicios de saneamiento para todas las personas\n");
}
>>>>>>> c8a309eb2ae73c10fbba6152159bd002e1d62c46

