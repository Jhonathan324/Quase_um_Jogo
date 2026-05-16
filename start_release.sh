#!/bin/bash

SDL3_LIB=/nix/store/30wrp9i8g265xw9cbvc1r82illh8dmsn-sdl3-3.2.14-lib
SDL3_IMG=/nix/store/8c5hyvjvip6hp0i34kvfbncy5x8rscj0-sdl3-image-3.2.4-lib
SDL3_TTF=/nix/store/g9s4lqf3vskig9nf0xml65d8ikaj5py1-sdl3-ttf-3.2.2

export LD_LIBRARY_PATH=$SDL3_LIB/lib:$SDL3_IMG/lib:$SDL3_TTF/lib

DISPLAY_NUM=:99
VNC_PORT=5900
WEB_PORT=5000
NOVNC_WEB=/nix/store/n7h60i6lqysmya4clas5vghfsjc6sspa-novnc-1.6.0/share/webapps/novnc
BINARY=bin/Release/game

cleanup() {
    pkill -f "Xvfb $DISPLAY_NUM" 2>/dev/null || true
    pkill -f "x11vnc.*$VNC_PORT"  2>/dev/null || true
    pkill -f "websockify.*$WEB_PORT" 2>/dev/null || true
    pkill -f "$BINARY"            2>/dev/null || true
    exit 0
}
trap cleanup SIGTERM SIGINT EXIT

pkill -f "Xvfb $DISPLAY_NUM"    2>/dev/null || true
pkill -f "x11vnc.*$VNC_PORT"    2>/dev/null || true
pkill -f "websockify.*$WEB_PORT" 2>/dev/null || true
sleep 1

echo "[RELEASE] Compilando..."
make release || { echo "Falha na compilacao!"; exit 1; }

echo "[RELEASE] Iniciando display virtual..."
Xvfb $DISPLAY_NUM -screen 0 1280x720x24 2>/dev/null &
sleep 2

echo "[RELEASE] Iniciando VNC..."
x11vnc -display $DISPLAY_NUM -rfbport $VNC_PORT -forever -nopw -shared -quiet 2>/dev/null &
sleep 1

echo "[RELEASE] Iniciando noVNC na porta $WEB_PORT..."
novnc --listen 0.0.0.0:$WEB_PORT --vnc localhost:$VNC_PORT --web $NOVNC_WEB 2>/dev/null &
sleep 2

echo "[RELEASE] Iniciando jogo (modo RELEASE)..."
export DISPLAY=$DISPLAY_NUM
$BINARY &
GAME_PID=$!

echo "[RELEASE] Jogo rodando! Acesse: porta $WEB_PORT -> /vnc_lite.html?autoconnect=true"
wait $GAME_PID
echo "[RELEASE] Jogo encerrado."
