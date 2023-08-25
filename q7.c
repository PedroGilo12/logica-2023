#include <stdio.h>
#include <string.h>
#include <ctype.h>

void simplificar_demorgan(char *texto) 
{
    char temp[1000];
    int i = 0, j = 0;

    while (texto[i] != '\0') 
    {
        if (texto[i] == '~') 
        {
            i++;
            temp[j++] = '(';

            while (texto[i] >= 'M' && texto[i] <= 'z') 
            {
                temp[j++] = '~';
                temp[j++] = texto[i++];
            }

            temp[j++] = ')';
        } 
        else 
        {
            temp[j++] = texto[i++];
        }
    }

    temp[j] = '\0';

    strcpy(texto, temp);
}

int aplicar_matematica(char *expressao) 
{
    int i = 0;
    while (expressao[i] != '\0') 
    {
        if (expressao[i] == '^') 
        {
            expressao[i] = '*';
        } 
        else if (expressao[i] == 'v') 
        {
            expressao[i] = '+';
        } 
        else if (expressao[i] >= 'M' && expressao[i] <= 'z') 
        {
            expressao[i] = '1';
        } 
        else if (expressao[i] == '~') 
        {
            expressao[i] = '0';
            int j = i + 1;
            while (expressao[j] >= 'M' && expressao[j] <= 'z') 
            {
                j++;
            }
            for (int k = j; k > i + 1; k--) 
            {
                expressao[k] = expressao[k - 1];
            }
            expressao[i + 1] = '*';
            i = j;
        } 
        else if (expressao[i] == '-' && expressao[i + 1] == '>') 
        {
            expressao[i] = '=';
            expressao[i + 1] = '=';
            expressao[i + 2] = '1';
            i += 2;
        }
        i++;
    }

    int resultado;
    sscanf(expressao, "%d", &resultado);

    return resultado;
}

int main() 
{
    char texto1[1000], texto2[1000];

    printf("Digite a primeira sentença: ");
    fgets(texto1, sizeof(texto1), stdin);
    texto1[strcspn(texto1, "\n")] = '\0';

    printf("Digite a segunda sentença: ");
    fgets(texto2, sizeof(texto2), stdin);
    texto2[strcspn(texto2, "\n")] = '\0';

    for (int i = 0; texto1[i]; i++) {
        texto1[i] = toupper(texto1[i]);
    }

    for (int i = 0; texto2[i]; i++) {
        texto2[i] = toupper(texto2[i]);
    }

    simplificar_demorgan(texto1);
    int formula1 = aplicar_matematica(texto1);

    simplificar_demorgan(texto2);
    int formula2 = aplicar_matematica(texto2);

    if ((formula1 && formula2 > 0) || (formula1 && formula2 <= 0)) 
    {
        printf("\nAs sentenças avaliadas são equivalentes.\n");
    } 
    else 
    {
        printf("\nAs duas sentenças não são equivalentes.\n");
    }

    return 0;
}
