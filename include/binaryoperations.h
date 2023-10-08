#ifndef BINARYOPERATIONS_H
#define BINARYOPERATIONS_H

#include <stdio.h>


// Cabeçalho com 13 bytes
typedef struct {
    char status;  // 1 para arquivo consistente, 0 para incosistente
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
} Cabecalho;

typedef struct {
    int tamanho;
    char* string;
} StringVariavel;

// Registro com 76 bytes
typedef struct {
    char removido; // 1 para removido e 0 para não removido

    // seguintes campos presentes no arquivo csv fornecido pela professora
    int grupo;
    int popularidade;
    int peso;
    StringVariavel tecnologiaOrigem;
    StringVariavel tecnologiaDestino;

    
} Registro;

// Função para abrir um arquivo binário para leitura
FILE *abrirArquivoLeitura(const char *nomeArquivo);

// Função para abrir um arquivo binário para escrita
FILE *abrirArquivoEscrita(const char *nomeArquivo);

// Função para fechar um arquivo binário
void fecharArquivo(FILE *arquivo);

// Função para ler um registro do arquivo binário
int lerRegistro(FILE *arquivo, Registro *registro);

// Função para escrever um registro no arquivo binário
int escreverRegistro(FILE *arquivo, const Registro *registro, int tamRegistro, Cabecalho* c);

#endif /* BINARYOPERATIONS_H */