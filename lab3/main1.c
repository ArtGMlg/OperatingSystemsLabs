#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"

void main()
{
    // CONSOLE_SCREEN_BUFFER_INFO csbi;
    // int columns, rows;
    // GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    // rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    // COORD coords = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));
    // coords.X /= 2;
    // coords.Y /= 2;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    COORD c;
    c.X = columns/2;
    c.Y = rows/2;

    HANDLE fin;
    boolean state = FALSE;
    while (!state)
    {
        fin = CreateFile("text.txt", FILE_READ_DATA, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (GetLastError() == 2)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x04);
            c.X -= 9;
            c.Y -= 1;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
            printf("File doesn't exist!\n");
            c.Y += 1;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x08);
            printf("Press enter to exit");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            getchar();
            return;
        } else if (GetLastError() == 32)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x01);
            c.X -= 14;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
            c.X = columns/2;
            printf("Waiting for file to be freed");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
            Sleep(7000);
            system("CLS");
            continue;
        }
        state = TRUE;
    }
    if (state)
    {
        char buf[50];
        ReadFile(fin, buf, 50, NULL, NULL);
        c.X -= 25;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, 50, NULL, NULL);
        Sleep(7000);
    }
}