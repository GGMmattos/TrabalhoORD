#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_REC_SIZE 512

void importacao(char nomeArquivoImpotacao[])
    {
        FILE *arquivoOriginal;  //arquivo que contém os jogos
        FILE *novoArquivo;      //Contém o novo arquivo com dados copiados do arquivo acima 
        int comp_reg;
        char buffer[100];
    
        arquivoOriginal = fopen(nomeArquivoImpotacao, "r");
        novoArquivo = fopen("dados", "w");

    //while (!feof(arquivoOriginal))
    //{
        int sucesso = proximoRegistro(buffer, arquivoOriginal);

        comp_reg = strlen(buffer); //calcula o tamanho do registro que esta no buffer
        fwrite(&comp_reg, sizeof(comp_reg), 1, novoArquivo); //grava o tamanho
        printf("\n%s\n", buffer);
        fwrite(buffer, sizeof(char),comp_reg, novoArquivo); // grava o buffer como uma sequencia de bytes
        // if (sucesso == 1)
        // {
        //     fwrite(buffer, sizeof(char), 64, novoArquivo);
        // }

        // printf("\n%d\n", comp_reg);
    }

    fclose(arquivoOriginal);
    fclose(novoArquivo);   
//}

int proximoRegistro(char registro[100], FILE *file)
{
    int contPipe = 0, tam = 0;
    char c;

    while (contPipe < 6)
    {   
        c = fgetc(file);
        
        registro[tam] = c; //atribui o caractere ao registro 

        if (c == '|')
        {
            contPipe += 1; //Conta os pipes quando encontrar, sendo que 4 pipes contituem 1 registro
        }
        tam += 1; //Com o acrecimo o programa trabalha em cima de outro registro com o mesmo procedimento acima.
     
        //printf("%c", c);
    }        

     return 1;    
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