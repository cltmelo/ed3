/*
* Name: Lucas Corlete Alves de Melo - NUSP: 13676461; Jean Carlos Pereira Cassiano - NUSP: 13864008
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
    cabecalho->status = '1';  
    cabecalho->proxRRN = 0;   
    cabecalho->nroTecnologias = 0;  
    cabecalho->nroParesTecnologias = 0;
    return cabecalho;
}

void atualizarCabecalho(FILE* arquivo, Cabecalho* cabecalho){
    fseek(arquivo, 0, SEEK_SET);
    fwrite(&cabecalho->status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho->proxRRN, sizeof(int), 1, arquivo);
    fwrite(&cabecalho->nroTecnologias, sizeof(int), 1, arquivo);
    fwrite(&cabecalho->nroParesTecnologias, sizeof(int), 1, arquivo);
}

int escreverRegistro(FILE *arquivo, const Registro *registro, int tamRegistro, Cabecalho *c){
    long pos =  (c->proxRRN)*(76) + 13;
    fseek(arquivo, pos, SEEK_SET);
    fwrite(&registro->removido, sizeof(char), 1, arquivo);
    fwrite(&registro->grupo, sizeof(int), 1, arquivo);
    fwrite(&registro->popularidade, sizeof(int), 1, arquivo);
    fwrite(&registro->peso, sizeof(int), 1, arquivo);
    fwrite(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
    if (registro->tecnologiaOrigem.tamanho != 0){
        fwrite(registro->tecnologiaOrigem.string, registro->tecnologiaOrigem.tamanho, 1, arquivo);
    }
    fwrite(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, arquivo);
    if (registro->tecnologiaDestino.tamanho != 0){
        fwrite(registro->tecnologiaDestino.string, registro->tecnologiaDestino.tamanho, 1, arquivo);
    }   
  
    c->nroParesTecnologias++;
    char LIXO = '$';
    for (int i  = tamRegistro; i < 76; i++){
        if (fwrite(&LIXO, 1, 1, arquivo) != 1) {
            printf("Erro ao preencher os bytes restantes com '$'\n");
        return 0;
        }
    }
    c->proxRRN++;
         
    return 1; // Escrita bem-sucedida
}




Registro* Convert(const char* Linha){
    Registro* registro = inicializarRegistro();
    int i = 0;
    char* aux = (char *)malloc(strlen(Linha) * sizeof(char));
    int j = 0;
    int tam = strlen(Linha);
    int novotam = tam;
    int primeiro = 0;
    while (i < tam) {
        if (Linha[i] == ',' && (i == 0 ||(i > 0 && Linha[i + 1] == ',') || i == (tam-2) )) {
            if (i == tam - 2){
                novotam += 3;
                aux = (char *)realloc(aux, novotam * sizeof(char));
                aux[j] = ',';
                aux[j+1] = '-';
                aux[j+2] = '1';
                
            } else if (i == 0 && primeiro == 0){
                novotam += 5;
                aux = (char *)realloc(aux, novotam * sizeof(char));
                aux[j] = 'N';
                aux[j+1]  = 'U';
                aux[j+2] = 'L';
                aux[j+3] = 'L';
                aux[j+4] = ',';
                primeiro = 1;
                i--;
            } else {
                novotam += 5;
                aux = (char *)realloc(aux, novotam * sizeof(char));
                aux[j] = ',';
                aux[j+1]  = 'N';
                aux[j+2] = 'U';
                aux[j+3] = 'L';
                aux[j+4] = 'L';
            }
            j += 5;   
        } else {
            aux[j] = Linha[i];
            j++;
        }
        i++;
    }
    aux = (char *)realloc(aux, (novotam + 1) * sizeof(char));
    aux[j] = '\0';
    // Inicializa a string variável com NULL (vazia)
    char *token = strtok((char *)aux, ",");
    if (token != NULL && strcmp(token, "NULL") != 0) {
        registro->tecnologiaOrigem.tamanho = strlen(token);
        registro->tecnologiaOrigem.string = strdup(token);
        token = strtok(NULL, ",");
        
    } else {
        registro->tecnologiaOrigem.tamanho = 0;
        token = strtok(NULL, ",");
    } 
    
    if (token != NULL && strcmp(token, "NULL") != 0) {
        registro->grupo = atoi(token);
        token = strtok(NULL, ",");
    } else {
        registro->grupo = -1;
        token = strtok(NULL, ",");
    }

    if (token != NULL && strcmp(token, "NULL") != 0) {
        registro->popularidade = atoi(token);
        token = strtok(NULL, ",");
    } else {
        registro->popularidade = -1;
        token = strtok(NULL, ",");
    }

    if (token != NULL && strcmp(token, "NULL") != 0) {
        registro->tecnologiaDestino.tamanho = strlen(token);
        registro->tecnologiaDestino.string = strdup(token);
        token = strtok(NULL, ",");
    } else {
        registro->tecnologiaDestino.tamanho = 0;
        token = strtok(NULL, ",");
    }
    
    if (token != NULL && strcmp(token, "NULL") != 0) {
        registro->peso = atoi(token);
    } else {
        registro->peso = -1;
        
    }
    
    registro->removido = '0';
    free(aux);
    return registro;
}


void LerBIN (FILE *arquivo) {
    // Move o cursor para o início do arquivo
    fseek(arquivo, 13, SEEK_SET);

    Registro* registro = inicializarRegistro();
    
    while (fread(&registro->removido, sizeof(char), 1, arquivo) == 1) {
        
        fread(&registro->grupo, sizeof(int), 1, arquivo);
        fread(&registro->popularidade, sizeof(int), 1, arquivo);
        fread(&registro->peso, sizeof(int), 1, arquivo);

        fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
        registro->tecnologiaOrigem.string = (char *)malloc(registro->tecnologiaOrigem.tamanho + 1);
        fread(registro->tecnologiaOrigem.string, registro->tecnologiaOrigem.tamanho, 1, arquivo);
        registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = '\0';

        fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, arquivo);
        registro->tecnologiaDestino.string = (char *)malloc(registro->tecnologiaDestino.tamanho + 1);
        fread(registro->tecnologiaDestino.string, registro->tecnologiaDestino.tamanho, 1, arquivo);
        registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = '\0';

        int tamRegistro = 21 + registro->tecnologiaDestino.tamanho + registro->tecnologiaOrigem.tamanho;
        char resto[76-tamRegistro];
        fread(resto, 1, 76-tamRegistro, arquivo);
        if (registro->removido == '0'){
            if (registro->tecnologiaOrigem.tamanho == 0){
                printf("NULO, ");
            } else {
                printf("%s, ", registro->tecnologiaOrigem.string);
            }
            

            if (registro->grupo == -1) {
                printf("NULO, ");
            } else {
                printf("%d, ", registro->grupo);
            }

            if (registro->popularidade == -1) {
                printf("NULO, ");
            } else {
                printf("%d, ", registro->popularidade);
            }
            // Verifica se o tamanho da string é 0
            if (registro->tecnologiaDestino.tamanho == 0) {
                printf("NULO, ");
            } else {
                printf("%s, ", registro->tecnologiaDestino.string);
            }
            // Imprime a variável 'peso'
            if (registro->peso == -1) {
                printf("NULO\n");
            } else {
                printf("%d\n", registro->peso);
            }
        }       
        
    }
}

void BuscarRRN(FILE *arquivo, int RRN, Cabecalho *cabecalho){
    long pos = (RRN)*(76) + 13;
    fseek(arquivo, pos, SEEK_SET);
    Registro* registro = inicializarRegistro();
    if (RRN < cabecalho->nroParesTecnologias){
        fread(&registro->removido, sizeof(char), 1, arquivo);
        if (registro->removido == '0'){
            fread(&registro->grupo, sizeof(int), 1, arquivo);
            fread(&registro->popularidade, sizeof(int), 1, arquivo);
            fread(&registro->peso, sizeof(int), 1, arquivo);

            fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
            registro->tecnologiaOrigem.string = (char *)malloc(registro->tecnologiaOrigem.tamanho + 1);
            fread(registro->tecnologiaOrigem.string, registro->tecnologiaOrigem.tamanho, 1, arquivo);
            registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = '\0';

            fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, arquivo);
            registro->tecnologiaDestino.string = (char *)malloc(registro->tecnologiaDestino.tamanho + 1);
            fread(registro->tecnologiaDestino.string, registro->tecnologiaDestino.tamanho, 1, arquivo);
            registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = '\0';

            int tamRegistro = 21 + registro->tecnologiaDestino.tamanho + registro->tecnologiaOrigem.tamanho;
            char resto[76-tamRegistro];
            fread(resto, 1, 76-tamRegistro, arquivo);        
            if (registro->tecnologiaOrigem.tamanho == 0){
                printf("NULO, ");
            } else {
                printf("%s, ", registro->tecnologiaOrigem.string);
            }
            

            if (registro->grupo == -1) {
                printf("NULO, ");
            } else {
                printf("%d, ", registro->grupo);
            }

            if (registro->popularidade == -1) {
                printf("NULO, ");
            } else {
                printf("%d, ", registro->popularidade);
            }
            // Verifica se o tamanho da string é 0
            if (registro->tecnologiaDestino.tamanho == 0) {
                printf("NULO, ");
            } else {
                printf("%s, ", registro->tecnologiaDestino.string);
            }
            // Imprime a variável 'peso'
            if (registro->peso == -1) {
                printf("NULO\n");
            } else {
                printf("%d\n", registro->peso);
            }
        } else {
            printf("Registro inexistente.\n");
        }
    } else {
        printf("Registro inexistente.\n");
    }
}

int main(){
    FILE *arquivo = fopen("../../docs/tecnologia.csv", "r"); // Ponteiro apontando para o arquivo csv
    
    FILE* BIN = abrirArquivoEscrita("data.bin");

    char linha[76];

    fgets(linha, sizeof(linha), arquivo); // Linha para ignorar primeira linha do arquivo de entrada
    Registro* r = inicializarRegistro();
    Cabecalho* c = inicializarCabecalho();
    atualizarCabecalho(BIN, c);
    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        r = Convert(linha);
        int tamRegistro = 21 + (r->tecnologiaDestino.tamanho) + (r->tecnologiaOrigem.tamanho);
        escreverRegistro(BIN, r, tamRegistro, c);
    }
    atualizarCabecalho(BIN, c);
    
    /*
    Estrutura de Decisão para executar funcionalidade escolhida pelo usuário
    switch (option){
        case 1:
        
        break;
    
        default:

        break;
    }
    */
    LerBIN (BIN);
    BuscarRRN(BIN, 0, c);
    fecharArquivo(BIN);
    fclose(arquivo);
    return 0;
}