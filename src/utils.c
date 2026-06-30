#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../hdr/geral.h"

// Para eu não me perder as funções deste .c esta organizado na mesma ordem das funções do gerais.h

void AtribuirFRectInRect(SDL_FRect *fretangulo, SDL_Rect *retangulo)
{
    retangulo->x = fretangulo->x;
    retangulo->y = fretangulo->y;
    retangulo->h = fretangulo->h;
    retangulo->w = fretangulo->w;
}

void CentralizarRectInRect(SDL_FRect *pai, SDL_FRect *filho)
{
    filho->x = pai->x + (pai->w - filho->w) / 2;
    filho->y = pai->y + (pai->h - filho->h) / 2;
}


void CentralizarRectsInRectV(SDL_FRect *pai, SDL_FRect *filho[], int n, float borda_x, float borda_y)
{
    borda_x = borda_x * pai->w;
    borda_y = borda_y * pai->h;
    float soma = 0;
    for (int i = 0; i < n; i++)
        soma += filho[i]->h;
    float espaco_interno_remanecente = (pai->h - borda_y * 2) - soma;
    float espacamento = espaco_interno_remanecente / (n - 1);
    for (int i = 0; i < n; i++)
    {
        filho[i]->x = pai->x + (pai->w - filho[i]->w) / 2;
        if (i != 0)
        {
            filho[i]->y = filho[i - 1]->y + filho[i - 1]->h + espacamento;
        }
        else
        {
            filho[i]->y = pai->y + borda_y;
        }
    }
}


