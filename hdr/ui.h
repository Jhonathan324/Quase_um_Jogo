#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "utils.h"

// Funções para criação de elementos dinamicos
CampoTexto InitTexto(SDL_Renderer *renderizador, SDL_FRect *retangulo, SDL_Color cor_fundo, char *texto, char *imagem, TTF_Font *fonte, SDL_Color cor_fonte, bool alinhado);
void DesenharTexto(SDL_Renderer *renderizador, CampoTexto texto);
void DestruirTexto(CampoTexto *texto);

Moldura InitMoldura(SDL_Renderer *renderizador, SDL_FRect *retangulo, char *file);
void DesenharMoldura(SDL_Renderer *renderizador, Moldura moldura);
void DestruirMoldura(Moldura *moldura);

Marcador InitMarcador(SDL_Renderer *renderizador, SDL_FRect *retangulo, bool ativo, char *imagem1, SDL_Color cor1, SDL_Color cor2);
void DesenharMarcador(SDL_Renderer *renderizador, Marcador marcador);
bool VerificarMarcador(Marcador *marcador, SDL_Point mouse, bool click);
void DestruirMarcador(Marcador *marcador);

Botao InitBotao(SDL_Renderer *renderizador, SDL_FRect *retangulo, char *imagem, char *texto, SDL_Color cor1, SDL_Color cor2, int indice, TTF_Font *fonte, SDL_Color cor_fonte);
void DesenharBotao(SDL_Renderer *renderizador, Botao botao);
bool VerificarBotao(Botao *botao, SDL_Point mouse, bool click);
void DestruirBotao(Botao *botao);

BotaoExpansivo InitBotaoExpansivo(SDL_Renderer *renderizador, SDL_FRect *retangulo, char *imagem, char *texto, char *textos[], SDL_Color cor, SDL_Color cor2, int indice, TTF_Font *fonte, SDL_Color cor_fonte, int n);
void DesenharBotaoExpansivo(SDL_Renderer *renderizador, BotaoExpansivo botao);
void DestruirBotaoExpansivo(BotaoExpansivo *botao);

#endif // UI_H_INCLUDED