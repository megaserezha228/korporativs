#include "KeyboardInput.h"

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    
    static struct termios original_termios;
    
    static void enableRawMode() {
        struct termios raw;
        tcgetattr(STDIN_FILENO, &raw);
        original_termios = raw;
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }
    
    static void disableRawMode() {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
    }
#endif

char KeyboardInput::getKey() {
#ifdef _WIN32
    int ch = _getch();
    if (ch == 224 || ch == 0) {
        ch = _getch();
        switch(ch) {
            case 72: return 'U';
            case 80: return 'D';
            case 75: return 'L';
            case 77: return 'R';
            default: return 0;
        }
    }
    return (char)ch;
#else
    enableRawMode();
    char c = getchar();
    if (c == 27) {
        char next = getchar();
        if (next == '[') {
            char arrow = getchar();
            disableRawMode();
            switch(arrow) {
                case 'A': return 'U';
                case 'B': return 'D';
                case 'C': return 'R';
                case 'D': return 'L';
                default: return 0;
            }
        }
        disableRawMode();
        return 0;
    }
    disableRawMode();
    return c;
#endif
}

bool KeyboardInput::keyPressed() {
#ifdef _WIN32
    return _kbhit() != 0;
#else
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
#endif
}