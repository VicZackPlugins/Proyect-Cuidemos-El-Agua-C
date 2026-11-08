#include <stdio.h>

int validar_nota(float nota_valor)
{
    
    if (nota_valor >= 1 && nota_valor <= 7 ) /// rango entre 1.0 y 7.0 para la nota
    {
        return 1; /// return 1 si la condicion se cumple
    }
    return 0; /// si no..return 0, ya que no se cumple la condicion
    // osea, casi que un else
}

float calcular_promedio_curso(float notas[], int cantidad)
{
    float promedio=0;
    for(int i=0; i < cantidad; i++)
    {
        promedio+=notas[i];

    }
    promedio=promedio/cantidad;
    return promedio;
}

int contar_aprobados(float notas[], int cantidad)
{
    int contador=0;
    for(int i=0; i < cantidad; i++)
    {
        if (notas[i] >= 4)
        {
            contador+=1;
        }
    }
    return contador;
}

int main()
{
    int cantidad=0;
    printf("ingrese la cantidad de alumnos\n");
    scanf("%d", &cantidad);
    float notas[cantidad];
    for (int i = 0; i < cantidad; i++)
    {
        do
        {
            printf("ingrese la nota del alumno : %d\n", i+1);
            scanf("%f", &notas[i]);
            validar_nota(notas[i]);
            if(!(notas[i]>= 1 && notas[i] <= 7))
            {
                printf("nota : %d incorrecta, ingresala nuevamente porfavor\n", i+1);
                printf("--------------------------------------\n");     
            }
        }while(!(notas[i]>= 1 && notas[i] <= 7));
    }
    printf("Promedio general del curso: %.2f\n", calcular_promedio_curso(notas, cantidad));
    printf("Cantidad de alumnos aprobados: %d", contar_aprobados(notas, cantidad));
    return 0;
}