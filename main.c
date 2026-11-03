#include <stdio.h>

// ======= Configuracion: ======== //

#define DIAS_SEMANA 7
#define TAM_FIJO 5

// =============== //

int main() {

    char nombre[][32];                  // Nombre de los hogares

    int personas[],                     // Cantidad de personas por hogar
        limitediario[],                 // Promedio litros a la semana por hogar
        consumoLitros[][DIAS_SEMANA];   // Consumo de litros por hogar por día


    return 0;

}
void registrarDatos(char nombre[][32], int personas[], int csumoLitros[][DIAS_SEMANA]) { //aqui se debe arreglar
    int cant, litros;//cantidad y litros
    char nom;//nombre
    printf("ingrese nombre del hogar\n");
     scanf("%d",&nom);
    printf("cantidad de ocupantes de la vivienda\n");
     scanf("%d",&cant);
     printf("consumo de litros\n");
     scanf("%d",&litros);
}
