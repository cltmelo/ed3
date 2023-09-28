/*
* Name: Lucas Corlete Alves de Melo - NUSP: 13676461; Jean Carlos Pereira Cassiano - NUSP: 138640008
* Course: SCC0607 - Estrutura de Dados III
* Professor: Cristina Dutra de Aguiar
* Project: Trabalho Introdutório, 1 e 2 de ED3
* Description: Este trabalho tem como objetivo armazenar dados em um arquivo binário bem como desenvolver funcionalidades para a manipulação desses dados. Novas funcionalidades serão adicionadas conforme o avançar da disciplina.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../includes/binaryoperations.h"
// #include "../includes/funcoesFornecidas.h"

// Função para printar arquivo
void Lerarquivo(FILE *arquivo){
    char linha[100]; // Ajustar conforme necessário
    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        printf("%s", linha);
    }
}

int main(){
    FILE *arquivo = fopen("../docs/tecnologia.csv", "r"); // Ponteiro apontando para o arquivo csv
    
    Lerarquivo(arquivo);
    fclose(arquivo);



    /*

    Estrutura de Decisão para executar funcionalidade escolhida pelo usuário
    switch (option){
        case 1:
        
        break;
    
        default:

        break;
    }
    
    */
    return 0;
}