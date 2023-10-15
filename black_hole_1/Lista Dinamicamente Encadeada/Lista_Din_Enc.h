#ifndef LISTA_DIN_ENC_H_INCLUDED
#define LISTA_DIN_ENC_H_INCLUDED


typedef int data;


typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista *li);
int insere_lista_inicio(Lista *li, data x);
int insere_lista_final(Lista *li, data x);
int insere_lista_ordenada(Lista *li, data x);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int remove_lista(Lista* li, data x);
int consulta_lista_pos(Lista *li, int pos, data *x);
int consulta_lista_cont(Lista* li, int y, data *x);
#endif // lISTA_DIN_ENC_H_NCLUDED