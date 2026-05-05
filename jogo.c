#include <stdio.h>
#include <stdbool.h>
#include "gerais.h"
#include "jogo.h"



void InitJogo(VariveisGerais *geral, VariveisJogo *jogo, TAMANHOS tamanhos){
    
    geral->jogador = (Player){100,
         3,
        (float)tamanhos.tamanho_bloco[0]/tamanhos.tamanho_jogador[0]*3,
    };

    jogo->jogador = InitPlayer(
    geral->renderizador, 
    (SDL_FRect){100,100,tamanhos.tamanho_jogador[0],tamanhos.tamanho_jogador[1]},
    (SDL_FRect){100,100,tamanhos.tamanho_jogador[0]/2,tamanhos.tamanho_jogador[1]*((float)2/3)},
    "C:/Users/17898981/projetos/Teste_SDL3/assets/images/entities/player/Samurai.png"
    );

    jogo->cor_fundo = (SDL_Color)AZUL;
    jogo->velocidade_jogador_x = 0;
    jogo->velocidade_jogador_y = 0;
    memset(jogo->mapa,0,sizeof(jogo->mapa));

    //for(int i = 0; i < TamanhosMapaX; i++) printf("%d", jogo->mapa[i][0]);
}

void CalcularJogo(VariveisGerais *geral, VariveisJogo *jogo, TAMANHOS tamanhos){
    // a fazer
    tamanhos->tamanho_jogador[0]/ (float)64 / 640; 
    tamanhos->tamanho_jogador[1]/ (float)48 / 360 ;  

    float x = tamanhos.tamanho_tela[0] * ( (double)jogo->jogador.retangulo_coli.x/tamanhos.tamanho_tela[0] );
    float y = tamanhos.tamanho_tela[1] * ( (double)jogo->jogador.retangulo_coli.y/tamanhos.tamanho_tela[1] );
    jogo->jogador = InitPlayer(
    geral->renderizador, 
    (SDL_FRect){x,y,tamanhos.tamanho_jogador[0],tamanhos.tamanho_jogador[1]},
    (SDL_FRect){x,y,tamanhos.tamanho_jogador[0]/2,tamanhos.tamanho_jogador[1]*((float)2/3)},
    "C:/Users/17898981/projetos/Teste_SDL3/assets/images/entities/player/Samurai.png"
    );
}

void CenaJogoLoop(VariveisGerais *geral, VariveisJogo *jogo)
{
    const bool *teclado = SDL_GetKeyboardState(NULL);

    if (teclado[SDL_SCANCODE_ESCAPE])
        geral->cena = CENA_PAUSE;

    // Logica do Player

    if (teclado[SDL_SCANCODE_A])
        jogo->velocidade_jogador_x -= geral->jogador.velocidade;
    if (teclado[SDL_SCANCODE_D])
        jogo->velocidade_jogador_x += geral->jogador.velocidade;
    if (teclado[SDL_SCANCODE_W])
        jogo->velocidade_jogador_y -= geral->jogador.velocidade;
    if (teclado[SDL_SCANCODE_S])
        jogo->velocidade_jogador_y += geral->jogador.velocidade;

    if (jogo->velocidade_jogador_x < -10)
        jogo->velocidade_jogador_x = -10;
    if (jogo->velocidade_jogador_x > 10)
        jogo->velocidade_jogador_x = 10;
    if (jogo->velocidade_jogador_y < -10)
        jogo->velocidade_jogador_y = -10;
    if (jogo->velocidade_jogador_y > 10)
        jogo->velocidade_jogador_y = 10;

    if (jogo->velocidade_jogador_x < 0 && jogo->velocidade_jogador_x > -0.5)
        jogo->velocidade_jogador_x = 0;
    if (jogo->velocidade_jogador_x > 0 && jogo->velocidade_jogador_x < 0.5)
        jogo->velocidade_jogador_x = 0;
    if (jogo->velocidade_jogador_y < 0 && jogo->velocidade_jogador_y > -0.5)
        jogo->velocidade_jogador_y = 0;
    if (jogo->velocidade_jogador_y > 0 && jogo->velocidade_jogador_y < 0.5)
        jogo->velocidade_jogador_y = 0;

    jogo->jogador.retangulo_coli.x += jogo->velocidade_jogador_x;
    jogo->jogador.retangulo_coli.y += jogo->velocidade_jogador_y;

    if (jogo->velocidade_jogador_x < 0)
        jogo->velocidade_jogador_x += 0.3;
    if (jogo->velocidade_jogador_x > 0)
        jogo->velocidade_jogador_x -= 0.3;
    if (jogo->velocidade_jogador_y < 0)
        jogo->velocidade_jogador_y += 0.3;
    if (jogo->velocidade_jogador_y > 0)
        jogo->velocidade_jogador_y -= 0.3;
}

void CenaJogoDesenhar(VariveisGerais *geral, VariveisJogo *jogo)
{
    // Limpeza de Tela
    SDL_SetRenderDrawColor(geral->renderizador, jogo->cor_fundo.r, jogo->cor_fundo.g, jogo->cor_fundo.b, jogo->cor_fundo.a);
    SDL_RenderClear(geral->renderizador);

    // player
    SDL_SetRenderDrawColor(geral->renderizador, 255, 0, 0, 255);
    SDL_RenderFillRect(geral->renderizador, &jogo->jogador.retangulo_coli);
}

PlayerInJogo InitPlayer(SDL_Renderer *renderizador, SDL_FRect retangulo_img, SDL_FRect retangulo_coli,  char *img){
    PlayerInJogo player = {
    100.0,
    3,
    (float)retangulo_coli.w/48,
    retangulo_img,
    retangulo_coli,
    retangulo_coli,
    retangulo_coli,
    IMG_LoadTexture(renderizador, img)};
    return player;

}