SDL3_LIB     = /nix/store/30wrp9i8g265xw9cbvc1r82illh8dmsn-sdl3-3.2.14-lib
SDL3_DEV     = /nix/store/19z41m01vxlw9y7jwkgplika1x9ska3z-sdl3-3.2.14-dev
SDL3_IMG_LIB = /nix/store/8c5hyvjvip6hp0i34kvfbncy5x8rscj0-sdl3-image-3.2.4-lib
SDL3_IMG_DEV = /nix/store/cpqwclxqv36y8h5gbv0b5bd6n00a72f7-sdl3-image-3.2.4-dev
SDL3_TTF     = /nix/store/g9s4lqf3vskig9nf0xml65d8ikaj5py1-sdl3-ttf-3.2.2

CC   = gcc
SRCS = main.c conf.c gera_mapa.c gerais.c geral.c jogo.c jogofuncoes.c menu.c pause.c

CFLAGS_COMMON = -Wall \
	-Iinclude \
	-I$(SDL3_DEV)/include \
	-I$(SDL3_IMG_DEV)/include \
	-I$(SDL3_TTF)/include

LDFLAGS = \
	-L$(SDL3_LIB)/lib     -lSDL3 \
	-L$(SDL3_IMG_LIB)/lib -lSDL3_image \
	-L$(SDL3_TTF)/lib     -lSDL3_ttf

CFLAGS_DEBUG   = $(CFLAGS_COMMON) -g -O0 -Wno-cpp
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2

OUT_DEBUG   = bin/Debug/game
OUT_RELEASE = bin/Release/game
OBJ_DEBUG   = obj/Debug
OBJ_RELEASE = obj/Release

OBJS_DEBUG   = $(patsubst %.c,$(OBJ_DEBUG)/%.o,$(SRCS))
OBJS_RELEASE = $(patsubst %.c,$(OBJ_RELEASE)/%.o,$(SRCS))

# ── WebAssembly (Emscripten) ──────────────────────────────────────────────
EM_CACHE     = /home/runner/emcache
EMCC         = EM_CACHE=$(EM_CACHE) emcc

IMG_SRC_INC  = wasm_deps/src/SDL3_image-3.2.4/include

IMG_WASM_LIB      = wasm_deps/build/SDL3_image/libSDL3_image.a
TTF_WASM_LIB      = wasm_deps/build/SDL3_ttf/libSDL3_ttf.a
FT_WASM_LIB       = wasm_deps/build/SDL3_ttf/external/freetype/libfreetype.a
PLUTOSVG_WASM_LIB = wasm_deps/build/SDL3_ttf/external/plutosvg/libplutosvg.a
PLUTOVG_WASM_LIB  = wasm_deps/build/SDL3_ttf/external/plutovg/libplutovg.a

CFLAGS_WASM = \
	-Wall \
	-O2 \
	-Iinclude \
	-I$(SDL3_TTF)/include/SDL3_ttf \
	-I$(IMG_SRC_INC) \
	--use-port=sdl3

LDFLAGS_WASM = \
	--use-port=sdl3 \
	$(IMG_WASM_LIB) \
	$(TTF_WASM_LIB) \
	$(FT_WASM_LIB) \
	$(PLUTOSVG_WASM_LIB) \
	$(PLUTOVG_WASM_LIB) \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s INITIAL_MEMORY=67108864 \
	-s USE_WEBGL2=1 \
	-s MIN_WEBGL_VERSION=2 \
	-s EXIT_RUNTIME=0 \
	-s STACK_SIZE=524288 \
	--preload-file assets \
	--preload-file map

OUT_WASM  = bin/wasm/game.html
OBJ_WASM  = obj/wasm
OBJS_WASM = $(patsubst %.c,$(OBJ_WASM)/%.o,$(SRCS))

# ── Targets ───────────────────────────────────────────────────────────────
.PHONY: all debug release wasm clean

all: debug

debug: $(OUT_DEBUG)

release: $(OUT_RELEASE)

wasm: $(OUT_WASM)

$(OUT_DEBUG): $(OBJS_DEBUG)
	@mkdir -p bin/Debug
	$(CC) $^ $(LDFLAGS) -o $@
	@echo "[DEBUG] Compilado: $@"

$(OUT_RELEASE): $(OBJS_RELEASE)
	@mkdir -p bin/Release
	$(CC) $^ $(LDFLAGS) -s -o $@
	@echo "[RELEASE] Compilado: $@"

$(OUT_WASM): $(OBJS_WASM)
	@mkdir -p bin/wasm
	$(EMCC) $^ $(LDFLAGS_WASM) -o $@
	@echo "[WASM] Compilado: $@"

$(OBJ_DEBUG)/%.o: %.c
	@mkdir -p $(OBJ_DEBUG)
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

$(OBJ_RELEASE)/%.o: %.c
	@mkdir -p $(OBJ_RELEASE)
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@

$(OBJ_WASM)/%.o: %.c
	@mkdir -p $(OBJ_WASM)
	$(EMCC) $(CFLAGS_WASM) -c $< -o $@

clean:
	rm -rf obj/ bin/Debug/game bin/Release/game bin/wasm/
	@echo "Limpo."
