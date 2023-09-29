/*
Função init_bin

Esta função parece ser responsável por inicializar o arquivo binário. Uma inicialização comum para arquivos binários é escrever um cabeçalho que pode conter metadados sobre o arquivo ou informações sobre o estado do arquivo. Por exemplo, você pode querer saber quantos registros existem no arquivo ou se o arquivo está consistente.

Vamos supor que você queira ter um cabeçalho simples que contém o número total de registros e um status de consistência (1 para consistente, 0 para inconsistente). Aqui está uma possível implementação:
*/

typedef struct {
    int numRegistros;
    int status; // 1 para consistente, 0 para inconsistente
} Cabecalho;

FILE* init_bin(FILE* bin){
    Cabecalho cabecalho;
    cabecalho.numRegistros = 0; // Inicialmente, não há registros
    cabecalho.status = 1; // Inicialmente, o arquivo é consistente

    // Escreve o cabeçalho no início do arquivo binário
    fwrite(&cabecalho, sizeof(Cabecalho), 1, bin);

    return bin;
}


/*
Função printar_binario

Esta função parece ser responsável por imprimir o conteúdo do arquivo binário. Vamos supor que você queira imprimir todos os registros no arquivo binário. Aqui está uma possível implementação:
*/

void printar_binario(const char *binArchiveName) {
    FILE *bin = fopen(binArchiveName, "rb");
    if (bin == NULL) {
        printf("Erro ao abrir o arquivo binário.\n");
        return;
    }

    Cabecalho cabecalho;
    fread(&cabecalho, sizeof(Cabecalho), 1, bin);

    printf("Número de registros: %d\n", cabecalho.numRegistros);
    printf("Status do arquivo: %s\n", cabecalho.status == 1 ? "Consistente" : "Inconsistente");

    Registro registro;
    while (fread(&registro, sizeof(Registro), 1, bin) == 1) {
        // Imprime os campos do registro aqui
        // Exemplo:
        // printf("Nome da Tecnologia: %s\n", registro.nomeTecnologiaOrigem);
    }

    fclose(bin);
}



