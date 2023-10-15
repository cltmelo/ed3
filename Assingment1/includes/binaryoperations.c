#include "../includes/binaryoperations.h"
#include "../includes/funcoesAuxiliares.h"

/*
----------------------------------------------------------------------------------------------------------------------------------
Funcionalidades do algoritmo: 
    1. Create Table (criaTable)
    2. Select From
    3. Select Where
    4. Select RRN (bucarRRN)
----------------------------------------------------------------------------------------------------------------------------------
*/


#define GLOBAL 256 //Só uma varável global aleatória para os arrays de nome de arquivo

//Funcionalidade 1
void criaTable(){
    char arq_csv[GLOBAL];
    char arq_bin[GLOBAL];
    scanf("%s", arq_csv);
    scanf("%s", arq_bin);
    FILE *csv = abrirArquivoLeitura(arq_csv);
    FILE *bin = abrirArquivoEscrita(arq_bin);

    //Pular o cabeçalho do .csv
    while (fgetc(csv) != "\n")
    {
        return;
    }

    // método de armazenamento em memória primária para as tecnologias lidas
    Lista *lista = cria_lista();

    Registro *registro = incializarRegistro();
    Cabecalho *cabecalho = incializarCabecalho();

    escreverCabecalho(bin, cabecalho);

    while (1)
    {
        char *input = malloc(GLOBAL*sizeof(char));
        readline(input);
        if(feof(stdin))
            break; //saida do laço no caso EOF
    
        Convert(input);

        if(registro->tecnologiaDestino.tamanho != 0)
            insere_lista_final(lista, input);

        if(registro->tecnologiaOrigem.tamanho != 0)
            insere_lista_final(lista, input);

        escreverRegistro(bin, registro);
        
        atualizaCabecalho(registro, cabecalho);

        free(input);
    }

    cabecalho->nroParesTecnologias = tamanho_lista(lista);

    cabecalho->status = REMOVIDO; //atualiza o status do cabeçalho como logicamente removido

    fseek(bin, 0, SEEK_SET);
    escreverCabecalho(bin, cabecalho);

    //Fechando os arquivos de dados
    fecharArquivo(csv);
    fecharArquivo(bin);

    //liberando memoria alocada (lista ligada)
    libera_lista(lista);

    //REQUISITO DO ENUNCIADO
    binarioNaTela(arq_bin);
}

//Funcionalidade 2
void LerBIN() {
    char arq_bin[GLOBAL];
    scanf("%s", arq_bin);

    FILE *arquivo = abrirArquivoEscrita(arq_bin);

    // Move o cursor para o início do arquivo
    fseek(arquivo, TAM_CABECALHO, SEEK_SET);

    Registro* registro = inicializarRegistro();
    
    while (fread(&registro->removido, sizeof(char), 1, arquivo) == REMOVIDO) {
        
        fread(&registro->peso, sizeof(int), 1, arquivo);
        fread(&registro->popularidade, sizeof(int), 1, arquivo);
        fread(&registro->grupo, sizeof(int), 1, arquivo);

        fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, arquivo);
        registro->tecnologiaDestino.string = (char *)malloc(registro->tecnologiaDestino.tamanho + 1);
        fread(registro->tecnologiaDestino.string, registro->tecnologiaDestino.tamanho, 1, arquivo);
        registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = NULL_TERM;
        
        fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
        registro->tecnologiaOrigem.string = (char *)malloc(registro->tecnologiaOrigem.tamanho + 1);
        fread(registro->tecnologiaOrigem.string, registro->tecnologiaOrigem.tamanho, 1, arquivo);
        registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = NULL_TERM;


        int tamRegistro = TAM_REGISTRO_FIXO + registro->tecnologiaDestino.tamanho + registro->tecnologiaOrigem.tamanho;
        char resto[TAM_REGISTRO-tamRegistro];
        fread(resto, 1, TAM_REGISTRO-tamRegistro, arquivo);
        if (registro->removido == '0'){
            if (registro->tecnologiaOrigem.tamanho == 0){
                printf("NULO, ");
            } else {
                printf("%s, ", registro->tecnologiaOrigem.string);
            }
            

            // Impressao da variável 'grupo'
            if (registro->grupo == -1) {
                printf("NULO, ");
            } else {
                printf("%d, ", registro->grupo);
            }

            // Impressao da variável 'popularidade'
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
            // Impressao da variável 'peso'
            if (registro->peso == -1) {
                printf("NULO\n");
            } else {
                printf("%d\n", registro->peso);
            }
        }       
        
    }
    fecharArquivo(arquivo);
}

