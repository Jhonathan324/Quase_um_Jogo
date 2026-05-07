#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED
#include "gerais.h"

#define TamanhosMapaX 512
#define TamanhosMapaY 128
#define MedidaImgPlayerX 120
#define MedidaImgPlayerY 80

//animação, quantidade de frames, tempo de execução
#define TablePlayerAnim \
    X(ATAQUE,            4) \
    X(ATAQUE2,           6) \
    X(ATAQUE2_MOVIMENTO, 6) \
    X(ATAQUE_COMBO,      10) \
    X(ATAQUE_MOVIMENTO_COMBO, 10) \
    X(ATAQUE_MOVIMENTO, 4) \
    X(AGACHAR,          1) \
    X(AGACHAR_TODO,     3) \
    X(AGACHAR_ATAQUE,   4) \
    X(LEVANTAR,         1) \
    X(CORRER_AGACHADO,  8) \
    X(DASH,             2) \
    X(MORRER,          10) \
    X(MORRER_CORRENDO, 10) \
    X(CAIR,             3) \
    X(HIT,              1) \
    X(IDLE,            10) \
    X(PULAR,            3) \
    X(PULO_TRANSICAO,   2) \
    X(ROLAR,           12) \
    X(CORRER,          10) \
    X(DESLIZAR,         2)\
    X(DESLIZAR_TODO,    4) \
    X(DESLIZAR_TRANSICAO_FIM, 1) \
    X(DESLIZAR_TRANSICAO_COMECO, 1) \
    X(INVERTER_PASSO,   3) \
    X(ESCALAR,          7) \
    X(ESCALAR_MOVIMENTO,7) \
    X(AGARRAR,          1) \
    X(DESLIZAR_PAREDE,  3) \
    

#define X(type, quant) type,

typedef enum {
   TablePlayerAnim
} ESTADO_PLAYER;
#undef X

typedef struct PlayerInJogo
{
    float vida;
    int coracoes;
    float velocidade_x;
    float velocidade_y;
    float acelera;
    float vel_max_x;
    float vel_max_y;
    SDL_FRect retangulo_img;
    SDL_FRect retangulo_coli;
    SDL_FRect retangulo_coli_h;
    SDL_FRect retangulo_coli_v;
    SDL_Texture *sprite_atlas;
    int estado_atual;
    int estado_passado;
    double frame;
    bool costas;
    bool coli_h;
    bool coli_v;
}PlayerInJogo;

typedef struct VariveisJogo
{
    SDL_Color cor_fundo;
    int velocidade_jogador_x;
    int velocidade_jogador_y;
    uint8_t mapa[TamanhosMapaX][TamanhosMapaY];
    PlayerInJogo jogador;
    double tempo;
} VariveisJogo;



void InitJogo(VariveisGerais *geral, VariveisJogo *jogo, TAMANHOS tamanhos);
void CalcularJogo(VariveisGerais *geral, VariveisJogo *jogo, TAMANHOS tamanhos);
void CenaJogoLoop(VariveisGerais *geral, VariveisJogo *jogo, double delta_t);
void CenaJogoDesenhar(VariveisGerais *geral, VariveisJogo *jogo);

PlayerInJogo InitPlayer(SDL_Renderer *renderizador, SDL_FRect retangulo_img, SDL_FRect retangulo_coli,  char *img);
void CalcularPlayer(const bool *teclado, PlayerInJogo *player, double delta_frame);
void DesenharPlayer(SDL_Renderer *renderizador, PlayerInJogo player);

#endif // JOGO_H_INCLUDED