// #include "../includes/funcoesFornecidas.h"
#include "../includes/binaryoperations.h"

/*
-----------------------------------------------------------------------------------------------
Montando o arquivo binário, desde o .csv.
-----------------------------------------------------------------------------------------------
*/

FILE *abrirArquivoLeitura(const char *nomeArquivo) {
    
    FILE* arquivo;

    arquivo = fopen(nomeArquivo, "rb");

    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return 0;
    }
    
    return arquivo; // Ponteiro no começo do arquivo
}

FILE *abrirArquivoEscrita(const char *nomeArquivo) {

    FILE* arquivo;

    arquivo = fopen(nomeArquivo, "wb+");

    if(arquivo == NULL){
        printf("Falha no processamento do arquivo.\n");
        return 0;
    }
    
    return arquivo; // Ponteiro no começo do arquivo
}

void fecharArquivo(FILE *arquivo) {
    if (arquivo != NULL) {
        fclose(arquivo);
    }
}

int lerRegistro(FILE *arquivo, Registro *registro) {
    if (fread(registro, sizeof(Registro), 1, arquivo) == 1) {
        return 1; // Leitura bem-sucedida
    }
    return 0; // Falha na leitura
}

void escreverRegistro(FILE *arquivo, const Registro *registro) { //REVISAR E VER SE FAZ SENTIDO***********
    
    fwrite(&registro->removido, sizeof(char), 1, arquivo);
    fwrite(&registro->grupo, sizeof(int), 1, arquivo);
    fwrite(&registro->popularidade, sizeof(int), 1, arquivo);
    fwrite(&registro->peso, sizeof(int), 1, arquivo);
    fwrite(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
    fwrite(registro->tecnologiaOrigem.string, sizeof(char), registro->tecnologiaOrigem.tamanho, arquivo);
    fwrite(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, arquivo);
    fwrite(registro->tecnologiaDestino.string, sizeof(char), registro->tecnologiaDestino.tamanho, arquivo);

}

// void escreverRegistro(FILE *arquivo, const Registro *registro) {
//     if (fwrite(registro, sizeof(Registro), 1, arquivo) == 1) {
//         return 1; // Escrita bem-sucedida
//     }
//     return 0; // Falha na escrita
// }

// Função para printar arquivo
void lerArquivo(FILE *arquivo){
    char linha[100]; // *****Ajustar conforme necessário******
    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        printf("%s", linha);
    }
}

/*
-----------------------------------------------------------------------------------------------
*/






/*
-----------------------------------------------------------------------------------------------
Funções auxiliares.
-----------------------------------------------------------------------------------------------
*/

void preencheLixo(char* campo, int tam_campo){

    int i = 0;

    //Enquanto for diferente de '\0', segue na string
    while(campo[i] != '\0')
        i++;

    i++; //caracter após o \0

    // Checa se é necessário adicionar lixo. Caso não, sai da função
    if((i-1) >= tam_campo)
        return;

    // Enquanto for menor que o tamanho do campo, preenche com lixo.
    while(i < tam_campo){
        campo[i] = LIXO;
        i++;
    }
}

int byte_offset(int RRN){
    return (RRN * TAM_REGISTRO);
}

/*
-----------------------------------------------------------------------------------------------
*/





/*
-----------------------------------------------------------------------------------------------
Funcionalidades do algoritmo: 
    1. Create Table
    2. Select From
    3. Select Where
    4. Select RRN
-----------------------------------------------------------------------------------------------
*/

short int crateTabel(const char *csvArchiveName, const char *binArchiveName)
{
    FILE *csv = abrirArquivoLeitura(csvArchiveName); // buscar o .csv
    FILE *bin = abrirArquivoEscrita(binArchiveName); // criar o .bin

    if (csv == NULL || bin == NULL)
        printf("\nFalha no processamento do arquivo.\n");
        return 1; // Caso o csv não seja encontrado ou o bin não criado, passa 1 DE ERRO para o file

    Cabecalho c;
    c.status = '0'; // Registro ativo
    c.proxRRN = 0;
    c.nroParesTecnologias = 0;
    c.nroParesTecnologias = 0;

    Registro r;
    // r.grupo;
    // r.peso;
    // r.popularidade;
    // r.removido;
    // r.tecnologiaOrigem;
    // r.tecnologiaDestino;



    
    
    
    
    
    
    
    fclose(csv);
    fclose(bin);
    binarioNaTela(binArchiveName);
    
    return 0;
}

/*
-----------------------------------------------------------------------------------------------
*/
