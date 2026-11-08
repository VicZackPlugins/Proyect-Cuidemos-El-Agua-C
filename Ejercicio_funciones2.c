#include <stdio.h>
void mostrar_inventario(int stock[],int tam){
    printf("[");
    for(int i=0;i<tam;i++){
        printf("%d ",stock[i]);
    }
    printf("]\n");
}
int realizar_venta(int stock[], int id_producto, int cantidad)
{
    if(id_producto<0 || id_producto>4 || cantidad>stock[id_producto])
    {
        printf("Error: Código inválido o stock insuficiente.");
        return 0;
    }else{
        return 1;
    }
}
int main()
{
    int tam=5;
    int stock[tam];
    int id_producto;
    int cantidad;
    printf("Ingresa el stock de productos (5 productos)\n");
    for(int i=0; i<tam; i++)
    {
        scanf("%d", &stock[i]);
    }
    mostrar_inventario(stock, tam);
    printf("Ingresa la ID del producto\n");
    scanf("%d", &id_producto);
    printf("Ingresa la cantidad\n");
    scanf("%d", &cantidad);
    if(realizar_venta(stock, id_producto, cantidad))
    {
        stock[id_producto]-=cantidad;
        printf("stock actualizado del producto %d : %d unidades .\n", id_producto, stock[id_producto]);
    }
    else
    {
        printf("operacion cancelada\n");
    }
    return 0;
}