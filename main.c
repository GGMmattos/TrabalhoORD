#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_REC_SIZE 512

void importacao(char nomeArquivoImpotacao[])
    {
        FILE *arquivoOriginal;  //Contem arquivo que contém os jogos
        FILE *novoArquivo;      //Contém o novo arquivo com dados copiados do arquivo acima 
        int cabecalho = -1;
        int tamreg;
        char buffer[MAX_REC_SIZE];
        

        arquivoOriginal = fopen(nomeArquivoImpotacao, "r");
        novoArquivo = fopen("dados.dat", "w");

        /*if (arquivoOriginal == NULL || novoArquivo == NULL) //Condicional para saber se algum arquivo deu erro ao abrir
        {
            fprintf(stderr, "Não foi possível abrir os arquivos");
            exit(EXIT_FAILURE);
        }*/
        /* 
             tamreg = strlen(buffer); //calcula o tamanho do registro que esta no buffer
             fwrite(&rec_lgth, sizeof(rec_lgth), 1, fd); //grava o tamanho
             fwrite(buffer, sizeof(char), rec_lgth, fd); // grava o buffer como uma sequencia de bytes*/
        
        //fwrite(&cabecalho, sizeof(int), 1, novoArquivo);



        //while (!feof(arquivoOriginal))
        //{
            buffer[0] = '\0'; //zera o buffer
            int sucessor = proximoRegistro(buffer, arquivoOriginal);
            printf("testre");
            if (sucessor == 1)
            {  
                tamreg = strlen(buffer);
                printf("%d", tamreg);
                fwrite(&tamreg, sizeof(tamreg), 1, novoArquivo);
                fwrite(buffer, sizeof(char), tamreg, novoArquivo);
            }
            
        //}
        fclose(arquivoOriginal);
        fclose(novoArquivo);
        
    }

int proximoRegistro(char registro[64], FILE *file)
{
    int contPipe = 0, tam = 0;
    char c;

    //memset(registro, '\0', 64); //colocar o \0 até dar 64  //memset preenche uma quantidade de uma determinada área da memória com um dado valor

    while (contPipe < 6 && tam < 64)
    {   

        c = fgetc(file);

        /* if (c == EOF) //verifica se é um valor vazio
        {
            return -1;
        }*/
        
        registro[tam] = c; //atribui o caractere ao registro 

        if (c == '|')
        {
            contPipe += 1; //Conta os pipes quando encontrar, sendo que 4 pipes contituem 1 registro
        }
        tam += 1; //Com o acrecimo o programa trabalha em cima de outro registro com o mesmo procedimento acima.
    return 1;
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "-i") == 0)
    {
        printf("\nNome do arquivo em que ocorrera a importacao = %s\n", argv[2]);
        printf("\n");
        importacao(argv[2]);
    }
    else if (argc == 3 && strcmp(argv[1], "-e") == 0)
    {

        printf("\nModo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        //operacoes(argv[2]);
    }
    else if (argc == 2 && strcmp(argv[1], "-p") == 0)
    {
        printf("\nModo de impressao da PED ativado ...\n");
        //imprime_ped();
    }
    else
    {

        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-i|-e) nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}