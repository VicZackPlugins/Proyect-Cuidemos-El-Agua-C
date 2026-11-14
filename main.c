#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


#define MAX_BORDER 42 // Largo maximo de los headers
#define CHAR_LINE '=' // Caracter que se usara como linea

FILE *datos;        // Datos guardados

char nombre_datos[] = "datos.txt";

// datos = fopen("db.txt", r); READ
// datos = fopen("db.txt", w); WRITTE
// datos = fopen("db.txt", a); APPEND
// fclose(file)

int cantidadDatos = 0;

// ========= FUNCIONES: ========== //

void limpiar_pantalla();
void esperar_exit();
void mostrarMenu();
void iniciarArreglos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void cargarDatosArchivos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void guardarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
void imprimir_titulo(char titulo[64]);
void imprimir_borde();

void registrarDatos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

void ConfigurarElementos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);
int Buscar_Hogar(char nombre_hogar[32], char nombre[MAX_DATOS][32]);

void Registrar_Datos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA]);

int obtener_datos();
int aumentar_cantidad_datos();
void ods_info();
void ver_tabla(float consumo_litros[MAX_DATOS][DIAS_SEMANA]);

int main() {
    
    char nombre[MAX_DATOS][32];                  // Nombre de los hogares

    int personas[MAX_DATOS];                     // Cantidad de personas por hogar

    float limiteDiario[MAX_DATOS],               // Promedio litros a la semana por hogar
          consumoLitros[MAX_DATOS][DIAS_SEMANA]; // Consumo de litros por hogar por día

    // Iniciar arreglos con valores por defecto (0 o "")
    iniciarArreglos(nombre, personas, limiteDiario, consumoLitros);
    cantidadDatos = obtener_datos();

    int opciones;                             // Ingreso de una opcion
    limpiar_pantalla();
    
    cargarDatosArchivos(nombre, personas, limiteDiario, consumoLitros);
    do {
        
        mostrarMenu();
        
        scanf("%d", &opciones);
        fflush(stdin);
        
        switch(opciones) {
            
            case 0: {
                // Cerrar Programa
                limpiar_pantalla();
                return 0;
            }
            case 1: {
                // ¿Que ODS aborda este programa?
                limpiar_pantalla();
                
                ods_info();

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
                Registrar_Datos(nombre, personas, limiteDiario, consumoLitros);

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
                ver_tabla(consumoLitros);
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

void limpiar_pantalla() {
    // FUNCION PARA LIMPIAR LA PANTALLA

    system("cls");
}

void esperar_exit() {
    // FUNCION PARA ESPERAR QUE EL USUARIO VUELVA AL MENU ANTERIOR
    /*
        No hay restricciones, puesto que no buscamos verdaderamente
        una entrada en especifico, simplemente queremos que el
        programa se frene para que los datos en pantalla queden pegados.
        Un ejemplo para el uso de esta funcion es en la opcion "Ver tabla de datos".
    */

    imprimir_borde();
    printf("\nPresione la tecla ENTER para volver... \n");

    /*
        Con fgets() podemos leer el teclado y detectar cualquier caracter
        incluyendo el ENTER, debido a que fgets() lee una linea hasta que
        detecta un salto de linea "\n" y exactamente la tecla ENTER
        equivale a un salto de linea en los caracteres.
    */

    char temp[128];
    fgets(temp, sizeof(temp), stdin);
    limpiar_pantalla();

}

void mostrarMenu() {
    imprimir_titulo("CUIDEMOS EL AGUA - ODS N 6");
    printf("\n 1. ¿Que ODS aborda este programa? \n 2. Configurar elementos \n 3. Registrar datos \n 4. Modificar un dato\n");
    printf(" 5. [Operacion principal del proyecto] \n 6. Ver tabla de datos \n 7. Ver estadisticas \n 8. Guardar datos\n");
    printf(" 9. Ayuda y Acerca de \n 0. Salir \n\n");
    imprimir_borde();
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

void imprimir_titulo(char titulo[64])
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

void imprimir_subtitulo(char subtitulo[64]) {
    
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

void imprimir_borde() {
    for (int i = 0; i < MAX_BORDER; i++) {
        printf("%c", CHAR_LINE);
    }

    printf("\n");
}

// ========= J U A N J O S E ========= //

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
    //// inicializamos los elementos para que tengan un valor 

    char temp_nombre_hogar[32];
    int temp_cantidad_personas;
    float temp_lim_diario;

    imprimir_titulo("CONFIGURAR ELEMENTO");
    imprimir_subtitulo("Ingrese los datos solicitados");
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
            limpiar_pantalla();
            printf("[ERROR] Ya existe un elemento con este nombre.\n");
            printf("        Por favor ingrese los datos nuevamente.\n\n");
            imprimir_titulo("CONFIGURAR ELEMENTO");
            imprimir_subtitulo("Ingrese los datos solicitados");
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
    limpiar_pantalla();
}

void Registrar_Datos(char nombre[MAX_DATOS][32], int personas[MAX_DATOS], float limiteDiario[MAX_DATOS], float consumoLitros[MAX_DATOS][DIAS_SEMANA])
{

    char input_usuario[32];

    char temp_nombre_hogar[32];

    int cantidad_datos = aumentar_cantidad_datos();     /// inicializamos la cantidad de datos como local para poder utilizarla
    int indice = cantidad_datos - 1;

    int resultado_busqueda;

    imprimir_titulo("REGISTRAR DATOS");
    imprimir_subtitulo("Configura el limite diario para");
    imprimir_subtitulo("un hogar seleccioando");
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

            printf("[AVISO] Hogar existente encontrado\n");
            printf("Nombre: %s\n", temp_nombre_hogar);

        }

    }while(resultado_busqueda == -1);

    if(resultado_busqueda != -1)
    {
        imprimir_titulo("Configuracion ");
        printf("\n >> ");
        scanf("%d", consumoLitros[cantidad_datos - 1][indice]);
        printf("cantidad de datos establecida");
        
    }


    
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

void ods_info() {
    imprimir_titulo("ODS 6: Agua Limpia y Saneamiento");
    printf("\n");
    printf("Mas de medio millon de personas no tiene acceso a agua  potable\n");
    printf("segura a su ves el  problema del saneamiento, malas condiciones\n");
    printf("tambien aguas residuales; que se generan en casa en  los  baños\n");
    printf("es el causante de degradar el ecosistema y  el  mayor  problema\n");  
    printf("un grave deficit de financiamiento, como una  mala  gestion  de\n"); 
    printf("las redes hidricas en zonas rurales\n");
    printf("\n");
    printf("Ayuda a garantizar la disponibilidad y la gestion sostenible del agua \ny los servicios de saneamiento para todas las personas\n\n");

    esperar_exit();

}
void ver_tabla(float consumo_litros[MAX_DATOS][DIAS_SEMANA]){
    for (int i = 0; i < cantidadDatos; i++)
    {
        for (int j = 0; j < DIAS_SEMANA; j++)
        {
            printf("%.2f ",consumo_litros[i][j]);
        }
        printf("\n");
    }
    esperar_exit();
}
