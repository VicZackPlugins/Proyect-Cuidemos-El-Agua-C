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
    // FUNCION PARA IMPRIMIR SUBTITULOS CENTRADOS

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

    for (int i = 0; i < MAX_BORDER; i++) {
        printf("%c", CHAR_LINE);
    }

    printf("\n");
}

void imprimirEspacios(int cantidad, int tipo) {
    // FUNCION PARA IMPRIMIR ESPACIOS CON UN FORMATO EN ESPECIFICO

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

void imprimirCabeceraTabla(int maxNameLen) {
    // FUNCION PARA IMPRIMIR LA CABECERA DE LA TABLA DE DATOS

    int espacios = maxNameLen + 1;

    imprimirEspacios(espacios, 1);

    printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬──────────┐\n");

    imprimirEspacios(espacios, 1);
    
    printf("│ DIA 1   │ DIA 2   │ DIA 3   │ DIA 4   │ DIA 5   │ DIA 6   │ DIA 7   │ TOTAL    │\n");

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
            sscanf(buffer, "%d", &CANTIDAD_DATOS);
            linea++;
            continue;
        }

        if (linea <= (CANTIDAD_DATOS + 1)) {
            sscanf(buffer, "%s %d %f", nombre[index], &personas[index], &limiteDiario[index]);
            index++;
            linea++;

            if (index >= CANTIDAD_DATOS) index = 0;

            continue;
        }

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

    //// inicializamos dias_exceso en 0

    int dias_exceso=0;

    //// en el caso de que el consumo de litros en un dia cualquiera sobrepase
    //// el limite maximo establecido para un hogar, aumentaremos esta variable en 1
    //// y luego la retornaremos
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

    //// inicializamos promedio diario en 0
    
    int promedio_diario=0;
    

    //// calculamos el promedio del hogar con su consumo de litros por todos los dias
    for(int i=0; i<DIAS_SEMANA; i++)
    {
        promedio_diario+=consumoLitros[indice_casa][i];
    }

    ///// el promedio se obtiene dividiendo la suma de el consumo
    ///// de todos los dias por los dias de la semana especificados
    promedio_diario/=DIAS_SEMANA;

    //// si el promedio diario es 0, lo ignoramos
    if(promedio_diario==0)
    {
        return 0;
    }
    
    //// en el caso de que un dia sobrepase el doble del promedio, retornamos 1
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
    /*
        leerNumeroFlotante() nos permite verificar si (por alguna razon)
        el usuario inserta un strign en vez de un valor numerico, lo que hace
        repetir el proceso de solicitar por un valor 
    */


    /// inicializamos variables temporales para transferir elementos
    char temp_nombre_hogar[32];
    float temp_cantidad_personas;
    float temp_lim_diario;

    /// Imprimimos titulos y subtitulos

    imprimirTitulo("CONFIGURAR ELEMENTO");
    imprimirSubtitulo("Ingrese los datos solicitados");
    printf("\n");

    //// Resultado busqueda nos permite almacenar la identificacion numerica del hogar
    int resultado_busqueda;
    do
    {
        //// solicitamos el Nombre del hogar, y verificamos que este no exista
        printf("| Nombre del hogar: \n| >> ");
        scanf("%s", temp_nombre_hogar);
        fflush(stdin);
        ///// resultado busqueda busca el nombre del hogar y retorna un valor
        resultado_busqueda = buscarHogar(temp_nombre_hogar, nombre);

        //// si el nombre ya esta utilizado en la base de datos
        //// volvemos a pedirlo hasta que se ingrese uno no utilizado
        if (resultado_busqueda != -1)
        {
            limpiarPantalla();
            printf("[ERROR] Ya existe un elemento con este nombre.\n");
            printf("        Por favor ingrese los datos nuevamente.\n\n");
            imprimirTitulo("CONFIGURAR ELEMENTO");
            imprimirSubtitulo("Ingrese los datos solicitados");
            printf("\n");
        }

    }while(resultado_busqueda != -1);
    
    do
    {
        ///// solicitamos el consumo diario maximo para un hogar
        //// si este consumo excede el maximo general de el limite de consumo
        //// imprimimos mensaje de error y volvemos a solicitar
        printf("\n| Consumo diario maximo\n| >> ");
        temp_lim_diario=leerNumeroFlotante();
        if (temp_lim_diario>LIM_LITRO)
        {
            printf("[ERROR] El consumo diario no puede exceder %d.\n", LIM_LITRO);  
        }

    }while(temp_lim_diario>LIM_LITRO);

    do
    {
        //// solicitamos la cantidad de personas para un hogar
        //// la cantidad puede ser de un minimo a un maximo especificado
        //// Si no se respeta este rango al ingresar un valor, volvemos a solicitar
        printf("\n| Cantidad de personas en el hogar\n| >> ");
        temp_cantidad_personas=leerNumeroFlotante();
        if (temp_cantidad_personas>MAX_PERSONAS || temp_cantidad_personas<MIN_PERSONAS)
        {
            printf("[ERROR] Un hogar tiene que tener entre %d a %d personas.\n", MIN_PERSONAS, MAX_PERSONAS);  
        }

    }while(temp_cantidad_personas>MAX_PERSONAS || temp_cantidad_personas<MIN_PERSONAS);


    /////// Aumentamos la cantidad de datos para almacenar un hogar, se aumenta en 1
    int cantidad_datos = aumentarCantidadDatos();
    ////// el indice corresponde al hogar ingresado actualmente, por eso el -1
    int indice = cantidad_datos - 1;

    //// El nombre en el indice de el hogar creado se convierte en la temporal que escanemosa antes
    strcpy(nombre[indice], temp_nombre_hogar);   
    //// (int)round(temp_cantidad_personas) nos permite redondear el valor
    //// si es que se ingreso un valor flotante, como por ejemplo
    //// 1.3 pasa a ser 1, o 1.8 pasa a ser 2 (no pueden haber 1.5 personas..)
    personas[indice] = (int)round(temp_cantidad_personas);
    /// la temporal de limite diario se transfiere a la de la base de datos, para posteriormente ser guardada
    limiteDiario[indice] = temp_lim_diario;

    /// Para todos los dias de la semana en el hogar creado, sus consumos diarios son 0
    /// para luego ser remplazados si se desea
    for(int i=0; i<DIAS_SEMANA; i++) {
        consumoLitros[cantidad_datos - 1][i]=0;
    }
    limpiarPantalla();
    ////// damos el aviso de que los datos se han guardado para el hogar especificado, y usamos 
    ///// la funcion guardar datos para copiar los valores que 
    printf("[AVISO] Datos guardados con exito para el hogar %s\n", temp_nombre_hogar);
    guardarDatos(nombre, personas, limiteDiario, consumoLitros);
}

