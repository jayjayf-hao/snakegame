#include "Renderer.h"
#include <windows.h>
#include <iostream>

Renderer::Renderer(int w, int h) : width(w), height(h), bufferSwapFlag(false) {
    buffer1.assign(height, std::vector<char>(width, ' '));
    buffer2.assign(height, std::vector<char>(width, ' '));

    hOutput1 = CreateConsoleScreenBuffer(
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    hOutput2 = CreateConsoleScreenBuffer(
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );

    CONSOLE_CURSOR_INFO cci = {1, false};
    SetConsoleCursorInfo(hOutput1, &cci);
    SetConsoleCursorInfo(hOutput2, &cci);

    SetConsoleActiveScreenBuffer(hOutput1);
}

Renderer::~Renderer() {
    CloseHandle(hOutput1);
    CloseHandle(hOutput2);
}

void Renderer::clear() {
    std::vector<std::vector<char>>& currentBuffer = bufferSwapFlag ? buffer2 : buffer1;
    for (auto& row : currentBuffer) {
        std::fill(row.begin(), row.end(), ' ');
    }
}

void Renderer::drawChar(int x, int y, char c) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        std::vector<std::vector<char>>& currentBuffer = bufferSwapFlag ? buffer2 : buffer1;
        currentBuffer[y][x] = c;
    }
}

void Renderer::drawText(int x, int y, const std::string& text) {
    for (size_t i = 0; i < text.size(); ++i) {
        drawChar(x + i, y, text[i]);
    }
}

void Renderer::render() {
    std::vector<std::vector<char>>& currentBuffer = bufferSwapFlag ? buffer2 : buffer1;
    HANDLE currentHandle = getCurrentBuffer();

    COORD coord = {0, 0};
    DWORD bytes;
    for (int y = 0; y < height; ++y) {
        WriteConsoleOutputCharacterA(currentHandle, currentBuffer[y].data(), width, coord, &bytes);
        coord.Y++;
    }
}

void Renderer::swapBuffers() {
    bufferSwapFlag = !bufferSwapFlag;
    SetConsoleActiveScreenBuffer(getCurrentBuffer());
}

HANDLE Renderer::getCurrentBuffer() const {
    return bufferSwapFlag ? hOutput2 : hOutput1;
}