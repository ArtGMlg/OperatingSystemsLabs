#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include <ctype.h>

void main()
{
    HANDLE fin = CreateFile("text.txt", FILE_READ_DATA, 0, NULL, OPEN_EXISTING, 0, NULL);
    char buf[30];
    ReadFile(fin, buf, 30, NULL, NULL);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, 30, NULL, NULL);
    DWORD cNumRead;
    DWORD cm;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdIn, &cm);
    SetConsoleMode(hStdIn, ENABLE_INSERT_MODE | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);
    int counter = 0;
    while (TRUE)
    {
        INPUT_RECORD irInBuf[1];
        ReadConsoleInput(hStdIn, irInBuf, 1, &cNumRead);
        for (size_t i = 0; i < cNumRead; i++)
        {
            switch (irInBuf->EventType)
            {
            case KEY_EVENT:
                if (irInBuf->Event.KeyEvent.bKeyDown)
                {
                    printf("\n");
                    putchar(irInBuf->Event.KeyEvent.uChar.AsciiChar);
                }
                break;
            case MOUSE_EVENT:
                if ((GetKeyState(VK_RBUTTON) & 0x80) != 0)
                {
                    return;
                }
                if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
                {
                    char buf[2];
                    DWORD num_read;
                    COORD pos = irInBuf->Event.MouseEvent.dwMousePosition;
                    ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR)buf, 1, pos, (LPDWORD)&num_read);
                    printf("\n%s %d %d", buf, pos.X, pos.Y);
                    CONSOLE_SCREEN_BUFFER_INFO cb;
                    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cb);
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                    char ch;
                    ch = buf[0];
                    putchar(toupper(ch));
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cb.dwCursorPosition);
                }
                break;
            }
        }        
    }
    SetConsoleMode(hStdIn, cm);
}
