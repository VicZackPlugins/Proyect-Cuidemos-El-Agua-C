#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

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

/* ===============================

          CONFIGURACIONES
                Y
        VARIABLES GLOBALES

=============================== */

#define DIAS_SEMANA 7               // COLUMNAS MAXIMAS DE LA MATRIZ
                                    // EN CASO DE MODIFICAR EL VALOR SE DEBE
                                    // MODIFICAR LA FUNCION cargarDatosArchivos()
                                    // Y SUS VALORES DE consumoLitros

#define MAX_DATOS 10                // VALOR MAXIMOS DE DATOS A GUARDAR EN LOS ARREGLOS
#define LIM_LITRO 5000              // LIMITE DE LITROS A GUARDAR EN LOS ARCHIVOS


#define MAX_BORDER 42               // LARGO MAXIMOS DE LOS BORDES DE TITULOS
#define CHAR_LINE '='               // CARACTER QUE SE USARA COMO BORDE DE TITULOS

#define CHAR_TABLE "─"              // CARACTER QUE SE USARA COMO LINEA HORIZONTAL 
                                    // DE LA TABLA DE DATOS

#define CHAR_SPACE ' '              // CARACTER QUE SE USARA COMO ESPACIO

FILE *datos;                        // REFERENCIA TIPO PUNTERO AL ARCHIVO QUE SE 
                                    // USARA PARA ALMACENAR LOS DATOS

char nombre_datos[] = "datos.txt";  // NOMBRE DEL ARCHIVO DONDE SE GUARDARAN LOS DATOS

// MODOS DE APERTURA DEL ARCHIVO DE DATOS:

// datos = fopen("datos.txt", r); READ
// datos = fopen("datos.txt", w); WRITTE
// datos = fopen("datos.txt", a); APPEND
// fclose(file)

int cantidadDatos = 0;              // CANTIDAD DE DATOS REGISTRADOS

/* ===============================

            FUNCIONES

=============================== */

void imprimirTitulo(char titulo[64]);
void imprimirSubtitulo(char subtitulo[64]);
void imprimirBorde();
void limpiarPantalla();
void volverAlMenu();
void mostrarMenu();
void iniciarArreglos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void cargarDatosArchivos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void guardarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
int Buscar_Hogar(char nombre_hogar[32], char nombre[MAX_DATOS][32]);

