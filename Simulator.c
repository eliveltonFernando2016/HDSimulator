/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Simulator.h"

Disco* disco_cria(char* nome, unsigned long tamanho){
    Disco* disco = (Disco*)calloc(1, sizeof(Disco));
    disco->espacoLivre = tamanho;
    disco->espacoOcupado = 0;
    disco->tamDisco = tamanho;
    strcpy(disco->nome, nome);
    disco->qtdeArquivos = 0;

    disco->disco = (void*)calloc(tamanho, sizeof(void));

    NoArquivo* arqAux = (NoArquivo*)calloc(1, sizeof(NoArquivo));
    disco->arquivos = (NoArquivo*)calloc(1, sizeof(NoArquivo));
    arqAux->tam = 0;
    arqAux->setores = NULL;
    arqAux->ant = disco->arquivos;
    arqAux->prox = disco->arquivos;
    disco->arquivos->ant = arqAux;
    disco->arquivos->prox = arqAux;

    NoSetor* noAux = (NoSetor*)calloc(1, sizeof(NoSetor));
    disco->livres = (NoSetor*)calloc(1, sizeof(NoSetor));
    noAux->inicio = 0;
    noAux->fim = tamanho;
    noAux->ant = disco->livres;
    noAux->prox = disco->livres;
    disco->livres->prox = noAux;
    disco->livres->ant = noAux;

    return disco;
}

TipoRetorno GravacaoEmDisco(Disco* d, char* arquivo){
    /*Incicio Abertura Arquivo*/
    FILE *arq;
	    
    arq = fopen(arquivo, "rb");
    if(!arq){
        perror("Erro na abertura do arquivo");
        return ARQUIVO_INEXISTENTE;
    }

    fseek(arq, 0, SEEK_END);
    int tamanho = ftell(arq);
    /*Fim Abertura e Validação arquivo*/

    if(tamanho==0){
        return ARQUIVO_INEXISTENTE;
    }
    else{
        rewind(arq);//Traz ponteiro para o começo do arquivo
        int tamanhoAux = tamanho;
        
        if(tamanho <= d->espacoLivre){ //Verifica se o disco tem espaço suficiente para adicionar o arquivo
            /*Inicio declaração de um nó arquivo*/
            NoArquivo* noArquivo = (NoArquivo*)calloc(1, sizeof(NoArquivo));
            strcpy(noArquivo->nome, arquivo);
            noArquivo->tam = tamanho;
            noArquivo->setores = (NoSetor*)calloc(1, sizeof(NoSetor));
            noArquivo->setores->inicio = 0;
            noArquivo->setores->fim = 0;
            noArquivo->ant = noArquivo->setores;
            noArquivo->prox = noArquivo->setores;
            
            noArquivo->ant = d->arquivos->prox->ant;
            d->arquivos->prox->ant = noArquivo;
            noArquivo->prox = d->arquivos->prox;
            d->arquivos->prox = noArquivo;
            /*Fim declaração nó arquivo*/

            while (tamanhoAux>0) {
                fread(d->disco, 1, 1, arq);
                d->livres->prox->inicio++;
                if(d->livres->prox->inicio == d->livres->prox->fim){//Verifica se a partição comporta o arquivo completo
                    d->livres->prox->prox->ant = d->livres->prox->ant;
                    d->livres->prox = d->livres->prox->prox;
                }
                tamanhoAux--;
                d->espacoLivre--;
                d->espacoOcupado++;
            }
        }
        else{
            return ESPACO_INSUFICIENTE;
        }
    }
    d->qtdeArquivos++;
    fclose(arq);
    return SUCESSO;
}

TipoRetorno RemocaoDoDisco(Disco* d, char* nome); //somente o nome do arquivo sem o caminho

TipoRetorno RecuperaArquivo(Disco* d, char* nome, FILE* arquivoFisico);