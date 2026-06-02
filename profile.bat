@echo off

cmake -B build
cmake --build build

if exist build\Debug\tinyrenderer.exe (
    powershell -Command "Measure-Command { .\build\Debug\tinyrenderer.exe }"
) else (
    powershell -Command "Measure-Command { .\build\tinyrenderer.exe }"
)

start framebuffer.tga
