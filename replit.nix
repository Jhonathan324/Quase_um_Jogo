{pkgs}: {
  deps = [
    pkgs.cmake
    pkgs.emscripten
    pkgs.novnc
    pkgs.x11vnc
    pkgs.xorg.xorgserver
    pkgs.sdl3-ttf
    pkgs.sdl3-image
    pkgs.sdl3
  ];
}
