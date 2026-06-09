---
name: Emscripten NixOS cache setup
description: Como contornar o bug de cache do emscripten 4.x no NixOS/Replit — o sysroot não pode ser copiado automaticamente pelo emcc devido a symlinks read-only.
---

## Problema
O emscripten 4.0.8 no NixOS tenta copiar o sysroot via `shutil.copytree` ao iniciar, mas falha com `PermissionError` no diretório `compiler-rt/include/sanitizer` (que é um symlink apontando para um diretório read-only no nix store).

## Solução
Pré-popular `/tmp/emcache` com o sysroot do nix store antes de chamar `emcc`, copiando recursivamente com resolução de symlinks via Python. Criar o arquivo stamp `sysroot_install.stamp` para que o emscripten pule a instalação automática.

**Why:** O emscripten checa a existência do stamp antes de rodar `install_system_headers`. Se o stamp existe, ele não tenta copiar o sysroot. O `/tmp/emcache` é volátil entre reinicializações, por isso o script `setup_emcache.py` deve rodar sempre antes de compilar.

**How to apply:** 
- Usar `EM_CACHE=/tmp/emcache` no Makefile
- Chamar `python3 setup_emcache.py` no script de inicialização antes de `make wasm`
- O script usa `os.path.realpath()` para seguir symlinks e copia apenas arquivos reais, evitando o bug do `shutil.copytree`

## Paths relevantes
- Nix cache pré-construído: `/nix/store/hxmxpb71x3f891nn4fdcg8pvmh2pmg0s-emscripten-4.0.8/share/emscripten/cache`
- Cache gravável: `/tmp/emcache`
- Stamp file: `/tmp/emcache/sysroot_install.stamp`

## SDL3 port no emscripten
- SDL3: `--use-port=sdl3` (emscripten baixa e compila SDL3 na primeira execução)
- SDL3_image: compilar do fonte com emcmake/emmake (porta não existe no emscripten)
- SDL3_ttf: compilar do fonte com emcmake/emmake + freetype/plutosvg/plutovg vendorizados

## Stack overflow em WASM (STACK_SIZE muito pequeno)
SDL3 3.2.4 usa mais stack do que SDL3 3.2.14. Com 512KB (`-s STACK_SIZE=524288`) o jogo crasha em `LoopCenaJogo` com "Stack overflow detected" e "memory access out of bounds".

**Fix:** Aumentar para 4MB (`-s STACK_SIZE=4194304`).

## SDL_Delay no loop WASM
`SDL_Delay(16)` dentro do callback de `emscripten_set_main_loop` causa chamada a `emscripten_sleep` que lança exceção sem Asyncify habilitado.

**Fix:** Guardar com `#ifndef __EMSCRIPTEN__`.

## Makefile TABs — CRÍTICO
O `edit` e `write` do agent convertem TABs para espaços no Makefile, quebrando todas as receitas. SEMPRE reescrever o Makefile via `bash cat > Makefile << 'EOF'` (heredoc) que preserva TABs reais.
