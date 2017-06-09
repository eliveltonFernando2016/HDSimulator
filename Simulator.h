/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulator.h
 * Author: elivelton
 *
 * Created on 8 de Junho de 2017, 14:38
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nosetor{
    unsigned long inicio;
    unsigned long fim;
    struct nosetor* prox;
    struct nosetor* ant;
}NoSetor;
 
typedef struct noarquivo{
    char nome[40];
    unsigned long tam;
    NoSetor* setores;
    struct noarquivo* prox;
    struct noarquivo* ant;
}NoArquivo;
 
typedef struct{
    char nome[40];
    void* disco;
    NoSetor* livres;
    NoArquivo* arquivos;
    unsigned long tamDisco;
    unsigned long espacoLivre;
    unsigned long espacoOcupado;
    unsigned long qtdeArquivos;    
}Disco;
 
typedef enum{
    FALSE = 0,
    TRUE = 10
}Boolean;
 
typedef enum{
    SUCESSO = 0,
    ESPACO_INSUFICIENTE,
    ARQUIVO_INEXISTENTE
}TipoRetorno;
 
Disco* disco_cria(char* nome, unsigned long tamanho);

TipoRetorno GravacaoEmDisco(Disco* d, char* arquivo); //nome arquivo deve conter o caminho absoluto ou relativo do arquivo

TipoRetorno RemocaoDoDisco(Disco* d, char* nome); //somente o nome do arquivo sem o caminho

TipoRetorno RecuperaArquivo(Disco* d, char* nome, FILE* arquivoFisico);

#endif /* SIMULATOR_H */

