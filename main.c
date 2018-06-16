#include <stdio.h>
#include <stdlib.h>

typedef struct mode_1{
    float valor;
    int i;      //linha
    int j;      //coluna
    struct mode_1 *prox;
    struct mode_1 *ant;
} valor_matriz;

int verifica_valores (int tamanho_matriz, int digitado_usuario){   //digitado usuario é o q precisa conferir
    if (digitado_usuario>tamanho_matriz || digitado_usuario<0){
        printf("\n<<VALOR INVALIDO>>\n");
        return 1;
    } else {
        return 0;       //valor válido
    }
}

int verificar_matriz (valor_matriz *first, int linha_atual, int coluna_atual){
    valor_matriz *tmp2;
    tmp2=first;

    while(tmp2!=NULL){
        if (linha_atual==(*tmp2).i && coluna_atual==(*tmp2).j){
            printf("\nA posicao que voce utilizou ja esta sendo usada!\n");
            return -1;
        }
        tmp2=(*tmp2).prox;
    }
    return 0;
}

valor_matriz *criar_matriz (valor_matriz *first, int coluna, int linha){
    valor_matriz *tmp;
    tmp=first;
    int verificar;
    int linha_atual, coluna_atual;
    float valor_atual;

    if(tmp!=NULL){                  //struct receber valor dos ponteiros proximo e do anterior
        while((*tmp).prox!=NULL){   //para criar sempre outra struct
            tmp=(*tmp).prox;
        }
        (*tmp).prox=malloc(sizeof(valor_matriz));
        (*(*tmp).prox).ant=tmp;
        tmp=(*tmp).prox;
        (*tmp).prox=NULL;       //CONFERIU QUE PONTEIRO PROXIMO NAO ESTÁ APONTANDO PARA NADA!
    }else{                      //1a struct, q n tem ponteiro anterior
        tmp=malloc(sizeof(valor_matriz));
        (*tmp).ant=NULL;
        (*tmp).prox=NULL;
        first=tmp;
    }
    //criar proximo
    printf("Digite o numero que deseja adicionar: ");
    scanf("%f", &valor_atual);
    printf("Digite a linha que deseja colocar o valor: ");
    setbuf(stdin, NULL);
    scanf("%d", &linha_atual);
    while (linha_atual>linha || linha_atual<0){
        printf("O valor que voce digitou nao eh valido!\n");
        printf("Digite novamente o valor!\n");
        setbuf(stdin, NULL);
        scanf("%d", &linha_atual);
        printf("\n");
    }
    printf("Digite a coluna que deseja colocar o valor: ");
    setbuf(stdin, NULL);
    scanf("%d", &coluna_atual);
    while (coluna_atual>coluna || coluna_atual<0){
        printf("O valor que voce digitou nao eh valido!\n");
        printf("Digite novamente o valor!\n");
        setbuf(stdin, NULL);
        scanf("%d", &coluna_atual);
        printf("\n");
    }

    verificar = verificar_matriz(first, linha_atual, coluna_atual);
    while (verificar!=0){
        printf("\nDigite novamente o valor da linha: ");
        setbuf(stdin, NULL);
        scanf("%d", &linha_atual);
        while (linha_atual>linha || linha_atual<0){
            printf("O valor que voce digitou nao eh valido!\n");
            printf("Digite novamente o valor!\n");
            setbuf(stdin, NULL);
            scanf("%d", &linha_atual);
            printf("\n");
        }
        printf("Digite novamente o valor da coluna: ");
        setbuf(stdin, NULL);
        scanf("%d", &coluna_atual);
        while (coluna_atual>coluna || coluna_atual<0){
            printf("O valor que voce digitou nao eh valido!\n");
            printf("Digite novamente o valor!\n");
            setbuf(stdin, NULL);
            scanf("%d", &coluna_atual);
            printf("\n");
        }
        verificar = verificar_matriz(first, linha_atual, coluna_atual);
    }
    //SE ESTIVER CERTINHO, CRIA STRUCT!
    (*tmp).i=linha_atual;
    (*tmp).j=coluna_atual;
    (*tmp).valor=valor_atual;

    return first;
}

