#!/usr/bin/env bash
set -e

echo "[WASM] Verificando cache do emscripten..."
python3 setup_emcache.py

echo "[WASM] Compilando..."
make wasm

echo "[WASM] Iniciando servidor WebAssembly..."
python3 wasm_server.py
