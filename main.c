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
    Disco* disco = disco_cria("Elivelton", 100000000);
    GravacaoEmDisco(disco, "/home/elivelton/Downloads/teste.jpg");
    GravacaoEmDisco(disco, "/home/elivelton/Música/Suit & Tie (Dillon Francis Remix).mp3");
    GravacaoEmDisco(disco, "Input/CRER.pdf");
    
    RemocaoDoDisco(disco, "/home/elivelton/Música/Suit & Tie (Dillon Francis Remix).mp3");

    //GravacaoEmDisco(disco, "/home/elivelton/Dropbox/disney2017.pdf");
//    GravacaoEmDisco(disco, "Input/TrabGA.ggb");
//    
//    RemocaoDoDisco(disco, "Input/quadricas.pdf");
//    
//    GravacaoEmDisco(disco, "Input/abada.jpg");

    printf("Quantidade de Arquivos: %d\n", disco->qtdeArquivos);
    printf("Quantidade Livre: %lu\n", disco->espacoLivre);
    printf("Quantidade Ocupada: %lu", disco->espacoOcupado);
    
    /*Incio Abertura e validação do arquivo*/
    FILE* recuperado;
    recuperado = fopen("OutPut/CRER.pdf", "wb");
    if(!recuperado){
        perror("Erro na abertura do arquivo");
    }
    /*Fim Abertura e Validação arquivo*/

    RecuperaArquivo(disco, "Input/CRER.pdf", recuperado);
    fclose(recuperado);

    return (EXIT_SUCCESS);
}