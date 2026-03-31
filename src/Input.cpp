#include "Input.h"
#include <conio.h>
#include <cctype>

char Input::getRawInput() {
    if (_kbhit()) {
        return _getch();
    }
    return 0;  // No input
}