#include "jogo.h"
#include <stdio.h>


PlayerInJogo InitPlayer(SDL_Renderer *renderizador, SDL_FRect retangulo_img, SDL_Rect retangulo_coli,  char *img){
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
    double movi_v = true, movi_h = 0;
    player->frame += delta_frame;

    // Logica do Player
    movi_h = (teclado[SDL_SCANCODE_D] - teclado[SDL_SCANCODE_A]);
    

    if(movi_h<0) player->costas = true;
    if(movi_h>0) player->costas = false;
    
    if(movi_h){ 
        if (player->estado_passado != VMM_PLAYER_CORRER){
            player->frame=0;
        }
        player->estado_passado = player->estado_atual;
        player->estado_atual = VMM_PLAYER_CORRER;
    }
    else{
        player->estado_passado = player->estado_atual;
        player->estado_atual = VMM_PLAYER_IDLE;
    }
    
    
    if(!movi_h) player->velocidade_x = 0;
    
    player->velocidade_x += player->acelera * delta_frame * movi_h;
    player->velocidade_y += player->acelera * delta_frame * movi_v;
    
    if(player->coli_v){
        movi_v = false;
        player->velocidade_y = false;
        player->retangulo_coli_v = player->retangulo_coli;
    }
    // vericando para a velocidade não passar do maximo
    if (player->velocidade_x < player->vel_max_x*-1)
        player->velocidade_x = player->vel_max_x*-1;

    if (player->velocidade_x > player->vel_max_x)
        player->velocidade_x = player->vel_max_x;

    if (player->velocidade_y < player->vel_max_y*-1)
        player->velocidade_y = player->vel_max_y*-1;

    if (player->velocidade_y > player->vel_max_y)
        player->velocidade_y = player->vel_max_y;

    printf("%f\n",player->velocidade_x);
    player->retangulo_coli_h.x += player->velocidade_x * delta_frame;
    player->retangulo_coli_v.y += player->velocidade_y * delta_frame;
        
    player->retangulo_coli.x = player->retangulo_coli_h.x;
    player->retangulo_coli.y = player->retangulo_coli_v.y;

    player->retangulo_coli_h = player->retangulo_coli;
    player->retangulo_coli_v = player->retangulo_coli;
    

    
    player->retangulo_img.y = player->retangulo_coli.y + player->retangulo_coli.h-player->retangulo_img.h;
    player->retangulo_img.x = player->retangulo_coli.x -  (player->retangulo_img.w * ((float)44/MedidaImgPlayerX)) - (player->costas)*(player->retangulo_img.w * ((float)11/MedidaImgPlayerX)); 
}

void DesenharPlayer(SDL_Renderer *renderizador, PlayerInJogo player){
    // se tiver em teste eu não comento
    SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);
    SDL_RenderFillRect(renderizador, &(SDL_FRect){
        player.retangulo_coli.x,
        player.retangulo_coli.y,
        player.retangulo_coli.w,
        player.retangulo_coli.h});

    Uint64 frame_atual = player.frame / 10; 
    #define X(index,quant) \
         case(index):{ \
         SDL_RenderTextureRotated(renderizador, player.sprite_atlas,&(SDL_FRect){MedidaImgPlayerX*(frame_atual%quant),MedidaImgPlayerY*index,MedidaImgPlayerX,MedidaImgPlayerY}, \
         &player.retangulo_img,0,0, player.costas ? SDL_FLIP_HORIZONTAL: 0);}break;

    switch(player.estado_atual){
        TabelaPlayerAnim
    }
    #undef X
}

void DesenharBloco(SDL_Renderer *renderizador, Bloco bloco){
    SDL_RenderTexture(renderizador, bloco.textura, &bloco.loc, &bloco.retangulo);

}

void ColisaoPlayerMapa(PlayerInJogo *jogador, Mapa mapa, int tamanho_bloco[2], int tamanho_tela[2]){
    for(int i = 0 ; i*tamanho_bloco[1] < tamanho_tela[1]; i++){
        for(int j = 0; j*tamanho_bloco[0] < tamanho_tela[0]; j++){
            if(mapa.tiles[i][j]){ 
                TiposVMMA tipo_de_coli = CalcularTipoVMMA(mapa.tiles[i][j]);
                switch (tipo_de_coli){
                    case VMMA_GRAMA_ON:
                    case VMMA_PEDRA_ON:{
                        SDL_Rect retangulo = {j*tamanho_bloco[0], i*tamanho_bloco[1], tamanho_bloco[0], tamanho_bloco[1]};
                        if(SDL_HasRectIntersection(&retangulo, &jogador->retangulo_coli_v))
                            jogador->coli_v = true;

                        if(SDL_HasRectIntersection(&retangulo, &jogador->retangulo_coli_h))
                            jogador->coli_h = true;
                    }break;
                        
                }
                
            }
        }
    }
}


void DesenharMapa(SDL_Renderer *renderizador, Mapa mapa, Camera camera, int tamanho_bloco[2], int tamanho_tela[2]){
    for(int i = 0 ; i*tamanho_bloco[1] < tamanho_tela[1]; i++){
        for(int j = 0; j*tamanho_bloco[0] < tamanho_tela[0]; j++){
            if(mapa.tiles[i][j]){ 
                SDL_FRect src = MapaTiles(mapa.tiles[i][j]);
                SDL_RenderTexture(renderizador, mapa.textura, &src , &(SDL_FRect){j*tamanho_bloco[0], i*tamanho_bloco[1], tamanho_bloco[0],tamanho_bloco[1]});
            }
        }
    }
}

SDL_FRect MapaTiles(int n){
    SDL_FRect rect = {
        .w = MedidaImgBloco,
        .h = MedidaImgBloco
    };

    #define X(index, x_loc, y_loc, tipo) \
        case(index):{ \
            rect.x = x_loc * MedidaImgBloco; \
            rect.y = y_loc * MedidaImgBloco;  \
        }break; 

    switch(n-1){
        TabelaBlocoAtlas
    }

    #undef X

    return rect;
}

TiposVMMA CalcularTipoVMMA(int n){
    TiposVMMA x;
    #define X(index, x_loc, y_loc, tipo) \
    case(index):{ \
        x = tipo; \
    }break; 

    switch(n-1){
        TabelaBlocoAtlas
    }

    #undef X
    
    return x;
}