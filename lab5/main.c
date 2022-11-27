#include <windows.h>
#include <stdio.h>

LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);
LPCSTR CoordsToString(WORD x, WORD y);
int getSize(DWORD lParam);
LPCSTR CreateMessage(WPARAM wParam);

int main()
{
    HINSTANCE hInstance;
    MSG msg;
    WNDCLASS wc;
    HWND hwnd;
    STARTUPINFO si;
    int nCmdShow;

    GetStartupInfo(&si);
    if (si.dwFlags & STARTF_USESHOWWINDOW)
    {
        nCmdShow = si.wShowWindow;
    } else {
        nCmdShow = SW_SHOWDEFAULT;
    }
    hInstance = GetModuleHandle(NULL);

    memset(&wc, 0, sizeof(wc));
    wc.lpszClassName = "MyClass";
    wc.lpfnWndProc = WinProc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hInstance = hInstance;

    if (!RegisterClass(&wc)) return 0;

    hwnd = CreateWindow("MyClass", "Our Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, NULL);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
}

LRESULT WINAPI WinProc(HWND hwnd, UINT tmsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    switch (tmsg)
    {
    case WM_LBUTTONDOWN:
        hdc = GetDC(hwnd);
        // char b[sizeof(lParam)];
        // char c[sizeof(lParam)];
        // itoa(LOWORD(lParam), b, 10);
        // itoa(HIWORD(lParam), c, 10);
        char result[sizeof((int) LOWORD(lParam)) + sizeof((int) HIWORD(lParam))];   // array to hold the result.
        sprintf_s(result, sizeof(result), "%u %u", (int) LOWORD(lParam), (int) HIWORD(lParam));
        TextOut(hdc, LOWORD(lParam), HIWORD(lParam), result, sizeof(result));
        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_CHAR:
        hdc = GetDC(hwnd);
        char resultC[sizeof(wParam) + 8];
        sprintf_s(resultC, sizeof(resultC), "Pressed %c", wParam);
        TextOut(hdc, 100, 50, resultC, sizeof(resultC));
        ReleaseDC(hwnd, hdc);
        return 0;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, tmsg, wParam, lParam);
}
