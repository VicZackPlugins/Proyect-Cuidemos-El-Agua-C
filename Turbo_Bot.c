#include <stdio.h>
#include <string.h>

int main()
{

    char texto[32];
    char vocales[5]={'a', 'e', 'i', 'o', 'u'};
    int contador=0;
    scanf("%s", texto);

    int tam_string;

    for(int i=0; i<strlen(texto); i++)
    {
        for(int j=0; j<5; j++)
        {
            if (texto[i]==vocales[j]) contador++;
        }
        
    }
    printf("%d", contador);



    return 0;
}