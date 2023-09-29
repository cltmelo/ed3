// ... [Código anterior]

// Função para ler um registro do arquivo CSV
Dados lerRegistroCSV(FILE *csv) {
    Dados dados;
    char buffer[100]; // Buffer temporário para leitura

    // Inicializar campos
    dados.removido = '-';
    dados.nomeTecnologiaOrigem.string = NULL;
    dados.nomeTecnologiaDestino.string = NULL;

    // Ler campos do CSV
    fscanf(csv, "%d,%d,%d,", &dados.grupo, &dados.popularidade, &dados.peso);
    scan_quote_string(buffer);
    dados.nomeTecnologiaOrigem.tamanho = strlen(buffer);
    dados.nomeTecnologiaOrigem.string = strdup(buffer);
    scan_quote_string(buffer);
    dados.nomeTecnologiaDestino.tamanho = strlen(buffer);
    dados.nomeTecnologiaDestino.string = strdup(buffer);

    return dados;
}

short int functionality_1(const char csvArchiveName[], const char binArchiveName[]) {
    FILE *csv = archive_open(csvArchiveName); // buscar o csv
    FILE *bin = fopen(binArchiveName, "wb+");  // criar/abrir o bin para escrita e leitura

    if (csv == NULL || bin == NULL) {
        printf("\nFalha no processamento do arquivo.\n");
        return 1; // Erro ao abrir arquivos
    }

    bin = init_bin(bin); // Inicializar cabeçalho do arquivo binário

    Dados dados;
    while (!feof(csv)) {
        dados = lerRegistroCSV(csv); // Ler registro do CSV
        Escrever_Dados(bin, dados); // Escrever registro no binário

        // Liberar memória alocada para strings
        free(dados.nomeTecnologiaOrigem.string);
        free(dados.nomeTecnologiaDestino.string);
    }

    // Atualizar cabeçalho (se necessário)
    Atualizar_Cabecalho(bin, /*nroTecnologia*/, /*nroParesTecnologia*/);

    fclose(csv);
    fclose(bin);

    binarioNaTela(binArchiveName); // Mostrar saída do arquivo binário

    return 0; // Sucesso
}

// ... [Restante do código]

