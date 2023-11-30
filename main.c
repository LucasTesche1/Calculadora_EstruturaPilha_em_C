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

typedef struct
{
    char items[100][100];
    int top;
} Stack;

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

double sqrt_custom(double x)
{
    if (x >= 0.0)
        return sqrt(x);
    else
    {
        printf("Erro: Raiz de número negativo\n");
        exit(EXIT_FAILURE);
    }
}

double log_custom(double x)
{
    if (x > 0.0)
        return log10(x);
    else
    {
        printf("Erro: Logaritmo de número não positivo\n");
        exit(EXIT_FAILURE);
    }
}

// Funções relacionadas à pilha
void initialize(Stack *stack)
{
    stack->top = -1;
}

int isEmpty(Stack *stack)
{
    return stack->top < 0;
}

void push(Stack *stack, char *item)
{
    if (stack->top == 100 - 1)
    {
        printf("Erro: A pilha está cheia\n");
        exit(EXIT_FAILURE);
    }
    strcpy(stack->items[++stack->top], item);
}

char *pop(Stack *stack)
{

    return stack->items[stack->top--];
}

// Função para converter notação pós-fixada para notação infixa
void postfixToInfix(char *expression)
{
    Stack operandStack;
    initialize(&operandStack);

    char *token = strtok(expression, " ");

    while (token != NULL)
    {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            push(&operandStack, token);
        }
        else if (strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0)
        {
            char operand[100];
            strcpy(operand, pop(&operandStack));

            char temp[100];
            sprintf(temp, "%s(%s)", token, operand);

            push(&operandStack, temp);
        }
        else if (strcmp(token, "log") == 0)
        {
            char operand[100];
            strcpy(operand, pop(&operandStack));

            char temp[100];
            sprintf(temp, "log(%s)", operand);

            push(&operandStack, temp);
        }
        else
        {
            char operand2[100], operand1[100];
            strcpy(operand2, pop(&operandStack));
            strcpy(operand1, pop(&operandStack));

            char temp[100];
            sprintf(temp, "(%s %s %s)", operand1, token, operand2);

            push(&operandStack, temp);
        }

        token = strtok(NULL, " ");
    }

    printf("Expressão Infixa: %s\n", operandStack.items[0]);
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
            double operando1, operando2;
            switch (token[0])
            {
            case '+':
                operando2 = desempilhar(&pilha);
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, operando1 + operando2);
                break;
            case '-':
                operando2 = desempilhar(&pilha);
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, operando1 - operando2);
                break;
            case '*':
                operando2 = desempilhar(&pilha);
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, operando1 * operando2);
                break;
            case '/':
                operando2 = desempilhar(&pilha);
                operando1 = desempilhar(&pilha);
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
                operando1 = desempilhar(&pilha);
                operando2 = desempilhar(&pilha);
                empilhar(&pilha, pow(operando1, operando2));
                break;
            case 'r':
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, sqrt_custom(operando1));
                break;
            case 'l':
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, log_custom(operando1));
                break;
            case 's':
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, sin(operando1));
                break;
            case 'c':
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, cos(operando1));
                break;
            case 't':
                operando1 = desempilhar(&pilha);
                empilhar(&pilha, tan(operando1));
                break;
            default:
                printf("Erro: Operador '%c' invalido\n", token[0]);
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, " ");
    }

    return desempilhar(&pilha);
}

void inverterString(char *str)
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

int main()
{
    const char *expressaoPosfixada = "0.5 45 sen 2 ^ +";
    char *expressaoPosfixada_copy = strdup(expressaoPosfixada);
    double resultadoPosfixado = avaliarExpressaoPosfixada(expressaoPosfixada_copy);

    printf("Resultado pos fixado: %.3f\n", resultadoPosfixado);

    free(expressaoPosfixada_copy);

    char expression[] = "0.5 45 sen 2 ^ +";
    postfixToInfix(expression);

    return 0;
}

/* RESULTADOS COM ÊXITO:

1 - 3 4 + 5 *
    (3 + 4) * 5
    35

2 - 7 2 * 4 +
    7 * 2 + 4
    18

3 - 8 5 2 4 + * +
    8 + (5 * (2 + 4))
    38

4 - 6 2 / 3 + 4 *
    (6 / 2 + 3) * 4
    24

5 - 9 5 2 8 * 4 + * +
    9 + (5 * (2 + 8 * 4))
    109

6 - 2 3 + log 5 /
    Aprox. 0.140

7 - 10 log 3 ^ 2 +
    5

8 - 45 60 + 30 cos *
    Aprox. 16,20

9 - 0.5 45 sen 2 ^ +
    Aprox. 2,30

10 - 3 4 + 5 tan *
     Aprox. -23,66

     */
