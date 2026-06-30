@echo off
cd /d "%~dp0"

if not exist bin\debug mkdir bin\debug

"C:\Program Files\CodeBlocks\MinGW\bin\gcc.exe" ^
-fdiagnostics-color=always ^
-g ^
src/*.c ^
-ISDL3/include ^
-ISDL3_image/include ^
-ISDL3_ttf/include ^
-LSDL3/lib ^
-LSDL3_image/lib ^
-LSDL3_ttf/lib ^
-lSDL3 ^
-lSDL3_image ^
-lSDL3_ttf ^
-o bin\debug\main.exe

echo Build finalizado.