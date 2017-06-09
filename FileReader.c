/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>

#include "FileReader.h"

int FileReader(char* fileName){
    ReaderFile* arq = (ReaderFile*)calloc(1, sizeof(ReaderFile));
    arq->arq = fopen(fileName, "rb");
    if(!arq->arq){
        perror("Erro na abertura do arquivo");
        exit(1);
    }
 
    fseek(arq, 0, SEEK_END);
    arq->sizeFile = ftell(arq);
    fclose(arq);
    
    return arq->sizeFile;
}