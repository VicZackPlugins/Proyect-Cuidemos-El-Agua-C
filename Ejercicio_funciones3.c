#include <stdio.h>

float ingresar_temperaturas(float temps[], int dias)
{
    for(int i=0; i<dias; i++)
    {
        do
        {
            printf("solicitando temperatura (dia %d)\n", i+1);
            scanf("%f", &temps[i]);
            if(temps[i]<-50 || temps[i]>60)
            {
                printf("ERROR: Temperatura ingresada no valida, vuelve a intentarlo (rango permitido -50.0 / 60.0)\n");
            }
        }while(temps[i]<-50 || temps[i]>60);
    }
    return 0;
}

float obtener_extremos(float temps[], int dias)
{
    float max_frio=temps[0];
    float max_calor=temps[0];
    float diferencia=0;
    for(int i=0; i<dias; i++)
    {
        if(temps[i]>max_calor)
        {
            max_calor=temps[i];
        }
    }
    for(int i=0; i<dias; i++)
    {
        if(temps[i]<max_frio)
        {
            max_frio=temps[i];
        }
    }
    ///// calculamos la diferencia entre estos 2 valores
    diferencia=max_frio-max_calor;
    return diferencia;
}

float obtener_promedio(float temps[], int dias, float promedio)
{
    float suma=0;
    for(int i=0; i<dias; i++)
    {
        suma+=temps[i];
    }
    promedio=suma/dias;
    return promedio;
}

float contar_dias_sobre_promedio(float temps[], int dias, float promedio)
{
    float contador=0;
    for(int i=0; i<dias; i++)
    {
        if(temps[i]>promedio)
        {
            contador++;
        }
    }
    return contador;
}



int main()
{
    int dias=7;
    float temps[dias];
    float promedio=0;
    ingresar_temperaturas(temps, dias);
    printf("Temperatura promedio semanal: %.2f °C\n", obtener_promedio(temps, dias, promedio));
    printf("Diferencia entre temperatura máxima y mínima: %.2f °C\n", obtener_extremos(temps, dias));
    printf("Cantidad de días sobre el promedio: %.0f dias\n", contar_dias_sobre_promedio(temps, dias, promedio)); /// esto es lo unico que no funciona por ahora
    return 0;
}