void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    /// FUNCION REGISTRAR DATOS PERMITE ESTABLECER EL CONSUMO DIARIO DE UN HOGAR


    //// nuevamente inicializamos temporales que nos permitiran transferir sus valores
    //// a el archivo de guardado
    char temp_nombre_hogar[32];
    float temp_dias_seleccion;
    int dias_seleccion;
    int resultado_busqueda;
    float consumo_seleccion;


    //// Imprimimos titulo
    //// y subtitulos de esta secciond el menu
    imprimirTitulo("REGISTRAR DATOS");
    imprimirSubtitulo("Configura el limite diario para");
    imprimirSubtitulo("un hogar seleccioando");
    printf("\n");
    printf("| Nombre del hogar\n >> "); 
    scanf("%s", temp_nombre_hogar);
    //// nuevamente escaneamos el nombre del hogar, pero esta vez, verificamos que exista
    //// si buscarhogar devuelve -1, no se encontro un hogar, volvemos al menu para poder
    //// crear un hogar y evitar un bucle infinito
    resultado_busqueda = buscarHogar(temp_nombre_hogar, nombre);
    if (resultado_busqueda == -1)
    {
        printf("[ERROR] Hogar de nombre [ %s ] no fue encontrado\n", temp_nombre_hogar);
        printf("Crea el hogar para poder editar sus elementos\n"); 
        printf("\n");
    }
    ///// si resultado de busqueda encuentra un hogar con ese nombre, seguimos
    //// con el codigo
    else if(resultado_busqueda != -1)
    {
        ///// limpiamos pantalla y nos deshacemoz de la verificacion anterior
        ///// (puramente estetico)
        limpiarPantalla();
        imprimirTitulo("REGISTRAR DATOS");
        imprimirSubtitulo("Configure el consumo diario");
        printf("\n");
        ///// mostramos el aviso de que se esta modificando el hogar
        //// solicitado anteriormente
        printf("[AVISO] Editando el hogar \"%s\"\n", temp_nombre_hogar);
        do 
        {
            ////// solicitamos el dia de la semana del cual se desea configurar su consumo diario
            ///// tiene que respetar el rango de dias semanales, (entre 1 y el maximo especificado en
            ///// la variable global DIAS_SEMANA)
            printf("\nIngrese el dia de la semana que desea configurar (de 1 hasta %d)\n", DIAS_SEMANA);
            printf("\n >> ");
            temp_dias_seleccion=leerNumeroFlotante();
            dias_seleccion=(int)round(temp_dias_seleccion);
            //// si el dia ingresado no respeta el rango, o, ya se establecio el valor
            //// de consumo diario en ese dia, imprimimos mensaje de error segun
            //// corresponda
            if(dias_seleccion>DIAS_SEMANA || dias_seleccion<1)
            {
                printf("\n");
                printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", DIAS_SEMANA);  
            }
            if(consumoLitros[resultado_busqueda][dias_seleccion-1]!=0)
            {
                printf("\n");
                printf("[ERROR] Este dia ya tiene un consumo establecido (consumo en el dia %d: %.2f)\n", dias_seleccion, consumoLitros[resultado_busqueda][dias_seleccion-1]);  
            }
        //// repetimos hasta que se respeten los limites y no haya un valor ocupando ese dia
        }while(dias_seleccion>DIAS_SEMANA || dias_seleccion<1 || consumoLitros[resultado_busqueda][dias_seleccion-1]!=0);
        do
        {
            ///// ahora solicitamos el consumo diario, ya que el dia fue valido
            printf("\nIngrese el consumo diario en litros para este hogar \nEn el dia %d (limite maximo: %d)", dias_seleccion, LIM_LITRO);
            printf("\n >> ");
            //// nuevamente verificamos si no se ingresa un string
            consumo_seleccion=leerNumeroFlotante();
            ///// si el consumo seleccionado supera el limite maximo global
            ///// lo solicitamos otra vez, ya que no es posible superar ese limite
            //// repetimos las veces que sea necesario hasta que se ingrese un valor
            //// valido
            if (consumo_seleccion>LIM_LITRO)
            {
                printf("\n");
                printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", LIM_LITRO);  
            }
        }while(consumo_seleccion>LIM_LITRO);
        ///// el consumo de litros de el hogar especificado pasa a tener el valor de lo seleccionado
        consumoLitros[resultado_busqueda][dias_seleccion-1]= consumo_seleccion;
        limpiarPantalla();
        //// damos los avisos de que se ejecuto todo con exito y mostramos los cambios
        printf("[AVISO] Consumo establecido a: %0.f  para el dia %d\n", consumo_seleccion, dias_seleccion);
        printf("[AVISO] Datos para el hogar: \"%s\" guardados con exito\n", temp_nombre_hogar);
        //// guardamos los datos y reseteamos variables para evitar errores
        guardarDatos(nombre, personas, limiteDiario, consumoLitros);
        consumo_seleccion=0;
        dias_seleccion=0;

        printf("\n" );
    }
}

