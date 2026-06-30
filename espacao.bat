@echo off

if not exist bin\debug mkdir bin\debug

"C:\Program Files\CodeBlocks\MinGW\bin\gcc.exe" ^
-fdiagnostics-color=always ^
-E ^
src\jogofuncoes.c ^
-ISDL3/include ^
-ISDL3_image/include ^
-ISDL3_ttf/include ^
-o codigo.c

echo Build finalizado.