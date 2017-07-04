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
    arqAux->tam = -1;
    arqAux->setores = NULL;
    arqAux->ant = disco->arquivos;
    arqAux->prox = disco->arquivos;
    disco->arquivos->ant = arqAux;
    disco->arquivos->prox = arqAux;

    NoSetor* noAux = (NoSetor*)calloc(1, sizeof(NoSetor));
    disco->livres = (NoSetor*)calloc(1, sizeof(NoSetor));
    noAux->inicio = 0;
    noAux->fim = tamanho-1;
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

    if(tamanho==0){                     //Verifica se o arquivo é válido.
        return ARQUIVO_INEXISTENTE;
    }
    else if(tamanho >= d->espacoLivre){ //Verifica se o disco tem espaço suficiente para armazena-lo.
        return ESPACO_INSUFICIENTE;
    }
    else{
        rewind(arq);//Traz ponteiro para o começo do arquivo
        unsigned long tamanhoAux = tamanho;

        /*Inicio declaração de um nó arquivo*/
        NoArquivo* noArquivo = (NoArquivo*)calloc(1, sizeof(NoArquivo));
        strcpy(noArquivo->nome, arquivo);
        noArquivo->tam = tamanho;
        noArquivo->setores = (NoSetor*)calloc(1, sizeof(NoSetor));
        noArquivo->setores->inicio = -1;
        noArquivo->setores->fim = -1;
        noArquivo->ant = noArquivo;
        noArquivo->prox = noArquivo;
        noArquivo->setores->ant = noArquivo->setores;
        noArquivo->setores->prox = noArquivo->setores;

        noArquivo->ant = d->arquivos->prox->ant;
        d->arquivos->prox->ant = noArquivo;
        noArquivo->prox = d->arquivos->prox;
        d->arquivos->prox = noArquivo;
        /*Fim declaração nó arquivo*/

        while (tamanhoAux > 0) {
            if(((d->livres->prox->fim - d->livres->prox->inicio)+1) >= tamanhoAux){ //Eu adiciono o arquivo completo caso haja espaço
                fread(d->disco+(d->livres->prox->inicio), 1, tamanho, arq); //Adicionando bit a bit no meu disco
                
                /*Adicionando um novo setor como ultimo nó*/
                NoSetor* novoNoSetorArquivo = (NoSetor*)calloc(1, sizeof(NoSetor));
                novoNoSetorArquivo->inicio = d->livres->prox->inicio;
                novoNoSetorArquivo->fim = d->livres->prox->inicio+tamanho;

                noArquivo->setores->ant->prox = novoNoSetorArquivo;
                novoNoSetorArquivo->ant = noArquivo->setores->ant;
                novoNoSetorArquivo->prox = noArquivo->setores;
                noArquivo->setores->ant = novoNoSetorArquivo;

                /*Se o arquivo for do mesmo tamanho que o setor livre,
                 eu reaponto o nó sentinela do primeiro para o segundo,
                 se caso o arquivo é menor, eu apenas atualizo o valor
                 de inicio do setor livre*/
                if((d->livres->prox->fim - d->livres->prox->inicio)+1 == tamanho){
                    d->livres->prox->prox->ant = d->livres->prox->ant;
                    NoSetor* aux = d->livres->prox;
                    d->livres->prox = d->livres->prox->prox;
                    free(aux);
                }
                else{
                    d->livres->prox->inicio += tamanho;
                }

                tamanhoAux=0;
            }
            else{
                fread(d->disco+(d->livres->prox->inicio), 1, d->livres->prox->fim - d->livres->prox->inicio, arq);
                NoSetor* noSetorArquivo = (NoSetor*)calloc(1, sizeof(NoSetor));
                noSetorArquivo->inicio = d->livres->prox->inicio;
                noSetorArquivo->fim = noSetorArquivo->inicio+(d->livres->prox->fim - d->livres->prox->inicio);

                /*Adicionando um novo setor como ultimo nó*/
                NoSetor* novoNoSetor = (NoSetor*)calloc(1, sizeof(NoSetor));
                noArquivo->setores->ant->prox = novoNoSetor;
                novoNoSetor->ant = noArquivo->setores->ant;
                novoNoSetor->prox = noArquivo->setores;
                noArquivo->setores->ant = novoNoSetor;

                novoNoSetor->inicio = d->livres->prox->inicio;
                novoNoSetor->fim = d->livres->prox->inicio+(d->livres->prox->fim - d->livres->prox->inicio);

                d->livres->prox->prox->ant = d->livres->prox->ant;
                NoSetor* aux = d->livres->prox;
                d->livres->prox = d->livres->prox->prox;
                free(aux);

                tamanhoAux -= d->livres->prox->fim - d->livres->prox->inicio;
            }
        }
    }
    d->espacoLivre -= tamanho;
    d->espacoOcupado += tamanho;
    d->qtdeArquivos++;
    fclose(arq);
    return SUCESSO;
}

