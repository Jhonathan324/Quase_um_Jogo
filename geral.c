#include <stdio.h>
#include <stdbool.h>
#include "gerais.h"


void InitCenaGeral(VariveisGerais *geral, TAMANHOS *tamanhos){
    GetTamanhos(tamanhos);
    geral->janela = SDL_CreateWindow(
        "Teste", 
        tamanhos->tamanho_tela[0], 
        tamanhos->tamanho_tela[1], 
        0
    ); // (640,360) resolução base. não pode ser menor;
    
    geral->jogador = (Player){
        100, 
        3, 
    };
    
    geral->fullscrean         = false;
    geral->rodando            = true;
    geral->cena               = CENA_MENU;
    geral->cena_continuar     = CENA_JOGO;
    geral->renderizador       = SDL_CreateRenderer(geral->janela, NULL);
    geral->resolucao_atual[0] = tamanhos->tamanho_tela[0];
    geral->resolucao_atual[1] = tamanhos->tamanho_tela[1];
    geral->troca_reso         = false;
    geral->botao_mouse_direito = false;
    geral->botao_mouse_esquerdo = false;
    geral->botao_mouse_meio = false;
    geral->botao_mouse_gira = false;
}

void CalcularGeral(VariveisGerais *geral, TAMANHOS *tamanhos){
    GetTamanhos(tamanhos);
    SDL_SetWindowSize(geral->janela,tamanhos->tamanho_tela[0], tamanhos->tamanho_tela[1]);
    SDL_SetWindowFullscreen(geral->janela, geral->fullscrean);
    
    geral->resolucao_atual[0] = tamanhos->tamanho_tela[0];
    geral->resolucao_atual[1] = tamanhos->tamanho_tela[1];
}
