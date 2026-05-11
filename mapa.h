#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "jogo.h"

typedef struct VariaveisMapa{
    int rolada;
    Marcador *marcador;
    Camera camera;
}VariaveisMapa;

void InitCenaMapa(SDL_Renderer *renderizador, VariaveisMapa *mapa);
void LoopCenaMapa(VariveisGerais *geral, VariveisMenu *menu);
void DesenharCenaMapa(VariveisGerais *geral, VariveisMenu *menu);

#endif // MAPA_H_INCLUDED
