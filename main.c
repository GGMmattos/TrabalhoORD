#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_REC_SIZE 512

struct{
    short cont_reg;
}cab; // cabeçalho do arquivo ( 4 bytes)


void importacao(char nomeArquivoImpotacao[])
    {
        FILE *arquivoOriginal;  //arquivo que contém os jogos
        FILE *novoArquivo;      //Contém o novo arquivo com dados copiados do arquivo acima 
        short comp_reg;
        char buffer[MAX_REC_SIZE];
    
        if((arquivoOriginal = fopen(nomeArquivoImpotacao, "r")) && (novoArquivo = fopen("dados", "w")) != NULL )
        {
            while (!feof(arquivoOriginal))
            {
                int sucesso = proximoRegistro(buffer, arquivoOriginal);
                if (sucesso == 1)
                {  
                    comp_reg = strlen(buffer);
                    fwrite(&comp_reg, sizeof(comp_reg), 1, novoArquivo); //grava o tamanho
                    fwrite(buffer, sizeof(char),comp_reg, novoArquivo); // grava o buffer como uma sequencia de bytes
                    //printf("%d\n", comp_reg);
                    //printf("%s", buffer);
                }
            }
            printf("ARQUIVOS IMPORTADOS COM SUCESSO");
            fclose(arquivoOriginal);
            fclose(novoArquivo);  
    }else{
        perror("FALHA AO IMPORTAR OS DADOS, ABORTANDO!!!");
    }


        }

int proximoRegistro(char registro[64], FILE *file)
{
    int contPipe = 0, i = 0;
    char c; 

    memset(registro, '\0', 64); 
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
            contPipe += 1; //Conta os pipes quando encontrar, sendo que 4 pipes contituem 1 registro
        }
       
    }        
    registro[i] = '\0';  
    return 1;
}
/**/
        /*case 'i':
            buscaLinha(buffer, COMP_REG, operacoesFile);
            strncpy(chave, buffer, 6);
            printf("\nINSERCAO DO REGISTRO DE CHAVE %s", chave);

            if (busca (chave, dados) != -1){

                printf("ERRO: CHAVE %s JA EXISTE NO REGISTRO", chave);
                break;
            }

            rewind(dados);
            
            fread(&cab, sizeof(cab), 1, dados);
           
            posChave = cab.cont_reg;

            if (posChave == -1){

                fseek(dados, 0, SEEK_END);
                fwrite(buffer, sizeof(char), COMP_REG, dados);
                printf("\nLOCAL DE INSERCAO: FIM DO ARQUIVO\n");
            }

            else{

                cab.cont_reg = PED(dados, posChave);
                
                fwrite(buffer, sizeof(char), COMP_REG, dados);
                rewind(dados);
                fwrite(&cab, sizeof(cab), 1, dados);

                printf("\nLOCAL: RRN = %d (byte-offset %d) [reutilizado]\n", posChave, byteoffset(posChave));
            }
            
            break;
            
*/
        /*case 'r':  
        
            buscaLinha(chave, 7, operacoesFile);
            printf("\nREMOCAO DO REGISTRO %s\n", chave);
            rewind(dados);

            fread(&cab, sizeof(cab), 1, dados);

            posChave = busca(chave, dados);
            
            if (posChave == -1)
            {
                puts("Erro: registro nao encontrado!");
                break;
            }
            // cab.cont_reg = posChave;

            // rewind(dados);
            // fwrite(&cab.cont_reg, sizeof(cab), 1, dados);
            
            fputc('*', dados);
            fwrite(&cab.cont_reg, sizeof(int), 1, dados);

            cab.cont_reg = posChave;

            rewind(dados);
            fwrite(&cab, sizeof(cab), 1, dados);

            printf("REMOVIDO");
            printf("\n");
            printf("Posicao: RRN = %d (byte-offset %d)\n", posChave, byteoffset(posChave));
            break;

            default:
            printf("\n NAO FOI POSSIVEL REMOVER");
        

            fseek(dados, 0, SEEK_END);
            if (((ftell(dados) - sizeof(cab)) % COMP_REG) != 0)  ftell = Retorna o valor atual do indicador de posição do fluxo. 
                                                                Esse valor pode ser usado pela função fseek com origem SEEK_SET 
                                                                para retornar o indicador a posição atual.
            {
              printf("NAO FOI POSSIVEL REALIZAR A OPERACAO");
              exit(1);
            }
        
        
        }*/
        
                //}
      //  }
//}

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