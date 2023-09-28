#include "../includes/funcoesfornecidas.h"
#include "../includes/binaryoperations.h"

FILE *abrirArquivoLeitura(const char *nomeArquivo) {
    return fopen(nomeArquivo, "rb"); // Ponteiro no começo do arquivo
}

FILE *abrirArquivoEscrita(const char *nomeArquivo) {
    return fopen(nomeArquivo, "wb"); // Ponteiro no começo do arquivo
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

int escreverRegistro(FILE *arquivo, const Registro *registro) {
    if (fwrite(registro, sizeof(Registro), 1, arquivo) == 1) {
        return 1; // Escrita bem-sucedida
    }
    return 0; // Falha na escrita
}
