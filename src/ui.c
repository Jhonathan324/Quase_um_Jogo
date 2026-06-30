#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../hdr/geral.h"

CampoTexto InitTexto(SDL_Renderer *renderizador, SDL_FRect *retangulo, SDL_Color cor_fundo, char *texto, char *imagem, TTF_Font *fonte, SDL_Color cor_fonte, bool alinhado){
    int x,y;
    float proporcao = 0;
    TTF_GetStringSize(fonte, texto, 0, &x, &y);
    SDL_Surface* surface = TTF_RenderText_Solid(fonte,texto,0,cor_fonte);
    proporcao = (float)x/y;
    if(!alinhado){
        retangulo->w = retangulo->h * proporcao;
        proporcao=0;
    }
    CampoTexto campo_texto = {
        *retangulo,
        texto,
        cor_fundo,
        SDL_CreateTextureFromSurface(renderizador, surface),
        imagem ? IMG_LoadTexture(renderizador, imagem) : NULL,
        proporcao
    };
    if (campo_texto.imagem) SDL_SetTextureScaleMode(campo_texto.imagem, SDL_SCALEMODE_NEAREST);
    SDL_DestroySurface(surface);
    return campo_texto;
}

void DesenharTexto(SDL_Renderer *renderizador, CampoTexto texto){
    if(texto.cor_fundo.a){
        SDL_SetRenderDrawBlendMode(renderizador,SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderizador,texto.cor_fundo.r,texto.cor_fundo.g,texto.cor_fundo.b,texto.cor_fundo.a);
        SDL_RenderFillRect(renderizador, &texto.retangulo);
    }
    if(texto.imagem){
        SDL_RenderTexture(renderizador, texto.imagem, NULL, &texto.retangulo);
    }
    if(texto.textura_texto){

        if(texto.proporcao){
            SDL_FRect retangulo_texto = texto.retangulo;
            retangulo_texto.w = texto.retangulo.h * texto.proporcao * 0.8;
            retangulo_texto.x += (texto.retangulo.w-retangulo_texto.w)/2;
            retangulo_texto.h = texto.retangulo.h * 0.8;
            retangulo_texto.y += (texto.retangulo.h-retangulo_texto.h)/2;
            SDL_RenderTexture(renderizador, texto.textura_texto, NULL, &retangulo_texto);
        }
        else{
            SDL_FRect retangulo_texto = texto.retangulo;
            retangulo_texto.w = texto.retangulo.w * 0.8;
            retangulo_texto.x += (texto.retangulo.w-retangulo_texto.w)/2;
            retangulo_texto.h = texto.retangulo.h * 0.8;
            retangulo_texto.y += (texto.retangulo.h-retangulo_texto.h)/2;
            SDL_RenderTexture(renderizador, texto.textura_texto, NULL, &retangulo_texto);
        }
    }
}

void DestruirTexto(CampoTexto *texto){

    texto->texto = NULL;

    if(texto->textura_texto){
        SDL_DestroyTexture(texto->textura_texto);
        texto->textura_texto = NULL;
    }

    if(texto->imagem){
        SDL_DestroyTexture(texto->imagem);
        texto->imagem = NULL;
    }
}

Moldura InitMoldura(SDL_Renderer *renderizador, SDL_FRect *retangulo, char *file)
{
    Moldura moldura = {*retangulo, file ? IMG_LoadTexture(renderizador, file) : NULL};
    if (moldura.textura) SDL_SetTextureScaleMode(moldura.textura , SDL_SCALEMODE_NEAREST);

    return moldura;
}



void DesenharMoldura(SDL_Renderer *renderizador, Moldura moldura)
{
    SDL_RenderTexture9Grid(
        renderizador,
        moldura.textura,
        NULL,
        EscalaMoldura,
        EscalaMoldura,
        EscalaMoldura,
        EscalaMoldura,
        2.0f,
        &moldura.retangulo
    );

}

void DestruirMoldura(Moldura *moldura){
    if(moldura->textura){
        SDL_DestroyTexture(moldura->textura);
        moldura->textura = NULL;
    }
}

Marcador InitMarcador(SDL_Renderer *renderizador, SDL_FRect *retangulo, bool ativo, char *imagem1, SDL_Color cor1, SDL_Color cor2){
    Marcador marcador = {
        *retangulo,
        0,
        false,
        ativo,
        cor1,
        cor2,
        imagem1 ? IMG_LoadTexture(renderizador, imagem1) : NULL
    };
    if (marcador.imagem1) SDL_SetTextureScaleMode(marcador.imagem1 , SDL_SCALEMODE_NEAREST);
    return marcador;
}

