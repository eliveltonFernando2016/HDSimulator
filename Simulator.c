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

    disco->disco = (void*)calloc(tamanho, sizeof(void));
    
    NoArquivo* arqAux = (NoArquivo*)calloc(1, sizeof(NoArquivo));
    disco->arquivos = (NoArquivo*)calloc(1, sizeof(NoArquivo));
    arqAux->nome = NULL;
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

TipoRetorno GravacaoEmDisco(Disco* d, char* arquivo){ //nome arquivo deve conter o caminho absoluto ou relativo do arquivo
    
}

TipoRetorno RemocaoDoDisco(Disco* d, char* nome); //somente o nome do arquivo sem o caminho

TipoRetorno RecuperaArquivo(Disco* d, char* nome, FILE* arquivoFisico);