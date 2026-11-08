#include <stdio.h>

int tamaño = 3; /// ajuste para las dimensiones del tablero

int inicializar_tablero(int tablero[tamaño][tamaño], int tamaño)
{
    for(int i=0; i<tamaño; i++) /// llenamos el tablero con 0 
    {
        for(int j=0; j<tamaño; j++)
        {
            tablero[i][j]=0;
        }
    }
    return 0;
}

    //// f = fila

    //// c = columna

int colocar_barco(int tablero[tamaño][tamaño], int f, int c)
{
    do
    {
        printf("seleccione la fila (0, 1, 2)\n");
        scanf("%d", &f);
        printf("seleccione la columna (0, 1, 2)\n");
        scanf("%d", &c);
        if(f<0 || f>2 || c<0 || c>2)
        {
            printf("posicion (%d, %d) invalida..intente otra vez\n", f, c);
        }
        else
        {
            tablero[f][c]=1;
            printf("barco colocado en la posicion (%d, %d)\n", f, c);
        }
    }while(f<0 || f>2 || c<0 || c>2);
}

int disparar(int tablero[tamaño][tamaño], int f, int c)
{
    do
    {
        printf("seleccione la fila (0, 1, 2)\n");
        scanf("%d", &f);
        printf("seleccione la columna (0, 1, 2)\n");
        scanf("%d", &c);
        if(f<0 || f>2 || c<0 || c>2)
        {
            printf("posicion (%d, %d) invalida..intente otra vez\n", f, c);
        }
    }while(f<0 || f>2 || c<0 || c>2);
}

int main()
{
    int tablero[tamaño][tamaño]; /// inicializamos el tablero
    int f; //// fila
    int c; //// columna
    printf("rellenamos el tablero con 0\n");
    inicializar_tablero(tablero, tamaño);
    printf("verificacion de proceso\n");
    for(int i=0; i<tamaño; i++)
    {
        for(int j=0; j<tamaño; j++)
        {
            printf("%d ", tablero[i][j]);
        }
        printf("\n");
    }
    printf("tablero creado!\n");
    printf("///// TEAM DEATHMACH ////\n");
    printf("---Coloca tu barco---\n");
    colocar_barco(tablero, f, c);
    printf("---Disparale al barco---\n");
    if(disparar(tablero, f, c)==1)
    {
        printf("barco encontrado en la posicion (%d, %d)\n", f, c);
        printf("Impacto!\n");
    }
    else
    {
        printf("no se encontro un barco en la posicion (%d, %d)...\n", f, c);
        printf("cayo al agua..\n");        
    }
    return 0;
}