void modificarDato(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{
    ///////// FUNCION MODIFICAR DATO TE PERMITE MODIFICAR LOS DATOS QUE YA INGRESASTE Y CAMBIARLOS POR OTROS (SOLO CONSUMO DIARIO)


    //// inicializamos temporales nuevamente
    //// (para traspasar sus globales)
    char temp_nombre_hogar[32];
    int resultado_busqueda;
    float temp_dias_seleccion;
    int dias_seleccion;
    float consumo_seleccion;

    //// imprimimos titulos y subtitulos (estetico)

    imprimirTitulo("MODIFICAR UN DATO");
    imprimirSubtitulo("Modifica un dato ya");
    imprimirSubtitulo("establecido para un hogar");
    printf("\n");
    printf("| Nombre del hogar\n |>> ");
    //// nuevamente preguntamos por el nombre del hogar y buscamos si existe
    //// si no, se devuelve al menu para crear un hogar, con el proposito
    /// de evitar bucles infinitos
    scanf("%s", temp_nombre_hogar);
    resultado_busqueda = buscarHogar(temp_nombre_hogar, nombre);
    ///// si no existe, mostramos un error y volvemos al menu
    if (resultado_busqueda == -1)
    {
        limpiarPantalla();
        printf("[ERROR] Hogar de nombre [ %s ] no encontrado \n", temp_nombre_hogar);
        printf("Crea el hogar para poder editar sus elementos\n"); 
        printf("\n");
        return;
    }
    //// o si no hay consumos que podamos editar, volvemos al menu para crear uno
    if(consumoLitros[resultado_busqueda][dias_seleccion-1]==0)
    {
        limpiarPantalla();
        printf("[ERROR] Este hogar no posee ningun consumo que modificar");
        printf("\n");  
        return;
    }

    ///// si no hay errores, ejecutamos la funcion de modificar

    if(resultado_busqueda != -1)
    {
        limpiarPantalla();
        imprimirTitulo("MODIFICAR UN DATO");
        imprimirSubtitulo("Modifica el consumo diario para un dia en especifico");
        printf("\n");
        //// damos los avisos correspondientes sobre la modificacion del hogar
        printf("[AVISO] Editando el hogar \"%s\"\n", temp_nombre_hogar);
        do 
        {
            ///// nuevamente solicitamos los dias de la semana
            //// el rango tiene que ser respetado, si no, volvemos a solicitar un dia valido
            //// entre 1 y el maximo establecido
            printf("\nIngresa el dia de la semana que deseas configurar (de 1 hasta %d)\n", DIAS_SEMANA);
            printf("\n >> ");
            temp_dias_seleccion=leerNumeroFlotante();
            dias_seleccion=(int)round(temp_dias_seleccion);
            if(dias_seleccion>DIAS_SEMANA || dias_seleccion<1)
            {
                printf("\n");
                printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", DIAS_SEMANA);  
            }
        }while(dias_seleccion>DIAS_SEMANA || dias_seleccion<1);
        do
        {
            ///// si el dia es valido, solicitamos el nuevo consumo para cambiar
            //// junto con dar el consumo anterior como referencia
            printf("\nRemplaza el consumo diario para este hogar en el dia %d (limite maximo: %d)", dias_seleccion, LIM_LITRO);
            printf("\nConsumo diario actual: %1.f", consumoLitros[resultado_busqueda][dias_seleccion-1]);
            printf("\n >> ");
            //// nuevamente prevenimos errores por ingresar string
            consumo_seleccion=leerNumeroFlotante();
            if (consumo_seleccion>LIM_LITRO)
            {
                printf("\n");
                printf("[ERROR] Valor fuera de rango, porfavor inserta un valor entre 0 y %d.\n", LIM_LITRO);  
            }
        }while(consumo_seleccion>LIM_LITRO);
        //// El consumo de litros del hogar en el dia especificado se remplaza por el que ingresamos ahora
        consumoLitros[resultado_busqueda][dias_seleccion-1]= consumo_seleccion;
        limpiarPantalla();
        //// Damos el aviso de que se ha modificado el dato con exito
        printf("[AVISO] Consumo establecido a: %1.f  para el dia %d\n", consumo_seleccion, dias_seleccion);
        printf("[AVISO] Datos para el hogar: \"%s\" guardados con exito\n", temp_nombre_hogar);
        //// guardamos y reiniciamos variables
        guardarDatos(nombre, personas, limiteDiario, consumoLitros);
        consumo_seleccion=0;
        dias_seleccion=0;
        printf("\n" );
    }
}

void operacionPrincipal(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    ///// OPERACION PRINCIPAL ES EN DONDE SE MUESTRAN LOS DATOS DE UN HOGAR 
    //// (CANTIDAD DE DIAS EXCESO Y EXISTENCIA DE FUGAS)

    /// imprimimos titulos (estetico)

    imprimirTitulo("EXCESOS Y FUGAS");
    imprimirSubtitulo("Verifica si el hogar contiene");
    imprimirSubtitulo("algun exceso o fuga");
    printf("\n");

    //// dias exceso representa los dias en los que se supero el consumo
    /// recomendado para ese hogar

    int dias_exceso=0;

    ///// para cada hogar, verificamos si el consumo en un dia supero
    ///// el consumo maximo para ese hogar, si ese es el caso, dias exceso sube para ese hogar en 1 segun
    //// los dias con exceso, 

    for(int i=0; i<CANTIDAD_DATOS; i++)
    {
        dias_exceso=verificacionExceso(i, limiteDiario, consumoLitros);
        printf("\n%s: %d dia(s) de exceso", nombre[i], dias_exceso);
        if(verificacionFuga(i, limiteDiario, consumoLitros))
        {
            ///// en el caso de que un dia sobrepase el doble del promedio
            //// del consumo general del hogar (desde el primer dia hasta el
            /// maximo especificado), diremos que existe una fuga en ese hogar
            printf(" | POSIBLE FUGA");
        }
    }
    printf("\n");
    volverAlMenu();
}

void mostrarTabla(char nombre[MAX_DATOS][32], float consumo_litros[MAX_DATOS][DIAS_SEMANA]){
    // FUNCION PARA VER LA TABLA DE DATOS DE LA MATRIZ

    float total_fila = 0;
    int maxNameLen = 0,
        log_num = 0,
        longitud_numero = 0;

    imprimirTitulo("TABLA DIAS");
    imprimirSubtitulo("Todos los valores representan Litros");
    printf("\n");

    for (int i = 0; i < CANTIDAD_DATOS; i++) {
        
        if (strlen(nombre[i]) > maxNameLen) {
            maxNameLen = strlen(nombre[i]);
        }

    }

    imprimirCabeceraTabla(maxNameLen);

    for (int i = 0; i < CANTIDAD_DATOS; i++)
    {
        
        printf("%s ", nombre[i]);
        
        imprimirEspacios(maxNameLen - strlen(nombre[i]), 1);
        
        for (int j = 0; j < DIAS_SEMANA; j++)
        {
            if ((j+1) % 2 != 0) printf("│ ");

            printf("%.2f ", consumo_litros[i][j]);
            
            if (consumo_litros[i][j] == 0) log_num = 0;
            else log_num = log10(consumo_litros[i][j]);
            longitud_numero = round(log_num + 1);

            imprimirEspacios((4 - longitud_numero), 1);

            if ((j+1) % 2 != 0) printf("│ ");

            total_fila += consumo_litros[i][j];
            log_num = 0;
            longitud_numero = 0;
        }

        printf("%.2f", total_fila);
        
        if (total_fila == 0) log_num = 0;
        else log_num = log10(total_fila);
        longitud_numero = round(log_num + 1);
        
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

void mostrarAcercaDeAyuda() {
    // FUNCION PARA MOSTRAR ACERCA DE Y AYUDA

    imprimirTitulo("AYUDA Y ACERCA DE");

}