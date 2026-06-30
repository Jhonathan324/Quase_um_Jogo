#ifndef UI_CENAS_H_INCLUDED
#define UI_CENAS_H_INCLUDED
#include "types.h"
#include "ui.h"

typedef struct VariveisMenu
{
    SDL_Color cor_fundo;
    SDL_Texture *imagem;
    Moldura moldura;
    Botao botao_iniciar;
    Botao botao_criacao;
    Botao botao_conf;
    Botao botao_sair;
} VariveisMenu;

typedef struct VariveisPause
{
    SDL_Color cor_fundo;
    SDL_Texture *imagem;
    Moldura moldura;
    Botao botao_iniciar;
    Botao botao_conf;
    Botao botao_sair;
} VariveisPause;



typedef struct VariveisConf
{
    SDL_Color cor_fundo;
    SDL_Texture *imagem;
    bool valida_fullscrean;
    int reso_inicial;
    Marcador troca_fullscreen;
    Botao botao_sair;
    BotaoExpansivo botao_reso;
    Moldura moldura;
    CampoTexto texto_reso;
    CampoTexto texto_full;
} VariveisConf;


// Funções para cenas em especico
void InitCenaMenu(VariveisGerais *geral, VariveisMenu *menu, Tamanhos tamanhos);
void LoopCenaMenu(VariveisGerais *geral, VariveisMenu *menu);
void DesenharCenaMenu(VariveisGerais geral, VariveisMenu menu);

void InitCenaPause(VariveisGerais *geral, VariveisPause *pause, Tamanhos tamanhos);
void LoopCenaPause(VariveisGerais *geral, VariveisPause *pause);
void DesenharCenaPause(VariveisGerais geral, VariveisPause pause);

void InitCenaConf(VariveisGerais *geral, VariveisConf *conf, Tamanhos tamanhos);
void LoopCenaConf(VariveisGerais *geral, VariveisConf *conf, Tamanhos *tamanhos);
void DesenharCenaConf(VariveisGerais geral, VariveisConf conf);

#endif // UI_CENAS_H_INCLUDED