bool VerificarMarcador(Marcador *marcador, SDL_Point mouse, bool click){
    if (marcador->timer)
    {
        if (marcador->timer > 1)
            marcador->timer--;

        else
        {
            marcador->timer = 0;
            marcador->ativo = !marcador->ativo;
            return true;
        }
    }

    // Cria um retangulo para verificar as colisões como o mouse
    SDL_Rect retangulo_colisao;
    AtribuirFRectInRect(&marcador->retangulo, &retangulo_colisao);

    // verifica se o mouse está emcima do botão
    if (SDL_PointInRect(&mouse, &retangulo_colisao))
        marcador->sobre = true;
    else
        marcador->sobre = false;

    // verifica se o botão de sair foi clicado
    if (marcador->sobre && click)
        marcador->timer = 15;

    return false;
}

void DesenharMarcador(SDL_Renderer *renderizador, Marcador marcador){
    if(marcador.ativo) SDL_RenderTexture(renderizador, marcador.imagem1, &(SDL_FRect){EscalaMarcador ,0,EscalaMarcador ,EscalaMarcador }, &marcador.retangulo);
    else SDL_RenderTexture(renderizador, marcador.imagem1, &(SDL_FRect){0,0,EscalaMarcador ,EscalaMarcador }, &marcador.retangulo);
    if(marcador.sobre){
        SDL_SetRenderDrawBlendMode(
                renderizador,
                SDL_BLENDMODE_BLEND
            );
            SDL_SetRenderDrawColor(renderizador, marcador.cor2.r, marcador.cor2.g, marcador.cor2.b, marcador.cor2.a);
            SDL_RenderFillRect(renderizador, &marcador.retangulo);
    }
}

void DestruirMarcador(Marcador *marcador){
    if(marcador->imagem1){
        SDL_DestroyTexture(marcador->imagem1);
        marcador->imagem1 = NULL;
    }
}

Botao InitBotao(SDL_Renderer *renderizador, SDL_FRect *retangulo, char *imagem, char *texto, SDL_Color cor1, SDL_Color cor2, int indice, TTF_Font *fonte, SDL_Color cor_fonte)
{
    // texto
    int x, y;
    float proporcao = 1;
    SDL_Texture *textura_texto = NULL;
    if (texto)
    {
        SDL_Surface *surface = TTF_RenderText_Solid(fonte, texto, 0, cor_fonte);
        textura_texto = SDL_CreateTextureFromSurface(renderizador, surface);
        TTF_GetStringSize(fonte, texto, 0, &x, &y);
        proporcao = (float)x / y;
        retangulo->w = retangulo->h * proporcao;
        SDL_DestroySurface(surface);
    }
    // Botão

    Botao botao = {
        *retangulo, // retangulo
        texto,      // texto
        proporcao,  // proporcao (porporção entre a largura sobre altura)
        0,          // timer
        false,      // sobre (verificar se o mouse esta sobre)
        indice,     // indice
        cor1,       // cor1 e cor2
        cor2,
        textura_texto,                                              // textura texto
        imagem ? IMG_LoadTexture(renderizador, imagem) : NULL};    // textura da imagem

    float tamanho_canto;
    if (retangulo->h >= retangulo->w)
        tamanho_canto = retangulo->w / 2;
    else
        tamanho_canto = retangulo->h / 2;

    // imagem
    if (botao.imagem) SDL_SetTextureScaleMode(botao.imagem, SDL_SCALEMODE_NEAREST);
    return botao;
}


void DesenharBotao(SDL_Renderer *renderizador, Botao botao)
{
    if (!botao.imagem)
    {
        if (!botao.sobre)
        {
            SDL_SetRenderDrawColor(renderizador, botao.cor1.r, botao.cor1.g, botao.cor1.b, botao.cor1.a);
        }
        else
        {
            SDL_SetRenderDrawColor(renderizador, botao.cor2.r, botao.cor2.g, botao.cor2.b, botao.cor2.a);
        }
        SDL_RenderFillRect(renderizador, &botao.retangulo);
    }
    else
    {

        SDL_RenderTexture9Grid(
            renderizador,
            botao.imagem,
            NULL,
            EscalaBotao,
            EscalaBotao,
            EscalaBotao,
            EscalaBotao,
            3.0f,
            &botao.retangulo
        );


        if(botao.sobre){
            SDL_SetRenderDrawBlendMode(renderizador,SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderizador, botao.cor2.r, botao.cor2.g, botao.cor2.b, botao.cor2.a);
            SDL_RenderFillRect(renderizador, &botao.retangulo);
        }
    }
    if (botao.textura)
    {
        SDL_FRect retangulo_texto = botao.retangulo;
        retangulo_texto.h *= 0.8;
        retangulo_texto.w = retangulo_texto.h * botao.proporcao;
        retangulo_texto.x = (botao.retangulo.x + (botao.retangulo.w - retangulo_texto.w) / 2);
        retangulo_texto.y = (botao.retangulo.y + (botao.retangulo.h - retangulo_texto.h) / 2);
        SDL_RenderTexture(renderizador, botao.textura, NULL, &retangulo_texto);
    }
}

