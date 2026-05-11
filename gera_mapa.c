#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "mapa.h"


// 🔹 Salvar Mapa
void SalvarMapa(Mapa *c) {
	char nome[64];
	sprintf(nome, "map/map_%d.bin", c->n);

	FILE *f = fopen(nome, "wb");
	if (!f) {
		printf("nao foi possivel salvar a Mapa\n");
		return;
	}
	printf("mapa salvo\n");
	fwrite(c->tiles, sizeof(uint8_t), TamanhosMapaX * TamanhosMapaY, f);
	fclose(f);
}


void CarregarMapa(Mapa *c, int n) {
	c->n = n;

	char nome[64];
	sprintf(nome, "map/map_%d.bin", c->n);

	FILE *f = fopen(nome, "rb");

	if (f) {
		fread(c->tiles, sizeof(uint8_t), TamanhosMapaX * TamanhosMapaY, f);
		fclose(f);
		printf("mapa %d carregado do disco\n", n);
	} else {
		printf("mapa %d gerado\n", n);
		memset(c->tiles,0,sizeof(c->tiles));
		SalvarMapa(c);
	}
}

void InitCenaMapa(SDL_Renderer *renderizador, VariaveisMapa *mapa){
	mapa->camera = (Camera){0,0};
	mapa->rolada = 7*5;
	
}

