#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include <windows.h>

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();
    void clear();
    void drawChar(int x, int y, char c);
    void drawText(int x, int y, const std::string& text);
    void render();
    void swapBuffers();

private:
    int width, height;
    HANDLE hOutput1, hOutput2;
    bool bufferSwapFlag;
    std::vector<std::vector<char>> buffer1, buffer2;
    HANDLE getCurrentBuffer() const;
};

#endif // RENDERER_H