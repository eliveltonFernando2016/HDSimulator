/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: elivelton
 *
 * Created on 8 de Junho de 2017, 14:36
 */

#include "Simulator.h"

int main() {
    TipoRetorno retorno;
    
    Disco* disco = disco_cria("Elivelton", 100000000);
    
    retorno = GravacaoEmDisco(disco, "/home/elivelton/Downloads/teste.jpg");
    if(retorno!=0){
        return (EXIT_FAILURE);
    }
    
    retorno = GravacaoEmDisco(disco, "Input/CRER.pdf");
    if(retorno!=0){
        return (EXIT_FAILURE);
    }
    
    retorno = GravacaoEmDisco(disco, "/home/elivelton/Música/Suit & Tie (Dillon Francis Remix).mp3");
    if(retorno!=0){
        return (EXIT_FAILURE);
    }

    retorno = RemocaoDoDisco(disco, "Input/CRER.pdf");
    if(retorno != 0){
        return (EXIT_FAILURE);
    }

    GravacaoEmDisco(disco, "/home/elivelton/Dropbox/disney2017.pdf");
    if(retorno != 0){
        return (EXIT_FAILURE);
    }

    printf("Quantidade de Arquivos: %d\n", disco->qtdeArquivos);
    printf("Quantidade Livre: %lu\n", disco->espacoLivre);
    printf("Quantidade Ocupada: %lu", disco->espacoOcupado);
    
    /*Incio Abertura e validação do arquivo*/
    FILE* recuperado;
    recuperado = fopen("OutPut/disney2017.pdf", "wb");
    if(!recuperado){
        perror("Erro na abertura do arquivo");
    }
    /*Fim Abertura e Validação arquivo*/

    retorno = RecuperaArquivo(disco, "/home/elivelton/Dropbox/disney2017.pdf", recuperado);
    fclose(recuperado);
    
    if(retorno != 0){
        remove("OutPut/CRER.pdf");
        return(EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}