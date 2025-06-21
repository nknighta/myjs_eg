#include "window.h"
#include <vector>
#include <string>

// Helper function to convert std::string to std::wstring
std::wstring s2ws_win(const std::string& s) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
        {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pCreate->lpCreateParams);
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            std::vector<std::string>* paragraphs = reinterpret_cast<std::vector<std::string>*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

            if (paragraphs) {
                RECT clientRect;
                GetClientRect(hWnd, &clientRect);
                
                std::wstring full_text;
                for(const auto& p : *paragraphs) {
                    full_text += s2ws_win(p) + L"\n\n";
                }

                RECT textRect = { 10, 10, clientRect.right - 10, clientRect.bottom - 10 };
                DrawText(hdc, full_text.c_str(), -1, &textRect, DT_WORDBREAK | DT_TOP | DT_LEFT);
            }

            EndPaint(hWnd, &ps);
        }
        break;
        case WM_SIZE:
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND CreateBrowserWindow(HINSTANCE hInstance, int nCmdShow, const std::vector<std::string>& paragraphs) {
    const wchar_t CLASS_NAME[] = L"BrowserWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Simple Browser",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        (LPVOID)&paragraphs
    );

    if (hWnd == NULL) {
        return NULL;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return hWnd;
}
