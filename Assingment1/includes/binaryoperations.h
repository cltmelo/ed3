#ifndef BINARYOPERATIONS_H
#define BINARYOPERATIONS_H

#include "../includes/funcoesFornecidas.h"
#include <stdio.h>


// Quantidade de bytes do registro de dados
#define TAM_REGISTRO 76
// Quantidade de bytes da parte fixa do registro
#define TAM_REGISTRO_FIXO 21
// Quantidade de bytes do cabeçalho
#define TAM_CABECALHO 13

// Caractere padrão para o preenchimento de bytes vazios no registro
#define LIXO '$'

// Caracteres padrão para remoção lógica
#define REMOVIDO '1'
#define NAO_REMOVIDO '0'


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
    char removido; // '1' (REMOVIDO) para removido e '0' (NAO_REMOVIDO) para não removido

    // seguintes campos presentes no arquivo .csv fornecido
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
int escreverRegistro(FILE *arquivo, const Registro *registro);



/*
-----------------------------------------------------------------------------------------------
Funionalidades requeridas:
-----------------------------------------------------------------------------------------------
*/

// 1. Create Table
// 2. Select From
// 3. Select Where
// 4. Select RRN



#endif /* BINARYOPERATIONS_H */