// Funcionalidade 3
void selectWhere(){ // Pode ser deveras custosa em termos de disco, Jean, por causa da alocação dinâmica.
    char arq_bin[GLOBAL];
    char nomeCampo[GLOBAL];
    int quatidade_busca;
    scanf("%s %d", arq_bin, &quatidade_busca);
    FILE *bin = abrirArquivoLeitura(arq_bin);

    Cabecalho cabecalho;
    int output = lerCabecalho(bin, &cabecalho);

    if(output == 1){
        printf("Falha no processamento do arquivo.\n");
        fecharArquivo(bin);
        return;
    }

    if(cabecalho.status == NAO_REMOVIDO){
        printf("Falha no processamento do arquivo.\n");
        fecharArquivo(bin);
        return;
    }

    
    // char* tmp = malloc(GLOBAL *sizeof(char)); // auxilar temp do campo a ser buscado
    char tmp[GLOBAL];

    // repete o processo de busca para cada campo distinto a ser avaliado 
    for(int i = 0; i < quatidade_busca; i++){
        scanf("%s", tmp);
        scanf("%s", nomeCampo);
    
        char* search_field = strtok(tmp, "\"");; // ponteiro para armazenamento do campo buscado depois da remocao das aspas

        
        char* actual_field = malloc(GLOBAL*sizeof(char)); // valor do campo sendo lido no momento (me enrolei com a estática, vai com a dinâmica mesmo)
        
        int contRRN = 0; // valor do RRN do registro a ser lido
        int contBuscado = 0; // Quantidade de registros que satisfazem busca
        int indexAux; // soh um auxilar p ver (contBuscado - [algo])

        Registro registro; // registro a ser devolvido

        while(1){ //tu colocou while(0) e ai o loop não executava kkkkk
            fseek(arq_bin, byte_offset(contRRN), SEEK_SET);
            char *aux;
            scan_quote_string(aux);
            
            // verifica se o registro atual satisfaz a busca
            if(strcmp(search_field, actual_field) == 0){
                fseek(arq_bin, byte_offset(contRRN), SEEK_SET);

                contBuscado++;

                if(lerRegistro(bin, &registro)) { //leitura do registro atual
                    break; //fim do arquivo
                }

                // imprime os dados contidos no registro lido
                if(registro.removido != REMOVIDO)
                    printRegister(&registro);

                // libera as strings alocadas
                free(registro.tecnologiaDestino.string);
                free(registro.tecnologiaOrigem.string);
            }
            contRRN++; //incremento do RRN para ir ao próximo registro
        }
        free(actual_field);

        if(contBuscado == 0){
            printf("Registro inexistente.\n");
        }

        indexAux = contBuscado - 1; //ata, era -1
        if(i < indexAux){
            fseek(bin, TAM_CABECALHO, SEEK_SET);
        }
    }
    //free(tmp); //pra que isso pae? utilizamos estática (acho qeu vai ser mais eficiente em termos de memória)
    fecharArquivo(bin); // Fechar arquivo
}


//Funcionalidade 4
void buscarRRN(){
    int RRN; // Quantidade de busca;
    char arq_bin[GLOBAL]; // Nome do arquivo binario

    // Recebe o nome do arquivo de entrada e a quantidade de valores para buscar
    scanf("%s %d", arq_bin, &RRN);

    FILE *arquivo = abrirArquivoLeitura(arq_bin);

    Cabecalho *cabecalho = incializarCabecalho();
    Registro* registro = inicializarRegistro();   

    long pos = byte_offset(RRN);
    fseek(arquivo, pos, SEEK_SET);
    
    if (RRN < cabecalho->nroParesTecnologias){
        fread(&registro->removido, sizeof(char), 1, arquivo);
        if (registro->removido == NAO_REMOVIDO){
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

            int tamRegistro = TAM_REGISTRO_FIXO + registro->tecnologiaDestino.tamanho + registro->tecnologiaOrigem.tamanho;
            char resto[TAM_REGISTRO-tamRegistro];
            fread(resto, 1, TAM_REGISTRO-tamRegistro, arquivo);        
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
    fecharArquivo(arquivo);
}

/*
----------------------------------------------------------------------------------------------------------------------------------
*/