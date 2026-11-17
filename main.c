#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

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
#define MAX_PERSONAS 20             // LIMITE MAXIMO DE PERSONAS POR HOGAR
#define MIN_PERSONAS 1              // LIMITE MINIMO DE PERSONAS


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

int CANTIDAD_DATOS = 0;              // CANTIDAD DE DATOS REGISTRADOS

/* ===============================

            FUNCIONES

=============================== */

// DECORACIONES VISUALES
void imprimirTitulo(char titulo[64]);
void imprimirSubtitulo(char subtitulo[64]);
void imprimirBorde();
void imprimirEspacios(int cantidad, int tipo);
void imprimirCabeceraTabla(int maxNameLen);

// UTILIDADES Y/O AUXILIARES
void limpiarPantalla();
void volverAlMenu();
void iniciarArreglos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void cargarDatosArchivos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
int verificacionExceso(int indice_casa, float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
int verificacionFuga(int indice_casa, float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
int obtenerDatos();
int aumentarCantidadDatos();
int buscarHogar(char nombre_hogar[32], char nombre[MAX_DATOS][32]);
int leerOpcionMenu();
int leerNumeroEntero();
float leerNumeroFlotante();

// PRINCIPALES
void mostrarMenu();
void mostrarODS();
void configurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void modificarDato(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void operacionPrincipal(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void mostrarTabla(char nombre[MAX_DATOS][32], float consumo_litros[MAX_DATOS][DIAS_SEMANA]);
void mostrarEstadisticas(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void guardarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void mostrarAyudaYAcercaDe();

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
    CANTIDAD_DATOS = obtenerDatos();

    // LIMPIAR LA PANTALLA ANTES PARA NO ACUMULAR INFORMACION
    // Y TODO QUEDE MAS LEGIBLE
    limpiarPantalla();

    // CARGAMOS LOS DATOS DEL ARCHIVO A LOS ARREGLOS Y VARIABLES CORRESPONDIENTES
    cargarDatosArchivos(nombre, personas, limiteDiario, consumoLitros);

    // VARIABLE PARA LEER LA ENTRADA DEL USUARIO
    int opciones;

    do {
        
        // MOSTRAR EL MENU DE OPCIONES
        mostrarMenu();
        
        // LEER LA ENTRADA DEL USUARIO
        opciones = leerOpcionMenu();
        
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
                mostrarODS();

                break;
            }
            case 2: {
                // -------------------- //
                // CONFIGURAR ELEMENTOS //
                // -------------------- //
                
                limpiarPantalla();
                configurarElementos(nombre, personas, limiteDiario, consumoLitros);

                break;
            }
            case 3: {
                // --------------- //
                // REGISTRAR DATOS //
                // --------------- //
                
                limpiarPantalla();
                registrarDatos(nombre, personas, limiteDiario, consumoLitros);
                
                break;
            }
            case 4: {
                // ----------------- //
                // MODIFICAR UN DATO //
                // ----------------- //

                limpiarPantalla();
                modificarDato(nombre, personas, limiteDiario, consumoLitros);

                break;
            }
            case 5: {
                // ------------------------ //
                // DETECTAR EXCESOS Y FUGAS //
                // ------------------------ //
                limpiarPantalla();
                operacionPrincipal(nombre, personas, limiteDiario, consumoLitros);

                break;
            }
            case 6: {
                // ------------------ //
                // VER TABLA DE DATOS //
                // ------------------ //

                limpiarPantalla();
                mostrarTabla(nombre, consumoLitros);
                
                break;
            }
            case 7: {
                // ---------------- //
                // VER ESTADÍSTICAS //
                // ---------------- //

                limpiarPantalla();
                mostrarEstadisticas(nombre, personas, limiteDiario, consumoLitros);

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
                mostrarAyudaYAcercaDe();

                break;
            }
            default: {
                limpiarPantalla();
                printf("[ERROR] Debe ingresar una opción válida.\n");
            }

        }

    } while (1);


    return 0;

}

/* ===============================

            FUNCIONES

=============================== */

// =====================
//
// DECORACIONES VISUALES
//
// =====================

void imprimirTitulo(char titulo[64])
{
    // FUNCION PARA IMPRIMIR TITULOS CON FORMATO AUTOMATIZADO Y CENTRADOS
    /*
        pos_texto = ((int)(MAX_BORDER / 2)) - ((int)(strlen(titulo) / 2));
        
        Esta variable lo que hace es calcular cuantos printf(" ") se deben
        ejecutar antes de imprimir el titulo, de esta forma se deja el titulo
        medianamente centrado.

        Lo que se hace es dividir por 2 el largo del lugar donde se imprimira
        el titulo

        LARGO BORDE: 10 ########## ==> 5 #####

        Luego se divide por 2 el largo del texto a introducir.

        LAGO TEXTO: 6 °°°°°° ==> 3 °°°

        Como tenemos ambas mitades, las consideramos como sus "Centros"
        y las restamos, hacer esto nos asegura que el texto quede centrado,
        en este caso la resta da 2, significa en se imprimira el titulo 
        luego de 2 printf(" "). Ejemplo visual:

        PRIMERA MITAD: ##°°°
        SEGUNDA MITAD: °°°##
        FINAL: ##°°°°°°##

        Y como se ve, el "texto" quedaria centrado en un largo de 10 caracteres.

    */

    int pos_texto = ((int)(MAX_BORDER / 2)) - ((int)(strlen(titulo) / 2));

    // BUCLE REPETIDO 3 VECES PARA HACER 3 FILAS
    for (int i = 0; i < 3; i++) {
        
        for (int v = 0; v < MAX_BORDER; v++) {
            // VERIFICAR SI ESTA EN LA LINEA CENTRAL PARA IMPRIMIR EL TITULO
            if (i == 1) {
                // SI NO ESTA EN LA POSICION CALCULADA, IMPRIMIR ESPACIOS
                if (v < pos_texto) {
                    printf(" ");
                    continue;
                }
                // SI ESTA EN LA POSICION CALCULADA, IMPRIMIR EL TITULO
                // Y SALTAR A LA SIGUENTE FILA
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
    // FUNCION PARA IMPRIMIR SUBTITULOS CENTRADOS

    // MISMA LOGICA QUE imprimirTitulo()
    // PERO EN UNA UNICA LINEA

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
    // IMPRIMIR BORDES DE LOS TITULOS

    // IMPRIMIR CARACTER POR CARACTER DE FORMA HORIZONTAL
    // PARA USAR EN imprimirTitulo()
    for (int i = 0; i < MAX_BORDER; i++) {
        printf("%c", CHAR_LINE);
    }

    printf("\n");
}

void imprimirEspacios(int cantidad, int tipo) {
    // FUNCION PARA IMPRIMIR ESPACIOS CON UN FORMATO EN ESPECIFICO
    /*
        Esta funcion tiene mas proposito para la funcion
        verTabla(), en donde se deben inprimir espacios para rellenar
        y mantener la estetica cuadrada de la tabla o "espacios" con
        diseño de linea.
    */


    // SI SE SELECCIONA EL TIPO 1 SE IMPRIME EL CARACTER DE ESPACIO
    if (tipo == 1) {
        for (int i = 0; i < cantidad; i++) {
            printf("%c", CHAR_SPACE);
        }
        return;
    }
    // SI SE SELECCIONA EL TIPO 2 SE IMPRIME EL CARACTER DE LINEA HORIZONTAL
    if (tipo == 2) {
        for (int i = 0; i < cantidad; i++) {
            // SE IMPRIME EL CARACTER ENTRE "" EN VEZ DE ''
            // DEBIDO A QUE SE USO CODIGO ASCII Y ESTE ALGUNAS VECES
            // SE DETECTA COMO "STRING" Y NO COMO CARACTER DEBIDO A SU TAMAÑO
            // EN BYTES
            printf("%s", CHAR_TABLE);
        }
        return;
    }

}

void imprimirCabeceraTabla(int maxNameLen) {
    // FUNCION PARA IMPRIMIR LA CABECERA DE LA TABLA DE DATOS

    int espacios = maxNameLen + 1;

    imprimirEspacios(espacios, 1);

    printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬──────────┐\n");

    imprimirEspacios(espacios, 1);
    
    printf("│ DÍA 1   │ DÍA 2   │ DÍA 3   │ DÍA 4   │ DÍA 5   │ DÍA 6   │ DÍA 7   │ TOTAL    │\n");

    imprimirEspacios(espacios, 2);

    printf("┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────────┤\n");

}

// =========================
//
// UTILIDADES Y/O AUXILIARES
//
// =========================

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
    // FUNCION PARA CARGAR LOS DATOS DEL ARCHIVO .TXT A LOS ARREGLOS Y VARIABLES CORRESPONDIENTES
    /*
        Se opto por el uso de fgets() combinado de sscanf() para leer
        los datos del archivo con menos posibilidad de error en comparacion
        al fscanf() el cual puede llegar a corromper el programa mas facilmente

        - Primero se utiliza el fgets(BUFFER, TAMAÑO DEL BUFFER, ARCHIVO) dentro
          de un bucle while mientras fgets() != NULL, estos nos asegura que se
          lean las lineas (Desde el primer caracter hasta detectar un salto de linea) 
          hasta el final del archivo (EOF).
        
        - Luego se utiliza sscanf(STRING, FORMATO, VARIBALE A GUARDAR) que lee
          la cadena de texto buffer[128] de manera formateada y guarda ese valor
          en una variable determinada.

        Adicionalmente se creo una variable auxiliar linea = 1 e index = 0, para
        hacer verificaciones y evitar errores de lectura en las lineas del archivo.
    */
    
    // ABRIR EL ARCHIVO
    datos = fopen(nombre_datos, "r");
    // VALIDAR SI EL ARCHIVO NO EXISTE O HUBO ERRORES AL ABRIRLO
    if (datos == NULL) {
        printf("[AVISO] No hay datos guardados, se inicia vacio.\n");

        // EN CASO DE ERROR O QUE NO EXISTIERA, LO CREAMOS
        fopen(nombre_datos, "w");
        if (datos != NULL) fclose(datos);

        return;
    }

    // DAMOS UN TAMAÑO DE BUFFER SUFICIENTE PARA QUE LEA TODA UNA LINEA ENTERA
    // USAMOS 128 DEBIDO A QUE LO MAXIMO QUE ALCANZARIA LA LINEA MAS LARGA SERIA APROX 96 CHARS
    char buffer[128];

    // DEFINIMOS VARIABLES AUXILIARES DE POSICION, CON ELLAS SABREMOS EN QUE LINEA 
    // NOS ENCONTRAMOS Y QUE INDICE LE CORRESPONDE A CADA VECTOR
    int linea = 1, index = 0;

    while(fgets(buffer, sizeof(buffer), datos) != NULL) {
        // SI ESTAMOS EN LA LINEA 1 LEEMOS LA CANTIDAD DE DATOS
        if (linea == 1) {
            sscanf(buffer, "%d", &CANTIDAD_DATOS);
            linea++;
            continue;
        }

        // SI ESTAMOS ENTRE LA LINEA 2 Y EL ULTIMO ELEMENTO (OJO: NO ULTIMA LINEA) EJ:
        /*
            1 | 2                           _
            2 | HOGAR_1 20 100.000000        |_______ LEEREMOS ESTAS LINEAS, LA 2 Y 3
            3 | HOGAR_2 12 3500.050049      _|
            4 | 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000
            5 | 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000
        
        */
        // LEEMOS EL FORMATO DEL ELEMENTO: NOMBRE DEL HOGAR - CANTIDAD DE PERSONAS - LIMITE DIARIO
        if (linea <= (CANTIDAD_DATOS + 1)) {
            sscanf(buffer, "%s %d %f", nombre[index], &personas[index], &limiteDiario[index]);
            index++;
            linea++;

            if (index >= CANTIDAD_DATOS) index = 0;

            continue;
        }

        // SI ESTAMOS ENTRE LAS LINEAS DE LAS MATRICES QUE CORRESPONDEN A LA CANTIDAD DE DATOS + 1 
        // Y LA ULTIMA LINEA EJ:
        /*
            1 | 2
            2 | HOGAR_1 20 100.000000
            3 | HOGAR_2 12 3500.050049                                          _
            4 | 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000   |_______ LEEREMOS ESTAS LINEAS, LA 4 Y 5
            5 | 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000  _|
        
        */
        // LEEMOS EL FORMATO DE LA FILA DE MATRIZ, QUE ES DEL DIA 1 AL DIA 7
        if (linea > (CANTIDAD_DATOS + 1)) {
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

int verificacionExceso(int indice_casa, float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    //// VERIFICACION EXCESO AGARRA UN HOGAR Y DIA Y VERIFICA SI SU CONSUMO DIARIO NO ES SUPERIOR A SU LIMITE ESTABLECIDO EN EL HOGAR

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

int verificacionFuga(int indice_casa, float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    ///// VERIFICACION FUGA AGARRA UN HOGAR Y, EN BASE A SI SUPERA EL DOBLE DEL PROMEDIO O NO, ESTABLECER SI EXISTE UNA FUGA
    
    int promedio_diario=0;
    
    for(int i=0; i<DIAS_SEMANA; i++)
    {
        promedio_diario+=consumoLitros[indice_casa][i];
    }

    promedio_diario/=DIAS_SEMANA;
    if(promedio_diario==0)
    {
        return 0;
    }
    
    for(int i=0; i<DIAS_SEMANA; i++)
    {
        if(consumoLitros[indice_casa][i]>promedio_diario*2)
        {
            return 1;
        }
    }
    return 0;
}

int obtenerDatos() {
    // FUNCION PARA OBTENER LA CANTIDAD DE DATOS DESDE EL ARCHIVO .TXT

    int cantidad_datos = 0;
    
    datos = fopen(nombre_datos, "r");
    if (datos == NULL) {
        return 0;
    }

    fscanf(datos, "%d", &cantidad_datos);

    fclose (datos);

    return cantidad_datos;
}

int aumentarCantidadDatos() {
    // FUNCION PARA AUMENTAR LA CANTIDAD DE DATOS DE LA VARIABLE GLOBAL CANTIDAD_DATOS

    return CANTIDAD_DATOS += 1;
}

int buscarHogar(char nombre_hogar[32], char nombre[MAX_DATOS][32])
{
    for (int i=0; i< CANTIDAD_DATOS; i++) 
    {
        if(strcmp(nombre_hogar, nombre[i]) == 0) 
        {
            return i;
        }
    }
    return -1;  
}

int leerOpcionMenu() {
    // FUNCION PARA LEER UNA OPCION DEL MENU VALIDA
    /*
        scanf() retorna el valor de 1 si leyo los datos de forma correcta,
        en caso de que se le ingrese un dato que sea distinto a lo esperado
        este retorna 0.

        Con este concepto se puede validar y evitar bucles infinitos al
        ingresar datos de tipos erroneos en una entrada donde por ejemplo
        se espera un entero.
    */

    int opcion;

    // VERIFICAR SI scanf() FALLA, DE SER ASI SE PIDE LA ENTRADA 
    // NUEVAMENTE Y SE IMPRIME UN MENSAJE DE ERROR
    while (scanf("%d", &opcion) != 1) {
        limpiarPantalla();
        printf("[ERROR] Debe ingresar una opción válida.\n");
        mostrarMenu();

        // LIMPIAR LA ENTRADA PARA LEER LA VARIABLE "LIMPIA"
        // SIN LA INFORMACION ANTERIOR
        while (getchar() != '\n');
    }
    
    // LIMPIAR EL INGRESO DE LA TECLA ENTER
    fflush(stdin);

    return opcion;

}

int leerNumeroEntero() {
    // FUNCION PARA LEER UN DATO TIPO ENTERO VALIDO
    /*
        scanf() retorna el valor de 1 si leyo los datos de forma correcta,
        en caso de que se le ingrese un dato que sea distinto a lo esperado
        este retorna 0.

        Con este concepto se puede validar y evitar bucles infinitos al
        ingresar datos de tipos erroneos en una entrada donde por ejemplo
        se espera un entero.
    */

    int numero;
    
    // VERIFICAR SI scanf() FALLA, DE SER ASI SE PIDE LA ENTRADA 
    // NUEVAMENTE Y SE IMPRIME UN MENSAJE DE ERROR
    while (scanf("%d", &numero) != 1) {
        printf("[ERROR] Debe ingresar una entrada válida.\n");
        printf("        Por favor ingrese el valor nuevamente.\n");
        printf(">> ");

        // LIMPIAR LA ENTRADA PARA LEER LA VARIABLE "LIMPIA"
        // SIN LA INFORMACION ANTERIOR
        while (getchar() != '\n');
    }

    // LIMPIAR EL INGRESO DE LA TECLA ENTER
    fflush(stdin);
    
    return numero;

}

float leerNumeroFlotante() {
    // FUNCION PARA LEER UN DATO TIPO FLOTANTE VALIDO
    /*
        scanf() retorna el valor de 1 si leyo los datos de forma correcta,
        en caso de que se le ingrese un dato que sea distinto a lo esperado
        este retorna 0.

        Con este concepto se puede validar y evitar bucles infinitos al
        ingresar datos de tipos erroneos en una entrada donde por ejemplo
        se espera un entero.
    */

    float numero;

    // VERIFICAR SI scanf() FALLA, DE SER ASI SE PIDE LA ENTRADA 
    // NUEVAMENTE Y SE IMPRIME UN MENSAJE DE ERROR
    while (scanf("%f", &numero) != 1) {
        printf("[ERROR] Debe ingresar una entrada válida.\n");
        printf("        Por favor ingrese el valor nuevamente.\n");
        printf(">> ");

        // LIMPIAR LA ENTRADA PARA LEER LA VARIABLE "LIMPIA"
        // SIN LA INFORMACION ANTERIOR
        while (getchar() != '\n');
    }
    
    // LIMPIAR EL INGRESO DE LA TECLA ENTER
    fflush(stdin);

    return numero;

}

// ===========
//
// PRINCIPALES
//
// ===========

void mostrarMenu() {
    // FUNCION PARA MOSTRAR EL MENU DE INICIO

    imprimirTitulo("CUIDEMOS EL AGUA - ODS N° 6");
    printf("\n 1. ¿Qué ODS aborda este programa? \n 2. Configurar elementos \n 3. Registrar datos \n 4. Modificar un dato\n");
    printf(" 5. Detectar excesos y fugas \n 6. Ver tabla de datos \n 7. Ver estadísticas \n 8. Guardar datos\n");
    printf(" 9. Ayuda y Acerca de \n 0. Salir \n\n");
    imprimirBorde();
    printf("Elija una opción: ");
}

void mostrarODS() {
    // FUNCION PARA MOSTRAR LA INFORMACION DEL ODS

    imprimirTitulo("ODS 6: Agua Limpia y Saneamiento");
    printf("\n");
    printf("Mas de medio millon de personas no tiene acceso a agua  potable\n");
    printf("segura a su ves el  problema del saneamiento, malas condiciones\n");
    printf("tambien aguas residuales, que se generan en casa en  los  baños\n");
    printf("es el causante de degradar el ecosistema y  el  mayor  problema\n");  
    printf("un grave deficit de financiamiento, como una  mala  gestion  de\n"); 
    printf("las redes hidricas en zonas rurales.\n");
    printf("\n");
    printf("¿Cómo este programa ayuda a esa meta?\n\n");
    printf("Ayuda a garantizar la disponibilidad y  la  gestion  sostenible\n");
    printf("del agua y servicios de saneamiento  para  todas  las  personas\n\n");

    volverAlMenu();

}

void configurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) 
{
    //// FUNCION PARA ESTABLECER VALORES EN UN HOGAR, PERSONAS Y CONSUMO QUE NO TENGAN EXISTENTES

    char temp_nombre_hogar[32];
    float temp_cantidad_personas;
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
        resultado_busqueda = buscarHogar(temp_nombre_hogar, nombre);   /// si el resultado de busqueda no coincide con el nombre de un hogar existente
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
    
    do
    {
        printf("\n| Limite diario maximo\n| >> "); //// Limite diario maximo para este hogar
        temp_lim_diario=leerNumeroFlotante();
        if (temp_lim_diario>LIM_LITRO)
        {
            printf("[ERROR] El consumo diario no puede exceder %d.\n", LIM_LITRO);  
        }

    }while(temp_lim_diario>LIM_LITRO);

    do
    {
        printf("\n| Cantidad de personas en el hogar\n| >> "); //// Personas por hogar
        temp_cantidad_personas=leerNumeroFlotante();
        if (temp_cantidad_personas>MAX_PERSONAS || temp_cantidad_personas<MIN_PERSONAS)
        {
            printf("[ERROR] Un hogar tiene que tener entre %d a %d personas.\n", MIN_PERSONAS, MAX_PERSONAS);  
        }

    }while(temp_cantidad_personas>MAX_PERSONAS || temp_cantidad_personas<MIN_PERSONAS);


    int cantidad_datos = aumentarCantidadDatos();     /// inicializamos la cantidad de datos como local para poder utilizarla
    int indice = cantidad_datos - 1;

    strcpy(nombre[indice], temp_nombre_hogar);   //// pasamos el valor de la funcion original a cantidad de datos
    personas[indice] = (int)round(temp_cantidad_personas);
    limiteDiario[indice] = temp_lim_diario;

    /// los valores ingresados se traspasan a cantidad de datos para ser almacenados
    for(int i=0; i<DIAS_SEMANA; i++) {
        consumoLitros[cantidad_datos - 1][i]=0;
    }
    limpiarPantalla();
    printf("[AVISO] Datos guardados con exito para el hogar %s\n", temp_nombre_hogar);
    guardarDatos(nombre, personas, limiteDiario, consumoLitros);
}



/////////// REGISTRAR DATOS


void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    /// FUNCION REGISTRAR DATOS PERMITE ESTABLECER EL CONSUMO DIARIO DE UN HOGAR

    char temp_nombre_hogar[32];
    float temp_dias_seleccion;
    int dias_seleccion;
    int resultado_busqueda;
    float consumo_seleccion;

    imprimirTitulo("REGISTRAR DATOS");
    imprimirSubtitulo("Configura el limite diario para");
    imprimirSubtitulo("un hogar seleccioando");
    printf("\n");
    printf("| Nombre del hogar\n >> "); //// Nombre del hogar para editar
    scanf("%s", temp_nombre_hogar); //// ingresamos el nombre del hogar (TIENE que existir, si no, se repite la pregunta)
    resultado_busqueda = buscarHogar(temp_nombre_hogar, nombre);   /// si el resultado de busqueda no coincide con el nombre de un hogar existente
                                                            /// volvemos a preguntar
    if (resultado_busqueda == -1)
    {
        printf("[ERROR] Hogar de nombre [ %s ] no fue encontrado\n", temp_nombre_hogar);
        printf("Crea el hogar para poder editar sus elementos\n"); 
        printf("\n");
    }
    else if(resultado_busqueda != -1)
    {
        limpiarPantalla();
        imprimirTitulo("REGISTRAR DATOS");
        imprimirSubtitulo("Configure el consumo diario");
        printf("\n");
        printf("[AVISO] Editando el hogar \"%s\"\n", temp_nombre_hogar);
        do 
        {
            printf("\nIngrese el dia de la semana que desea configurar (de 1 hasta %d)\n", DIAS_SEMANA);
            printf("\n >> ");
            temp_dias_seleccion=leerNumeroFlotante();
            dias_seleccion=(int)round(temp_dias_seleccion);
            if(dias_seleccion>DIAS_SEMANA || dias_seleccion<1)
            {
                printf("\n");
                printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", DIAS_SEMANA);  
            }
            if(consumoLitros[resultado_busqueda][dias_seleccion-1]!=0)
            {
                printf("\n");
                printf("[ERROR] Este dia ya tiene un limite establecido (limite en el dia %d: %.2f)\n", dias_seleccion, consumoLitros[resultado_busqueda][dias_seleccion-1]);  
            }

        }while(dias_seleccion>DIAS_SEMANA || dias_seleccion<1 || consumoLitros[resultado_busqueda][dias_seleccion-1]!=0);
        do
        {
            printf("\nIngrese el consumo diario en litros para este hogar \nEn el dia %d (limite maximo: %d)", dias_seleccion, LIM_LITRO);
            printf("\n >> ");
            consumo_seleccion=leerNumeroFlotante();
            if (consumo_seleccion>LIM_LITRO)
            {
                printf("\n");
                printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", LIM_LITRO);  
            }
        }while(consumo_seleccion>LIM_LITRO);
        consumoLitros[resultado_busqueda][dias_seleccion-1]= consumo_seleccion;
        limpiarPantalla();
        printf("[AVISO] Consumo establecido a: %0.f  para el dia %d\n", consumo_seleccion, dias_seleccion);
        printf("[AVISO] Datos para el hogar: \"%s\" guardados con exito\n", temp_nombre_hogar);
        guardarDatos(nombre, personas, limiteDiario, consumoLitros);
        consumo_seleccion=0;
        dias_seleccion=0;

        printf("\n" );
    }
}

void modificarDato(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    ///////// FUNCION MODIFICAR DATO TE PERMITE MODIFICAR LOS DATOS QUE YA INGRESASTE Y CAMBIARLOS POR OTROS (SOLO CONSUMO DIARIO)

    char temp_nombre_hogar[32];
    int resultado_busqueda;
    float temp_dias_seleccion;
    int dias_seleccion;
    float consumo_seleccion;

    imprimirTitulo("MODIFICAR UN DATO");
    imprimirSubtitulo("Modifica un dato ya");
    imprimirSubtitulo("establecido para un hogar");
    printf("\n");
    printf("| Nombre del hogar\n |>> "); //// Nombre del hogar para editar
    scanf("%s", temp_nombre_hogar); //// ingresamos el nombre del hogar (TIENE que existir, si no, se repite la pregunta)
    resultado_busqueda = buscarHogar(temp_nombre_hogar, nombre);   /// si el resultado de busqueda no coincide con el nombre de un hogar existente
                                                            /// volvemos a preguntar
    if (resultado_busqueda == -1)
    {
        printf("[ERROR] Hogar de nombre [ %s ] no encontrado\n", temp_nombre_hogar);
        printf("Crea el hogar para poder editar sus elementos\n"); 
        printf("\n");
    }
    else if(resultado_busqueda != -1)
    {
        limpiarPantalla();
        imprimirTitulo("MODIFICAR UN DATO");
        imprimirSubtitulo("Modifica el consumo diario para un dia en especifico");
        printf("\n");
        printf("[AVISO] Editando el hogar \"%s\"\n", temp_nombre_hogar);
        do 
        {
            printf("\nIngresa el dia de la semana que deseas configurar (de 1 hasta %d)\n", DIAS_SEMANA);
            printf("\n >> ");
            temp_dias_seleccion=leerNumeroFlotante();
            dias_seleccion=(int)round(temp_dias_seleccion);
            if(dias_seleccion>DIAS_SEMANA || dias_seleccion<1)
            {
                printf("\n");
                printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", DIAS_SEMANA);  
            }
            if(consumoLitros[resultado_busqueda][dias_seleccion-1]==0)
            {
                printf("\n");
                printf("[ERROR] Este dia no tiene un limite asignado que cambiar\n");  
            }
        }while(dias_seleccion>DIAS_SEMANA || dias_seleccion<1 || consumoLitros[resultado_busqueda][dias_seleccion-1]==0);
        do
        {
            printf("\nRemplaza el consumo diario para este hogar en el dia %d (limite maximo: %d)", dias_seleccion, LIM_LITRO);
            printf("\nConsumo diario actual: %1.f", consumoLitros[resultado_busqueda][dias_seleccion-1]);
            printf("\n >> ");
            consumo_seleccion=leerNumeroFlotante();
            if (consumo_seleccion>LIM_LITRO)
            {
                printf("\n");
                printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", LIM_LITRO);  
            }
        }while(consumo_seleccion>LIM_LITRO);
        consumoLitros[resultado_busqueda][dias_seleccion-1]= consumo_seleccion;
        limpiarPantalla();
        printf("[AVISO] Limite establecido a: %1.f  para el dia %d\n", consumo_seleccion, dias_seleccion);
        printf("[AVISO] Datos para el hogar: \"%s\" guardados con exito\n", temp_nombre_hogar);
        guardarDatos(nombre, personas, limiteDiario, consumoLitros);
        consumo_seleccion=0;
        dias_seleccion=0;
        printf("\n" );
    }
}

void operacionPrincipal(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    ///// OPERACION PRINCIPAL ES EN DONDE SE MUESTRAN LOS DATOS DE UN HOGAR (CANTIDAD DE DIAS EXCESO Y EXISTENCIA DE FUGAS)

    imprimirTitulo("EXCESOS Y FUGAS");
    imprimirSubtitulo("Verifica si el hogar contiene");
    imprimirSubtitulo("algun exceso o fuga");
    printf("\n");
    int dias_exceso=0;
    for(int i=0; i<CANTIDAD_DATOS; i++)
    {
        dias_exceso=verificacionExceso(i, limiteDiario, consumoLitros);
        printf("\n%s: %d dia(s) de exceso", nombre[i], dias_exceso);
        if(verificacionFuga(i, limiteDiario, consumoLitros))
        {
            printf(" | POSIBLE FUGA");
        }
    }
    printf("\n");
    volverAlMenu();
}

void mostrarTabla(char nombre[MAX_DATOS][32], float consumo_litros[MAX_DATOS][DIAS_SEMANA]){
    // FUNCION PARA VER LA TABLA DE DATOS DE LA MATRIZ

    float total_fila = 0;

    // VARIABLE PARA SABER EL LARGO MAXIMO DEL NOMBRE DE UN HOGAR
    // Y ASI ACOMODAR LA TABLA PARA EVITAR DESFACES
    int maxNameLen = 0,
    
    // VARIABLE PARA CALCULAR EL LOGATIRMO EN BASE 10 DE UN NUMERO
    // Y DE ESTA FORMA SABER CUANTOS DIGITOS TIENE EL NUMERO.
        log_num = 0,
    
    // GUARDAR LA LOGITUD DE NUMERO CALCULADA EN log_num
        longitud_numero = 0;

    imprimirTitulo("TABLA DIAS");
    imprimirSubtitulo("Todos los valores representan Litros");
    printf("\n");

    // ENCONTRAR EL NOMBRE MAS LARGO Y SU VALOR DE LONGITUD
    for (int i = 0; i < CANTIDAD_DATOS; i++) {
        
        if (strlen(nombre[i]) > maxNameLen) {
            maxNameLen = strlen(nombre[i]);
        }

    }

    // LLAMAR A LA FUNCION PARA IMPRIMIR LA CABECERA DE LA TABLA Y PASARLE
    // LOS ESPACIOS QUE DEBERA RELLENAR EN CASO DE QUE UN NOMBRE SEA MAS CORTO
    // QUE EL NOMBRE MAS LARGO
    imprimirCabeceraTabla(maxNameLen);

    for (int i = 0; i < CANTIDAD_DATOS; i++)
    {
        
        printf("%s ", nombre[i]);
        
        imprimirEspacios(maxNameLen - strlen(nombre[i]), 1);
        
        for (int j = 0; j < DIAS_SEMANA; j++)
        {
            if ((j+1) % 2 != 0) printf("│ ");

            printf("%.2f ", consumo_litros[i][j]);
            
            // SI EL CONSUMO DE LITROS EN 0, PONEMOS EL log_num en 0
            // PARA EVITAR ERRORES AL CALCULAR LOG10 DE 0.
            if (consumo_litros[i][j] == 0) log_num = 0;
            else log_num = log10(consumo_litros[i][j]);
            longitud_numero = round(log_num + 1);

            // IMPRIMIR LOS ESPACIOS RESTANTES, COMO LOS VALORES SE ANCLAN A 5000 COMO MAX
            // SOLO HAY QUE RELLENAR SI EL NUMERO ES MENOR A ESOS 4 DIGITOS
            imprimirEspacios((4 - longitud_numero), 1);

            if ((j+1) % 2 != 0) printf("│ ");

            total_fila += consumo_litros[i][j];
            log_num = 0;
            longitud_numero = 0;
        }

        printf("%.2f", total_fila);

        // SI EL CONSUMO DE LITROS EN 0, PONEMOS EL log_num en 0
        // PARA EVITAR ERRORES AL CALCULAR LOG10 DE 0.
        if (total_fila == 0) log_num = 0;
        else log_num = log10(total_fila);
        longitud_numero = round(log_num + 1);
        
        // IMPRIMIR LOS ESPACIOS RESTANTES, COMO LA SUMA DE VALORES QUEDA EN 35000 COMO MAX
        // SOLO HAY QUE RELLENAR SI EL NUMERO ES MENOR A ESOS 5 DIGITOS
        imprimirEspacios((5 - longitud_numero), 1);

        printf(" │");

        total_fila = 0;

        printf("\n");
        imprimirEspacios((maxNameLen + 1), 2);
        
        if (i != (CANTIDAD_DATOS - 1))
            printf("┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────────┤\n");
            
        else 
            printf("┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴──────────┘\n");

    }

    printf("\n");

    volverAlMenu();
}

void mostrarEstadisticas(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) {
    // FUNCION PARA MOSTRAR LAS ESTADISTICAS DE LOS DATOS


    float consumoTotalDeHogares = 0,
          consumoTotalHogarAnterior = 0,
          consumoTotalHogarActual = 0;

    float consumoPromedioPersona = 0;
    
    int totalPersonas = 0,
        totalDiasExceso = 0;

    int indexHogarMayorConsumo = 0;

    imprimirTitulo("ESTADÍSTICAS DE CONSUMO");

    for (int i = 0; i < CANTIDAD_DATOS; i++) {
        
        for (int v = 0; v < DIAS_SEMANA; v++) {
            consumoTotalDeHogares += consumoLitros[i][v];
            
            consumoTotalHogarActual += consumoLitros[i][v];
        }

        if (consumoTotalHogarActual > consumoTotalHogarAnterior) {
            indexHogarMayorConsumo = i;
        }
        
        consumoTotalHogarAnterior = consumoTotalHogarActual;    
        consumoTotalHogarActual = 0;

        totalDiasExceso += verificacionExceso(i, limiteDiario, consumoLitros);

    }
    
    printf("\n» Consumo total de los hogares: %.2f L\n", consumoTotalDeHogares);
    printf("» Total de días con exceso de consumo: %d\n", totalDiasExceso);
    printf("» Hogar con mayor el consumo: %s\n", nombre[indexHogarMayorConsumo]);
    printf("\n┌ Promedio de litros por persona (L/PP) diario:\n");

    for (int i = 0; i < DIAS_SEMANA; i++) {
        for (int v = 0; v < CANTIDAD_DATOS; v++) {
            consumoPromedioPersona += consumoLitros[v][i];

            if (i == 0) {
                totalPersonas += personas[v];
            }

        }
        
        consumoPromedioPersona /= totalPersonas;

        printf("│ DIA %d: %.2f [L/PP]\n", (i + 1), consumoPromedioPersona);

    }

    printf("\n");

    volverAlMenu();
    limpiarPantalla();
}

void guardarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]) {
    // FUNCION PARA GUARDAR LOS DATOS DE LOS ARREGLOS Y VARIABLES CORRESPONDIENTES EN EL ARCHIVO .TXT

    datos = fopen(nombre_datos, "w");

    fprintf(datos, "%d\n", CANTIDAD_DATOS);

    for (int i = 0; i < CANTIDAD_DATOS; i++) {
        fprintf(datos, "%s %d %f\n", nombre[i], personas[i], limiteDiario[i]);
    }

    for (int i = 0; i < CANTIDAD_DATOS; i++){
        
        for (int v = 0; v < DIAS_SEMANA; v++) {
            if (v < DIAS_SEMANA - 1) {

                fprintf(datos, "%f ", consumoLitros[i][v]);

            } else if (i != CANTIDAD_DATOS - 1 && v == DIAS_SEMANA - 1) {

                fprintf(datos, "%f\n", consumoLitros[i][v]);

            } else if (i == CANTIDAD_DATOS - 1 && v == DIAS_SEMANA - 1) {
                
                fprintf(datos, "%f", consumoLitros[i][v]); 
            
            }
        }

    }

    fclose(datos);

}

void mostrarAyudaYAcercaDe() {
    // FUNCION PARA MOSTRAR ACERCA DE Y AYUDA

    imprimirTitulo("AYUDA Y ACERCA DE");
    
    printf("\n");
    printf("AYUDA:\n");
    printf("\n");

    printf("1. ¿Qué ODS aborda?         » Muestra información sobre el ODS.\n");
    printf("2. Configurar elementos     » Ingresa los datos básicos de un nuevo hogar.\n");
    printf("3. Registrar datos          » Ingresa un registros de litros para un día en un hogar.\n");
    printf("4. Modificar un dato        » Corrige un dato ya registrado de litros para un día específico.\n");
    printf("5. Detectar excesos y fugas » Indica cuantos días de exceso tiene un hogar y posible fuga.\n");
    printf("6. Ver tabla                » Muestra los datos de litros por día\n");
    printf("7. Estadísticas             » Muestra consumo total, hogar con mayor consumo,\n");
    printf("                              promedio por persona por día y días con exceso.\n");
    printf("8. Guardar datos            » Guarda todos los datos en el archivo.\n");
    printf("9. Ayuda y Acerca de        » Muestra esta ayuda y la información del programa.\n");
    printf("0. Salir                    » Guarda automáticamente y termina el programa.\n");
    
    printf("\n");
    printf("ACERCA DE:\n");
    printf("\n");
    printf("Programa    » Cuidemos el Agua\n");
    printf("Versión     » 26.3.1\n");
    printf("ODS         » ODS 6 - Agua Limpia y Saneamiento\n");
    printf("Curso       » Taller de Programación I\n");
    printf("Integrantes » Vicente Barrientos, Juan José Machuca, Elías Pérez\n");

    printf("\n");
    volverAlMenu();

}