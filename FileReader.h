/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileReader.h
 * Author: elivelton
 *
 * Created on 8 de Junho de 2017, 16:52
 */

#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>


typedef struct{
    FILE *arq;
    int sizeFile;
}ReaderFile;

int FileReader(char* fileName);

#endif /* FILEREADER_H */