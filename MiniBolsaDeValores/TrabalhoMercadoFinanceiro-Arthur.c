//INSTITUTO FEDERAL DA BAHIA - SALVADOR
//ALUNO: Arthur Silva Martins
//DISCIPLINA: Estrutura de Dados
//Orientador: Antonio Carlos

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

//Declaração de funções do menu de cadastro e oferta de venda
void CadastrarEOfertar();

//Declaração de funções do menu de Inserção
void InserirCompra();

//Declaração de funções do menu de listagem
void ListarOfertas();

//Declaração de funções do menu de exclusão
void Excluir();

//Função para limpar o buffer
void LimparBuffer();

//FUNÇÃO DE LIMPEZA DE BUFFER
void LimparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//FIM DA FUNÇÃO DE LIMPEZA

typedef struct Bolsa
{
    int quantidadepapel;
    char nome[10];
    int preco;
    int Flag1;

} Bolsa;

Bolsa *Papeis; //Declarando a struct em formma de ponteiro para alocar dinamicamente o espaço 


int main()
{   

    int opcao = 7;

    do  //MENU PRINCIPAL DO PROGRAMA
    {
        //system("clear||cls");

        printf("\n -----Bem Vindo(a) a Bolsa de Valores-----\n");
        printf("\n Digite 1 Para Cadastrar Papel:\n");
        printf("\n Digite 2 Para Comprar:\n");
        printf("\n Digite 3 Para Listar Ofertas:\n");
        printf("\n Digite 4 Para Excluir Oferta:\n");
        printf("\n Digite 0 Para Encerrar:\n");

        scanf("%d", &opcao);
        LimparBuffer(); //FUNÇÃO PARA LIMPAR O BUFFER DO TECLADO DEPOIS DAS LEITURAS COM SCANFS

        switch (opcao)
        {

        case 1:
            CadastrarEOfertar();
            break;

        case 2:
            InserirCompra();
            break;

        case 3:
            ListarOfertas();
            break;

        case 4:
            Excluir();
            break;

        default:
            printf("\nOpcao invalida ou programa encerrado\n");
        }

    } while (opcao != 0);

    return 0;
}


void CadastrarEOfertar() 
{

    int opcao = 0, qtd = 0;

    printf("\nDigite quantos papeis a bolsa ira ofertar na manha de hoje:\n");
    scanf("%d", &qtd);
    LimparBuffer();

    Papeis = (Bolsa *)(malloc(qtd * sizeof(Bolsa))); //ALOCANDO A QUANTIDADE DE PAPEIS USANDO A ESTRUTURA DINÂMICA

    if (Papeis == NULL) //VERIFICANDO SUCESSO DA ALOCAÇÃO
    {

        printf("\nErro na alocacao da memoria!!\n");

    }
    else
    {

        printf("\nEspaco reservado com sucesso!!\n");

        do //MENU PARA CADASTRO DO PAPEL, SERÁ INSERIDO NOS ESPAÇOS ALOCADOS DINAMICAMENTE, OS ITENS SÃO NOME, QUANTIDADE E PREÇO
        {
            for (size_t i = 0; i < sizeof(Papeis); i++) //DECLARAÇÃO COM SIZE_T PARA FAZER A COMPARAÇÃO COM O SIZEOF DA STRUCT PAPEIS.
            {
                if (Papeis[i].Flag1 == 0)
                {
                    printf("\nDigite o nome do papel a ser cadastrado:\n");
                    fgets(Papeis[i].nome, sizeof(Papeis[i].nome), stdin);

                    LimparBuffer();

                    printf("\nDigite a quantidade do papel a ser ofertado:\n");
                    scanf("%d", &Papeis[i].quantidadepapel);

                    LimparBuffer();

                    printf("\nDigite o preco em reais da unidade do papel que esta sendo ofertado:\n");
                    scanf("%d", &Papeis[i].preco);

                    LimparBuffer();

                    Papeis[i].Flag1 = 1; //INSERINDO A OFERTA COM SUCESSO NA STRUCT CORRESPONDENTE
                    break;
                } 
            }

            printf("\n1 - Continuar cadastrando\n0 - Sair\n"); //CADASTRANDO MAIS PAPEIS OU NÃO 
            scanf("%d", &opcao);
            LimparBuffer();

        } while (opcao != 0);
    }
}

