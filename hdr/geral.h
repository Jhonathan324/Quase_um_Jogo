#ifndef GERAl_H_INCLUDED
#define GERAl_H_INCLUDED

#include "types.h"
#include "utils.h"



// Funções especificas
void GetTamanhos(Tamanhos *tamanhos);

// Funções só pra tratamento de eventos
void ModuloEvento(VariveisGerais *geral);
void InitCenaGeral(VariveisGerais *geral, Tamanhos *tamanhos);
void CalcularGeral(VariveisGerais *geral, Tamanhos *tamanhos);



#endif // GERAl_H_INCLUDED
