#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

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
                    SetConsoleCursorPosition(hStdIn, irInBuf->Event.MouseEvent.dwMousePosition);
                    printf("\n%d %d", irInBuf->Event.MouseEvent.dwMousePosition.X, irInBuf->Event.MouseEvent.dwMousePosition.Y);
                }
                break;
            default:
                printf("\nNo such event handler implemented");
            }
        }        
    }
    
}
