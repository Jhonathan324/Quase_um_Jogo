#include "jogo.h"
#include <stdio.h>


PlayerInJogo InitPlayer(SDL_Renderer *renderizador, SDL_FRect retangulo_img, SDL_FRect retangulo_coli,  char *img){
    PlayerInJogo player = {
    100.0,
    3,
    0,
    0,
    (float)retangulo_coli.w/100,
    (float)retangulo_coli.w/48,
    (float)retangulo_coli.h/48,
    retangulo_img,
    retangulo_coli,
    retangulo_coli,
    retangulo_coli,
    IMG_LoadTexture(renderizador, img),
    0,0,0,0,0,0};
    SDL_SetTextureScaleMode(player.sprite_atlas, SDL_SCALEMODE_NEAREST);
    return player;
}

void CalcularPlayer(const bool *teclado, PlayerInJogo *player, double delta_frame){
    double movi_v = 0, movi_h = 0;
    player->frame += delta_frame;

    // Logica do Player
    movi_h = (-teclado[SDL_SCANCODE_A] + teclado[SDL_SCANCODE_D]) * player->acelera;
    movi_v = (-teclado[SDL_SCANCODE_W] + teclado[SDL_SCANCODE_S]) * player->acelera;

    if(movi_h<0) player->costas = true;
    if(movi_h>0) player->costas = false;
    
    if(movi_h){ 
        if (player->estado_passado != CORRIDA){
            player->frame=0;
        }
        player->estado_passado = player->estado_atual;
        player->estado_atual = CORRIDA;
    }
    else{
        player->estado_passado = player->estado_atual;
        player->estado_atual = IDLE;
    }

    

    if(!movi_h) player->velocidade_x = 0;
    if(!movi_v) player->velocidade_y = 0;

    player->velocidade_x += movi_h * delta_frame * delta_frame;
    player->velocidade_y += movi_v * delta_frame * delta_frame;

    // vericando para a velocidade não passar do maximo
    if (player->velocidade_x < player->vel_max_x*-1)
        player->velocidade_x = player->vel_max_x*-1;

    if (player->velocidade_x > player->vel_max_x)
        player->velocidade_x = player->vel_max_x;

    if (player->velocidade_y < player->vel_max_y*-1)
        player->velocidade_y = player->vel_max_y*-1;

    if (player->velocidade_y > player->vel_max_y)
        player->velocidade_y = player->vel_max_y;
    
    player->retangulo_coli.x += player->velocidade_x;
    player->retangulo_coli.y += player->velocidade_y;

    CentralizarRectInRect(&player->retangulo_coli, &player->retangulo_img);
}

void DesenharPlayer(SDL_Renderer *renderizador, PlayerInJogo player){
    // se tiver em teste eu não comento
    SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);
    SDL_RenderFillRect(renderizador, &player.retangulo_coli);

    Uint64 frame_atual = player.frame; 
    switch(player.estado_atual){
        case(IDLE):{
            frame_atual /= 10;
            SDL_RenderTextureRotated(renderizador, player.sprite_atlas,&(SDL_FRect){MedidaImgPlayerX*(frame_atual%10),MedidaImgPlayerY*0,MedidaImgPlayerX,MedidaImgPlayerY},
            &player.retangulo_img,0,0, player.costas ? SDL_FLIP_HORIZONTAL: 0);    
        ;
        }break;
        case(CORRIDA):{
            frame_atual /= 5;
            SDL_RenderTextureRotated(renderizador, player.sprite_atlas,&(SDL_FRect){MedidaImgPlayerX*(frame_atual%16),MedidaImgPlayerY*2,MedidaImgPlayerX,MedidaImgPlayerY},
            &player.retangulo_img,0,0, player.costas ? SDL_FLIP_HORIZONTAL: 0);    
        ;
        }break;
        case(ATAQUE):{
            frame_atual /= 15;
            SDL_RenderTextureRotated(renderizador, player.sprite_atlas,&(SDL_FRect){MedidaImgPlayerX*(frame_atual%16),MedidaImgPlayerY*3,MedidaImgPlayerX,MedidaImgPlayerY},
            &player.retangulo_img,0,0, player.costas ? SDL_FLIP_HORIZONTAL: 0);    
        ;
        }break;
        case(DANO):{
            frame_atual /= 15;
            SDL_RenderTextureRotated(renderizador, player.sprite_atlas,&(SDL_FRect){MedidaImgPlayerX*(frame_atual%16),MedidaImgPlayerY*1,MedidaImgPlayerX,MedidaImgPlayerY},
            &player.retangulo_img,0,0, player.costas ? SDL_FLIP_HORIZONTAL: 0);    
        ;
        }break;
    }

    

}