TipoRetorno RemocaoDoDisco(Disco* d, char* nome){
    NoArquivo* noArqAux = d->arquivos->prox;

    while (noArqAux != d->arquivos && strcmp(nome, noArqAux->nome)!=0){ //Laço para chegar até o nó do arquivo
        noArqAux = noArqAux->prox;
    }

    if(strcmp(nome, noArqAux->nome)!=0){
        return ARQUIVO_INEXISTENTE;
    }

    //Atualiza os valores de espaço livre e ocupado
    d->espacoLivre += ((noArqAux->setores->fim - noArqAux->setores->inicio)+1);
    d->espacoOcupado -= ((noArqAux->setores->fim - noArqAux->setores->inicio)+1);

    //Reaponta do primeiro setor para o segundo
    noArqAux->setores->prox->ant = noArqAux->setores->ant;
    noArqAux->setores = noArqAux->setores->prox;

    /*
     * Possibilidades:
     * Ao lado direito do primeiro: atualiza o fim pra menos,
     * Ao lado esquerdo do primeiro: atualiza o inicio pra mais,
     * Não fica ao lado de nenhum antigo setor livre. Criando um novo nó de espaço livre,
     */
    devolve_livre(d->livres, noArqAux->setores->prox);

    //Reaponta os nós arquivos e remove nó
    noArqAux->prox->ant = noArqAux->ant;
    noArqAux->ant->prox = noArqAux->prox;

    d->qtdeArquivos--;
    NoArquivo* noDeleta = noArqAux;
    free(noDeleta);
    return SUCESSO;
}

TipoRetorno RecuperaArquivo(Disco* d, char* nome, FILE* arquivoFisico){
    NoArquivo* noArqAux = d->arquivos->prox;
    int i;

    while (noArqAux != d->arquivos && strcmp(nome, noArqAux->nome) != 0){    //Laço para chegar até o nó do arquivo
        noArqAux = noArqAux->prox;
    }
    
    if(strcmp(nome, noArqAux->nome)!=0){
        return ARQUIVO_INEXISTENTE;
    }

    NoSetor* noSetorAux = noArqAux->setores->prox;

    while (noSetorAux->inicio != -1) {
        for(i=noSetorAux->inicio; i <= noSetorAux->fim; i++){
            fwrite(d->disco+i, sizeof(char), 1, arquivoFisico); //Escreve no arquivo fisico.
        }
        noSetorAux = noSetorAux->prox;
    }
    
    return SUCESSO;
}

void devolve_livre(NoSetor* sentinela, NoSetor* disponivel){
    if (disponivel == NULL){
        return;
    }

    NoSetor* aux = sentinela->prox;
    //posiciona o aux
    while(aux != sentinela && disponivel->inicio > aux->inicio){
        aux = aux->prox;
    }
    no_insereAntes(aux, disponivel);
    no_verifica(disponivel);
}

void no_insereAntes(NoSetor* referencia, NoSetor* novo){
    novo->ant = referencia->ant;
    novo->prox = referencia;
    referencia->ant->prox = novo;
    referencia->ant = novo;
}

void no_verifica(NoSetor* no){
    //Verifica se ha a necessidade de mesclar com o no anterior
    if(no->inicio == no->ant->fim + 1){
        no->inicio = no->ant->inicio;
        //no_destroi(no->ant);
    }
    //Verifica se ha a necessidade de mesclar com o no posterior
    if(no->fim == no->prox->inicio+1){
        no->fim = no->prox->fim;
        //no_destroi(no->prox);
    }
}