void Registrar_Datos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void Modificar_Un_Dato(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
int verificacion_exceso(int indice_casa, float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
int verificacion_fuga(int indice_casa, float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

int obtener_datos();
int aumentar_cantidad_datos();
void imprimir_espacios(int cantidad, int tipo);
void ods_info();
void ver_tabla(char nombre[MAX_DATOS][32], float consumo_litros[MAX_DATOS][DIAS_SEMANA]);
void cabecera_tabla(int maxNameLen);

/* ===============================

           FUNCION MAIN

=============================== */

int main() {

    // CORREGIR ERRORES DE CARACTERES RAROS EN LA CONSOLA
    SetConsoleOutputCP(65001);
    
    // VECTOR PARA LOS NOMBRES DE LOS HOGARES
    char nombre[MAX_DATOS][32];

    // VECTOR PARA LA CANTIDAD DE PERSONAS POR HOGAR
    int personas[MAX_DATOS];

    // VECTOR PARA LOS LITROS DIARIOS RECOMENDADOS POR HOGAR
    float limiteDiario[MAX_DATOS],
    
    // MATRIZ QUE ALMACENA LOS LITROS CONSUMIDOS POR DIA POR HOGAR
          consumoLitros[MAX_DATOS][DIAS_SEMANA];

    // INICIAR LOS ARREGLOS EN 0 o "" COMO VALORES POR DEFECTO
    iniciarArreglos(nombre, personas, limiteDiario, consumoLitros);
    cantidadDatos = obtener_datos();

    // VARIABLE PARA LEER LA ENTRADA DEL USUARIO
    int opciones;

    // LIMPIAR LA PANTALLA ANTES PARA NO ACUMULAR INFORMACION
    // Y TODO QUEDE MAS LEGIBLE
    limpiarPantalla();

    // CARGAMOS LOS DATOS DEL ARCHIVO A LOS ARREGLOS Y VARIABLES CORRESPONDIENTES
    cargarDatosArchivos(nombre, personas, limiteDiario, consumoLitros);

    do {
        
        // MOSTRAR EL MENU DE OPCIONES
        mostrarMenu();
        
        // LEER LA ENTRADA DEL USUARIO
        scanf("%d", &opciones);

        // LIMPIAR EL INGRESO DE LA TECLA ENTER
        fflush(stdin);
        
        switch(opciones) {
            
            case 0: {
                // --------------- //
                // CERRAR PROGRAMA //
                // --------------- //

                guardarDatos(nombre, personas, limiteDiario, consumoLitros);
                limpiarPantalla();

                return 0;
            }
            case 1: {
                // ------------------------------ //
                // ¿QUÉ ODS ABORDA ESTE PROGRAMA? //
                // ------------------------------ //
                
                limpiarPantalla();
                ods_info();

                break;
            }
            case 2: {
                // -------------------- //
                // CONFIGURAR ELEMENTOS //
                // -------------------- //
                
                limpiarPantalla();
                ConfigurarElementos(nombre, personas, limiteDiario, consumoLitros);

                break;
            }
            case 3: {
                // --------------- //
                // REGISTRAR DATOS //
                // --------------- //
                
                limpiarPantalla();
                Registrar_Datos(nombre, personas, limiteDiario, consumoLitros);
                
                break;
            }
            case 4: {
                // ----------------- //
                // MODIFICAR UN DATO //
                // ----------------- //

                limpiarPantalla();
                Modificar_Un_Dato(nombre, personas, limiteDiario, consumoLitros);

                break;
            }
            case 5: {
                // ------------------------ //
                // DETECTAR EXCESOS Y FUGAS //
                // ------------------------ //

                limpiarPantalla();

                break;
            }
            case 6: {
                // ------------------ //
                // VER TABLA DE DATOS //
                // ------------------ //

                limpiarPantalla();
                ver_tabla(nombre, consumoLitros);
                
                break;
            }
            case 7: {
                // ---------------- //
                // VER ESTADÍSTICAS //
                // ---------------- //

                limpiarPantalla();

                break;
            }
            case 8: {
                // ------------- //
                // GUARDAR DATOS //
                // ------------- //

                limpiarPantalla();

                guardarDatos(nombre, personas, limiteDiario, consumoLitros);
                printf("[AVISO] Datos guardados de manera satisfactoria.\n");

                break;
            }
            case 9: {
                // Ayuda y Acerca de
                limpiarPantalla();

                break;
            }
            case 10: {
                // ========== T E S T ========== //
                limpiarPantalla();

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
                limpiarPantalla();
                printf("[ERROR] Debe ingresar una opcion valida.\n");
            }

        }

    } while (1);


    return 0;

}

/* ===============================

            FUNCIONES

=============================== */


// ------------- //
// V I C E N T E //
// ------------- //


void imprimirTitulo(char titulo[64])
{

    int pos_texto = ((int)(MAX_BORDER / 2)) - ((int)(strlen(titulo) / 2));

    for (int i = 0; i < 3; i++) {
        
        for (int v = 0; v < MAX_BORDER; v++) {
            if (i == 1) {
                if (v < pos_texto) {
                    printf(" ");
                    continue;
                }
                else if (v == pos_texto) {
                    printf("%s", titulo);
                    break;
                }
            }

            printf("%c", CHAR_LINE);
        }

        printf("\n");
    }

}

void imprimirSubtitulo(char subtitulo[64]) {
    
    int pos_texto = ((int)(MAX_BORDER / 2)) - ((int)(strlen(subtitulo) / 2));

    for (int i = 0; i < MAX_BORDER; i++) {
        if (i < pos_texto) {
            printf(" ");
            continue;
        }
        else if (i == pos_texto) {
            printf("%s", subtitulo);
            break;
        }

        printf("%c", CHAR_LINE);
    }

    printf("\n");

}

void imprimirBorde() {
    for (int i = 0; i < MAX_BORDER; i++) {
        printf("%c", CHAR_LINE);
    }

    printf("\n");
}

void limpiarPantalla() {
    // FUNCION PARA LIMPIAR LA PANTALLA
    /*
        La funcion system("COMANDO") permite ejecutar un comando
        en la terminal, en este caso para Windows el comando es: cls

        ¿Por qué limpiar la pantalla?
        R: Lo que buscamos es no obstruir el flujo del programa
           con demasiada informacion en pantalla, debidoa  que sin esto
           siempre la informacion anterior se queda presente, haciendo 
           que visualmente se pierda el foco de las acciones a realizar.
    */

    system("cls");
}

void volverAlMenu() {
    // FUNCION PARA ESPERAR QUE EL USUARIO VUELVA AL MENU ANTERIOR
    /*
        No hay restricciones, puesto que no buscamos verdaderamente
        una entrada en especifico, simplemente queremos que el
        programa se frene para que los datos en pantalla queden pegados.
        Un ejemplo para el uso de esta funcion es en la opcion "Ver tabla de datos".
    */

    imprimirBorde();
    printf("\nPresione la tecla ENTER para volver...    ");

    /*
        Con fgets() podemos leer el teclado y detectar cualquier caracter
        incluyendo el ENTER, debido a que fgets() lee una linea hasta que
        detecta un salto de linea "\n" y exactamente la tecla ENTER
        equivale a un salto de linea en los caracteres, nos viene perfecto.

        fgets() recibe como parametros un string temporal (Buffer), 
        el tamaño del string temporal (se puede usar la funcion sizeof(ARREGLO), 
        para obtener el valor del arreglo o buffer sin necesidad de editar ambos
        valores) y como último parametro el archivo, o lugar de donde leera
        los datos, en este caso para leer el teclado se utiliza: stdin.
        
        fgets(char [buffer], int [tamaño buffer], FILE [archivo o sdtin]);
    */

    // DAR BUFFER DE UN TAMAÑO QUE NO PROVOQUE ERRORES
    char temp[128];

    // USAR fgets() PARA LEER EL TECLADO
    fgets(temp, sizeof(temp), stdin);
    limpiarPantalla();

}

void mostrarMenu() {
    // FUNCION PARA MOSTRAR EL MENU DE INICIO

    imprimirTitulo("CUIDEMOS EL AGUA - ODS N° 6");
    printf("\n 1. ¿Qué ODS aborda este programa? \n 2. Configurar elementos \n 3. Registrar datos \n 4. Modificar un dato\n");
    printf(" 5. Detectar excesos y fugas \n 6. Ver tabla de datos \n 7. Ver estadísticas \n 8. Guardar datos\n");
    printf(" 9. Ayuda y Acerca de \n 0. Salir \n\n");
    imprimirBorde();
    printf("Elija una opción: ");
}

void estadisticas(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) {

    float consumoTotalDeHogares = 0,
          consumoTotalHogarAnterior = 0,
          consumoTotalHogarActual = 0,
          consumoPromedioPersona = 0;

    int indexHogarMayorConsumo = 0;

    imprimirTitulo("ESTADÍSTICAS");

    for (int i = 0; i < cantidadDatos; i++) {
        
        for (int v = 0; v < DIAS_SEMANA; v++) {
            consumoTotalDeHogares += consumoLitros[i][v];
            
            consumoTotalHogarActual += consumoLitros[i][v];
        }

        if (consumoTotalHogarActual > consumoTotalHogarAnterior) {
            indexHogarMayorConsumo = i;
        }
        
        consumoTotalHogarAnterior = consumoTotalHogarActual;    
        consumoTotalHogarActual = 0;

    }

}

void iniciarArreglos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) {
    // FUNCION PARA INICIAR LOS ARREGLOS EN 0 O EN "" COMO VALORES POR DEFECTO
    /*
        En este caso particular se utiliza la funcion
        strcpy(STRING DESTINO, VALOR NUEVO), esta función es de 
        la librería <string.h> y sirve para copiar una cadena de texto
        y pegarla en una cadena definida previamente.
        
        Es esencial utilizarla para cambiar el valor de una cadena 
        de texto que este dentro de una matriz o vector, esto debido
        a que no es valido hacer por ejemplo:
        vector[0] = "Hola mundo"

    */

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
                sscanf(buffer, "%f %f %f %f %f %f %f", 
                    &consumoLitros[index][0], 
                    &consumoLitros[index][1], 
                    &consumoLitros[index][2], 
                    &consumoLitros[index][3], 
                    &consumoLitros[index][4],
                    &consumoLitros[index][5],
                    &consumoLitros[index][6]
                );
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

    for (int i = 0; i < cantidadDatos; i++) {
        fprintf(datos, "%s %d %f\n", nombre[i], personas[i], limiteDiario[i]);
    }

    for (int i = 0; i < cantidadDatos; i++){
        
        for (int v = 0; v < DIAS_SEMANA; v++) {
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


// --------------- //
// J U A N J O S E //
// --------------- //


int Buscar_Hogar(char nombre_hogar[32], char nombre[MAX_DATOS][32])
{
    for (int i=0; i< cantidadDatos; i++) 
    {
        if(strcmp(nombre_hogar, nombre[i]) == 0) 
        {
            return i;
        }
    }
    return -1;  
}

void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) 
{
    //// Archivos temporales que nos permitiran traspasar los valores de los datos
    /// almacenados para comparacion

    char temp_nombre_hogar[32];
    int temp_cantidad_personas;
    float temp_lim_diario;

    imprimirTitulo("CONFIGURAR ELEMENTO");
    imprimirSubtitulo("Ingrese los datos solicitados");
    printf("\n");

    //// Leer datos y responder ante restricciones
    int resultado_busqueda;
    do
    {
        printf("| Nombre del hogar: \n| >> "); //// Nombre del hogar a evaluar
        scanf("%s", temp_nombre_hogar); //// escaneamos la temporal para comparar caracteres
        fflush(stdin);
        resultado_busqueda = Buscar_Hogar(temp_nombre_hogar, nombre);   /// si el resultado de busqueda no coincide con el nombre de un hogar existente
                                                                /// volvemos a preguntar
        if (resultado_busqueda != -1)
        {
            limpiarPantalla();
            printf("[ERROR] Ya existe un elemento con este nombre.\n");
            printf("        Por favor ingrese los datos nuevamente.\n\n");
            imprimirTitulo("CONFIGURAR ELEMENTO");
            imprimirSubtitulo("Ingrese los datos solicitados");
            printf("\n");
        }

    }while(resultado_busqueda != -1);   /// repetir mientras no hayan resultados coincidente

    printf("\n| Cantidad Personas \n| >> "); //// cantidad de personas en un hogar
    scanf("%d", &temp_cantidad_personas);

    printf("\n| Limite diario maximo\n| >> "); //// Limite diario maximo para este hogar
    scanf("%f", &temp_lim_diario);

    int cantidad_datos = aumentar_cantidad_datos();     /// inicializamos la cantidad de datos como local para poder utilizarla
    int indice = cantidad_datos - 1;

    strcpy(nombre[indice], temp_nombre_hogar);   //// pasamos el valor de la funcion original a cantidad de datos
    personas[indice] = temp_cantidad_personas;
    limiteDiario[indice] = temp_lim_diario;

    /// los valores ingresados se traspasan a cantidad de datos para ser almacenados
    for(int i=0; i<DIAS_SEMANA; i++) {
        consumoLitros[cantidad_datos - 1][i]=0;
    }

    guardarDatos(nombre, personas, limiteDiario, consumoLitros);

    printf("[AVISO] Datos guardados con exito para el hogar %d\n", temp_nombre_hogar);
    limpiarPantalla();
}

void Registrar_Datos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    char temp_nombre_hogar[32];
    int dias_seleccion;
    int resultado_busqueda;
    int consumo_seleccion;

    imprimirTitulo("REGISTRAR DATOS");
    imprimirSubtitulo("Configura el limite diario para");
    imprimirSubtitulo("un hogar seleccioando");
    printf("\n");

    do
    {
        printf("Nombre del hogar\n >> "); //// Nombre del hogar para editar
        scanf("%s", temp_nombre_hogar); //// ingresamos el nombre del hogar (TIENE que existir, si no, se repite la pregunta)
        resultado_busqueda = Buscar_Hogar(temp_nombre_hogar, nombre);   /// si el resultado de busqueda no coincide con el nombre de un hogar existente
                                                                /// volvemos a preguntar
        if (resultado_busqueda == -1)
        {
            printf("[ERROR] Hogar de nombre [ %s ] no encontrado\n", temp_nombre_hogar);
            printf("Porfavor utilize un nombre relacionado con un hogar existente\n"); 
            printf("\n");
        }
        else if(resultado_busqueda != -1)
        {
            limpiarPantalla();
            imprimirTitulo("REGISTRAR DATOS");
            imprimirSubtitulo("Configura el limite diario para");
            imprimirSubtitulo("un hogar seleccioando");
            printf("\n");
            printf("[AVISO] Hogar existente encontrado\n");
            printf("Nombre: \"%s\"\n", temp_nombre_hogar);
            do 
            {
                printf("\nIngresa el dia de la semana que deseas configurar (de 1 hasta %d)\n", DIAS_SEMANA);
                printf("\n >> ");
                scanf("%d", &dias_seleccion);
                if(dias_seleccion>DIAS_SEMANA || dias_seleccion<1)
                {
                    printf("\n");
                    printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", DIAS_SEMANA);  
                }
                if(consumoLitros[resultado_busqueda][dias_seleccion]!=0)
                {
                    printf("\n");
                    printf("[ERROR] Este dia ya tiene un limite establecido (limite en el dia %d: %d)\n", dias_seleccion, consumoLitros[resultado_busqueda][dias_seleccion]);  
                }

            }while(dias_seleccion>DIAS_SEMANA || dias_seleccion<1 || consumoLitros[resultado_busqueda][dias_seleccion]!=0);
            do
            {
                printf("\nIngresa el consumo diario para este hogar en el dia %d (limite maximo: %d)", dias_seleccion, LIM_LITRO);
                printf("\n >> ");
                scanf("%d", &consumo_seleccion);
                if (consumo_seleccion>LIM_LITRO)
                {
                    printf("\n");
                    printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", LIM_LITRO);  
                }
            }while(consumo_seleccion>LIM_LITRO);
            consumoLitros[resultado_busqueda][dias_seleccion]= consumo_seleccion;
            limpiarPantalla();
            printf("[AVISO] Limite establecido a: %d  para el dia %d\n", consumo_seleccion, dias_seleccion);
            printf("[AVISO] Datos para el hogar: \"%s\" guardados con exito\n", temp_nombre_hogar);
            printf("D E B U G: Limite actual para hogar  \"%s\" en el dia %d es %0.f", temp_nombre_hogar, dias_seleccion, consumoLitros[resultado_busqueda][dias_seleccion]);
            consumo_seleccion=0;
            dias_seleccion=0;
            guardarDatos(nombre, personas, limiteDiario, consumoLitros);
            printf("\n" );
        }
    }while(resultado_busqueda == -1);
}

void Modificar_Un_Dato(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    char temp_nombre_hogar[32];
    int resultado_busqueda;
    int dias_seleccion;
    int consumo_seleccion;

    imprimirTitulo("MODIFICAR UN DATO");
    imprimirSubtitulo("Modifica un dato ya");
    imprimirSubtitulo("establecido para un hogar");
    printf("\n");
    do 
    {
        printf("Nombre del hogar\n >> "); //// Nombre del hogar para editar
        scanf("%s", temp_nombre_hogar); //// ingresamos el nombre del hogar (TIENE que existir, si no, se repite la pregunta)
        resultado_busqueda = Buscar_Hogar(temp_nombre_hogar, nombre);   /// si el resultado de busqueda no coincide con el nombre de un hogar existente
                                                                /// volvemos a preguntar
        if (resultado_busqueda == -1)
        {
            printf("[ERROR] Hogar de nombre [ %s ] no encontrado\n", temp_nombre_hogar);
            printf("Porfavor utilize un nombre relacionado con un hogar existente\n"); 
            printf("\n");
        }
        else if(resultado_busqueda != -1)
        {
            limpiarPantalla();
            imprimirTitulo("MODIFICAR UN DATO");
            imprimirSubtitulo("Modifica un dato ya establecido para un hogar");
            printf("\n");
            printf("[AVISO] Hogar existente encontrado\n");
            printf("Nombre: \"%s\"\n", temp_nombre_hogar); 
            do 
            {
                printf("\nIngresa el dia de la semana que deseas configurar (de 1 hasta %d)\n", DIAS_SEMANA);
                printf("\n >> ");
                scanf("%d", &dias_seleccion);
                if(dias_seleccion>DIAS_SEMANA || dias_seleccion<1)
                {
                    printf("\n");
                    printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", DIAS_SEMANA);  
                }
                if(consumoLitros[resultado_busqueda][dias_seleccion]==0)
                {
                    printf("\n");
                    printf("[ERROR] Este dia no tiene un limite asignado que cambiar\n");  
                }
            }while(dias_seleccion>DIAS_SEMANA || dias_seleccion<1 || consumoLitros[resultado_busqueda][dias_seleccion]==0);
            do
            {
                printf("\nRemplaza el consumo diario para este hogar en el dia %d (limite maximo: %d)", dias_seleccion, LIM_LITRO);
                printf("\nConsumo diario actual: %0.f", consumoLitros[resultado_busqueda][dias_seleccion]);
                printf("\n >> ");
                scanf("%d", &consumo_seleccion);
                if (consumo_seleccion>LIM_LITRO)
                {
                    printf("\n");
                    printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", LIM_LITRO);  
                }
            }while(consumo_seleccion>LIM_LITRO);
            consumoLitros[resultado_busqueda][dias_seleccion]= consumo_seleccion;
            limpiarPantalla();
            printf("[AVISO] Limite establecido a: %d  para el dia %d\n", consumo_seleccion, dias_seleccion);
            printf("[AVISO] Datos para el hogar: \"%s\" guardados con exito\n", temp_nombre_hogar);
            printf("D E B U G: Limite actual para hogar  \"%s\" en el dia %d es %0.f", temp_nombre_hogar, dias_seleccion, consumoLitros[resultado_busqueda][dias_seleccion]);
            consumo_seleccion=0;
            dias_seleccion=0;
            guardarDatos(nombre, personas, limiteDiario, consumoLitros);
            printf("\n" );
        }
    }while(resultado_busqueda == -1);
}


int verificacion_exceso(int indice_casa, float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{
    int dias_exceso=0;
    for(int i=0; i<DIAS_SEMANA; i++)
    {
        if(consumoLitros[indice_casa][i]>limiteDiario[indice_casa])
        {
            dias_exceso++;
        }
    }
    return dias_exceso;
}

int verificacion_fuga(int indice_casa, float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{
    
    int promedio_diario=0;
    
    for(int i=0; i<DIAS_SEMANA; i++)
    {
        promedio_diario+=consumoLitros[indice_casa][i];
    }

    promedio_diario/=DIAS_SEMANA;
    
    for(int i=0; i<DIAS_SEMANA; i++)
    {
        if(consumoLitros[indice_casa][i]>=promedio_diario*2);
        return 1;
    }
    return 0;
}
// --------- //
// E L I A S //
// --------- //

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

void imprimir_espacios(int cantidad, int tipo) {

    if (tipo == 1) {
        for (int i = 0; i < cantidad; i++) {
            printf("%c", CHAR_SPACE);
        }
        return;
    }

    if (tipo == 2) {
        for (int i = 0; i < cantidad; i++) {
            printf("%s", CHAR_TABLE);
        }
        return;
    }

}

void ods_info() {
    imprimirTitulo("ODS 6: Agua Limpia y Saneamiento");
    printf("\n");
    printf("Mas de medio millon de personas no tiene acceso a agua  potable\n");
    printf("segura a su ves el  problema del saneamiento, malas condiciones\n");
    printf("tambien aguas residuales; que se generan en casa en  los  baños\n");
    printf("es el causante de degradar el ecosistema y  el  mayor  problema\n");  
    printf("un grave deficit de financiamiento, como una  mala  gestion  de\n"); 
    printf("las redes hidricas en zonas rurales\n");
    printf("\n");
    printf("Ayuda a garantizar la disponibilidad y la gestion sostenible del agua \ny los servicios de saneamiento para todas las personas\n\n");

    volverAlMenu();

}

void ver_tabla(char nombre[MAX_DATOS][32], float consumo_litros[MAX_DATOS][DIAS_SEMANA]){

    float total_fila = 0;
    int maxNameLen = 0,
        log_num = 0,
        longitud_numero = 0;

    imprimirTitulo("TABLA DIAS ");
    printf("\n");

    for (int i = 0; i < cantidadDatos; i++) {
        
        if (strlen(nombre[i]) > maxNameLen) {
            maxNameLen = strlen(nombre[i]);
        }

    }

    cabecera_tabla(maxNameLen);

    for (int i = 0; i < cantidadDatos; i++)
    {
        
        printf("%s ", nombre[i]);
        
        imprimir_espacios(maxNameLen - strlen(nombre[i]), 1);
        
        for (int j = 0; j < DIAS_SEMANA; j++)
        {
            if ((j+1) % 2 != 0) printf("│ ");

            printf("%.2f ", consumo_litros[i][j]);
            
            if (consumo_litros[i][j] == 0) log_num = 0;
            else log_num = log10(consumo_litros[i][j]);
            longitud_numero = round(log_num + 1);

            imprimir_espacios((4 - longitud_numero), 1);

            if ((j+1) % 2 != 0) printf("│ ");

            total_fila += consumo_litros[i][j];
            log_num = 0;
            longitud_numero = 0;
        }

        printf("%.2f", total_fila);
        
        if (total_fila == 0) log_num = 0;
        else log_num = log10(total_fila);
        longitud_numero = round(log_num + 1);
        
        imprimir_espacios((5 - longitud_numero), 1);

        printf(" │");

        total_fila = 0;

        printf("\n");
        imprimir_espacios((maxNameLen + 1), 2);
        
        if (i != (cantidadDatos - 1))
            printf("┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────────┤\n");
            
        else 
            printf("┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴──────────┘\n");

    }

    printf("\n");

    volverAlMenu();
}

void cabecera_tabla(int maxNameLen) {

    int espacios = maxNameLen + 1;

    imprimir_espacios(espacios, 1);

    printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬──────────┐\n");

    imprimir_espacios(espacios, 1);
    
    printf("│ DIA 1   │ DIA 2   │ DIA 3   │ DIA 4   │ DIA 5   │ DIA 6   │ DIA 7   │ TOTAL    │\n");

    imprimir_espacios(espacios, 2);

    printf("┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────────┤\n");

}