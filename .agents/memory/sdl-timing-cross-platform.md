---
name: SDL timing cross-platform
description: SDL_GetPerformanceFrequency difere entre Linux e WASM/emscripten, causando delta_t 1000x menor no WASM e física congelada.
---

## Problema
`SDL_GetPerformanceFrequency()` retorna unidades diferentes por plataforma:
- Linux/desktop: ~1,000,000,000 (nanosegundos)
- WASM/emscripten: ~1,000,000 (microsegundos)

Usar o delta bruto do contador diretamente causa delta_t 1000x menor no WASM que no desktop. Com física projetada para escala de ns, o jogo fica estático no WASM.

**Why:** O código de física usa delta_t * 100 com constantes calibradas para o timer de nanosegundos do Linux. No WASM o timer é em microsegundos, então delta_t é 1000x menor.

**How to apply:** Sempre normalizar para nanosegundos antes de passar delta_t para a física:

```c
static double nanos_por_tick; // = 1e9 / SDL_GetPerformanceFrequency()

// Em main():
nanos_por_tick = 1000000000.0 / (double)SDL_GetPerformanceFrequency();
tempo_inicial = SDL_GetPerformanceCounter();

// Em frame():
Uint64 agora = SDL_GetPerformanceCounter();
tempo = (double)(agora - tempo_inicial) * nanos_por_tick;
tempo_inicial = agora;
```

Isso dá ~16,670,000 ns por frame em ambas as plataformas a 60fps.

## Outras lições relacionadas (mesmo projeto)

### Makefile TABs — CRÍTICO
`edit`/`write` do agent convertem TABs para espaços no Makefile. SEMPRE reescrever via `bash cat > Makefile << 'EOF'` (heredoc).

### Stack overflow no WASM
SDL3 3.2.4 porta emscripten usa mais stack. Mínimo: `-s STACK_SIZE=4194304` (4MB).

### SDL_Delay no loop WASM
`SDL_Delay()` dentro do callback do emscripten chama `emscripten_sleep`, lança exceção sem Asyncify. Guardar com `#ifndef __EMSCRIPTEN__`.

### Medição de delta_t
Medir do INÍCIO do frame atual ao INÍCIO do próximo (não do início ao fim do mesmo frame). O `SDL_RenderPresent` no WASM não bloqueia para vsync, então medir só o render time dá ~0-1ms.
