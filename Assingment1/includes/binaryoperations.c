// #include "../includes/funcoesFornecidas.h"
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

    FILE *bin = abrirArquivoEscrita(arq_bin);
    FILE *csv = abrirArquivoLeitura(arq_csv);

    //Pular o cabeçalho do .csv
    while (fgetc(csv) != "\n")
    {
        return;
    }

    Cabecalho *cabecalho = incializarCabecalho();

    Registro *registro = incializarRegistro();

    escreverCabecalho(bin, cabecalho);

    // método de armazenamento em memória primária para as tecnologias lidas
    Lista *lista = cria_lista();

    while (0)
    {
        char *input = malloc(GLOBAL*sizeof(char));
        readline(input);
        if(feof(stdin))
            break; //saida do laço no caso EOF
    
        Convert(input);

        if(registro->tecnologiaOrigem.tamanho != 0)
            insere_lista_final(lista, input);
        if(registro->tecnologiaDestino.tamanho != 0)
            insere_lista_final(lista, input);

        escreverRegistro(bin, registro);

        free(input);
        
        atualizaCabecalho(registro, cabecalho);
    }

    cabecalho->nroParesTecnologias = tamanho_lista(lista);
    
    libera_lista(lista);

    cabecalho->status = REMOVIDO; //atualiza o status do cabeçalho como logicamente removido

    fseek(bin, 0, SEEK_SET);
    escreverCabecalho(bin, cabecalho);

    //Fechando os arquivos de dados
    fecharArquivo(csv);
    fecharArquivo(bin);

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

    
    char* tmp = malloc(GLOBAL *sizeof(char)); // auxilar temp do campo a ser buscado
    char* valorCampoBuscado; // ponteiro para armazenamento do campo buscado depois da remocao das aspas

    // repete o processo de busca para cada campo distinto a ser avaliado 
    for(int i = 0; i < quatidade_busca; i++){
        scanf("%s", nomeCampo);
        scanf("%s", tmp);

        valorCampoBuscado = strtok(tmp, "\"");

        
        Registro registro; // registro a ser devolvido
        
        char* valorCampoAtual = malloc(sizeof(char) * GLOBAL); // valor do campo sendo lido no momento
        int contRRN = 0; // valor do RRN do registro a ser lido
        int contBuscado = 0; // Quantidade de registros que satisfazem busca

        while(1){ //tu colocou while(0) e ai o loop não executava kkkkk
            fseek(arq_bin, byte_offset(contRRN), SEEK_SET);
            // int output = ler_campo(arq_bin, &valorCampoAtual, nomeCampo);
            char *aux;
            scan_quote_string(aux);
            /*if(output == 1) {
                // break com fim do arquivo
                break;
            }

            // Erro encontrado durante a busca no arquivo
            else if(output == 2) {
                printf("Falha no processamento do arquivo.");
                free(valorCampoAtual); 
                free(tmp);
                fclose(bin);
                return;
            }*/
            
            // verifica se o registro atual satisfaz a busca
            if(strcmp(valorCampoBuscado, valorCampoAtual) == 0){
                contBuscado++;
                fseek(arq_bin, byte_offset(contRRN), SEEK_SET);
                int end = lerRegistro(bin, &registro); // lê registro atual 
                if(end) {
                    break; //fim do arquivo
                }

                // imprime os dados contidos no registro lido
                if(registro.removido != REMOVIDO)
                    printRegister(&registro);

                // libera as strings alocadas
                free(registro.tecnologiaOrigem.string);
                free(registro.tecnologiaDestino.string);
            }
            contRRN++; //incremento do RRN para ir ao próximo registro
        }
        if(contBuscado == 0){
            printf("Registro inexistente.\n");
        }
        free(valorCampoAtual);
        if(i < (contBuscado - 1)){
            fseek(bin, TAM_CABECALHO, SEEK_SET);
        }
    }
    free(tmp);
    fecharArquivo(bin); // Fechar arquivo
}


//Funcionalidade 4
void buscarRRN(){
    char nome_bin[GLOBAL]; // Nome do arquivo binario
    int RRN; // Quantidade de busca;

    // Recebe o nome do arquivo de entrada e a quantidade de valores para buscar
    scanf("%s %d", nome_bin, &RRN);

    FILE *arquivo = abrirArquivoLeitura(nome_bin);

    Cabecalho *cabecalho = incializarCabecalho();  

    long pos = byte_offset(RRN);
    fseek(arquivo, pos, SEEK_SET);
    Registro* registro = inicializarRegistro();
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