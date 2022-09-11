#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_REC_SIZE 512

void importacao(char nomeArquivoImpotacao[])
    {
        FILE *arquivoOriginal;  //arquivo que contém os jogos
        FILE *novoArquivo;      //Contém o novo arquivo com dados copiados do arquivo acima 
        short comp_reg;
        char buffer[MAX_REC_SIZE];
    
        arquivoOriginal = fopen(nomeArquivoImpotacao, "r");
        novoArquivo = fopen("dados", "w");
      while (!feof(arquivoOriginal))
      {
        int sucesso = proximoRegistro(buffer, arquivoOriginal);
         if (sucesso == 1)
         {  
            comp_reg = strlen(buffer);
            fwrite(&comp_reg, sizeof(comp_reg), 1, novoArquivo); //grava o tamanho
            fwrite(buffer, sizeof(char),comp_reg, novoArquivo); // grava o buffer como uma sequencia de bytes
         }
      }
    fclose(arquivoOriginal);
    fclose(novoArquivo);  
    }

 
//}

int proximoRegistro(char registro[64], FILE *file)
{
    int contPipe = 0, i = 0;
    char c;
    
    //memset(registro, '\0', 100); //colocar o \0 até dar 64 
    while (contPipe < 6 ||  c == '\0')
    {   
        c = fgetc(file);
        if (c == EOF)
        {
            return -1;
        }

        registro[i] = c; //atribui o caractere ao registro 
        i += 1;

        if (c == '|')
        {
            contPipe += 1; //Conta os pipes quando encontrar, sendo que 4 pipes contituem 1 registro
        }
       
    }        
    registro[i] = '\0';  
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