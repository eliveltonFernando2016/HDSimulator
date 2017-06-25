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
    Disco* disco = disco_cria("Elivelton", 1000000);
    GravacaoEmDisco(disco, "arquivo_teste.jpg"); 
    GravacaoEmDisco(disco, "/home/elivelton/Dropbox/disney2017.pdf");
    GravacaoEmDisco(disco, "/home/elivelton/Dropbox/STB _ CEP _ VOUCHER.pdf");
    GravacaoEmDisco(disco, "/home/elivelton/Dropbox/Relatorio de Visita Tecnica.pdf");
    GravacaoEmDisco(disco, "/home/elivelton/Dropbox/Fotos/IMG_6278.JPG");
    
    
    
    return (EXIT_SUCCESS);
}