bool VerificarBotao(Botao *botao, SDL_Point mouse, bool click)
{
    if (botao->timer)
    {
        if (botao->timer > 1)
            botao->timer--;

        else
        {
            botao->timer = 0;
            return true;
        }
    }

    // Cria um retangulo para verificar as colisões como o mouse
    SDL_Rect retangulo_colisao;
    AtribuirFRectInRect(&botao->retangulo, &retangulo_colisao);

    // verifica se o mouse está emcima do botão
    if (SDL_PointInRect(&mouse, &retangulo_colisao))
        botao->sobre = true;
    else
        botao->sobre = false;

    // verifica se o botão de sair foi clicado
    if (botao->sobre && click)
        botao->timer = 15;

    return false;
}

void DestruirBotao(Botao *botao){
    botao->texto = NULL;

    if(botao->textura){
        SDL_DestroyTexture(botao->textura);
        botao->textura = NULL;
    }

    if(botao->imagem){
        SDL_DestroyTexture(botao->imagem);
        botao->imagem = NULL;
    }
}

BotaoExpansivo InitBotaoExpansivo(SDL_Renderer *renderizador, SDL_FRect *retangulo, char *imagem, char *texto, char *textos[], SDL_Color cor1, SDL_Color cor2, int indice, TTF_Font *fonte, SDL_Color cor_fonte, int n)
{
    // texto
    int x, y;
    float proporcao = 1;
    SDL_Texture *textura_texto = NULL;
    if (texto)
    {
        SDL_Surface *surface_texto = TTF_RenderText_Solid(fonte, texto, 0, cor_fonte);
        textura_texto = SDL_CreateTextureFromSurface(renderizador, surface_texto);
        TTF_GetStringSize(fonte, texto, 0, &x, &y);
        proporcao = (float)x / y;
        retangulo->w = retangulo->h * proporcao;
        SDL_DestroySurface(surface_texto);
    }
    // Botão

    Botao botao = {
        *retangulo, // retangulo
        texto,      // texto
        proporcao,  // proporcao (porporção entre a largura sobre altura)
        0,          // timer
        false,      // sobre (verificar se o mouse esta sobre)
        indice,     // indice
        cor1,       // cor1 e cor2
        cor2,
        textura_texto,                                              // textura texto
        imagem ? IMG_LoadTexture(renderizador, imagem) : NULL};    // textura da imagem

    float tamanho_canto;
    if (retangulo->h >= retangulo->w)
        tamanho_canto = retangulo->w / 2;
    else
        tamanho_canto = retangulo->h / 2;

    // imagem
    if (botao.imagem) SDL_SetTextureScaleMode(botao.imagem, SDL_SCALEMODE_NEAREST);

    Botao *botoes = malloc(sizeof(Botao) * n);
    for (int i = 0; i < n; i++)
    {
        botoes[i] = botao;
        botoes[i].texto = textos[i];
        botoes[i].retangulo.y = botao.retangulo.y + botao.retangulo.h * (i + 1);

        SDL_Surface *surface_texto = TTF_RenderText_Solid(fonte, textos[i], 0, cor_fonte);
        botoes[i].textura = SDL_CreateTextureFromSurface(renderizador, surface_texto);
        TTF_GetStringSize(fonte, textos[i], 0, &x, &y);
        botoes[i].proporcao = (float)x / y;
        SDL_DestroySurface(surface_texto);
        // printf("%s ",botoes[i].texto);
        // printf("%f\n",botoes[i].retangulo.y);
    }
    BotaoExpansivo botao_e = {n, botao, botoes, false};
    return botao_e;
}