void InserirCompra()
{

    int opcao = 0, y = 0, z = 0;
    size_t x = 0; //DECLARAÇÃO COM SIZE_T PARA FAZER COMPARAÇÃO COM A VARIAVEL "I" NOS "IFS" NECESSÁRIOS SEM AVISOS DE WARNINGS

    printf("\nBem vindo(a) ao menu de compras da nossa Bolsa, abaixo temos as ofertas do dia:\n");

    LimparBuffer();

    for (size_t i = 0; i < sizeof(Papeis); i++) 
    {
        if (Papeis[i].Flag1 == 1)
        {
            printf("\nOFERTA Numero: %d", i);
            printf("\nQuantidades Disponiveis Para Comprar: %d", Papeis[i].quantidadepapel);
            printf("\nValor Unitario: %d reais", Papeis[i].preco);
            printf("\nPapel: %s \n", Papeis[i].nome);
        }
    }

    do
    {
        printf("\nDigite o numero da oferta que deseja comprar: \n"); //ESCOLHENDO QUAL OFERTA DESEJARÁ COMPRAR
        scanf("%u", &x);
        LimparBuffer();

        for (size_t i = 0; i < sizeof(Papeis); i++)
        {   
            if (x == i)
            {
                printf("\nPois bem, voce selecionou a oferta numero %d, com nome: %s \n", i, Papeis[i].nome); //EXIBE O NOME E A OFERTA ESCOLHIDA

                printf("\nDigite a quantidade que deseja comprar: \n");
                scanf("%d", &z);
                LimparBuffer();

                printf("\nDigite o preco que voce ira ofertar: \n");
                scanf("%d", &y);
                LimparBuffer();

                if ((z != 0) && (z <= Papeis[i].quantidadepapel) && (y == Papeis[i].preco))
                {

                    Papeis[i].quantidadepapel = Papeis[i].quantidadepapel - z; //FAZ O DESCONTO DA QUANTIDADE DE PAPEIS COMPRADAS 

                    y = y * z; //FAZ O CALCULO DO VALOR GASTO POR VOCÊ NA COMPRA DAQUELE PAPEL

                    printf("\n Voce adquiriu %d unidades do papel %s e gastou um total de: %d reais \n", z, Papeis[i].nome, y);

                }
                else
                {
                    printf("\nAlgo deu errado, revise o preco ofertado ou a quantidade!!\n");

                }
            }
            printf("\n1 - Efetuar outra compra ou refazer uma compra \n0 - Sair\n");
            scanf("%d", &opcao);
            LimparBuffer();
        }
    } while (opcao != 0);
}


void ListarOfertas()
{
    int x = 0;

    do
    {
        printf("\n Digite 1 para listar os nomes das acoes disponiveis, 2 para informacoes detalhada ou 0 para sair:\n");
        scanf("%d", &x);

        if (x == 1) //OPÇÃO PARA LISTAR APENAS OS NOMES DOS PAPEIS DISPONÍVEIS
        {
            printf("\n*-------Bem vindo(a), abaixo temos a lista de nomes das acoes ofertadas no dia:-------*\n"); 

            LimparBuffer();

            for (size_t i = 0; i < sizeof(Papeis); i++)
            {
                if (Papeis[i].Flag1 == 1)
                {
                    printf("\nPapel: %s \n", Papeis[i].nome);
                }
            }
        }
        else if (x == 2) //OPÇÃO PARA LISTAGEM DOS PAPEIS DE FORMA DETALHADA
        {

            printf("\n*-------Bem vindo(a), abaixo temos a lista de ofertas do dia:-------*\n"); 

            LimparBuffer();

            for (size_t i = 0; i < sizeof(Papeis); i++)
            {
                if (Papeis[i].Flag1 == 1)
                {
                    printf("\nOFERTA Numero: %d", i);
                    printf("\nQuantidades Disponiveis Para Comprar: %d", Papeis[i].quantidadepapel);
                    printf("\nValor Unitario: %d reais", Papeis[i].preco);
                    printf("\nPapel: %s \n", Papeis[i].nome);
                }
            }
        }
        else if ((x != 1) && (x != 2) && (x != 0))
        {
            printf("\n Opcao invalida, tente novamente\n");
        }
    } while (x != 0);
}


void Excluir() //MENU DE EXCLUSÃO DE UMA OFERTA, FUNCIONA DA SEGUINTE FORMA: ESCOLHO QUAL OFERTA DESEJO EXCLUIR COM BASE NO INDICE DA STRUCT, VERIFICO A EXISTÊNCIA DE UMA OFERTA NAQUELE INDICE,
{              //CASO EXISTA OFERTA, A FLAG SERÁ 1, LOGO EU TRANSFORMO A FLAG PARA 0, LIBERANDO O ESPAÇO PARA SER PREENCHIDO POR OUTRO CADASTRO.

    int op = 0;
    size_t x = 0;

    do
    {
        printf("\n Digite 1 para excluir alguma acao ofertada ou 0 para sair:\n");
        scanf("%d", &op);

        LimparBuffer();

        if (op == 1)
        {
            for (size_t i = 0; i < sizeof(Papeis); i++)
            {
                if (Papeis[i].Flag1 == 1)
                {
                    printf("\nOFERTA Numero: %d", i);
                    printf("\nQuantidades Disponiveis Para Comprar: %d", Papeis[i].quantidadepapel);
                    printf("\nValor Unitario: %d reais", Papeis[i].preco);
                    printf("\nPapel: %s \n", Papeis[i].nome);
                }
            }

            printf("\n*-------Qual das ofertas acima deseja excluir? Digite o numero da oferta correspondente.-------*\n");
            scanf("%u", &x);

            for (size_t i = 0; i < sizeof(Papeis); i++)
            {
                if (Papeis[i].Flag1 == 1) ////VERIFICANDO EXISTÊNCIA DA OFERTA SELECIONADA
                {

                    if (i == x) 
                    {

                        printf("Nome: %s\n", Papeis[i].nome);
                        printf("Quantidade: %d\n", Papeis[i].quantidadepapel);
                        printf("Preco: %d\n", Papeis[i].preco);
                        printf("\n----------------\n");
                        Papeis[i].Flag1 = 0; //CASO EXISTA E SEJA CORRESPONDENTE AO QUE VOCÊ DESEJA, A FLAG VIRA 0 E A OFERTA É EXCLUIDA.
                        printf("Papel removido com sucesso\n");
                    }
                }
            }
        }
    } while (op != 0);
}