void consultar_valor(valor_matriz *first, int linha_max, int coluna_max){
    int bandeira=0;     //Se ela receber 1, quer dizer que encontrou um numero !=0
    int linha, coluna;
    valor_matriz *tmp3;
    tmp3 = first;
    printf("\nQual a linha e a coluna (NESSA ORDEM!) que você deseja saber o valor?");
    setbuf(stdin, NULL);
    scanf("%d %d", &linha, &coluna);
    while (linha<0 || linha>linha_max || coluna<0 || coluna>coluna_max){
        printf("Valor digitado errado!\n");
        printf("Digite novamente o valor da linha e da coluna (NESSA ORDEM!): ");
        setbuf(stdin, NULL);
        scanf("%d %d", &linha, &coluna);
    }

    while(tmp3!=NULL){
        if ((*tmp3).i==linha && (*tmp3).j==coluna){
            printf("\nNumero achado!\n");
            printf("Valor do numero digitado na linha %d e coluna %d: %f\n\n", linha, coluna, (*tmp3).valor);
            bandeira=1;
            break;
        }
        tmp3=(*tmp3).prox; //vai p proxima struct
    }
    if (bandeira==0){
        printf("Valor do numero na linha %d e coluna %d: 0\n\n", linha, coluna);
    }
}

void soma_linhas (valor_matriz *first, int linha){

    int lin;
    int confere;     //confere se valor digitado pelo usuário está certo
    float res;
    valor_matriz*tmp;
    tmp=first;
    res=0;

    printf("Qual linha voce gostaria de operar?\n");
    setbuf(stdin, NULL);
    scanf("%d", &lin);
    confere = verifica_valores(linha, lin);
    while (confere!=0){
        printf("Linha invalida!\n");
        printf("Qual linha voce gostaria de operar?\n");
        setbuf(stdin, NULL);
        scanf("%d", &lin);
        confere = verifica_valores(linha, lin);
    }

    while(tmp!=NULL){
        if((*tmp).i==lin){
            res+=(*tmp).valor;
        }
            tmp=(*tmp).prox;
    }

    printf("A Soma da linha resulta: %f\n\n", res);
}

void soma_colunas (valor_matriz *first, int coluna){
    int cool;
    int confere;     //confere se valor digitado pelo usuário está certo
    float res;
    valor_matriz*tmp;
    tmp=first;
    res=0;

    printf("Qual coluna voce gostaria de operar?\n");
    setbuf(stdin, NULL);
    scanf("%d", &cool);

    confere = verifica_valores(coluna, cool);
    while (confere!=0){
        printf("Coluna invalida!\n");
        printf("Qual coluna voce gostaria de operar?\n");
        setbuf(stdin, NULL);
        scanf("%d", &cool);
        confere = verifica_valores(coluna, cool);
    }

    while(tmp!=NULL){
        if((*tmp).j==cool){
            res+=(*tmp).valor;
        }
            tmp=(*tmp).prox;
    }

    printf("A soma das colunas resulta:%f\n\n", res);
}

void exclusao (valor_matriz *first){
    valor_matriz*tmp;
    tmp=first;


    while((*tmp).prox!=NULL){
        free((*tmp).ant);
        tmp=(*tmp).prox;
    }
        free(tmp);
}

void mudanca (valor_matriz*first){
    valor_matriz*tmp;
    tmp=first;
    int a;
    int b;
    float c;

    printf("Escolha a linha que deseja mudar\n");
    scanf("%d", &a);

    printf("Escolha a coluna que deseja mudar\n");
    scanf("%d", &b);

    printf("Qual o valor que voce deseja colocar nessa posicao?\n");
    scanf("%f", &c);

    while(tmp!=NULL){
        if((*tmp).i==a && (*tmp).j==b){
            (*tmp).valor=c;
        }
        tmp=(*tmp).prox;
    }
}

