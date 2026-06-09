#include <stdio.h>
#include <stdbool.h>
#include "mapa.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static Tamanhos      tamanhos;
static VariveisGerais geral;
static VariveisMenu   menu;
static VariveisPause  pausa;
static VariveisJogo   jogo;
static VariveisConf   conf;
static VariaveisMapa  mapa;
static Uint64         tempo_inicial;
static double         tempo;

static void frame(void)
{
    tempo_inicial = SDL_GetPerformanceCounter();

    while (SDL_PollEvent(&geral.evento))
        ModuloEvento(&geral);

    switch (geral.cena)
    {
    case CENA_MENU:
        LoopCenaMenu(&geral, &menu);
        DesenharCenaMenu(geral, menu);
        break;

    case CENA_JOGO:
        printf("LoopCenaJogo\n");
        LoopCenaJogo(&geral, &jogo, tempo);
        DesenharCenaJogo(geral, jogo, tamanhos);
        break;

    case CENA_CRIACAO:
        LoopCenaMapa(&geral, &mapa);
        DesenharCenaMapa(geral, mapa);
        break;

    case CENA_PAUSE:
        LoopCenaPause(&geral, &pausa);
        DesenharCenaPause(geral, pausa);
        break;

    case CENA_CONF:
        LoopCenaConf(&geral, &conf, &tamanhos);
        DesenharCenaConf(geral, conf);
        break;

    case CENA_SAIR:
        geral.rodando = false;
        #ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
        #endif
        break;

    default:
        geral.cena = CENA_MENU;
        break;
    }

    if (geral.troca_reso) {
        geral.troca_reso = false;
        InitCenaMenu(&geral, &menu, tamanhos);
        InitCenaPause(&geral, &pausa, tamanhos);
        InitCenaMapa(geral.renderizador, &mapa, tamanhos);
        CalcularCenaJogo(&geral, &jogo, tamanhos);
        geral.resolucao_antiga[0] = geral.resolucao_atual[0];
        geral.resolucao_antiga[1] = geral.resolucao_atual[1];
    }
    if (geral.carregar_mapa) {
        printf("CalcularCenaJogo\n");
        CalcularCenaJogo(&geral, &jogo, tamanhos);
        geral.carregar_mapa = false;
    }

    SDL_RenderPresent(geral.renderizador);

    SDL_Delay(16);
    tempo = (double)(SDL_GetPerformanceCounter() - tempo_inicial);

    printf("%lf\n",tempo);
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    tamanhos.escala = 2;
    InitCenaGeral(&geral, &tamanhos);

    menu  = (VariveisMenu){AZUL};
    InitCenaMenu(&geral, &menu, tamanhos);

    pausa = (VariveisPause){SEMI_PRETO};
    InitCenaPause(&geral, &pausa, tamanhos);

    jogo  = (VariveisJogo){AZUL_CLARO};
    InitCenaJogo(&geral, &jogo, tamanhos);

    conf  = (VariveisConf){AZUL};
    InitCenaConf(&geral, &conf, tamanhos);
    conf.reso_inicial = tamanhos.escala;

    mapa  = (VariaveisMapa){AZUL};
    InitCenaMapa(geral.renderizador, &mapa, tamanhos);

    tempo_inicial = SDL_GetPerformanceCounter();

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(frame, 0, 1);
    #else
    while (geral.rodando)
        frame();

    SDL_DestroyRenderer(geral.renderizador);
    SDL_DestroyWindow(geral.janela);
    SDL_Quit();
    #endif

    return 0;
}
