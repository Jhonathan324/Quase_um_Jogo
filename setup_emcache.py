#!/usr/bin/env python3
"""
Popula /tmp/emcache a partir do cache pré-construído do nix store,
tratando symlinks e permissões do NixOS corretamente.
"""
import os, shutil, stat, sys

NIXCACHE = "/nix/store/hxmxpb71x3f891nn4fdcg8pvmh2pmg0s-emscripten-4.0.8/share/emscripten/cache"
EM_CACHE  = "/tmp/emcache"
STAMP     = os.path.join(EM_CACHE, "sysroot_install.stamp")

def stamp_valid():
    return os.path.isfile(STAMP)

def force_rmtree(path):
    def handle_error(func, fpath, exc_info):
        try:
            os.chmod(fpath, stat.S_IRUSR | stat.S_IWUSR | stat.S_IXUSR)
            func(fpath)
        except Exception:
            pass
    shutil.rmtree(path, onerror=handle_error)

def safe_copy(src, dst):
    os.makedirs(dst, exist_ok=True)
    try:
        entries = list(os.scandir(src))
    except PermissionError:
        return
    for entry in entries:
        sp = entry.path
        dp = os.path.join(dst, entry.name)
        real = os.path.realpath(sp)
        if os.path.isdir(real):
            safe_copy(real, dp)
        elif os.path.isfile(real):
            try:
                shutil.copy2(real, dp)
                os.chmod(dp, stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
            except Exception:
                pass

def setup():
    if stamp_valid():
        print(f"[emcache] Cache OK: {STAMP}", flush=True)
        return

    print(f"[emcache] Configurando cache em {EM_CACHE} ...", flush=True)
    if os.path.exists(EM_CACHE):
        force_rmtree(EM_CACHE)

    safe_copy(NIXCACHE, EM_CACHE)

    # Garante que todos os arquivos e dirs sejam graváveis
    for root, dirs, files in os.walk(EM_CACHE):
        for d in dirs:
            try: os.chmod(os.path.join(root, d), 0o755)
            except: pass
        for f in files:
            try: os.chmod(os.path.join(root, f), 0o644)
            except: pass

    # Stamp file para emscripten não tentar recriar o sysroot
    with open(STAMP, "w") as fh:
        fh.write("x")

    print(f"[emcache] Pronto! stamp={os.path.exists(STAMP)}", flush=True)

if __name__ == "__main__":
    setup()
