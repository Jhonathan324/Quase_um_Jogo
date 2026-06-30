#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "desumano.h"

#define CORCORFUNDO {20, 20, 20, 255}
#define COR1 {20, 20, 20, 255}
#define PRETO {0, 0, 0, 255}
#define BRANCO {255, 255, 255, 255}
#define VERMELHO {255, 20, 20, 255}
#define VERDE {20, 255, 20, 255}
#define AZUL {20, 20, 255, 255}
#define AZUL_CLARO {140, 210, 230, 255}
#define SEMI_PRETO {0, 0, 0, 128}

#define EscalaHud 16
#define EscalaMoldura 16
#define EscalaMarcador 16
#define EscalaBotao 8
#define CantoFixo 48
#define MedidaImgPlayerX 120
#define MedidaImgPlayerY 80
#define MedidaImgPlayerColiX 21
#define MedidaImgPlayerColiY 38
#define MedidaImgInimigo1X 48
#define MedidaImgInimigo1Y 32
#define MedidaImgInimigo2X 120
#define MedidaImgInimigo2Y 80
#define MedidaImgBloco 16

#define TamanhosMapaX 512
#define TamanhosMapaY 128

typedef struct Bloco{
	SDL_Texture *textura;
	SDL_FRect loc;
	SDL_FRect retangulo;
} Bloco;




// enuns
typedef enum {
    CENA_MENU,
    CENA_JOGO,
    CENA_PAUSE,
    CENA_CRIACAO,
    CENA_CONF,
    CENA_VITORIA, 
    CENA_DERROTA, 
    CENA_CREDITOS, // algum dia eu vou usar
    CENA_SAIR,
}ESTADO_JOGO;

typedef struct Camera {
    int x;
    int y;
} Camera;


// elementos UI
typedef struct CampoTexto{
    SDL_FRect retangulo;
    char *texto;
    SDL_Color cor_fundo;
    SDL_Texture *textura_texto;
    SDL_Texture *imagem;
    float proporcao;
} CampoTexto;


typedef struct Moldura
{
    SDL_FRect retangulo;
    SDL_Texture *textura;
} Moldura;

typedef struct Marcador{
    SDL_FRect retangulo;
    int timer;
    bool sobre;
    bool ativo;
    SDL_Color cor1;
    SDL_Color cor2;
    SDL_Texture *imagem1;
} Marcador;

typedef struct Botao
{
    SDL_FRect retangulo;
    char *texto;
    float proporcao;
    int timer;
    bool sobre;
    int indice;
    SDL_Color cor1;
    SDL_Color cor2;
    SDL_Texture *textura;
    SDL_Texture *imagem;
} Botao;

typedef struct BotaoExpansivo
{
    int n;
    Botao botao_pai;
    Botao *botao_filho;
    bool expandido;
} BotaoExpansivo;

// Coisas mais especificas
typedef struct Tamanhos
{
    int escala;
    float tela[2];
    float menu[2];
    float botao1[2];
    float botao2[2];
    float barra_vida[2];
    float jogador[2];
    float jogador_coli[2];
    float inimigo1[2];
    float inimigo2[2];
    float bloco1[2];
} Tamanhos;

// Structs abstratas
typedef struct Player
{
    int vida;
    int coracoes;
} Player;

// Structs especicas para organizar dados

typedef struct VariveisGerais
{
    SDL_Window *janela;
    SDL_Renderer *renderizador;
    SDL_Event evento;
    SDL_Point ponto_mouse;
    SDL_Texture *textura_hud;
    SDL_FRect barra_de_vida;
    bool debug;
    bool rodando;
    bool fullscrean;
    bool troca_reso;
    bool carregar_mapa;
    int botao_mouse_direito;
    int botao_mouse_esquerdo;
    int botao_mouse_meio;
    int botao_mouse_gira;
    int resolucao_atual[2];
    int resolucao_antiga[2];
    float mouse_x, mouse_y;
    float mouse_x_back, mouse_y_back;
    Player jogador;
    ESTADO_JOGO cena;
    ESTADO_JOGO cena_passada;
    ESTADO_JOGO cena_continuar;
} VariveisGerais;




#endif 