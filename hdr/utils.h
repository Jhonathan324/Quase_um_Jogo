#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "types.h"

// Funções desnecessarias
void AtribuirFRectInRect(SDL_FRect *fretangulo, SDL_Rect *retangulo);

// Funções para ajustes dinamicos
void CentralizarRectInRect(SDL_FRect *rect_pai, SDL_FRect *rect_filho);
void CentralizarRectsInRectV(SDL_FRect *pai, SDL_FRect *filho[], int n, float borda_x, float borda_y);

#endif // UTILS_H_INCLUDED
