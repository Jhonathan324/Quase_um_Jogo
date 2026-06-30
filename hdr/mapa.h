#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "types.h"
#include "ui.h"

typedef struct Mapa{
	int n;
	uint16_t tiles[TamanhosMapaY][TamanhosMapaX];
	SDL_Texture *textura;
	SDL_Rect area_vitoria;
} Mapa;

typedef struct MarcadorBloco{
    SDL_FRect retangulo;
    bool sobre;
    bool ativo;
    SDL_Color cor1;
    SDL_Color cor2;
    SDL_FRect partes[3][3];
} MarcadorBloco;

typedef struct VariaveisMapa{
    SDL_Color cor_fundo;
    SDL_FRect selecao;
    SDL_Point selecao_coli;
    SDL_Point selecao_coli_back;
    SDL_Point selecao_coli_preencimento;
    int rolada;
    int bloco_uso;
    int velocidade;
    int tamanho_bloco[2];
    bool preencher;
    Mapa mapa;
    Camera camera;
    Camera camera_back;
    Botao botao_salvar;
    Botao botao_carregar;
    Moldura moldura_bloco;
    Marcador marcador_preencher;
    MarcadorBloco marcador[600];
}VariaveisMapa;

//Criação de Mapa
void SalvarMapa(Mapa *c);
void CarregarMapa(Mapa *c, int n);

bool VerificarMarcadorBloco(MarcadorBloco *marcador, SDL_Point mouse, int rolada);
void DesenharMarcadorBloco(SDL_Renderer *renderizador, MarcadorBloco marcador, int indix, SDL_Texture *textura,int rolada);

void DesenharBloco(SDL_Renderer *renderizador, Bloco bloco);
void DesenharMapa(SDL_Renderer *renderizador, Mapa mapa, Camera camera, int tamanho_bloco[2], int tamanhos_tela[2]);
SDL_FRect MapaTiles(int n);



void InitCenaMapa(SDL_Renderer *renderizador, VariaveisMapa *mapa, Tamanhos tamanhos);
void LoopCenaMapa(VariveisGerais *geral, VariaveisMapa *mapa);
void DesenharCenaMapa(VariveisGerais geral, VariaveisMapa mapa);

#endif // MAPA_H_INCLUDED
