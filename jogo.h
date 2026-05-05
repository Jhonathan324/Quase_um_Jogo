#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED
#include "gerais.h"

#define TamanhosMapaX 512
#define TamanhosMapaY 128
#define medida_img_x
#define medida_img_y

typedef struct PlayerInJogo
{
    float vida;
    int coracoes;
    float velocidade;
    SDL_FRect retangulo_img;
    SDL_FRect retangulo_coli;
    SDL_FRect retangulo_coli_h;
    SDL_FRect retangulo_coli_v;
    SDL_Texture *sprites_atlas;
}PlayerInJogo;

typedef struct VariveisJogo
{
    SDL_Color cor_fundo;
    int velocidade_jogador_x;
    int velocidade_jogador_y;
    uint8_t mapa[TamanhosMapaX][TamanhosMapaY];
    PlayerInJogo jogador;
} VariveisJogo;



void InitJogo(VariveisGerais *geral, VariveisJogo *jogo, TAMANHOS tamanhos);
void CalcularJogo(VariveisGerais *geral, VariveisJogo *jogo, TAMANHOS tamanhos);
void CenaJogoLoop(VariveisGerais *geral, VariveisJogo *jogo);
void CenaJogoDesenhar(VariveisGerais *geral, VariveisJogo *jogo);

PlayerInJogo InitPlayer(SDL_Renderer *renderizador, SDL_FRect retangulo_img, SDL_FRect retangulo_coli,  char *img);

#endif // JOGO_H_INCLUDED