void DesenharBotaoExpansivo(SDL_Renderer *renderizador, BotaoExpansivo botao)
{
    if (!botao.botao_pai.imagem){
        SDL_SetRenderDrawColor(renderizador, botao.botao_pai.cor1.r, botao.botao_pai.cor1.g, botao.botao_pai.cor1.b, botao.botao_pai.cor1.a);
        SDL_RenderFillRect(renderizador, &botao.botao_pai.retangulo);
    }
    else
    {
            {
                SDL_RenderTexture9Grid(
                renderizador,
                botao.botao_pai.imagem,
                NULL,
                EscalaBotao,
                EscalaBotao,
                EscalaBotao,
                EscalaBotao,
                3.0f,
                &botao.botao_pai.retangulo
            );
    }
    if(botao.expandido){
        SDL_SetRenderDrawBlendMode(
            renderizador,
            SDL_BLENDMODE_BLEND
        );
        SDL_SetRenderDrawColor(renderizador, botao.botao_pai.cor2.r, botao.botao_pai.cor2.g, botao.botao_pai.cor2.b, botao.botao_pai.cor2.a);
        SDL_RenderFillRect(renderizador, &botao.botao_pai.retangulo);
    }


    if (botao.botao_pai.textura)
    {
        SDL_FRect retangulo_texto = botao.botao_pai.retangulo;
        retangulo_texto.h *= 0.8;
        retangulo_texto.w = retangulo_texto.h * botao.botao_pai.proporcao;
        retangulo_texto.x = (botao.botao_pai.retangulo.x + (botao.botao_pai.retangulo.w - retangulo_texto.w) / 2);
        retangulo_texto.y = (botao.botao_pai.retangulo.y + (botao.botao_pai.retangulo.h - retangulo_texto.h) / 2);
        SDL_RenderTexture(renderizador, botao.botao_pai.textura, NULL, &retangulo_texto);
    }
    for (int i1 = 0; i1 < botao.n && botao.expandido; i1++)
    {
        if (!botao.botao_filho[i1].imagem)
        {
            if (!botao.botao_filho[i1].sobre)
            {
                SDL_SetRenderDrawColor(renderizador, botao.botao_filho[i1].cor1.r, botao.botao_filho[i1].cor1.g, botao.botao_filho[i1].cor1.b, botao.botao_filho[i1].cor1.a);
            }
            else
            {
                SDL_SetRenderDrawColor(renderizador, botao.botao_filho[i1].cor2.r, botao.botao_filho[i1].cor2.g, botao.botao_filho[i1].cor2.b, botao.botao_filho[i1].cor2.a);
            }
            SDL_RenderFillRect(renderizador, &botao.botao_filho[i1].retangulo);
        }
        else
            {
                SDL_RenderTexture9Grid(
                renderizador,
                botao.botao_filho[i1].imagem,
                NULL,
                EscalaBotao,
                EscalaBotao,
                EscalaBotao,
                EscalaBotao,
                3.0f,
                &botao.botao_filho[i1].retangulo
            );
            if(botao.botao_filho[i1].sobre ){
            SDL_SetRenderDrawBlendMode(
                renderizador,
                SDL_BLENDMODE_BLEND
            );
            SDL_SetRenderDrawColor(renderizador, botao.botao_filho[i1].cor2.r, botao.botao_filho[i1].cor2.g, botao.botao_filho[i1].cor2.b, botao.botao_filho[i1].cor2.a);
            SDL_RenderFillRect(renderizador, &botao.botao_filho[i1].retangulo);
        }
        }

        if (botao.botao_filho[i1].textura)
        {
            SDL_FRect retangulo_texto = botao.botao_filho[i1].retangulo;
            retangulo_texto.h *= 0.8;
            retangulo_texto.w = retangulo_texto.h * botao.botao_filho[i1].proporcao;
            retangulo_texto.x = (botao.botao_filho[i1].retangulo.x + (botao.botao_filho[i1].retangulo.w - retangulo_texto.w) / 2);
            retangulo_texto.y = (botao.botao_filho[i1].retangulo.y + (botao.botao_filho[i1].retangulo.h - retangulo_texto.h) / 2);
            SDL_RenderTexture(renderizador, botao.botao_filho[i1].textura, NULL, &retangulo_texto);
        }
    }
}}

void DestruirBotaoExpansivo(BotaoExpansivo *botao){
    DestruirBotao(&botao->botao_pai);

    if(botao->botao_filho){
        for(int i = 0; i < botao->n; i++){
            DestruirBotao(&botao->botao_filho[i]);
        }

        free(botao->botao_filho);
        botao->botao_filho = NULL;
    }
}

