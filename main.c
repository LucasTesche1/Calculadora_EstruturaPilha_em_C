    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <math.h>
    #include <string.h>
    
    #ifndef M_PI
    #define M_PI (3.14159265358979323846)
    #endif
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

    double sqrt_custom(double x) {
        if (x >= 0.0)
            return sqrt(x);
        else {
            printf("Erro: Raiz de número negativo\n");
            exit(EXIT_FAILURE);
        }
    }

    double log_custom(double x) {
        if (x > 0.0)
            return log10(x);
        else {
            printf("Erro: Logaritmo de número não positivo\n");
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
                    empilhar(&pilha, sin(operando1 * (M_PI / 180.0))); 
                break;
                case 'c':
                    operando1 = desempilhar(&pilha);
                    empilhar(&pilha, cos(operando1 * (M_PI / 180.0))); 
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

void inverterString(char *str) {
    if (str == NULL)
        return;
    int length = strlen(str);
    int start = 0;
    int end = length - 1;

    while (start < end) {
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

        inverterString(expressao_copy);

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
            empilhar(&pilha, sqrt_custom(operando1));
            break;
        case 'l':
            empilhar(&pilha, log_custom(operando1));
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
        const char *expressaoPosfixada = "3 4 + 5 t *";
        char *expressaoPosfixada_copy = strdup(expressaoPosfixada);
        double resultadoPosfixado = avaliarExpressaoPosfixada(expressaoPosfixada_copy);

        printf("Resultado pos fixado: %.2f\n", resultadoPosfixado);

        free(expressaoPosfixada_copy);

        /*const char *expressaoPrefixada = "(3 + 4) * 5";
        double resultadoPrefixado = avaliarExpressaoPrefixada(expressaoPrefixada);

        printf("Resultado pre fixado: %f\n", resultadoPrefixado);

        */

        return 0;
    }

    /*Este código agora suporta as seguintes operações:
    - + para soma
    - - para subtração
    - * para multiplicação
    - / para divisão
    - ^ para potenciação
    - r para radiciação
    - l para logaritmo na base 10
    - s para seno
    - c para cosseno
    - t para tangente
    */

   /*
   TESTES COM ÊXITO: 1,2,3,4

   TESTES COM PROBLEMAS: 
   */