/*
* Name: Lucas Corlete Alves de Melo - NUSP: 136676461; Jean Carlos Pereira Cassiano - NUSP: 138640008
* Course: SCC0607 - Estrutura de Dados III
* Professor: Cristina Dutra de Aguiar
* Project: Trabalho Introdutório, 1 e 2 de ED3
* Description: Este trabalho tem como objetivo armazenar dados em um arquivo binário bem como desenvolver funcionalidades para a manipulação desses dados. Novas funcionalidades serão adicionadas conforme o avançar da disciplina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/binaryoperations.h"



Registro* inicializarRegistro() {
    Registro *r = (Registro*)malloc(sizeof(Registro));
    if (r == NULL) {
        perror("Erro ao alocar memória para o registro");
        exit(EXIT_FAILURE);
    }
    r->removido = '0';
    r->grupo = 0;
    r->popularidade = 0;
    r->peso = 0;

    return r;
}


FILE *abrirArquivoLeitura(const char *nomeArquivo) {
    return fopen(nomeArquivo, "rb"); // Ponteiro no começo do arquivo
}

FILE *abrirArquivoEscrita(const char *nomeArquivo) {
    return fopen(nomeArquivo, "wb+"); // Ponteiro no começo do arquivo
}

void fecharArquivo(FILE *arquivo) {
    if (arquivo != NULL) {
        fclose(arquivo);
    }
}

Cabecalho* inicializarCabecalho() {
    Cabecalho* cabecalho = (Cabecalho*)malloc(sizeof(Cabecalho));
    cabecalho->status = '1';  // Inicializa como arquivo consistente
    cabecalho->proxRRN = 12;   // Valor padrão para o próximo RRN
    cabecalho->nroTecnologias = 0;  // Inicializa com zero tecnologias
    cabecalho->nroParesTecnologias = 0;  // Inicializa com zero pares de tecnologias
    return cabecalho;
}

int lerRegistro(FILE *arquivo, Registro *registro) {
    if (fread(registro, sizeof(Registro), 1, arquivo) == 1) {
        return 1; // Leitura bem-sucedida
    }
    return 0; // Falha na leitura
}

void atualizarCabecalho(FILE* arquivo, Cabecalho* cabecalho){
    fseek(arquivo, 0, SEEK_SET);
    fwrite(&cabecalho, 13, 1, arquivo);
}

int escreverRegistro(FILE *arquivo, const Registro *registro, int tamRegistro, Cabecalho *c){
    fseek(arquivo, c->proxRRN, SEEK_SET);
    if (fwrite(&registro, tamRegistro, 1, arquivo) != 1) {
        printf("Erro ao escrever os dados do registro\n");
        return 0; // Falha na escrita
    }
    c->nroParesTecnologias++;
    c->proxRRN += 76;
    char LIXO = '$';
    for (int i  = tamRegistro; i < 76; i++){
        if (fwrite(&LIXO, 1, 1, arquivo) != 1) {
            printf("Erro ao preencher os bytes restantes com '$'\n");
        return 0;
        }
    }
         
    //atualizarCabecalho(arquivo, c);
    return 1; // Escrita bem-sucedida
}

Registro* Convert(const char* Linha){
    Registro* registro = inicializarRegistro();
    // Inicializa a string variável com NULL (vazia)

    char *token = strtok((char *)Linha, ",");
    
    if (token != NULL) {
        registro->tecnologiaOrigem.tamanho = strlen(token);
        registro->tecnologiaOrigem.string = strdup(token);
        token = strtok(NULL, ",");
        }

    if (token != NULL) {
        registro->grupo = atoi(token);
        token = strtok(NULL, ",");
    }

    if (token != NULL) {
        registro->popularidade = atoi(token);
        token = strtok(NULL, ",");
    }

    if (token != NULL) {
        registro->tecnologiaDestino.tamanho = strlen(token);
        registro->tecnologiaDestino.string = strdup(token);
        token = strtok(NULL, ",");
    }

    if (token != NULL) {
        registro->peso = atoi(token);
    }
    
    registro->removido = '0';

    return registro;
}


    void LerBIN (FILE *arquivo) {
        // Move o cursor para o início do arquivo
        fseek(arquivo, 0, SEEK_SET);

        Registro* registro;
        
        while (fread(&registro, sizeof(Registro), 1, arquivo) == 1) {
            int tamRegistro = 21 + registro->tecnologiaDestino.tamanho + registro->tecnologiaOrigem.tamanho;
            char resto[76-tamRegistro];
            fread(resto, 1, 76-tamRegistro, arquivo);
            printf("%s, %d, %d, %s, %d\n", registro->tecnologiaOrigem.string, registro->grupo, registro->popularidade, registro->tecnologiaDestino.string, registro->peso); 
        }
    }



int main(){
    FILE *arquivo = fopen("../../docs/tecnologia.csv", "r"); // Ponteiro apontando para o arquivo csv
    
    FILE* BIN = abrirArquivoEscrita("data.bin");

    char linha[76];

    fgets(linha, sizeof(linha), arquivo); // Linha para ignorar primeira linha do arquivo de entrada
    Registro* r = inicializarRegistro();
    Cabecalho* c = inicializarCabecalho();
    fseek(BIN, 0, SEEK_SET);
    fwrite(&c, sizeof(Cabecalho), 1, BIN);
    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        r = Convert(linha);
        int tamRegistro = 21 + (r->tecnologiaDestino.tamanho) + (r->tecnologiaOrigem.tamanho);
        escreverRegistro(BIN, r, tamRegistro, c);
    }
    
    /*
    Estrutura de Decisão para executar funcionalidade escolhida pelo usuário
    switch (option){
        case 1:
        
        break;
    
        default:

        break;
    }
    */
    //LerBIN (BIN);
    printf("%d", c->nroParesTecnologias);
    fecharArquivo(BIN);
    fclose(arquivo);
    return 0;
}