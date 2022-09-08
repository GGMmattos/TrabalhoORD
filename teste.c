#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_REC_SIZE 512


        


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


        FILE *arquivoOriginal;  //arquivo que contém os jogos
        FILE *novoArquivo;      //Contém o novo arquivo com dados copiados do arquivo acima 
        int comp_reg;
        char buffer[100];
    
        arquivoOriginal = fopen("game1reg.txt", "r");
        novoArquivo = fopen("dadoslkkuyku", "w");

        comp_reg = strlen(buffer); //calcula o tamanho do registro que esta no buffer
        fwrite(&comp_reg, sizeof(comp_reg), 1, novoArquivo); //grava o tamanho
        fwrite("buffer", sizeof(char),comp_reg, novoArquivo); // grava o buffer como uma sequencia de bytes
  
    return 0;
}
