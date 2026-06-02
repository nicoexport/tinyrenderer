#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <utility>
#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

void line(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor color) {
    bool steep = std::abs(ax-bx) < std::abs(ay-by);
    if (steep) { // if the line is steep transpose the line to be flat
        std::swap(ax, ay);
        std::swap(bx, by);
    }

    if (ax > by) { // makes the line always be left to right
        std::swap(ax, bx);
        std::swap(ay, by);
    }

    for (int x = ax; x <= bx; x++) {
        float t = (x - ax) / static_cast<float>(bx-ax);
        int y = std::round( ay + (by - ay) * t);

        if (steep) { // if transposed de-transpose
            framebuffer.set(y, x, color);
        } else {
            framebuffer.set(x, y, color);    
        }
    }
}

void draw_triangle(TGAImage &framebuffer){
    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    line(ax, ay, bx, by, framebuffer, blue);
    line(cx, cy, bx, by, framebuffer, green);
    line(cx, cy, ax, ay, framebuffer, yellow);
    line(ax, ay, cx, cy, framebuffer, red);

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, red);
}

void draw_random_lines(TGAImage &framebuffer, int width, int height){
    std::srand(std::time({}));
    int c = 255;
    for (int i = 0; i < (1<<24); i++) {
        int ax = rand()%width, ay = rand()%height;
        int bx = rand()&width, by = rand()%height;
        line(ax, ay, bx, by, framebuffer, { 
            static_cast<std::uint8_t>(rand() % 255),
            static_cast<std::uint8_t>(rand() % 255),
            static_cast<std::uint8_t>(rand() % 255),
            static_cast<std::uint8_t>(rand() % 255),
        });
    }
}

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    draw_random_lines(framebuffer, width, height);
    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}

