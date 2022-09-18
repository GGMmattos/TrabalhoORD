#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_REC_SIZE 512
#define COMP_CAMPO 60

struct{
    int cont_reg;
}cab; // cab



int buscaLinha(char campo[], int tamanho, FILE *file){
    int i = 0;
    char k = fgetc(file);

    
    while (k != '\n')
    {
        if (feof(file)) 
            return -1;

        if (i < tamanho - 1)
            campo[i++] = k;

        k = fgetc(file);
    }

    campo[i] = 0;

    return i;

}


int byteoffset(int posChave)
{
    return posChave  + sizeof(cab);
}

void operacoes(char *argv)
{
    FILE *dados;
    FILE *operacoes;
    char campo[MAX_REC_SIZE];
    char buffer[MAX_REC_SIZE];
    char opera;
    int  posChave;

    operacoes = fopen(argv, "rb"); //Abre o arquivo de operações para leitura binária 
        if(fopen("dados.dat", "r+b") == NULL){  // Abre o arquivo dados que contém os dados rsrs
            printf("ERRO O ARQUIVO DE DADOS NÃO EXISTE");
    }

    while ((opera = fgetc(operacoes) != EOF)) // realiza as operações até que o arquivo esteja vazio
    {
        buffer[0] = 0;
        fgetc(operacoes);

        switch (opera)
        {
        case 'b':
            printf("MODO BUSCA ATIVADO");
            break;
        case 'i':
            printf("MODO INSERCAO ATIVADO");
        case 'r':
            printf("MODO REMOCAO ATIVADO");
        default:
            break;
        }
    }
    



}

void importacao(char nomeArquivoImpotacao[])
    {
        FILE *arquivoOriginal;  //arquivo que contém os jogos
        FILE *novoArquivo;      //Contém o novo arquivo com dados copiados do arquivo acima 
        short comp_reg;
        int cabecalho = -1; //cabeçalho LED
        char buffer[MAX_REC_SIZE];
    
        if((arquivoOriginal = fopen(nomeArquivoImpotacao, "r")) && (novoArquivo = fopen("dados", "w")) != NULL )
        {
            fwrite(&cabecalho, sizeof(int), 1, novoArquivo);
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
            printf("ARQUIVOS IMPORTADOS COM SUCESSO");
            fclose(arquivoOriginal);
            fclose(novoArquivo);  
        }else{
            perror("FALHA AO IMPORTAR OS DADOS, ABORTANDO!!!");
    }

        }

int proximoRegistro(char registro[], FILE *file)
{
    int contPipe = 0, i = 0;
    char c = ' '; 

    //memset(registro, '\0', 64); 
    while (contPipe < 6)
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
            contPipe += 1; //Conta os pipes quando encontrar, sendo que 6 pipes contituem 1 registro
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