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
    Disco* disco = disco_cria("Elivelton", 10000000);
    GravacaoEmDisco(disco, "Input/teste.jpg");
    GravacaoEmDisco(disco, "Input/disney2017.pdf");
    GravacaoEmDisco(disco, "Input/Suit&Tie.mp3");
    
    RemocaoDoDisco(disco, "Input/Suit&Tie.mp3");
    
    GravacaoEmDisco(disco, "Input/quadricas.pdf");
    GravacaoEmDisco(disco, "Input/TrabGA.ggb");
    
    RemocaoDoDisco(disco, "Input/quadricas.pdf");
    
    GravacaoEmDisco(disco, "Input/abada.jpg");

    printf("Quantidade de Arquivos: %d\n", disco->qtdeArquivos);
    printf("Quantidade Livre: %lu\n", disco->espacoLivre);
    printf("Quantidade Ocupada: %lu", disco->espacoOcupado);
    
    /*Incio Abertura e validação do arquivo*/
    FILE* recuperado;
    recuperado = fopen("OutPut/quadricas.pdf", "wb");
    if(!recuperado){
        perror("Erro na abertura do arquivo");
    }
    /*Fim Abertura e Validação arquivo*/

    RecuperaArquivo(disco, "Input/quadricas.pdf", recuperado);

    return (EXIT_SUCCESS);
}