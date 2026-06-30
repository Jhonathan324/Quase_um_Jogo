#include <stdio.h>
#include <stdbool.h>
#include "../hdr/geral.h"

void GetTamanhos(Tamanhos *tamanhos)
{
    if(tamanhos->escala >= 0 && tamanhos->escala <=6){
        tamanhos->tela[0] = 320 * (tamanhos->escala + 2);
        tamanhos->tela[1] = 180 * (tamanhos->escala + 2);
    }
    else{
        tamanhos->escala = 0;
        tamanhos->tela[0] = 640;
        tamanhos->tela[1] = 360;
    }

    tamanhos->menu[0]         = tamanhos->tela[0] * (float)CantoFixo          / 640 * 6;
    tamanhos->menu[1]         = tamanhos->tela[1] * (float)CantoFixo          / 360 * 6;

    tamanhos->bloco1[0]       = tamanhos->tela[0] * (float)MedidaImgBloco     / 640 * 2;
    tamanhos->bloco1[1]       = tamanhos->tela[1] * (float)MedidaImgBloco     / 360 * 2;

    tamanhos->botao1[0]       = tamanhos->tela[0] * (float)MedidaImgBloco     / 640 * 2;
    tamanhos->botao1[1]       = tamanhos->tela[1] * (float)MedidaImgBloco     / 360 * 2;

    tamanhos->botao2[0]       = tamanhos->tela[0] * (float)MedidaImgBloco     / 640 * 2;
    tamanhos->botao2[1]       = tamanhos->tela[1] * (float)MedidaImgBloco     / 360 * 2;

    tamanhos->barra_vida[0]   = tamanhos->tela[0] * (float)(EscalaHud*4)      / 640 * 2;
    tamanhos->barra_vida[1]   = tamanhos->tela[1] * (float)(EscalaHud*1)      / 360 * 2;

    tamanhos->jogador[0]      = tamanhos->tela[0] * (float)MedidaImgPlayerX   / 640 * 2;
    tamanhos->jogador[1]      = tamanhos->tela[1] * (float)MedidaImgPlayerY   / 360 * 2;

    tamanhos->inimigo1[0]     = tamanhos->tela[0] * (float)MedidaImgInimigo1X / 640 * 2;
    tamanhos->inimigo1[1]     = tamanhos->tela[1] * (float)MedidaImgInimigo1Y / 360 * 2;

    tamanhos->inimigo2[0]     = tamanhos->tela[0] * (float)MedidaImgInimigo2X / 640;
    tamanhos->inimigo2[1]     = tamanhos->tela[1] * (float)MedidaImgInimigo2Y / 360;

    tamanhos->jogador_coli[0] = tamanhos->tela[0] * (float)MedidaImgPlayerColiX / 640 * 2;
    tamanhos->jogador_coli[1] = tamanhos->tela[1] * (float)MedidaImgPlayerColiY / 360 * 2;

}


void InitCenaGeral(VariveisGerais *geral, Tamanhos *tamanhos){
    GetTamanhos(tamanhos);
    geral->janela = SDL_CreateWindow(
        "Teste", 
        tamanhos->tela[0], 
        tamanhos->tela[1], 
        0
    ); // (640,360) resolução base. não pode ser menor;

    geral->rodando              = true;
    geral->fullscrean           = false;
    geral->troca_reso           = false;
    geral->debug                = false;
    geral->botao_mouse_direito  = false;
    geral->botao_mouse_esquerdo = false;
    geral->botao_mouse_meio     = false;
    geral->botao_mouse_gira     = false;
    geral->cena                 = CENA_MENU;
    geral->cena_continuar       = CENA_JOGO;
    geral->resolucao_atual[0]   = tamanhos->tela[0];
    geral->resolucao_atual[1]   = tamanhos->tela[1];
    geral->resolucao_antiga[0]  = tamanhos->tela[0];
    geral->resolucao_antiga[1]  = tamanhos->tela[1];
    geral->renderizador         = SDL_CreateRenderer(geral->janela, NULL);
    geral->textura_hud          = IMG_LoadTexture(geral->renderizador, "assets/imagens/ui/panels/hud geral.png");
    geral->barra_de_vida        = (SDL_FRect){EscalaHud*19, EscalaHud*1, EscalaHud*4, EscalaHud*1};

    SDL_SetTextureScaleMode(geral->textura_hud, SDL_SCALEMODE_NEAREST);
}

void CalcularGeral(VariveisGerais *geral, Tamanhos *tamanhos){
    GetTamanhos(tamanhos);
    SDL_SetWindowSize(geral->janela,tamanhos->tela[0], tamanhos->tela[1]);
    SDL_SetWindowFullscreen(geral->janela, geral->fullscrean);

    geral->resolucao_atual[0] = tamanhos->tela[0];
    geral->resolucao_atual[1] = tamanhos->tela[1];
}


void ModuloEvento(VariveisGerais *geral)
{
    if (geral->evento.type == SDL_EVENT_QUIT)
    {
        geral->rodando = false;
    }
    //mouse 
    SDL_GetMouseState(&geral->mouse_x, &geral->mouse_y);
    geral->ponto_mouse.x = geral->mouse_x;
    geral->ponto_mouse.y = geral->mouse_y;


    if (geral->evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
        if(geral->evento.button.button == SDL_BUTTON_LEFT)
            geral->botao_mouse_esquerdo = true;

        if(geral->evento.button.button == SDL_BUTTON_RIGHT)
            geral->botao_mouse_direito = true;

        if(geral->evento.button.button == SDL_BUTTON_MIDDLE){
            geral->botao_mouse_meio = true;
        }
    }
    else if(geral->evento.type == SDL_EVENT_MOUSE_WHEEL){
        geral->botao_mouse_gira = geral->evento.wheel.y;
    }
    else if(geral->evento.type == SDL_EVENT_MOUSE_BUTTON_UP){
        geral->botao_mouse_esquerdo = false;
        geral->botao_mouse_direito = false;
        geral->botao_mouse_meio = false;
    }
}