#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

    void importacao(char nomeArquivoImpotacao[])
    {
        FILE *arquivoOriginal;  //Contem arquivo que contém os jogos
        FILE *novoArquivo;      //Contém o novo arquivo com dados copiados do arquivo acima 
        int cabecalho = -1;

        arquivoOriginal = fopen(nomeArquivoImpotacao, "r");
        novoArquivo = fopen("dados.dat", "w");

        if (arquivoOriginal == NULL || novoArquivo == NULL)
        {
            fprintf(stderr, "Não foi possível abrir os arquivos");
            exit(EXIT_FAILURE);
        }




    }

int main(int argc, char *argv[]) {

    if (argc == 3 && strcmp(argv[1], "-i") == 0) {

        printf("Modo de importacao ativado ... nome do arquivo = %s\n", argv[2]);
        importacao(argv[2]);

    } else if (argc == 3 && strcmp(argv[1], "-e") == 0) {

        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        // executar_operacoes(argv[2]));

    } else if (argc == 2 && strcmp(argv[1], "-p") == 0) {

        printf("Modo de impressao da LED ativado ...\n");
        // imprimir_led();

    } else {

        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-i|-e) nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);

    }


    return 0;
}