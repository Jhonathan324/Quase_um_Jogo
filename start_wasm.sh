#!/usr/bin/env bash
set -e

echo "[WASM] Compilando..."
make wasm

echo "[WASM] Iniciando servidor WebAssembly..."
python3 wasm_server.py
