#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

typedef struct No
{
    double dado;
    struct No *proximo;
} No;

typedef struct
{
    No *topo;
} Pilha;

void inicializar(Pilha *pilha)
{
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, double valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("Erro: Falha na alocacao de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

double desempilhar(Pilha *pilha)
{
    if (pilha->topo != NULL)
    {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    }
    else
    {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

double avaliarExpressaoPosfixada(const char *expressao)
{
    Pilha pilha;
    inicializar(&pilha);
    char *token = strtok((char *)expressao, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]))
        {
            empilhar(&pilha, atof(token));
        }
        else
        {
            double operando2 = desempilhar(&pilha);
            double operando1 = desempilhar(&pilha);
            switch (token[0])
            {
            case '+':
                empilhar(&pilha, operando1 + operando2);
                break;
            case '-':
                empilhar(&pilha, operando1 - operando2);
                break;
            case '*':
                empilhar(&pilha, operando1 * operando2);
                break;
            case '/':
                if (operando2 != 0.0)
                {
                    empilhar(&pilha, operando1 / operando2);
                }
                else
                {
                    printf("Erro: Divisao por zero\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case '^':
                empilhar(&pilha, pow(operando1, operando2));
                break;
            case 'r':
                empilhar(&pilha, pow(operando1, 1.0 / operando2));
                break;
            case 'l':
                empilhar(&pilha, log10(operando1));
                break;
            case 's':
                empilhar(&pilha, sin(operando1));
                break;
            case 'c':
                empilhar(&pilha, cos(operando1));
                break;
            case 't':
                empilhar(&pilha, tan(operando1));
                break;
            default:
                printf("Erro: Operador invalido\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }

    return desempilhar(&pilha);
}

void reverseString(char *str)
{
    if (str == NULL)
        return;
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

double avaliarExpressaoPrefixada(const char *expressao)
{
    Pilha pilha;
    inicializar(&pilha);
    char *expressao_copy = strdup(expressao);

    strrev(expressao_copy);

    char *token = strtok(expressao_copy, " ");
    while (token != NULL)
    {
        if (isdigit(token[0]))
        {
            empilhar(&pilha, atof(token));
        }
        else
        {

            double operando1 = desempilhar(&pilha);
            double operando2 = desempilhar(&pilha);

            switch (token[0])
            {
            case '+':
                empilhar(&pilha, operando1 + operando2);
                break;
            case '-':
                empilhar(&pilha, operando1 - operando2);
                break;
            case '*':
                empilhar(&pilha, operando1 * operando2);
                break;
            case '/':
                if (operando2 != 0.0)
                {
                    empilhar(&pilha, operando1 / operando2);
                }
                else
                {
                    printf("Erro: Divisao por zero\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case '^':
                empilhar(&pilha, pow(operando1, operando2));
                break;
            case 'r':
                empilhar(&pilha, pow(operando1, 1.0 / operando2));
                break;
            case 'l':
                empilhar(&pilha, log10(operando1));
                break;
            case 's':
                empilhar(&pilha, sin(operando1));
                break;
            case 'c':
                empilhar(&pilha, cos(operando1));
                break;
            case 't':
                empilhar(&pilha, tan(operando1));
                break;
            default:
                printf("Erro: Operador invalido\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }

    free(expressao_copy);

    return desempilhar(&pilha);
}

int main()
{
    const char *expressaoPosfixada = "3 5 2 * +";
    char *expressaoPosfixada_copy = strdup(expressaoPosfixada);
    double resultadoPosfixado = avaliarExpressaoPosfixada(expressaoPosfixada_copy);

    printf("Resultado pos fixado: %f\n", resultadoPosfixado);

    free(expressaoPosfixada_copy);

    const char *expressaoPrefixada = "+ 3 * 5 2";
    double resultadoPrefixado = avaliarExpressaoPrefixada(expressaoPrefixada);

    printf("Resultado pre fixado: %f\n", resultadoPrefixado);

    return 0;
}
