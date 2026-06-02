@echo off

cmake -B build
cmake --build build

if exist build\Debug\tinyrenderer.exe (
    build\Debug\tinyrenderer.exe
) else (
    build\tinyrenderer.exe
)

start framebuffer.tga