int main()
{
    int i;      //linha
    int j;      //coluna
    char continuar;     //ve se pessoa quer criar outra matriz
    int cont1=0;      //contador que serve para ver quantos numeros a pessoa adiiconou
    int o_que_fazer;  //escolhe o que fazer agora
    valor_matriz *first=NULL;

    printf("Digite a quantidade de linhas (m) da matriz: ");
    scanf("%d", &i);
    while (i<=0){
        printf("\nQuantidade de linhas incorreta, coloque um valor acima de 0");
        scanf("%d", &i);
    }
    printf("Digite a quantidade de colunas (n) da matriz: ");
    scanf("%d", &j);
    while (j<=0){
        printf("\nQuantidade de linhas incorreta, coloque um valor acima de 0");
        scanf("%d", &j);
    }
    j--;
    i--;

    while (1){
        printf("\nO que voce deseja fazer agora?\n");
        printf("(0) Adicionar um valor na matriz\n");
        printf("(1) Consultar um valor da matriz\n");
        printf("(2) Consultar a soma dos valores de uma linha\n");
        printf("(3) Consultar a soma dos valores de uma coluna\n");
        printf("(4) Excluir a matriz\n");
        printf("(5) Atribuir um novo valor para a matriz\n");
        printf("(6) Finalizar programa\n");
        setbuf(stdin, NULL);
        scanf("%d", &o_que_fazer);
        printf("\n");
        //printf("linha -- %d \ncoluna -- %d\n\n", i, j);
        //printf("%d", cont1);
        //printf("\ntamanho total: %d\n", ((i+1)*(j+1))-cont1);

        if (o_que_fazer==0){    //Adicionar valor matriz
            if (cont1>=((i+1)*(j+1))){      //para que a pessoa nao adicione mais valores do que a matriz permite
                printf("Voce ja colocou valores para toda a matriz, nao tem como adicionar mais valores\n");
            } else {
                first = criar_matriz(first, j, i);  //ADD CÉLULA NA MATRIZ
                cont1++;
            }
            printf("\n\n");
        }

        if(o_que_fazer==1){
            consultar_valor(first, i, j);
        }

        if(o_que_fazer==2){
            soma_linhas(first, i);
        }

        if (o_que_fazer==3){
            soma_colunas(first, j);
        }

        if (o_que_fazer==4){
            exclusao(first);
            first=NULL;
            printf("Voce deseja criar outra matriz (S/N)?\n");
            setbuf(stdin, NULL);
            scanf("%c", &continuar);
            if (continuar=='n' || continuar=='N'){
                printf("voce nao quer mais criar uma matriz, entao o programa ira fechar!\n");
                return 0;
            }
            if (continuar=='s' || continuar=='S'){
                printf("Digite a quantidade de linhas (m) da matriz: ");
                scanf("%d", &i);
                while (i<=0){
                    printf("\nQuantidade de linhas incorreta, coloque um valor acima de 0");
                    scanf("%d", &i);
                }
                printf("Digite a quantidade de colunas (n) da matriz: ");
                scanf("%d", &j);
                while (j<=0){
                    printf("\nQuantidade de linhas incorreta, coloque um valor acima de 0");
                    scanf("%d", &j);
                }
                cont1=0;    //para zerar o contador tbm
                j--;
                i--;
            }
            while (continuar!='S' && continuar!='s' && continuar!='N' && continuar!='n'){
                printf("\nO que voce digitou eh invalido! digite novamente! SO S ou N");
                setbuf(stdin, NULL);
                scanf("%c", &continuar);
            }
        }

        if (o_que_fazer==5){
            mudanca (first);
        }

        if (o_que_fazer==6){
            return 0;
        }
        if (o_que_fazer!=0 && o_que_fazer!=1 && o_que_fazer!=2 && o_que_fazer!=3 && o_que_fazer!=4 && o_que_fazer!=5 && o_que_fazer!=6){
            printf("Valor digitado para a escolha do que fazer eh invalido! Digite novamente!!\n");
        }
    }

    return 0;
}
