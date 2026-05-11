#include <stdio.h>
#include <stdbool.h>
#include "jogo.h"

int main(void)
{
    //Ligando os mudulos
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //iniacilização de tudo
    TAMANHOS tamanhos;
    tamanhos.escala = 0;
    VariveisGerais geral;
    InitCenaGeral(&geral, &tamanhos);

    //iniciazação das variaveis da cena menu
    VariveisMenu menu = {AZUL}; // cor de fundo
    InitCenaMenu(&geral, &menu, tamanhos);

    //iniciazação das variaveis da cena pause
    VariveisPause pause = {SEMI_PRETO}; // cor de fundo
    InitCenaPause(&geral, &pause, tamanhos);

    //iniciazação das variaveis da cena jogo
    VariveisJogo jogo;
    InitCenaJogo(&geral, &jogo, tamanhos);
    //iniciazação das variaveis da cena da conf
    VariveisConf conf;
    InitCenaConf(&geral, &conf, tamanhos);
    conf.reso_inicial = tamanhos.escala;

    Uint64 tempo_inicial = SDL_GetPerformanceCounter();
    double tempo;
    while (geral.rodando)
    {
        tempo_inicial = SDL_GetPerformanceCounter();
        while (SDL_PollEvent(&geral.evento))
        {
            ModuloEvento(&geral);
        }

        switch (geral.cena)
        {
        // Cenas
        case (CENA_MENU):
            LoopCenaMenu(&geral, &menu);
            DesenharCenaMenu(geral, menu);
            break;

        case (CENA_JOGO):
            LoopCenaJogo(&geral, &jogo, tempo);
            DesenharCenaJogo(geral, jogo);
            break;

        case (CENA_PAUSE):
            LoopCenaPause(&geral, &pause);
            DesenharCenaPause(geral, pause);
            break;

        case (CENA_CONF):
            LoopCenaConf(&geral, &conf, &tamanhos);
            DesenharCenaConf(geral, conf);
            break;

        case (CENA_SAIR):
            geral.rodando = false;
            break;

        default:
            geral.cena = CENA_MENU;
            break;
        }

        if (geral.troca_reso ){
            geral.troca_reso = false;
            InitCenaMenu(&geral, &menu, tamanhos);
            InitCenaPause(&geral, &pause, tamanhos);
            CalcularCenaJogo(&geral, &jogo, tamanhos);
        }

        // Limpar a Tela
        SDL_RenderPresent(geral.renderizador);
        SDL_Delay(16); // ~60 FPS
        tempo = (double)(SDL_GetPerformanceCounter() - tempo_inicial) / SDL_GetPerformanceFrequency();
    }

    // Saindo do jogo
    SDL_DestroyRenderer(geral.renderizador);
    SDL_DestroyWindow(geral.janela);
    SDL_Quit();

    return 0;
}
